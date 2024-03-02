#include "./String.h"
#include <cstring>
using namespace Balefire;
using namespace std;

StringData::StringData()
{
  data.add( 0 );
}

String::String()
{
}

String::String( const char* value )
{
  *this = new StringData();
}

String::operator const char*()
{
}

