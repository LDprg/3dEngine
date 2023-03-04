/*****************************************************************/ /**
 * \file   DrawableSystem.hpp
 * \brief  System for Drawable
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/System.hpp>

namespace __XXECS::Entity
{
    class DrawableSystem : public System<DrawableSystem>
    {
    public:
        static auto Create(entt::entity entity) -> void;

        static auto Update(entt::entity entity) -> void;
    };
}
