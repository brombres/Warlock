set( SPINE_ROOT "${CMAKE_SOURCE_DIR}/../../../../../../Libraries/spine-runtimes/spine-c/spine-c" )

add_library(
  Spine STATIC
  "${SPINE_ROOT}/src/spine/Animation.c"
  "${SPINE_ROOT}/src/spine/AnimationState.c"
  "${SPINE_ROOT}/src/spine/AnimationStateData.c"
  "${SPINE_ROOT}/src/spine/Array.c"
  "${SPINE_ROOT}/src/spine/Atlas.c"
  "${SPINE_ROOT}/src/spine/AtlasAttachmentLoader.c"
  "${SPINE_ROOT}/src/spine/Attachment.c"
  "${SPINE_ROOT}/src/spine/AttachmentLoader.c"
  "${SPINE_ROOT}/src/spine/Bone.c"
  "${SPINE_ROOT}/src/spine/BoneData.c"
  "${SPINE_ROOT}/src/spine/BoundingBoxAttachment.c"
  "${SPINE_ROOT}/src/spine/ClippingAttachment.c"
  "${SPINE_ROOT}/src/spine/Color.c"
  "${SPINE_ROOT}/src/spine/Debug.c"
  "${SPINE_ROOT}/src/spine/Event.c"
  "${SPINE_ROOT}/src/spine/EventData.c"
  "${SPINE_ROOT}/src/spine/extension.c"
  "${SPINE_ROOT}/src/spine/IkConstraint.c"
  "${SPINE_ROOT}/src/spine/IkConstraintData.c"
  "${SPINE_ROOT}/src/spine/Json.c"
  "${SPINE_ROOT}/src/spine/Json.h"
  "${SPINE_ROOT}/src/spine/MeshAttachment.c"
  "${SPINE_ROOT}/src/spine/PathAttachment.c"
  "${SPINE_ROOT}/src/spine/PathConstraint.c"
  "${SPINE_ROOT}/src/spine/PathConstraintData.c"
  "${SPINE_ROOT}/src/spine/PhysicsConstraint.c"
  "${SPINE_ROOT}/src/spine/PhysicsConstraintData.c"
  "${SPINE_ROOT}/src/spine/PointAttachment.c"
  "${SPINE_ROOT}/src/spine/RegionAttachment.c"
  "${SPINE_ROOT}/src/spine/Sequence.c"
  "${SPINE_ROOT}/src/spine/Skeleton.c"
  "${SPINE_ROOT}/src/spine/SkeletonBinary.c"
  "${SPINE_ROOT}/src/spine/SkeletonBounds.c"
  "${SPINE_ROOT}/src/spine/SkeletonClipping.c"
  "${SPINE_ROOT}/src/spine/SkeletonData.c"
  "${SPINE_ROOT}/src/spine/SkeletonJson.c"
  "${SPINE_ROOT}/src/spine/Skin.c"
  "${SPINE_ROOT}/src/spine/Slot.c"
  "${SPINE_ROOT}/src/spine/SlotData.c"
  "${SPINE_ROOT}/src/spine/TransformConstraint.c"
  "${SPINE_ROOT}/src/spine/TransformConstraintData.c"
  "${SPINE_ROOT}/src/spine/Triangulator.c"
  "${SPINE_ROOT}/src/spine/VertexAttachment.c"
)

target_include_directories( Spine PUBLIC "${SPINE_ROOT}/include" )

# Force release flags for this target regardless of parent build type
target_compile_options( Spine PRIVATE -O3 -DNDEBUG )
target_link_options( Spine PRIVATE -O3 )
