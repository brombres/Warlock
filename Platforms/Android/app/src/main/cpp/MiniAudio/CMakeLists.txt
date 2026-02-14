add_library( MiniAudio STATIC MiniAudio.cpp )

set( MINIAUDIO_ROOT "${CMAKE_SOURCE_DIR}/../../../../../../Libraries/miniaudio" )

target_include_directories( MiniAudio PUBLIC ${MINIAUDIO_ROOT} )

# Force release flags for this target regardless of parent build type
target_compile_options( MiniAudio PRIVATE -O3 -DNDEBUG )
target_link_options( MiniAudio PRIVATE -O3 )
