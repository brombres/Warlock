#include "Balefire/Balefire.h"
using namespace BALEFIRE;

int DataReader::read_byte()
{
  if (position == count)
  {
    BALEFIRE_LOG_ERROR( "Internal error: DataReader::read_byte() at end of input." );
    return 0;
  }

  return data[position++];
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

  int result = (b & 0x3f);   //   0..63 (unsigned)
  if (result >= 32) result -= 64;   // -64..63 (signed)

  for (int i=4; --i>=0; )
  {
    // Up to 4 more bytes
    int next = read_byte();
    result = (result << 7) | (next & 0x7f);
    if ( !(next & 0x80) ) break;
  }

  return result;
}

float DataReader::read_real32()
{
  int data = read_int32();
  return *((float*)&data);
}

void DataReader::skip( int n )
{
  position += n;
}
