#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <chrono>
#include <thread>
#include <cstdlib>
#include <thread>

//#include "Buttons.h"
//#include "ButtonController.h"
#include <iostream>
#include "Button.h"
#include "CustomText.h"
#include "ButtonFunctions.h"
#include "HotKey.h"

int main()
{
    int horizontalScreen = 800;
    int verticalScreen = 600;

    // create the window
    sf::RenderWindow window(sf::VideoMode(horizontalScreen, verticalScreen), "Minecraft AFK Tool");
    
    //Initiate Font
    sf::Font Roboto;
    Roboto.loadFromFile("Roboto-Medium.ttf");

    // Create Logo
    sf::Sprite logo;
    sf::Texture texture;
    texture.loadFromFile("AFK_TOOL_LOGO.png");
    logo.setTexture(texture);
    logo.setOrigin(sf::Vector2f(texture.getSize().x / 2, 0));
    logo.setScale(sf::Vector2f(0.4f, 0.4f));
    logo.setPosition(sf::Vector2f(horizontalScreen / 2, 0));

    //Create AFK kill button
    Button autoKillB("Auto Kill", Roboto, "G");                             // Create Button
    autoKillB.setButtonPosition(sf::Vector2f(100.f,180.f));
    std::thread afkKillThread(autoKillInputs, std::ref(autoKillB));         // Create Button Function thread
    afkKillThread.detach();
    std::thread autoKillHotkey(hotKey, std::ref(autoKillB), 0x47);          // Create Button Hotkey
    autoKillHotkey.detach();
    CustomText autoKillText("Automatically Kill Mobs. Have sword in left hand, \nfood in right hand.", Roboto);
    autoKillText.setPosition(sf::Vector2f(300.f, 185.f));
    autoKillText.setScale(sf::Vector2f(0.8f,0.8f));

    //Create Concrete destroy button
    Button autoConcreteB("Concrete", Roboto, "H");
    autoConcreteB.setButtonPosition(sf::Vector2f(100.f, 260.f));
    std::thread autoConcreteThread(autoConcrete, std::ref(autoConcreteB));
    autoConcreteThread.detach();
    std::thread concreteHotKey(hotKey, std::ref(autoConcreteB), 0x48);          
    concreteHotKey.detach();
    CustomText autoConcreteText("Automatically create concrete. Have pickaxe in left hand, \nconcrete powder in right hand.", Roboto);
    autoConcreteText.setPosition(sf::Vector2f(300.f, 265.f));
    autoConcreteText.setScale(sf::Vector2f(0.8f, 0.8f));

    // Create Left Click
    Button rightClickB("Left Click", Roboto, "J");
    rightClickB.setButtonPosition(sf::Vector2f(100.f, 340.f));
    std::thread rightClickThread(ContinousLeftClick, std::ref(rightClickB));
    rightClickThread.detach();
    std::thread rightClickHotkey(hotKey, std::ref(rightClickB), 0x4A);
    rightClickHotkey.detach();
    CustomText rightClickText("Continously hold down Left Click.", Roboto);
    rightClickText.setPosition(sf::Vector2f(300.f, 353.f));
    rightClickText.setScale(sf::Vector2f(0.8f, 0.8f));

    //Create Right Click button
    Button walkB("Right Click", Roboto, "K");
    walkB.setButtonPosition(sf::Vector2f(100.f, 420.f));
    std::thread walkThread(ContinousRightClick, std::ref(walkB));
    walkThread.detach();
    std::thread walkHotkey(hotKey, std::ref(walkB), 0x4B);
    walkHotkey.detach();
    CustomText walkText("Continously hold down right click.", Roboto);
    walkText.setPosition(sf::Vector2f(300.f, 432.f));
    walkText.setScale(sf::Vector2f(0.8f, 0.8f));
    
    //Create stop icon with text
    sf::CircleShape stopShape(22);
    stopShape.setPosition(sf::Vector2f(230.f,490.f));
    stopShape.setOutlineColor(sf::Color(255, 51, 51));
    stopShape.setFillColor(sf::Color(255,102,102,128));
    CustomText stopText("M", Roboto);
    stopText.setPosition(sf::Vector2f(240.5f, 492.f));
    stopText.setScale(sf::Vector2f(1.5,1.5));
    CustomText stopText2("Stop all functions.", Roboto);
    stopText2.setPosition(sf::Vector2f(300.f, 500.5f));
    stopText2.setScale(sf::Vector2f(0.8f, 0.8f));

    // Create lines
    sf::RectangleShape line1(sf::Vector2f(750.f,5.f));
    line1.setFillColor(sf::Color::Black);
    line1.setPosition(sf::Vector2f(30.f,565.f));

    sf::RectangleShape line2(sf::Vector2f(5.f, 20.f));
    line2.setFillColor(sf::Color::Black);
    line2.setPosition(sf::Vector2f(205.f, 545.f));

    sf::RectangleShape line3(sf::Vector2f(5.f, 20.f));
    line3.setFillColor(sf::Color::Black);
    line3.setPosition(sf::Vector2f(295.f, 545.f));

    // Custom texts
    CustomText hotkeyDescription("Hotkeys", Roboto);
    hotkeyDescription.setPosition(sf::Vector2f(215.f,541.f));
    std::thread stopThread(stopHotKey, std::ref(autoKillB), std::ref(autoConcreteB), std::ref(rightClickB), std::ref(walkB), 0x4D);
    stopThread.detach();

    CustomText redDescription("Functions might run for a moment after deactivation", Roboto);
    redDescription.setPosition(sf::Vector2f(400.f, 573.f));
    redDescription.setScale(sf::Vector2f(0.8f,0.8f));
    redDescription.changeColor(sf::Color(255,0,0));

    //Made by
    CustomText myName("Made by Michael Forest", Roboto);
    myName.setPosition(sf::Vector2f(10.f, window.getSize().y - 28));

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // Logo
        window.draw(logo);

        // Auto Kill
        autoKillB.updateButton(window);
        autoKillText.updateText(window);
        //window.draw(autoKillText);

        // Concrete
        autoConcreteB.updateButton(window);
        autoConcreteText.updateText(window);

        // Right click
        rightClickB.updateButton(window);
        rightClickText.updateText(window);

        //Walk
        walkB.updateButton(window);
        walkText.updateText(window);

        //Stop shape
        window.draw(stopShape);
        stopText.updateText(window);
        stopText2.updateText(window);

        // Draw lines
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);

        // Draw seperate text
        hotkeyDescription.updateText(window);
        redDescription.updateText(window);

        //Made by Michael Forrest text
        myName.updateText(window);

        // end the current frame
        window.display();
    }

    return 0;
}