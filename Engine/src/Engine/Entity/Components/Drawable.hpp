/*****************************************************************/ /**
 * \file   Drawable.hpp
 * \brief  Drawable component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include "Engine/Math/Vertex.hpp"

#include <Common/interface/RefCntAutoPtr.hpp>
#include <Graphics/GraphicsEngine/interface/Buffer.h>

namespace __XXECS::Entity
{
    struct Drawable
    {
        Math::Vertices vertices;
        Math::Indices indices;

        Diligent::RefCntAutoPtr<Diligent::IBuffer> vertexBuffer;
        Diligent::RefCntAutoPtr<Diligent::IBuffer> indexBuffer;

        Drawable(Math::Vertices vertices, Math::Indices indices)
            : vertices(std::move(vertices)), indices(std::move(indices))
        {
        }
    };
}
