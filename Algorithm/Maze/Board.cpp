#include "pch.h"
#include "Board.h"
#include "Player.h"

const char* TILE = "■";

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size, Player* player)
{
    _size = size;
    _player = player;

    GenerateMap();
}

void Board::Render()
{
    ConsoleHelper::SetCursorPosition(0, 0);
    ConsoleHelper::ShowConsoleCursor(false);
    ConsoleHelper::SetCursorColor(ConsoleColor::RED);

    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            ConsoleColor color = GetTileColor(Pos{ y, x });
            ConsoleHelper::SetCursorColor(color);

            cout << TILE;
        }

        cout << endl;
    }
}

// Binary Tree 미로 생성 알고리즘
// from - Mazes for Programmers
void Board::GenerateMap()
{
    for (int y = 0; y < _size; y++)
    {
        for (int x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
            {
                _tile[y][x] = TileType::WALL;
            }
            else
            {
                _tile[y][x] = TileType::EMPTY;
            }
        }
    }

    // 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
                continue;   // 위에서 이미 막아놓은 벽은 continue
            
            if (y == _size - 2 && x == _size - 2)
                continue;   // 마지막 벽까지 왔을 땐, 뚫지 않음

            // ---- 모서리 상황에서는 한쪽으로만 뚫리도록 예외 처리
            if (y == _size - 2)
            {
                _tile[y][x + 1] = TileType::EMPTY;
                continue;
            }

            if (x == _size - 2)
            {
                _tile[y + 1][x] = TileType::EMPTY;
                continue;
            }
            // ----

            const int32 randValue = ::rand() & 2;
            if (randValue == 0)
            {
                _tile[y][x + 1] = TileType::EMPTY;
            }
            else
            {
                _tile[y + 1][x] = TileType::EMPTY;
            }
        }
    }
}

TileType Board::GetTileType(Pos pos)
{
    if (pos.x < 0 || pos.x >= _size)
        return TileType::NONE;

    if (pos.y < 0 || pos.y >= _size)
        return TileType::NONE;

    return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    if (_player && _player->GetPos() == pos)
        return ConsoleColor::YELLOW;

    if (GetExitPos() == pos)
        return ConsoleColor::BLUE;

    TileType tileType = GetTileType(pos);

    switch (tileType)
    {
    case TileType::EMPTY:
        return ConsoleColor::GREEN;
    case TileType::WALL:
        return ConsoleColor::RED;
    }
    
    return ConsoleColor::WHITE;
}
