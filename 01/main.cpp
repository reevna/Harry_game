// cmake -G "MinGW Makefiles"
// cmake --build .

// Quiddich
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <exception>
#include "menu.h"
#include "map.h"

using namespace sf;

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1200;
    constexpr unsigned WINDOW_HEIGHT = 800;
    const int SECOND_LEVEL_SCORE = 5;
    const int THIRD_LEVEL_SCORE = 8;
    const int FINAL_LEVEL_SCORE = 12;
    const int LIVES_AMMOUNT = 5;
    RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Quiddich");

    menu(window);

    //////////////// MAp //////////////////////
    Image map_image;
    map_image.loadFromFile("img/map.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite mapSprite;
    mapSprite.setTexture(map);

    randomMapGenerate();
    int x = 0;
    int y = 0;

    //////////// Texts ///////////////////////
    sf::Font font;
    font.loadFromFile("font/HarryFont.ttf");
    Text scoreText("", font, 50);
    scoreText.setFont(font);
    scoreText.setString("Snitches");
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(650, 20);

    Text levelText("", font, 50);
    levelText.setFont(font);
    levelText.setString("Level");
    levelText.setFillColor(sf::Color::Black);
    levelText.setPosition(20, 10);

    Text gameOverText("", font, 100);
    gameOverText.setFont(font);
    gameOverText.setString("Game is over");
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setPosition(400, 230);

    Text harryWinsText("", font, 150);
    harryWinsText.setFont(font);
    harryWinsText.setString("Harry wins !");
    harryWinsText.setFillColor(sf::Color::Blue);
    harryWinsText.setPosition(370, 230);

    //////////// life /////////////////////////
    sf::Texture healthtexture;
    healthtexture.loadFromFile("img/health6.png");
    sf::Sprite health(healthtexture);
    health.setPosition(850, 20);
    health.setTextureRect(IntRect(0, 0, 310, 48)); //full health

    //////////// Chocolate ////////////////////
    sf::Texture barTexture;
    barTexture.loadFromFile("img/bar.png");
    sf::Sprite bar(barTexture);
    bar.setPosition(-100, -100);

    //////////// Harry /////////////////////////
    sf::Texture harryTexture;
    harryTexture.loadFromFile("img/harry.png");
    sf::Sprite harry(harryTexture);
    harry.setOrigin(90.f, 90.f);
    float start_harry_pos_x = WINDOW_WIDTH / 2;
    float start_harry_pos_y = WINDOW_HEIGHT / 2;
    harry.setPosition(start_harry_pos_x, start_harry_pos_y);
    harry.setTextureRect(IntRect(0, 0, 180, 142));

    //////////// Snitch /////////////////////////
    sf::Texture snitchTexture;
    snitchTexture.loadFromFile("img/snitch.png");
    snitchTexture.setSmooth(true);
    sf::Sprite snitch(snitchTexture);
    snitch.setScale(sf::Vector2f(0.3f, 0.3f));
    snitch.setRotation(310.f);

    sf::Vector2f snitchSpeed = {250.f, 85.f};

    //////////// Malfoy /////////////////////////
    sf::Texture malfoyTexture;
    malfoyTexture.loadFromFile("img/malfoy.png");
    sf::Sprite malfoy(malfoyTexture);

    sf::Vector2f malfoySpeed = {300.f, 75.f};

    //////////// Blager /////////////////////////
    sf::Texture blagerTexture;
    blagerTexture.loadFromFile("img/blager.png");
    blagerTexture.setSmooth(true);
    sf::Sprite blager(blagerTexture);
    blager.setScale(sf::Vector2f(0.5f, 0.5f));
    sf::Vector2f blagerSpeed = {350.f, 15.f};

    //////////// Victory /////////////////////////
    sf::Texture victoryTexture;
    victoryTexture.loadFromFile("img/victory.png");
    victoryTexture.setSmooth(true);
    sf::Sprite victory(victoryTexture);

    bool snichIsCaught = false;
    bool snitchIsOut = false;
    bool harryIsHit = false;
    int score = 0;
    int life = LIVES_AMMOUNT;
    int level = 1;
    bool gameIsOver = false;
    bool harryWins = false;
    bool showLevelText = true;
    bool barIsShown = false;
    auto pos = harry.getPosition();
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        sf::Event Event;

        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (Event.key.code == sf::Keyboard::Up)
                {
                    harry.move(0, -10);
                }
                else if (Event.key.code == sf::Keyboard::Down)
                {
                    harry.move(0, 10);
                }
                else if (Event.key.code == sf::Keyboard::Left)
                {
                    harry.setScale(sf::Vector2f(-1, 1));
                    harry.move(-10, 0);
                }
                else if (Event.key.code == sf::Keyboard::Right)
                {
                    harry.setScale(sf::Vector2f(1, 1));
                    harry.move(10, 0);
                }
            }
            auto pos = harry.getPosition();
            if (pos.x >= WINDOW_WIDTH)
            {
                pos.x = 5;
                harry.setPosition(pos);
            }
            else if (pos.x < 0)
            {
                pos.x = WINDOW_WIDTH - 5;
                harry.setPosition(pos);
            }
            else if (pos.y >= WINDOW_HEIGHT)
            {
                pos.y = 5;
                harry.setPosition(pos);
            }
            else if (pos.y < 0)
            {
                pos.y = WINDOW_HEIGHT - 5;
                harry.setPosition(pos);
            }
        }
        // check if Harry is out of borders

        const float deltaTime = clock.restart().asSeconds();

        sf::Vector2f snitchPos = snitch.getPosition();
        snitchPos += snitchSpeed * deltaTime;

        if (snitchPos.x > WINDOW_WIDTH || snitchPos.x < 0 || snitchPos.y > WINDOW_HEIGHT || snitchPos.y < 0)
        {
            snitchIsOut = true;
        }
        snitch.setPosition(snitchPos);

        if ((snichIsCaught) || (!snichIsCaught && snitchIsOut))
        {
            float x = std::rand() % (WINDOW_WIDTH / 10);
            float y = std::rand() % WINDOW_HEIGHT;
            snitch.setPosition(x, y);
            snichIsCaught = false;
            snitchIsOut = false;
        }

        if (harry.getGlobalBounds().intersects(snitch.getGlobalBounds()))
        {
            snichIsCaught = true;
            ++score;
        }

        scoreText.setString("Snitches: " + std::to_string(score));

        ///////////////// Game levels //////////////////////

        if ((score > 0) && (score < SECOND_LEVEL_SCORE))
        {
            level = 1;
        }
        if ((score >= SECOND_LEVEL_SCORE) && (score < THIRD_LEVEL_SCORE))
        {
            level = 2;
            snitch.move(0.2, -0.7); // летит вверх
        }
        if ((score >= THIRD_LEVEL_SCORE) && (score < FINAL_LEVEL_SCORE))
        {
            level = 3;
            snitch.move(0.3, 0.3);
            if (barIsShown)
            {
                bar.setPosition(-100, -100);
                barIsShown = false;
            }
        }

        if (score >= FINAL_LEVEL_SCORE)
        {
            harryWins = true;
        }

        levelText.setString("Level: " + std::to_string(level));

        ////////////////   Moving blager
        int randomMoveX = std::rand() % WINDOW_WIDTH;
        int randomMoveY = std::rand() % WINDOW_HEIGHT;
        sf::Vector2f blagerPosition = blager.getPosition();
        blagerPosition += blagerSpeed * deltaTime;
        blager.setPosition(blagerPosition);
        blager.move(0.2, -0.1);

        if (blagerPosition.x >= WINDOW_WIDTH)
        {
            blager.setPosition(0, randomMoveY);
        }
        else if (blagerPosition.x < 0)
        {
            blager.setPosition(0, randomMoveY);
        }
        else if (blagerPosition.y >= WINDOW_HEIGHT)
        {
            blager.setPosition(0, randomMoveY);
        }
        else if (blagerPosition.y < 0)
        {
            blager.setPosition(0, randomMoveY);
        }

        if (harry.getGlobalBounds().intersects(blager.getGlobalBounds()))
        {
            // boom.setPosition(blagerposition.x, blagerposition.y);
            harryIsHit = true;
            --life;
            blager.setPosition(-100, rand() % 2);
        }

        // if (blagerposition.x - pos.x >= 1)
        // {
        //     boom.setPosition(-200, -200);
        // }

        ////////////////   Moving Malfoy
        sf::Vector2f malfoyPosition = malfoy.getPosition();
        malfoyPosition += malfoySpeed * deltaTime;

        if ((malfoyPosition.x >= 1300) && (malfoySpeed.x > 0))
        {
            malfoySpeed.x = -malfoySpeed.x;
            malfoy.setScale(sf::Vector2f(-1, 1));
        }
        if ((malfoyPosition.x < 0) && (malfoySpeed.x < 0))
        {
            malfoySpeed.x = -malfoySpeed.x;
            malfoy.setScale(sf::Vector2f(1, 1));
        }
        if ((malfoyPosition.y >= 800) && (malfoySpeed.y > 0))
        {
            malfoySpeed.y = -malfoySpeed.y;
        }
        if ((malfoyPosition.y < 0) && (malfoySpeed.y < 0))
        {
            malfoySpeed.y = -malfoySpeed.y;
        }
        malfoy.setPosition(malfoyPosition);

        if (harry.getGlobalBounds().intersects(malfoy.getGlobalBounds()))
        {
            harryIsHit = true;
            --life;
            malfoySpeed.x = -malfoySpeed.x;
            malfoy.setScale(sf::Vector2f(-1, 1));
        }

        /////////////// Levels of live /////////////////////////////////

        if (harryIsHit && life == LIVES_AMMOUNT - 1)
        {
            health.setTextureRect(IntRect(310, 0, 310, 48));
            harryIsHit = false;
        }
        if (harryIsHit && life == LIVES_AMMOUNT - 2)
        {
            health.setTextureRect(IntRect(620, 0, 310, 48));
            harryIsHit = false;
        }

        if (harryIsHit && life == LIVES_AMMOUNT - 3)
        {
            harry.setTextureRect(IntRect(180, 0, 180, 142));
            health.setTextureRect(IntRect(930, 0, 310, 48));
            harryIsHit = false;
        }

        if (harryIsHit && life == LIVES_AMMOUNT - 4)
        {
            health.setTextureRect(IntRect(1240, 0, 310, 68));
            harryIsHit = false;
        }

        if (harryIsHit && life == 0)
        {
            gameIsOver = true;
        }

        //////////////// Chocolate Bar ////////////////////////
        bool barIsShown = false;
        if ((life == 1) && (!barIsShown))
        {
            barIsShown = true;
            bar.setPosition(300, 300);
        }

        if (harry.getGlobalBounds().intersects(bar.getGlobalBounds()))
        {
            bar.setPosition(-100, -100);
            harry.setTextureRect(IntRect(0, 0, 180, 142));
            health.setTextureRect(IntRect(930, 0, 310, 48));
            ++life;
        }

        window.clear();

        ///////////// Map  ///////////////////
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')
                    mapSprite.setTextureRect(IntRect(0, 0, 100, 100));
                if (TileMap[i][j] == 'c')
                    mapSprite.setTextureRect(IntRect(100, 0, 100, 100));
                if (TileMap[i][j] == 'b')
                    mapSprite.setTextureRect(IntRect(200, 0, 100, 100));
                mapSprite.setPosition(j * 100, i * 100);
                window.draw(mapSprite);
            }

        if (gameIsOver)
        {
            malfoySpeed = {0.f, 0.f};
            blagerSpeed = {0.f, 0.f};
            harry.setTextureRect(IntRect(360, 0, 180, 142));
            window.draw(gameOverText);
            window.draw(harry);
        }
        else if (harryWins)
        {
            malfoySpeed = {0.f, 0.f};
            blagerSpeed = {0.f, 0.f};
            harry.setTextureRect(IntRect(540, 0, 220, 142));
            window.draw(harryWinsText);
            window.draw(harry);
            window.draw(victory);
        }

        else
        {
            window.draw(scoreText);
            window.draw(levelText);
            window.draw(health);
            window.draw(harry);
            window.draw(snitch);
            window.draw(blager);
            window.draw(malfoy);
            window.draw(bar);
        }

        window.display();
    }

    return 0;
}
