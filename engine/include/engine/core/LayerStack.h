#pragma once
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "engine/core/Layer.h"

namespace engine::core
{

class LayerStack
{

public:
    LayerStack() = default;
    ~LayerStack() = default;

    template <std::derived_from<Layer> LayerToPush, typename... Args>
    void QueuePush(Args&&... args)
    {
        auto factory = [this, ... capturedArgs = std::forward<Args>(args)]() mutable {
            m_layers.emplace_back(std::make_unique<LayerToPush>(std::forward<decltype(capturedArgs)>(capturedArgs)...));
        };

        m_queuedActions.emplace_back(std::move(factory));
    }

    template <std::derived_from<Layer> FromLayer, std::derived_from<Layer> ToLayer, typename... Args>
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

    template <std::derived_from<Layer> Reference, std::derived_from<Layer> LayerToInsert, typename... Args>
    void QueueInsertAbove(Args&&... args)
    {
        auto factory = [this, ... capturedArgs = std::forward<Args>(args)]() mutable {
            auto it = FindLayer<Reference>();
            auto layer = std::make_unique<LayerToInsert>(std::move(capturedArgs)...);

            if (it == m_layers.end())
                throw std::logic_error(std::string("Reference layer not found to insert a layer above it."));

            m_layers.insert(std::next(it), std::move(layer));
        };

        m_queuedActions.emplace_back(std::move(factory));
    }

    template <std::derived_from<Layer> Reference, std::derived_from<Layer> LayerToInsert, typename... Args>
    void QueueInsertBelow(Args&&... args)
    {
        auto factory = [this, ... capturedArgs = std::forward<Args>(args)]() mutable {
            auto it = FindLayer<Reference>();
            auto layer = std::make_unique<LayerToInsert>(std::move(capturedArgs)...);

            if (it == m_layers.end())
                throw std::logic_error(std::string("Reference layer not found to insert a layer below it."));

            m_layers.insert(it, std::move(layer));
        };

        m_queuedActions.emplace_back(std::move(factory));
    }

    template <std::derived_from<Layer> LayerToErase>
    void QueueRemove()
    {
        auto factory = [this]() mutable {
            auto it = FindLayer<LayerToErase>();

            if (it == m_layers.end())
                throw std::logic_error(std::string("Layer not found to erase it."));

            m_layers.erase(it);
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
    template <typename T>
    auto FindLayer()
    {
        return std::ranges::find_if(m_layers,
                                    [](const auto& layer) { return dynamic_cast<T*>(layer.get()) != nullptr; });
    }

private:
    std::vector<std::unique_ptr<Layer>> m_layers{};
    std::vector<std::function<void()>> m_queuedActions;
};

} // namespace engine::core