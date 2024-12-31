#ifndef ROGUE_INTERFACE_H
#define ROGUE_INTERFACE_H

#if defined(__APPLE__)
  #define WARLOCK_PLATFORM_APPLE 1

  #if defined(TARGET_IPHONE_SIMULATOR)
    #if TARGET_IPHONE_SIMULATOR
      #define WARLOCK_PLATFORM_IOS 1
      #define WARLOCK_PLATFORM_IOS_SIMULATOR 1
    #endif
  #endif

  #if !defined(WARLOCK_PLATFORM_IOS)
    #if defined(TARGET_OS_IPHONE)
      #if TARGET_OS_IPHONE
        #define WARLOCK_PLATFORM_IOS 1
      #endif
    #endif
  #endif

  #if !defined(WARLOCK_PLATFORM_IOS)
    #define WARLOCK_PLATFORM_MACOS 1
  #endif
#endif

#ifdef WARLOCK_PLATFORM_MACOS
  #import <Cocoa/Cocoa.h>
#else
  //#import <Foundation/Foundation.h>
#endif

#include "RogueProgram.h"

#ifdef __cplusplus
extern "C" {
#endif

void RogueInterface_configure( int argc, char* argv[] );
void RogueInterface_launch();

//void WarlockInterface_create_window( int id, RogueString* title );

//NSData* RogueInterface_post_messages( const unsigned char* data, int count );
//NSData* RogueInterface_send_message( const unsigned char* data, int count );
//void    RogueInterface_set_arg_count( int count );
//void    RogueInterface_set_arg_value( int index, const char* value );

#import "WarlockInterface.h"

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ROGUE_INTERFACE_H
