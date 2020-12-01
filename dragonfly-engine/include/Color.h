// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

#pragma once
#include <SFML/Graphics.hpp>

namespace df {

	// Colors Dragonfly recognizes
	enum Color {
		UNDEFINED_COLOR = -1,
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		// Custom colors
		GRAY,
		GREY,
		LTGRAY,
		LTGREY,
		DKGREY,
		DKGRAY,
		ORANGE,
		MIDGREEN,
		TEAL,
		MIDBLUE,
		VIOLET,
		PURPLE,
	};

	// Default color used if none specified
	const Color COLOR_DEFAULT = WHITE;
	
	// Hard-coded background color
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;

	// Convert from df::Color to sf::Color
	static sf::Color getColor(Color color)
	{
		switch (color)
		{
			case BLACK:
				return sf::Color::Black;
			case RED:
				return sf::Color::Red;
			case GREEN:
				return sf::Color::Green;
			case YELLOW:
				return sf::Color::Yellow;
			case BLUE:
				return sf::Color::Blue;
			case MAGENTA:
				return sf::Color::Magenta;
			case CYAN:
				return sf::Color::Cyan;
			case WHITE:
				return sf::Color::White;
			// Custom colors
			case GREY:
			case GRAY:
				return sf::Color(128, 128, 128);
			case LTGREY:
			case LTGRAY:
				return sf::Color(200, 200, 200);
			case DKGREY:
			case DKGRAY:
				return sf::Color(80, 80, 80);
			case ORANGE:
				return sf::Color(255, 140, 0);
			case MIDGREEN:
				return sf::Color(36, 180, 0);
			case TEAL:
				return sf::Color(0, 128, 128);
			case MIDBLUE:
				return sf::Color(0, 160, 255);
			case VIOLET:
				return sf::Color(128, 140, 255);
			case PURPLE:
				return sf::Color(180, 0, 200);
			// Default to white
			default:
				return sf::Color::White;
		}
	}


	// Convert from string to df::Color
	// This could be done more intelligently with a map
	static df::Color parseColor(std::string color_string)
	{
		// default colors
		if (color_string == "black") {
			return BLACK;
		} else if (color_string == "red") {
			return RED;
		} else if (color_string == "green") {
			return GREEN;
		} else if (color_string == "yellow") {
			return YELLOW;
		} else if (color_string == "blue") {
			return BLUE;
		} else if (color_string == "magenta") {
			return MAGENTA;
		} else if (color_string == "cyan") {
			return CYAN;
		} else if (color_string == "white") {
			return WHITE;
		// custom colors
		} else if (color_string == "gray") {
			return GRAY;
		} else if (color_string == "grey") {
			return GREY;
		} else if (color_string == "ltgray") {
			return LTGRAY;
		} else if (color_string == "ltgrey") {
			return LTGREY;
		} else if (color_string == "dkgray") {
			return DKGRAY;
		} else if (color_string == "dkgrey") {
			return DKGREY;
		} else if (color_string == "orange") {
			return ORANGE;
		} else if (color_string == "midgreen") {
			return MIDGREEN;
		} else if (color_string == "teal") {
			return TEAL;
		} else if (color_string == "midblue") {
			return MIDBLUE;
		} else if (color_string == "violet") {
			return VIOLET;
		} else if (color_string == "purple") {
			return PURPLE;
		} else {
			return UNDEFINED_COLOR;
		}
	}
}