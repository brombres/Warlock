#ifndef BALEFIRE_STRING_H
#define BALEFIRE_STRING_H

#include "Types.h"
#include "BulkData.h"

namespace Balefire
{
  struct StringData : RefCounted
  {
    int character_count = 0;
    BulkData<Byte> data;

    StringData();
  };

  struct String : SmartPointer<StringData>
  {
    String() {}
    String( const char* value );
    operator const char*();
  };
};

#endif // BALEFIRE_STRING_H
