#include "engine/core/Layer.h"

namespace engine::core
{

LayerState Layer::GetState() const
{
    return m_state;
}

void Layer::SetState(const LayerState state)
{
    m_state = state;
}

LayerVisibility Layer::GetVisibility() const
{
    return m_visibility;
}

void Layer::SetVisibility(const LayerVisibility visibility)
{
    m_visibility = visibility;
}

} // namespace engine::core
