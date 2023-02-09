
#include <iostream>
#include <sstream>

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
    int menuNum;
    sf::Event event;
    // pollEvents(window);
    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            window.clear(sf::Color(129, 181, 221));
            newGame.setColor(sf::Color::Black);
            exitText.setColor(sf::Color::Black);
            menuNum = 0;
            if (sf::IntRect(210, 430, 250, 45).contains(sf::Mouse::getPosition(window)))
            {
                newGame.setColor(sf::Color::Blue);
                menuNum = 1;
            }
            if (sf::IntRect(210, 500, 250, 45).contains(sf::Mouse::getPosition(window)))
            {
                exitText.setColor(sf::Color::Blue);
                menuNum = 2;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (menuNum == 1)
                {
                    isMenu = false;
                }
                else if (menuNum == 2)
                {
                    window.close();
                    isMenu = false;
                    std::cerr << "incorrect stop" << std::endl;
                }
            }
            if (event.type == sf::Event::Closed)
            {
                isMenu = false;
                window.close();
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
}