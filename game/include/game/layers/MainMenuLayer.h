#pragma once

#include "engine/core/Layer.h"

class MainMenuLayer : public engine::core::Layer
{
public:
    MainMenuLayer() = default;
    ~MainMenuLayer() override = default;

    void OnUpdate() override;
    void OnRender() override;
};
