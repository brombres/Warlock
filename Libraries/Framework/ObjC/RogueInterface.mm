#import "RogueInterface.h"

#include <cstdio>
#include <cstring>
using namespace std;

static int    RogueInterface_argc = 0;
static char** RogueInterface_argv = {0};

void RogueInterface_configure( int argc, char* argv[] )
{
  RogueInterface_argc = argc;
  RogueInterface_argv = argv;
}

void RogueInterface_launch()
{
  Rogue_configure( RogueInterface_argc, RogueInterface_argv );
  Rogue_launch();
}

void RogueInterface_check_gc()
{
  Rogue_check_gc();
}
