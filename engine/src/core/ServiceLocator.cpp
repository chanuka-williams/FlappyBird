#include "engine/core/ServiceLocator.h"

engine::core::Application* engine::core::ServiceLocator::GetApplication()
{
    if (s_app == nullptr)
        throw std::runtime_error("ServiceLocator::SetApp must be called before GetApplication");

    return s_app;
}

void engine::core::ServiceLocator::SetApp(Application* app)
{
    s_app = app;
}

engine::core::AssetManager& engine::core::ServiceLocator::GetAssetManager()
{
    if (s_app == nullptr)
        throw std::runtime_error("ServiceLocator::SetApp must be called before GetAssetManager");

    return s_app->GetAssetManager();
}
LayerStack& engine::core::ServiceLocator::GetLayerStack()
{
    if (s_app == nullptr)
        throw std::runtime_error("ServiceLocator::SetApp must be called before GetAssetManager");

    return s_app->GetLayerStack();
}