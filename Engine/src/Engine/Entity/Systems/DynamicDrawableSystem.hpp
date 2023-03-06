/*****************************************************************/ /**
 * \file   DynamicDrawableSystem.hpp
 * \brief  System for Dynamic Drawable
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <Engine/Entity/ShapeSystem.hpp>

namespace __XXECS::Entity
{
    class DynamicDrawableSystem : public ShapeSystem<DynamicDrawableSystem>
    {
    public:
        static auto Create(const entt::entity& entity) -> void;

        static auto Run(const entt::entity &entity) -> void;
    };
}
