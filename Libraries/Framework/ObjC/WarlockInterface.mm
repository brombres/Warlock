#if false
#include <cstdio>

#import "RogueInterface.h"
#import "WarlockInterface.h"

#include "Balefire/Balefire.h"
using namespace BALEFIRE;

NSString* rogue_string_to_ns_string( RogueString* st )
{
  if ( !st ) return nil;
  return [NSString stringWithUTF8String:(const char*)st->data->as_utf8];
}

RogueString* ns_string_to_rogue_string( NSString* st )
{
  if ( !st ) return 0;

  return RogueString_create( [st UTF8String] );
}

extern "C" void WarlockInterface_create_window( int id, RogueString* title )
{
  Balefire::instance->create_window( 1, RogueString_to_c_string(title) );
}

extern "C" RogueString* WarlockInterface_find_asset( RogueString* filepath )
{
  NSString* ns_name = rogue_string_to_ns_string( filepath );
  NSString* ns_filepath = [[NSBundle mainBundle] pathForResource:ns_name ofType:nil];
  if (ns_filepath == nil) return 0;
  return ns_string_to_rogue_string( ns_filepath );
}
#endif
