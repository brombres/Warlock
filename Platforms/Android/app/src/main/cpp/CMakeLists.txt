cmake_minimum_required(VERSION 3.22.1)
project(warlock-native LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Let CMake find SDL3 from the prefab in the AAR
find_package(SDL3 REQUIRED CONFIG)

#---------------------------------------------------------------------
# libtess2
#---------------------------------------------------------------------
add_subdirectory( Tess2 )

#---------------------------------------------------------------------
# miniaudio
#---------------------------------------------------------------------
add_subdirectory( MiniAudio )

#---------------------------------------------------------------------
# spine
#---------------------------------------------------------------------
add_subdirectory( Spine )

#---------------------------------------------------------------------
# Utilities
#---------------------------------------------------------------------
add_subdirectory( Utilities )


#---------------------------------------------------------------------
# Warlock
#---------------------------------------------------------------------
add_library(
  warlock SHARED
  Warlock.cpp
  Rogue/RogueProgram-Android.cpp
)

target_compile_options( warlock PRIVATE -Wno-nullability-completeness )

# Prebuilt .a files for this ABI
set( ANDROID_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI}" )

# Paths relative to this CMakeLists
set(BGFX_ROOT "${CMAKE_SOURCE_DIR}/../../../../../../Libraries/bgfx")
set(BX_ROOT   "${CMAKE_SOURCE_DIR}/../../../../../../Libraries/bx")
set(BIMG_ROOT "${CMAKE_SOURCE_DIR}/../../../../../../Libraries/bimg")

add_library(bgfx STATIC IMPORTED)
set_target_properties(bgfx PROPERTIES
    IMPORTED_LOCATION "${ANDROID_LIB_DIR}/libbgfx.a"
)

add_library(bx STATIC IMPORTED)
set_target_properties(bx PROPERTIES
    IMPORTED_LOCATION "${ANDROID_LIB_DIR}/libbx.a"
)

add_library(bimg STATIC IMPORTED)
set_target_properties(bimg PROPERTIES
    IMPORTED_LOCATION "${ANDROID_LIB_DIR}/libbimg.a"
)

add_library(bimg_decode STATIC IMPORTED)
set_target_properties(bimg_decode PROPERTIES
    IMPORTED_LOCATION "${ANDROID_LIB_DIR}/libbimg_decode.a"
)

target_include_directories( warlock
    PRIVATE
        "${BGFX_ROOT}/include"
        "${BX_ROOT}/include"
        "${BIMG_ROOT}/include"
)

# System libs
find_library(ANDROID_LOG_LIB log)
find_library(ANDROID_LIB android)
find_library(GLES_LIB GLESv2)      # or GLESv3 depending on NDK; GLESv2 is fine for bgfx
find_library(EGL_LIB EGL)
find_library(VULKAN_LIB vulkan)

# link everything
target_link_libraries(
  warlock
    PRIVATE
      bgfx
      bimg
      bimg_decode
      bx
      SDL3::SDL3
      MiniAudio
      Spine
      Tess2
      Utilities
      ${GLES_LIB}
      ${EGL_LIB}
      ${VULKAN_LIB}
      ${ANDROID_LIB}
      ${ANDROID_LOG_LIB}
)

target_link_options(warlock PRIVATE "-Wl,-z,max-page-size=16384")
