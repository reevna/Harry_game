
#include <iostream>
#include <sstream>

using namespace sf;

void menu(sf::RenderWindow &window)
{
    sf::Font font;
    font.loadFromFile("font/HarryFont.ttf");
    sf::Text introText("", font, 90);
    introText.setFont(font);
    introText.setString("Welcome to the Qiuddich game");
    introText.setFillColor(sf::Color::White);
    introText.setPosition(180, 190);

    sf::Texture newGameTexture, exitTextButton, menuBackground, menuLogoTexture;
    newGameTexture.loadFromFile("img/ng1.png");
    exitTextButton.loadFromFile("img/exit1.png");
    menuBackground.loadFromFile("img/scroll.png");
    menuLogoTexture.loadFromFile("img/logo2.png");

    sf::Sprite newGame(newGameTexture);
    sf::Sprite exitText(exitTextButton);
    sf::Sprite menuBg(menuBackground);
    sf::Sprite menuLogo(menuLogoTexture);

    sf::Text instructions("", font, 50);
    instructions.setFont(font);
    instructions.setString("Collect snitches, \n be aware of blagers and Malfoy. \n \n Use arrows to fly.");
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(530, 360);
    menuLogo.setPosition(500, 40);

    newGame.setPosition(210, 430);
    exitText.setPosition(210, 500);
    menuBg.setPosition(130, 310);

    bool isMenu = true;
    int menuNum = 0;
    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {
        newGame.setColor(Color::Black);
        exitText.setColor(Color::Black);
        menuNum = 0;
        window.clear(Color(129, 181, 221));
        // sf::Event event;

        if (IntRect(210, 430, 250, 45).contains(Mouse::getPosition(window)))
        {
            newGame.setColor(Color::Blue);
            menuNum = 1;
        }
        if (IntRect(210, 500, 250, 45).contains(Mouse::getPosition(window)))
        {
            exitText.setColor(Color::Blue);
            menuNum = 2;
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1)
                isMenu = false; //если нажали первую кнопку, то выходим из меню
            if (menuNum == 2)
            {
                window.close();
                isMenu = false;
            }
        }

        window.draw(menuBg);
        window.draw(newGame);
        window.draw(exitText);
        window.draw(introText);
        window.draw(instructions);
        window.draw(menuLogo);

        window.display();
    }
}