set( SPINE_ROOT "${CMAKE_SOURCE_DIR}/../../../../../../Libraries/spine-runtimes/spine-cpp" )

# spine-c is now a thin wrapper over spine-cpp, so build the C++ runtime directly.
# Glob every translation unit so the source list tracks the installed spine-cpp
# version instead of being pinned to a hand-maintained file list.
file( GLOB SPINE_SOURCES CONFIGURE_DEPENDS "${SPINE_ROOT}/src/spine/*.cpp" )

add_library(
  Spine STATIC
  ${SPINE_SOURCES}
)

target_include_directories( Spine PUBLIC "${SPINE_ROOT}/include" )

# Force release flags for this target regardless of parent build type
target_compile_options( Spine PRIVATE -O3 -DNDEBUG )
target_link_options( Spine PRIVATE -O3 )
