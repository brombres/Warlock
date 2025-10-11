#import <UIKit/UIKit.h>
#import <objc/runtime.h>

@implementation NSObject (SDLStatusBarSwizzle)

+ (void)load {
    // Run once when the app loads
    Class sdlVC = NSClassFromString(@"SDL_uikitviewcontroller");
    if (!sdlVC) {
        return; // SDL not loaded yet
    }

    SEL originalSel = @selector(prefersStatusBarHidden);
    Method originalMethod = class_getInstanceMethod(sdlVC, originalSel);

    // Our replacement block
    BOOL (^replacementBlock)(id) = ^BOOL(id _self) {
        return YES; // always hide
    };

    IMP replacementIMP = imp_implementationWithBlock(replacementBlock);

    // Replace implementation
    method_setImplementation(originalMethod, replacementIMP);
}

@end
