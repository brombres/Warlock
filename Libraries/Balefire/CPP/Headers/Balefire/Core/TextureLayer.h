#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  enum TextureLayer
  {
    ALBEDO       = 0,
    // This texture defines the base color of a surface without any lighting effects.
    // It is also known as the diffuse map.

    NORMAL       = 1,
    // This texture simulates small surface details like bumps and dents without adding extra
    // polygons. It modifies the surface normals to create the illusion of depth.

    SPECULAR     = 2,
    // This texture controls the shininess and reflectivity of a surface.
    // It determines which parts of the surface reflect light and how much.

    ROUGHNESS    = 3,
    // This texture defines the roughness of a surface, affecting how light is scattered.
    // Rough surfaces have diffuse reflections, while smooth surfaces have sharp reflections.

    METALNESS    = 4,
    // This texture specifies which parts of a surface are metallic and which are not.
    // It affects how light interacts with the material, giving it a metallic or non-metallic
    // appearance.

    HEIGHT       = 5,
    // This texture provides information about the height of each point on the surface, often used
    // for displacement mapping to create actual geometric detail.

    OCCLUSION    = 6,
    // This texture simulates the shadowing that occurs in crevices and corners where light is
    // occluded. It enhances the perception of depth and detail.

    EMISSIVE     = 7,
    // This texture defines parts of the surface that emit light, making them glow. It is used for
    // creating effects like glowing signs or lights.

    TRANSPARENCY = 8,
    // This texture controls the transparency of different parts of the surface. It is used for
    // rendering effects like glass or foliage.

    DETAIL       = 9,
    // This texture adds additional fine details to a surface, often overlaid on top of other maps
    // to enhance realism.

    SUBSURFACE_SCATTERING = 10,
    // This texture simulates the scattering of light beneath the surface of translucent materials,
    // like skin or wax.

    REFLECTION            = 11,
    // This texture is used to simulate reflective surfaces, often in conjunction with environment
    // mapping techniques.

    DISPLACEMENT          = 12,
    // Similar to height maps, these textures are used to actually displace vertices in a mesh,
    // creating real geometric changes based on the texture data.

    GLOSS                 = 13,
    // This texture controls the glossiness of a surface, determining how sharp or blurry the
    // reflections are.

    COUNT                 = 14
  };
};

