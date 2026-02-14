set( UTILITIES_ROOT "${CMAKE_SOURCE_DIR}/../../../../../../Libraries/Warlock/Libraries/Framework/C" )

add_library(
  Utilities STATIC
  "${UTILITIES_ROOT}/Utilities.c"
)

target_include_directories( Utilities PUBLIC "${UTILITIES_ROOT}" )

# Force release flags for this target regardless of parent build type
target_compile_options( Utilities PRIVATE -O3 -DNDEBUG )
target_link_options( Utilities PRIVATE -O3 )
