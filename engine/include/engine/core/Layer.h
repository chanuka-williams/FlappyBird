#pragma once

namespace engine::core
{

enum class LayerState
{
    ACTIVE,
    PAUSED
};

enum class LayerVisibility
{
    VISIBLE,
    HIDDEN
};

class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;

    [[nodiscard]] LayerState GetState() const;
    void SetState(LayerState state);

    [[nodiscard]] LayerVisibility GetVisibility() const;
    void SetVisibility(LayerVisibility visibility);

private:
    LayerState m_state = LayerState::ACTIVE;
    LayerVisibility m_visibility = LayerVisibility::VISIBLE;
};

} // namespace engine::core