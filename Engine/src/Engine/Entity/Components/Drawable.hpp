/*****************************************************************/ /**
 * \file   Drawable.hpp
 * \brief  Drawable component
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <Buffer.h>
#include <Common/interface/RefCntAutoPtr.hpp>

#include "Engine/Math/Vertex.hpp"

namespace __XXECS
{
    struct Drawable
    {
        Vertices vertices;
        Indices indices;

        Diligent::RefCntAutoPtr<Diligent::IBuffer> vertexBuffer;
        Diligent::RefCntAutoPtr<Diligent::IBuffer> indexBuffer;

        static auto Create(Drawable &target) -> void;
        static auto Draw(Drawable &target) -> void;
    };
}