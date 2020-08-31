#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>

#include <iostream>

class Button
{
public:
	Button() : buttonShape(sf::Vector2f(120.f,50.f))
	{
		buttonShape.setFillColor(sf::Color(210, 210, 210));
	}

	Button(std::string _text, sf::Font &_font) : buttonShape(sf::Vector2f(120.f,50.f)) , text(), checkBox(), checkBoxTexture()
	{
		//Set square 
		buttonShape.setFillColor(sf::Color(210, 210, 210));

		//Set text in box
		text.setFont(_font);
		text.setPosition(sf::Vector2f(buttonShape.getPosition().x + buttonShape.getSize().x / 5, buttonShape.getPosition().y + buttonShape.getSize().y / 4));
		text.setString(_text);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::Black);

		//Set checkbox
		//sf::Texture texture;
		checkBoxTexture.loadFromFile("square_softedge.png");
		checkBox.setTexture(checkBoxTexture);
		checkBox.setColor(sf::Color::White);
		checkBox.setScale(sf::Vector2f(0.07f, 0.07f));
		checkBox.setPosition(sf::Vector2f(buttonShape.getPosition().x - 70, buttonShape.getPosition().y - 6));
	}

	Button(std::string _text, sf::Font& _font, std::string hotkey) : buttonShape(sf::Vector2f(120.f, 50.f)), text(), checkBox(), checkBoxTexture(), hotkeyCircle(25.f), hotkeyText()
	{
		//Set square 
		buttonShape.setFillColor(sf::Color(210, 210, 210));

		//Set text in box
		text.setFont(_font);
		text.setPosition(sf::Vector2f(buttonShape.getPosition().x + buttonShape.getSize().x / 5, buttonShape.getPosition().y + buttonShape.getSize().y / 4));
		text.setString(_text);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::Black);

		//Set checkbox
		checkBoxTexture.loadFromFile("square_softedge.png");
		checkBox.setTexture(checkBoxTexture);
		checkBox.setColor(sf::Color::White);
		checkBox.setScale(sf::Vector2f(0.07f, 0.07f));
		checkBox.setPosition(sf::Vector2f(buttonShape.getPosition().x - 70, buttonShape.getPosition().y - 6));

		//Set hotkey circle with text
		hotkeyCircle.setFillColor(sf::Color(192,192,192,128));
		hotkeyCircle.setPosition(sf::Vector2f(150.f,150.f));
		hotkeyText.setFont(_font);
		hotkeyText.setPosition(sf::Vector2f(230.f, 186.f));
		hotkeyText.setString(hotkey);
		hotkeyText.setCharacterSize(30);
		hotkeyText.setFillColor(sf::Color::Black);
	}

	//Check if mouse is inside button and update color
	bool CheckMouseOver(sf::RenderWindow &window)
	{
		if (buttonShape.getPosition().x < sf::Mouse::getPosition(window).x 
				&& sf::Mouse::getPosition(window).x <= buttonShape.getPosition().x + buttonShape.getSize().x 
			&& buttonShape.getPosition().y < sf::Mouse::getPosition(window).y 
				&& sf::Mouse::getPosition(window).y < buttonShape.getPosition().y + buttonShape.getSize().y)
		{
			buttonShape.setFillColor(sf::Color(190, 190, 190));
			return 1;
		}
		else
		{
			buttonShape.setFillColor(sf::Color(210, 210, 210));
			return 0;
		}
	}

	//Ensure it is a single click
	bool singleClick()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) != lastMouseState
			&& lastMouseState == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void CheckClick(sf::RenderWindow &window)
	{
		if (CheckMouseOver(window) && !activated && singleClick())
		{
			activated = true;
			std::cout << "activated = true" << std::endl;
		}
		else if (CheckMouseOver(window) && activated && singleClick())
		{
			activated = false;
			std::cout << "activation = false" << std::endl;
		}

		lastMouseState = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}

	void setButtonPosition(sf::Vector2f position)
	{
		buttonShape.setPosition(position);
		text.setPosition(sf::Vector2f(buttonShape.getPosition().x + 13, buttonShape.getPosition().y + buttonShape.getSize().y / 4));
		checkBox.setPosition(sf::Vector2f(buttonShape.getPosition().x - 70, buttonShape.getPosition().y - 6));
		hotkeyCircle.setPosition(sf::Vector2f(position.x + buttonShape.getSize().x + 10, position.y));
		hotkeyText.setPosition(sf::Vector2f(position.x + buttonShape.getSize().x + 24, position.y + 5));
	}

	void updateButton(sf::RenderWindow &window)
	{
		CheckClick(window);
		window.draw(buttonShape);
		window.draw(text);
		if (activated)
		{
			checkBox.setColor(sf::Color::Green);
		}
		else
		{
			checkBox.setColor(sf::Color::White);
		}
		window.draw(checkBox);
		window.draw(hotkeyCircle);
		window.draw(hotkeyText);
	}

	bool checkState()
	{
		return activated;
	}

	void changeState()
	{
		activated = !activated;
	}

	void setState(bool newState)
	{
		activated = newState;
	}

	void changeColor(sf::Color color)
	{
		buttonShape.setFillColor(color);
	}

private:
	//The visuals of the button
	sf::RectangleShape buttonShape;

	//Font
	sf::Font font;

	//Text
	sf::Text text;

	//Checkbox
	sf::Sprite checkBox;
	sf::Texture checkBoxTexture;

	//Hotkey box
	sf::CircleShape hotkeyCircle;
	sf::Text hotkeyText;

	//Button state
	bool lastMouseState;

	//Determin if the buttons function is activated
	bool activated = false;


};

