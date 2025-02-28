#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_resize2.h"
#include "Utilities.h"

unsigned char* Warlock_decode_image(
    unsigned char* bytes, int byte_count,
    int* width, int* height, int* channels
  )
{
  int requested_channels = *channels;
  return (unsigned char*) stbi_load_from_memory(
    bytes, byte_count,
    width, height,
    channels, requested_channels
  );
}


STBIRDEF unsigned char * stbir_resize_uint8_srgb( const unsigned char *input_pixels , int input_w , int input_h, int input_stride_in_bytes,
                                                        unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                                        stbir_pixel_layout pixel_type );
void Warlock_resize_image(
    unsigned char* input_pixels,
    int  input_width,
    int  input_height,
    unsigned char* output_pixels,
    int  output_width,
    int  output_height
  )
{
  stbir_resize_uint8_srgb(
    (unsigned char*) input_pixels, input_width, input_height, 0,
    (unsigned char*) output_pixels, output_width, output_height, 0,
    STBIR_RGBA_PM
  );
}
