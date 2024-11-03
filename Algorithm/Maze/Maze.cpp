#include "pch.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main()
{
    ::srand(static_cast<unsigned>(time(nullptr)));

    board.Init(25, &player);
    player.Init(&board);

    uint64 lastTick = 0;
    while (true)
    {
#pragma region Check FrameRate
        const uint64 currentTick = ::GetTickCount64();
        const uint64 deltaTick = currentTick - lastTick;
        lastTick = currentTick;
#pragma endregion

        // 1. Input


        // 2. Logic
        player.Update(deltaTick);

        // 3. Rendering
        board.Render();
    }
}
