#pragma once

#include "engine/core/Layer.h"

#include "raylib.h"

class BouncingBallLayer : public engine::core::Layer
{
public:
    BouncingBallLayer() = default;
    ~BouncingBallLayer() override = default;

    void OnUpdate() override;
    void OnRender() override;

private:
    const float m_radius = 6.0f;
    const float m_acceleration = 500.0f;
    const float m_mass = 5.0f;
    const float m_restitution = 0.8f;

    Vector2 m_position =
        Vector2(static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f);

    Vector2 m_velocity = Vector2(0.0f, 0.0f);
};