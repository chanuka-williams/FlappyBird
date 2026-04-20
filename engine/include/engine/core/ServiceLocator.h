#pragma once
#include "Application.h"

namespace engine::core
{

class ServiceLocator
{
public:
    static Application* GetApplication();
    static void SetApp(Application* app);

    static AssetManager& GetAssetManager();
    static LayerStack& GetLayerStack();

private:
    inline static Application* s_app = nullptr;
};

} // namespace engine::core