#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "engine/core/Layer.h"

class LayerStack
{

public:
    LayerStack() = default;
    ~LayerStack() = default;

    template <std::derived_from<engine::core::Layer> LayerToPush, typename... Args>
    void QueuePush(Args&&... args)
    {
        auto factory = [this, ... capturedArgs = std::forward<Args>(args)]() mutable {
            m_layers.emplace_back(std::make_unique<LayerToPush>(std::forward<decltype(capturedArgs)>(capturedArgs)...));
        };

        m_queuedActions.emplace_back(std::move(factory));
    }

    template <std::derived_from<engine::core::Layer> FromLayer, std::derived_from<engine::core::Layer> ToLayer,
              typename... Args>
    void QueueTransition(Args&&... args)
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

        m_queuedActions.push_back(std::move(factory));
    }

    template <std::derived_from<engine::core::Layer> LayerToErase>
    void QueueRemove()
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

        m_queuedActions.push_back(std::move(factory));
    }

    void ProcessActions()
    {
        for (const auto& action : m_queuedActions)
            action();

        m_queuedActions.clear();
    }

    auto begin()
    {
        return m_layers.begin();
    }

    auto end()
    {
        return m_layers.end();
    }

    [[nodiscard]] auto begin() const
    {
        return m_layers.cbegin();
    }

    [[nodiscard]] auto end() const
    {
        return m_layers.cend();
    }

private:
    std::vector<std::unique_ptr<engine::core::Layer>> m_layers{};
    std::vector<std::function<void()>> m_queuedActions;
};