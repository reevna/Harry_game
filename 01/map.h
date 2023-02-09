#include <SFML\Graphics.hpp>
#include <iostream>
const int HEIGHT_MAP = 8;
const int WIDTH_MAP = 12;

sf::String TileMap[HEIGHT_MAP] = {
    "            ",
    "  c         ",
    "            ",
    "            ",
    "         c  ",
    "    c       ",
    "            ",
    "            ",

};

void randomMapGenerate()
{
    int randomElementX = 0;
    int randomElementY = 0;
    srand(time(0));
    int countClouds = 3;
    int bar = 1;

    while (countClouds > 0)
    {
        randomElementX = 1 + rand() % (WIDTH_MAP);
        randomElementY = 1 + rand() % (HEIGHT_MAP);

        if (TileMap[randomElementY][randomElementX] == ' ')
        {
            TileMap[randomElementY][randomElementX] = 'c';
            countClouds--;
        }
    }
}