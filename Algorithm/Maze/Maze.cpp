#include "pch.h"
#include "ConsoleHelper.h"

int main()
{
    const char* TILE = "■";
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


        // 3. Rendering

        ConsoleHelper::SetCursorPosition(0, 0);
        ConsoleHelper::ShowConsoleCursor(false);
        ConsoleHelper::SetCursorColor(ConsoleColor::RED);

        for (int32 y = 0; y < 25; y++)
        {
            for (int32 x = 0; x < 25; x++)
            {
                cout << TILE;
            }

            cout << endl;
        }
    }
}
