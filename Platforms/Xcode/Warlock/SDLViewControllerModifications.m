#import <objc/runtime.h>
#import <UIKit/UIKit.h>

@implementation UIViewController (SDLViewControllerModifications)

#pragma mark - Replacement Methods

// Disable system gesture deferral (edge lag)
- (UIRectEdge)Warlock_preferredScreenEdgesDeferringSystemGestures {
    return UIRectEdgeNone;
}

// Auto-hide the home indicator
- (BOOL)Warlock_prefersHomeIndicatorAutoHidden {
    return YES;
}

// Hide the status bar
- (BOOL)Warlock_prefersStatusBarHidden {
    return YES;
}

#pragma mark - Swizzling Logic

+ (void)load {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        Class targetClass = NSClassFromString(@"SDL_uikitviewcontroller");
        if (!targetClass) return;

        struct {
            SEL original;
            SEL swizzled;
        } methods[] = {
            { @selector(preferredScreenEdgesDeferringSystemGestures), @selector(Warlock_preferredScreenEdgesDeferringSystemGestures) },
            { @selector(prefersHomeIndicatorAutoHidden), @selector(Warlock_prefersHomeIndicatorAutoHidden) },
            { @selector(prefersStatusBarHidden), @selector(Warlock_prefersStatusBarHidden) }
        };

        for (int i = 0; i < sizeof(methods) / sizeof(methods[0]); i++) {
            SEL origSel = methods[i].original;
            SEL swizSel = methods[i].swizzled;

            Method swizMethod = class_getInstanceMethod(self, swizSel);
            Method origMethod = class_getInstanceMethod(targetClass, origSel);

            if (origMethod && swizMethod) {
                method_exchangeImplementations(origMethod, swizMethod);
            } else {
                // SDL may not implement all of these; add them if missing
                const char *types = method_getTypeEncoding(swizMethod);
                class_addMethod(targetClass, origSel, (IMP)[self instanceMethodForSelector:swizSel], types);
            }
        }

        dispatch_after( dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC)), dispatch_get_main_queue(),
          ^{
            UIWindow *keyWindow = [UIApplication sharedApplication].keyWindow;
            UIViewController *vc = keyWindow.rootViewController;
            if ([vc respondsToSelector:@selector(setNeedsUpdateOfScreenEdgesDeferringSystemGestures)]) {
                [vc setNeedsUpdateOfScreenEdgesDeferringSystemGestures];
            }
          });
    });
}

@end
