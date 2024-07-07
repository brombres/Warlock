#include "Balefire/Balefire.h"
using namespace BALEFIRE;
using namespace std;

int DataReader::read_byte()
{
  if (position == count)
  {
    BALEFIRE_LOG_ERROR( "Internal error: DataReader::read_byte() at end of input." );
    return 0;
  }

  return data[position++];
}

int DataReader::read_bytes( unsigned char** data_pointer )
{
  int byte_count = read_int32x();
  *data_pointer = data + position;
  position += byte_count;
  return byte_count;
}

int DataReader::read_int32s( int** data_pointer )
{
  int int32_count = read_int32x(); // includes 1 extra for BOM

  auto alignment_flag_ptr = data + position++;
  position += 4;  // next 4 bytes are the alignment padding buffer

  int aligned_data_start = position;
  while (aligned_data_start & 3) --aligned_data_start;
  if (position != aligned_data_start && !*alignment_flag_ptr)
  {
    memmove( data+aligned_data_start, data+position, int32_count*4 );
    *alignment_flag_ptr = (unsigned char)1;
  }
  position += int32_count * 4;

  int* int32s = (int*)(data + aligned_data_start);

  int byte_order_marker = *int32s;
  if (byte_order_marker != 0x11223344)
  {
    // Rewrite the data, reversing the byte order. BOM gets reversed as well.
    int* cur = int32s - 1;
    int n = int32_count;
    while (--n >= 0)
    {
      // aabbccdd ->   dd000000
      //             | 00cc0000
      //             | 0000bb00
      //             | 000000aa
      int x = *(++cur);
      *cur = (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | ((x >> 24) & 0xff);
    }
  }

  if (data_pointer) *data_pointer = int32s + 1;
  return int32_count - 1;
}

int DataReader::read_int32()
{
  if (position+4 > count)
  {
    BALEFIRE_LOG_ERROR( "Internal error: DataReader::read_int32() at end of input." );
    return 0;
  }

  int result = data[position] << 24;
  result |= data[position+1] << 16;
  result |= data[position+2] << 8;
  result |= data[position+3];
  position += 4;

  return result;
}

int DataReader::read_int32x()
{
  // Reads a variable-length encoded value that is stored in 1..5 bytes.
  // Encoded values are treated as signed.
  //
  // - If the first two bits are not "10" then the first byte is cast to
  //   a signed integer value and returned. This allows for the range
  //   -64..127 using the following bit patterns:
  //
  //     0xxxxxxx    0 .. 127
  //     11xxxxxx  -64 ..  -1
  //
  // - If the first two bits are "10" then the data has been encoded
  //   in the next 6 bits as well as any number of following bytes,
  //   using 7 data bits per byte with an MSBit of 0 representing a halt
  //   or 1 a continuation. The next bit after the leading 10 is
  //   treated as negative magnitude.
  //
  //     10xxxxxx 0yyyyyyy            (13-bit number xxxxxxyyyyyyy)
  //     10xxxxxx 1yyyyyyy 0zzzzzzz   (20-bit number xxxxxxyyyyyyyzzzzzzz)
  //     etc.
  int b = read_byte();
  if ((b & 0xc0) != 0x80)
  {
    if (b <= 127) return b;
    return (b - 256);
  }

  int result = (b & 0x3f);        //   0..63 (unsigned)
  if (result >= 32) result -= 64; // -64..-1 (signed)

  for (int i=7; --i>=0; )
  {
    // Up to 7 more bytes
    int next = read_byte();
    result = (result << 7) | (next & 0x7f);
    if ( !(next & 0x80) ) break;
  }

  return result;
}

bool DataReader::read_logical()
{
  return read_int32x() != 0;
}

float DataReader::read_real32()
{
  int data = read_int32();
  return *((float*)&data);
}

string DataReader::read_string()
{
  int count = read_int32x();
  string result = "";
  result.reserve( count );
  while (--count >= 0)
  {
    int unicode = read_int32x();
    if (unicode <= 0x7F)
    {
      // 1-byte sequence: 0xxxxxxx
      result += (char)(unicode);
    }
    else if (unicode <= 0x7FF)
    {
      // 2-byte sequence: 110xxxxx 10xxxxxx
      result += (char)((unicode >> 6) | 0xC0);
      result += (char)((unicode & 0x3F) | 0x80);
    }
    else if (unicode <= 0xFFFF)
    {
      // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
      result += (char)((unicode >> 12) | 0xE0);
      result += (char)(((unicode >> 6) & 0x3F) | 0x80);
      result += (char)((unicode & 0x3F) | 0x80);
    }
    else if (unicode <= 0x10FFFF)
    {
      // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
      result += (char)((unicode >> 18) | 0xF0);
      result += (char)(((unicode >> 12) & 0x3F) | 0x80);
      result += (char)(((unicode >> 6) & 0x3F) | 0x80);
      result += (char)((unicode & 0x3F) | 0x80);
    }
  }
  return result;
}

void DataReader::seek( int pos )
{
  position = pos;
}

void DataReader::skip( int n )
{
  position += n;
}
