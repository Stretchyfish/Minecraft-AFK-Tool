#pragma once
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <chrono>

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


void autoKillInputs(Button &button)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;


	while (true)
	{
		if (button.checkState())
		{
			for (int i = 0; i < 20; i++)
			{
				input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

				SendInput(1, &input, sizeof(input));

				input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

				SendInput(1, &input, sizeof(input));

				std::this_thread::sleep_for(std::chrono::milliseconds(625));
			}

			input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

			SendInput(1, &input, sizeof(input));

			std::this_thread::sleep_for(std::chrono::milliseconds(1610));

			input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;

			SendInput(1, &input, sizeof(input));



		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void autoConcrete(Button &button)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		if (button.checkState())
		{
			input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

			SendInput(1, &input, sizeof(input));

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

			SendInput(1, &input, sizeof(input));

			std::this_thread::sleep_for(std::chrono::seconds(5));

			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

			SendInput(1, &input, sizeof(input));

			input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;

			SendInput(1, &input, sizeof(input));
		}

	}

}

void ContinousLeftClick(Button &button)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		if (button.checkState())
		{
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

			SendInput(1, &input, sizeof(input));

			std::this_thread::sleep_for(std::chrono::seconds(5));

			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &input, sizeof(input));
		}
	}
}

void ContinousRightClick(Button &button)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		if (button.checkState())
		{
			input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

			SendInput(1, &input, sizeof(input));

			std::this_thread::sleep_for(std::chrono::seconds(5));

			input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;

			SendInput(1, &input, sizeof(input));
		}
	}
}

