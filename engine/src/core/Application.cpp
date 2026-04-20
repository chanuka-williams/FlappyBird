#include "engine/core/Application.h"
#include "engine/core/Layer.h"
#include "raylib.h"

namespace engine::core
{

Application::Application(const AppSpec& appSpec)
{
    InitWindow(appSpec.width, appSpec.height, appSpec.windowTitle.c_str());
    m_assetManager.Initialize();
}

Application::~Application()
{
    CloseWindow();
}

void Application::Run()
{
    // Main game loop
    while (!WindowShouldClose())
    {
        m_layerStack.ProcessActions();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const auto& layer : m_layerStack)
        {
            if (layer->GetState() == LayerState::ACTIVE)
                layer->OnUpdate();

            if (layer->GetVisibility() == LayerVisibility::VISIBLE)
                layer->OnRender();
        }

        EndDrawing();
    }
}

AssetManager& Application::GetAssetManager()
{
    return m_assetManager;
}

LayerStack& Application::GetLayerStack()
{
    return m_layerStack;
}

} // namespace engine::core