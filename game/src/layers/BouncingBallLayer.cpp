#include "game/layers/BouncingBallLayer.h"

#include "engine/core/ServiceLocator.h"

#include "game/layers/MainMenuLayer.h"

void BouncingBallLayer::OnUpdate()
{
    if (IsKeyPressed(KEY_ONE))
        engine::core::ServiceLocator::GetLayerStack().QueueTransition<BouncingBallLayer, MainMenuLayer>();

    constexpr float maxDeltaTime = 1.0f / 60.0f; // Cap physics to 60 FPS
    const float deltaTime = std::min(GetFrameTime(), maxDeltaTime);

    // Apply gravity
    m_velocity.y += m_acceleration * deltaTime;

    m_position.y += m_velocity.y * deltaTime;

    if (const float groundLevel = static_cast<float>(GetScreenHeight()) - m_radius; m_position.y >= groundLevel)
    {
        m_position.y = groundLevel;

        if (m_velocity.y > 0.0f)
            m_velocity.y = -m_velocity.y * m_restitution;

        // Stop bouncing if the velocity is very small
        if (std::abs(m_velocity.y) < 0.1f)
            m_velocity.y = 0.0f;
    }
}

void BouncingBallLayer::OnRender()
{
    DrawCircleV(m_position, m_radius, RED);
}
