#include "game/layers/MainMenuLayer.h"

#include "engine/core/ServiceLocator.h"
#include "game/layers/BouncingBallLayer.h"
#include "raylib.h"

void MainMenuLayer::OnUpdate()
{
    if (IsKeyPressed(KEY_TWO))
        engine::core::ServiceLocator::GetLayerStack().QueueTransition<MainMenuLayer, BouncingBallLayer>();
}

void MainMenuLayer::OnRender()
{
    DrawText("Hello World !", 20, 20, 20, BLACK);
}