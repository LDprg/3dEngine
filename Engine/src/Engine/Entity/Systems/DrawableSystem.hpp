/*****************************************************************/ /**
 * \file   DrawableSystem.hpp
 * \brief  System for Drawable
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/ShapeSystem.hpp>

namespace __XXECS::Entity
{
    class DrawableSystem : public ShapeSystem<DrawableSystem>
    {
    public:
        static auto Create(const entt::entity& entity) -> void;

        static auto Run(const entt::entity &entity) -> void;
    };
}
