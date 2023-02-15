/*****************************************************************/ /**
 * \file   Drawable.hpp
 * \brief  Drawable component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include "Engine/Math/Vertex.hpp"

namespace __XXECS
{
    struct Drawable
    {
        Math::Vertices vertices;
        Math::Indices indices;

        Diligent::RefCntAutoPtr<Diligent::IBuffer> vertexBuffer;
        Diligent::RefCntAutoPtr<Diligent::IBuffer> indexBuffer;

        Drawable(const Math::Vertices &vertices, const Math::Indices &indices)
            : vertices(vertices), indices(indices)
        {
        }

        static auto Create(Drawable &target) -> void;
        static auto Draw(Drawable &target) -> void;
    };
}
