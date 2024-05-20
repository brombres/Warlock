#include <cstdio>

#include "NativeInterface.h"

#include "Balefire/Balefire.h"
using namespace BALEFIRE;

void NativeInterface_create_window( int id, RogueString* title )
{
  Balefire::instance->create_window( 1, RogueString_to_c_string(title) );
}
