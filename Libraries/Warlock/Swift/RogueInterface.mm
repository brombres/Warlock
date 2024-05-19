#include "RogueInterface.h"

//#import <AVFoundation/AVAudioPlayer.h>


#ifdef PLASMACORE_PLATFORM_IOS
//  #import <UIKit/UIKit.h>
//  #import <GLKit/GLKit.h>
  //#import "Project-iOS-Swift.h"
#else
  //#import "Warlock-macOS-Swift.h"
#endif

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
