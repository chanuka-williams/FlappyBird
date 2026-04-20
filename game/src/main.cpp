#include "engine/core/Application.h"
#include "engine/core/ServiceLocator.h"

#include "game/layers/MainMenuLayer.h"

int main()
{
    using namespace engine::core;
    const AppSpec appSpec;
    Application game(appSpec);

    // ReSharper disable once CppDFALocalValueEscapesFunction
    // The game's lifetime covers entire program execution so this is safe.
    ServiceLocator::SetApp(&game);
    ServiceLocator::GetLayerStack().QueuePush<MainMenuLayer>();
    
    game.Run();
    return 0;
}