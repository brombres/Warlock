#if BGFX_SHADER_LANGUAGE_METAL
#else
  #define bgfxTextureSize textureSize
  #define lerp(a,b,t) mix(a,b,t)
#endif
