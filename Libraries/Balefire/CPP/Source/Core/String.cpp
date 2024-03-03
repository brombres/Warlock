#include "Balefire/Core/String.h"
#include <cstring>
using namespace BALEFIRE;
using namespace std;

//==============================================================================
// StringData
//==============================================================================
StringData::StringData()
{
}

StringData::StringData( const char* utf8 )
{
  Int64 byte_count = strlen( utf8 );
  if ((count=utf8_character_count(utf8,byte_count)) == -1)
  {
    // Invalid UTF-8
    count = 0;
    is_ascii = true;
  }
  else
  {
    this->utf8.reserve( byte_count+1 );
    memcpy( this->utf8.data, utf8, byte_count );
    this->utf8.count = byte_count;
    this->utf8[byte_count] = 0;

    is_ascii = (count == byte_count);
  }
}

Int64 StringData::utf8_character_count( const char* utf8, Int64 byte_count )
{
  // Returns -1 if 'utf8' is not a valid UTF-8 string.
  if (byte_count == -1) byte_count = (Int64) strlen(utf8);

  Int64 character_count = 0;
  Int64 i;
  for (i=0; i<byte_count; ++character_count)
  {
    int b = utf8[ i ];
    if (b & 0x80)
    {
      if ( !(b & 0x40) ) { return -1;}

      if (b & 0x20)
      {
        if (b & 0x10)
        {
          // %11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
          if (b & 0x08) { return -1;}
          if (i + 4 > byte_count || ((utf8[i+1] & 0xC0) != 0x80) || ((utf8[i+2] & 0xC0) != 0x80)
              || ((utf8[i+3] & 0xC0) != 0x80)) { return -1;}
          i += 4;
        }
        else
        {
          // %1110xxxx 10xxxxxx 10xxxxxx
          if (i + 3 > byte_count || ((utf8[i+1] & 0xC0) != 0x80) || ((utf8[i+2] & 0xC0) != 0x80))
          {
            return -1;
          }
          i += 3;
        }
      }
      else
      {
        // %110x xxxx 10xx xxxx
        if (i + 2 > byte_count || ((utf8[i+1] & 0xC0) != 0x80)) { return -1; }
        i += 2;
      }
    }
    else
    {
      ++i;
    }
  }

  return character_count;
}

//==============================================================================
// String
//==============================================================================
String::String() : Ref<StringData>()
{
}

String::String( String const &existing ) : Ref<StringData>(existing)
{
  external_string = existing.external_string;
  external_byte_count = existing.external_byte_count;
  external_character_count = existing.external_character_count;
}

String::String( const char* utf8 ) : Ref<StringData>()
{
  external_string = utf8;
}

String::String( StringData* data ) : Ref<StringData>(data)
{
}

Int64 String::count()
{
  if (external_string)
  {
    if (external_character_count == -1)
    {
      external_byte_count = strlen( external_string );
      external_character_count = StringData::utf8_character_count( external_string, external_byte_count );
      if (external_character_count == -1) external_character_count = 0;
    }
    return external_character_count;
  }

  if (data) return data->count;
  return 0;
}

Int64 String::hashcode() {
  if (external_string)
  {
    if (external_byte_count == -1) count();
    return compute_hash_code( external_string, external_byte_count );
  }

  if ( !data ) return 0;

  Int64 hash;
  if ((hash=data->hashcode)) return hash;

  hash = compute_hash_code( data->utf8.data, data->utf8.count );
  data->hashcode = hash;
  return hash;
}

String& String::operator=( const char* utf8 )
{
  external_string = utf8;
  if (data)
  {
    data->release();
    data = nullptr;
  }

  return *this;
}

String& String::operator=( String& other )
{
  Ref<StringData>::operator=( other );
  external_string = other.external_string;
  external_byte_count = other.external_byte_count;
  external_character_count = other.external_character_count;
  return *this;
}

String& String::operator=( StringData* new_data )
{
  if (external_string)
  {
    external_string = nullptr;
    external_byte_count = external_character_count = -1;
  }
  Ref<StringData>::operator=( new_data );
  return *this;
}

bool String::operator==( const char* utf8 )
{
  if (external_string)
  {
    if (external_byte_count == -1) count();
    Int64 utf8_byte_count = (Int64)strlen(utf8);
    if (external_byte_count != utf8_byte_count) return false;
    return 0 == strcmp( external_string, utf8 );
  }

  if ( !data ) return !utf8[0];

  Int64 byte_count = (Int64)strlen( utf8 );
  if (data->utf8.count != byte_count) return false;

  return 0 == memcmp( data->utf8.data, utf8, byte_count );
}

bool String::operator==( String& other )
{
  if (external_string)
  {
    if (other.external_string)
    {
      if (external_byte_count == -1) count();
      if (other.external_byte_count == -1) other.count();
      if (external_byte_count != other.external_byte_count) return false;
      return 0 == strcmp( external_string, other.external_string );
    }
    else
    {
      return other == external_string;  // invoke other.operator==(const char*)
    }
  }
  else if (other.external_string)
  {
    return other == *this;  // invoke other.operator==(String&)
  }

  if ( !data ) return !other.data;
  if ( !other.data ) return false;

  if (data->count != other.data->count) return false;
  if (hashcode() != other.hashcode()) return false;

  return 0 == memcmp( data->utf8.data, other.data->utf8.data, data->utf8.count );
}

Int64 String::compute_hash_code( const char* utf8, Int64 byte_count )
{
  Int64 hash = 0;
  while (--byte_count >= 0)
  {
    hash = ((hash<<3) - hash) + (unsigned char)*(++utf8);
  }
  if (hash) return hash;
  else      return 1;
}

String::operator const char*()
{
  if (external_string) return external_string;
  if ( !data ) return "";
  return data->utf8.data;
}
