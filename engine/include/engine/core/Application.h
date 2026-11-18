#pragma once

#include "engine/core/AppSpec.h"
#include "engine/core/AssetManager.h"
#include "engine/core/LayerStack.h"

namespace engine::core
{

class Application
{
public:
    explicit Application(const AppSpec& appSpec);
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void Run();

    AssetManager& GetAssetManager();
    LayerStack& GetLayerStack();

private:
    AssetManager m_assetManager{};
    LayerStack m_layerStack{};
};

} // namespace engine::core
