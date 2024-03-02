#ifndef BALEFIRE_STRING_H
#define BALEFIRE_STRING_H

#include "Balefire/Core/Types.h"
#include "Balefire/Core/BulkData.h"
#include "Balefire/Core/Ref.h"
#include "Balefire/Core/RefCounted.h"

namespace Balefire
{
  struct StringData : RefCounted
  {
    Int64 count = 0;
    Int64 byte_cursor = 0;
    Int64 character_cursor = 0;
    Int64 hashcode = 0;
    bool  is_ascii  = false;
    BulkData<char> utf8;

    StringData();
    StringData( const char* utf8 );

    static Int64 utf8_character_count( const char* utf8, Int64 byte_count );
  };

  struct String : Ref<StringData>
  {
    String();
    String( String const &existing );
    String( const char* utf8 );
    String( StringData* data );

    Int64 count();
    Int64 hashcode();

    String& operator=( const char* utf8 );
    String& operator=( String& other );
    String& operator=( StringData* new_data );
    bool operator==( const char* utf8 );
    bool operator==( String& other );
    operator char*();
    operator const char*();

    static Int64 compute_hash_code( const char* utf8, Int64 byte_count );
  };
};

#endif // BALEFIRE_STRING_H
