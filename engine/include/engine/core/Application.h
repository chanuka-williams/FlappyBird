#pragma once

#include <vector>

#include "engine/core/AppSpec.h"
#include "engine/core/AssetManager.h"
#include "engine/core/Layer.h"

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

    void ProcessLayerActions();

    template <std::derived_from<Layer> LayerToPush, typename... Args>
    void QueueLayerPush(Args&&... args)
    {
        auto factory = [this, ... capturedArgs = std::forward<Args>(args)]() mutable {
            m_layers.emplace_back(std::make_unique<LayerToPush>(std::forward<decltype(capturedArgs)>(capturedArgs)...));
        };

        m_queuedLayerActions.emplace_back(std::move(factory));
    }

    template <std::derived_from<Layer> FromLayer, std::derived_from<Layer> ToLayer, typename... Args>
    void QueueLayerTransition(Args&&... args)
    {
        auto factory = [this, ... capturedArgs = std::forward<Args>(args)]() mutable {
            auto toLayer = std::make_unique<ToLayer>(std::forward<Args>(capturedArgs)...);

            for (auto& layer : m_layers)
            {
                if (!dynamic_cast<FromLayer*>(layer.get()))
                    continue;

                layer = std::move(toLayer);
                return;
            }
        };

        m_queuedLayerActions.push_back(std::move(factory));
    }

    template <std::derived_from<Layer> LayerToErase>
    void QueueLayerRemove()
    {
        auto factory = [this]() mutable {

            int indexToErase = -1;

            for (int i = 0; i < m_layers.size(); ++i)
            {
                if (!dynamic_cast<LayerToErase*>(m_layers[i].get()))
                    continue;

                indexToErase = i;
                break;
            }

            if (indexToErase >= 0)
            {
                m_layers.erase(m_layers.begin() + indexToErase);
            }

        };

        m_queuedLayerActions.push_back(std::move(factory));
    }

private:
    AssetManager m_assetManager{};
    std::vector<std::unique_ptr<Layer>> m_layers{};
    std::vector<std::function<void()>> m_queuedLayerActions;
};

} // namespace engine::core
