set( TESS2_ROOT "${CMAKE_SOURCE_DIR}/../../../../../../Libraries/libtess2" )

add_library(
  Tess2 STATIC
  "${TESS2_ROOT}/Source/bucketalloc.c"
  "${TESS2_ROOT}/Source/dict.c"
  "${TESS2_ROOT}/Source/geom.c"
  "${TESS2_ROOT}/Source/mesh.c"
  "${TESS2_ROOT}/Source/priorityq.c"
  "${TESS2_ROOT}/Source/sweep.c"
  "${TESS2_ROOT}/Source/tess.c"
)

target_include_directories( Tess2 PUBLIC "${TESS2_ROOT}/Include" )

target_compile_definitions( Tess2 PRIVATE isnanf=isnan )

# Force release flags for this target regardless of parent build type
target_compile_options( Tess2 PRIVATE -O3 -DNDEBUG )
target_link_options( Tess2 PRIVATE -O3 )
