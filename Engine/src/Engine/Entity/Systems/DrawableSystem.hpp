/*****************************************************************/ /**
 * \file   DrawableSystem.hpp
 * \brief  System for Drawable
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/System.hpp>
#include <Engine/Entity/Components/Drawable.hpp>

namespace __XXECS::Entity
{
    class DrawableSystem : System<DrawableSystem>
    {
    public:
        static auto Create(Drawable &target) -> void;

        static auto Update(Drawable &target) -> void;
    };
}
