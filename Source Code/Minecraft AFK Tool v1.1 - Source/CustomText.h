#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>

class CustomText
{
public:
	CustomText(std::string _text, sf::Font &_font) : text() , font()
	{
		text.setFont(_font);
		text.setPosition(sf::Vector2f(100.f,100.f));
		text.setString(_text);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::Black);
	}

	void setScale(sf::Vector2f factor)
	{
		//Default scale is (1,1)
		text.setScale(factor);
	}

	void setPosition(sf::Vector2f position)
	{
		text.setPosition(position);
	}

	void updateText(sf::RenderWindow &window)
	{
		window.draw(text);
	}

	void changeColor(sf::Color color)
	{
		text.setFillColor(color);
	}

private:
	sf::Text text;
	sf::Font font;
};

