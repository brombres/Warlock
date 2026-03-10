//  Main.swift
#include <cstdio>
#include <cstdlib>
using namespace std;

#import <TargetConditionals.h>

#import "RogueInterface.h"

#include <SDL3/SDL.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

// For swizzling
#if TARGET_OS_OSX
  #import <Cocoa/Cocoa.h>
  #import <objc/runtime.h>
  void SwizzleApplicationShouldHandleReopen();
  void InstallMouseMomentumMonitor();
#endif

SDL_AppResult SDL_AppInit( void** appstate, int argc, char* argv[] )
{
  *appstate = NULL;

  RogueInterface_configure( argc, argv );
  RogueInterface_launch();
  RogueWarlockWarlock__configure();

  #if TARGET_OS_OSX
    SwizzleApplicationShouldHandleReopen();
    InstallMouseMomentumMonitor();
  #endif

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate( void *appstate )
{
  RogueWarlockWarlock__tick();
  RogueInterface_check_gc();
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent( void *appstate, SDL_Event *event )
{
  Warlock_sdl_event = event;
  RogueLogical is_running = RogueWarlockWarlock__handle_event();
  return is_running ? SDL_APP_CONTINUE : SDL_APP_SUCCESS;
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit( void *appstate, SDL_AppResult result )
{
  bgfx::frame();
  bgfx::frame();

  // Cleanup
  bgfx::shutdown();

  SDL_Quit();
  exit( (int)result );
}

#if TARGET_OS_OSX
BOOL Warlock_applicationShouldHandleReopen(id self, SEL _cmd, NSApplication *sender, BOOL hasVisibleWindows)
{
  RogueWarlockWarlock__handle_dock_icon_click();
  return YES;
}

void SwizzleApplicationShouldHandleReopen()
{
  id delegate = [NSApp delegate];
  Class _class = [delegate class];

  SEL selector = @selector(applicationShouldHandleReopen:hasVisibleWindows:);
  Method originalMethod = class_getInstanceMethod( _class, selector );

  if (!originalMethod)
  {
    // If not implemented yet, add it
    BOOL added = class_addMethod( _class, selector, (IMP)Warlock_applicationShouldHandleReopen, "c@:@@" );
    if (added)
    {
      NSLog(@"Successfully added applicationShouldHandleReopen:hasVisibleWindows:");
    }
    else
    {
      NSLog(@"Failed to add applicationShouldHandleReopen:hasVisibleWindows:");
    }
  }
  else
  {
    // Otherwise, replace (swizzle) the existing implementation
    method_setImplementation( originalMethod, (IMP)Warlock_applicationShouldHandleReopen );
    NSLog( @"Successfully swizzled applicationShouldHandleReopen:hasVisibleWindows:" );
  }
}

void InstallMouseMomentumMonitor()
{
  [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskScrollWheel
      handler:^NSEvent * _Nullable(NSEvent *event)
  {
    if ([event hasPreciseScrollingDeltas])
    {
      RogueWarlockWarlock__handle_scroll_event_precision_info__RogueGeometryXY_RogueLogical_RogueLogical(
        (RogueGeometryXY){ [event deltaX], [event deltaY] },
        (RogueLogical)([event phase] != NSEventPhaseEnded && [event momentumPhase] != NSEventPhaseEnded),
        (RogueLogical)([event momentumPhase] != NSEventPhaseNone)
      );
    }

    return event;
  }];
}
#endif // TARGET_OS_OSX
