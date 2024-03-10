#include <cstdio>

#include "Balefire/Core/BulkData.h"
#include "Balefire/Core/String.h"
using namespace BALEFIRE;

void println( BulkData<int> &data )
{
  printf( "[" );
  for (int i=0; i<data.count; ++i)
  {
    if (i > 0) printf( "," );
    printf( "%d", data[i] );
  }
  printf( "] (capacity %lld)\n", data.capacity );
}

int main()
{
  printf( "Hello C++\n" );

  //char data[4] = {'A','B','C',0};
  String a = new StringData("ABC");
  String b = new StringData("ABC");
  printf("%d\n",a == b);
  printf("%d\n",!!a.data);
  printf("%d\n",!!b.data);

  return 0;
}
