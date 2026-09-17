#include <memory>
#include "raylib.h"
#include "Astar/Astar.h"
#include "Game/Game.h"
#include "src/World/World.h"

int main()
{
    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->Start();
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        game->Update();

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}


