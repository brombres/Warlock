// Utilities.h

#pragma once

#if defined(__cplusplus)
  #define EXTERN_C extern "C"
#else
  #define EXTERN_C
#endif

EXTERN_C unsigned char* Warlock_decode_image(
  unsigned char* bytes, int byte_count,
  int* width, int* height,
  int* channels
);

EXTERN_C void Warlock_resize_image(
  unsigned char* input_pixels,
  int  input_width,
  int  input_height,
  unsigned char* output_pixels,
  int  output_width,
  int  output_height
);

