#pragma once

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <Windows.h>
#include <thread>
#include <chrono>

void hotKey(Button &button, int key)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		if (GetAsyncKeyState(key))
		{
			button.changeState();

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}

void stopHotKey(Button &button1, Button &button2, Button &button3, Button &button4, int key)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		if (GetAsyncKeyState(key))
		{
			button1.setState(false);
			button2.setState(false);
			button3.setState(false);
			button4.setState(false);

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}