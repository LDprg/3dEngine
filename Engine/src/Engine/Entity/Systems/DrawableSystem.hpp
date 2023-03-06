/*****************************************************************/ /**
 * \file   DrawableSystem.hpp
 * \brief  System for Drawable
 * 
 * \author LD
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <Engine/Core/Application.hpp>
#include <Engine/Entity/ShapeSystem.hpp>
#include <Engine/Entity/Components/Drawable.hpp>

#include <DeviceContext.h>

namespace __XXECS::Entity
{
    class DrawableSystem : public ShapeSystem<DrawableSystem>
    {
    public:
        static auto Create(const entt::entity &entity) -> void;

        template<typename T>
        static auto Update(T &v) -> void
        {
            for (auto &entity : v)
            {
                auto &target = GetEntityManager().get<Drawable>(entity);

                Application::Get()->GetImmediateContext().GetNative()->UpdateBuffer(
                    target.vertexBuffer, 0, target.vertices.SizeInBytes(), target.vertices,
                    Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
            }
        }

        static auto Run(const entt::entity &entity) -> void;
    };
}
