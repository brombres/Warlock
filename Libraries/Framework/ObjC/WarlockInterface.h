#if false
#pragma once

#include "RogueProgram.h"

#ifdef __cplusplus
extern "C" {
#endif

void WarlockInterface_create_window( int id, RogueString* title );

RogueString* WarlockInterface_find_asset( RogueString* filepath );

//void WarlockInterface_decode_image(

    /*
RogueGraphics__Bitmap* Plasmacore_decode_image( RogueByte* bytes, RogueInt32 count )
{
  NSData* data = [NSData dataWithBytesNoCopy:bytes length:count freeWhenDone:NO];
#if defined(ROGUE_PLATFORM_IOS)
  CGImageRef bitmap_image = [UIImage imageWithData:data].CGImage;
#else
  CGImageRef bitmap_image = [[[NSImage alloc] initWithData:data] CGImageForProposedRect:NULL context:NULL hints:NULL];
#endif

  if(bitmap_image)
  {
    // Get the width and height of the image
    RogueInt32 width = (RogueInt32)CGImageGetWidth(bitmap_image);
    RogueInt32 height = (RogueInt32)CGImageGetHeight(bitmap_image);
    RogueClassBitmap__Bitmap* bitmap = RogueBitmap__Bitmap__create__Int32_Int32( width, height );

    // Uses the bitmap creation function provided by the Core Graphics framework.
    CGContextRef gc = CGBitmapContextCreate((GLubyte*)bitmap->pixels->data->as_int32s, width, height, 8, width * 4,
                                            CGColorSpaceCreateDeviceRGB(), kCGImageAlphaPremultipliedLast );
    CGContextDrawImage(gc, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height), bitmap_image);
    CGContextRelease(gc);
    return bitmap;
  }
  else
  {
    return NULL;
  }

}
*/

#ifdef __cplusplus
} // extern "C"
#endif
#endif
