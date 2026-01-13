//
//  SDLDeepLinkEvent.m
//  Warlock
//
//  Created by Brom Bresenham on 10/29/25.
//
#import <objc/runtime.h>
#import <Foundation/Foundation.h>

#include <SDL3/SDL.h>

// OPTIONAL: define WARLOCK_URL_SCHEME in Xcode > Build Settings > Preprocessor Directives
//
 // Example: WARLOCK_URL_SCHEME='@"tombsweeper"'

#define WARLOCK_DEEP_LINK_EVENT 55136

static void Warlock_HandleDeepLink(NSURL *url)
{
  if (!url) return;
  NSLog(@"[DeepLink] Received URL: %@", url.absoluteString);

  #if defined (WARLOCK_URL_SCHEME)
    if ( ![[url scheme] isEqualToString:WARLOCK_URL_SCHEME] ) return;
  #endif

  const char *cURL = strdup(url.absoluteString.UTF8String);
  SDL_Event e;
  SDL_zero(e);
  e.type = SDL_EVENT_USER;
  e.user.code = WARLOCK_DEEP_LINK_EVENT;
  e.user.data1 = (void *)cURL;
  e.user.data2 = NULL;
  SDL_PushEvent(&e);
}

#if TARGET_OS_IOS
// ----------------------------------------------------------
// iOS
// ----------------------------------------------------------
#import <UIKit/UIKit.h>

static BOOL (*orig_openURL)(id, SEL, UIApplication *, NSURL *, NSDictionary *);
static void (*orig_sceneOpenURL)(id, SEL, UIScene *, NSSet<UIOpenURLContext *> *);

static BOOL swizzled_openURL(id self, SEL _cmd, UIApplication *app, NSURL *url, NSDictionary *options)
{
  BOOL result = NO;
  if (orig_openURL) result = orig_openURL(self, _cmd, app, url, options);
  Warlock_HandleDeepLink(url);
  return result;
}

static void swizzled_sceneOpenURL(id self, SEL _cmd, UIScene *scene, NSSet<UIOpenURLContext *> *contexts)
{
  if (orig_sceneOpenURL) orig_sceneOpenURL(self, _cmd, scene, contexts);
  for (UIOpenURLContext *ctx in contexts) Warlock_HandleDeepLink(ctx.URL);
}

__attribute__((constructor))
static void InitDeepLinkInterceptor_iOS(void)
{
    Class delegateClass = objc_getClass("SDLUIKitDelegate");
    if (!delegateClass) {
      NSLog(@"[DeepLink] ⚠️ Could not find SDLUIKitDelegate — check SDL3 version");
      return;
    }

    SEL sel = @selector(application:openURL:options:);
    Method m = class_getInstanceMethod(delegateClass, sel);
    if (m) {
      orig_openURL = (void *)method_getImplementation(m);
      method_setImplementation(m, (IMP)swizzled_openURL);
      NSLog(@"[DeepLink] ✅ Swizzled SDLUIKitDelegate openURL");
    } else {
      NSLog(@"[DeepLink] ⚠️ SDLUIKitDelegate has no application:openURL:options: method");
    }
}

#elif TARGET_OS_OSX
// ----------------------------------------------------------
// macOS
// ----------------------------------------------------------
#import <AppKit/AppKit.h>

@interface WarlockDeepLinkDelegate : NSObject <NSApplicationDelegate>
@end

@implementation WarlockDeepLinkDelegate
- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls {
  for (NSURL *url in urls) {
    Warlock_HandleDeepLink( url );
  }
}
@end

__attribute__((constructor))
static void InstallWarlockDeepLinkDelegate(void)
{
  NSApplication *app = [NSApplication sharedApplication];
  WarlockDeepLinkDelegate *delegate = [[WarlockDeepLinkDelegate alloc] init];
  [app setDelegate:delegate];
  NSLog(@"[DeepLink] Installed WarlockDeepLinkDelegate");
}
#endif
