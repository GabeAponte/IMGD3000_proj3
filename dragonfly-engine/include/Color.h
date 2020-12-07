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
		BLUE,
		YELLOW,
		CYAN,
		MAGENTA,
		WHITE,
		// Custom colors
		// Grays
		GRAY,
		GREY,
		LTGRAY,
		LTGREY,
		DKGREY,
		DKGRAY,
		SLATE,
		// Mids
		MIDRED,
		MIDGREEN,
		MIDBLUE,
		ORANGE,
		TEAL,
		PURPLE,
		// Darks
		BURGUNDY,
		DKGREEN,
		DKBLUE,
		BROWN,
		NAVY,
		VIOLET,
		// Pastels
		PINK,
		LIME,
		SKYBLUE,
		IVORY,
		SEAFOAM,
		INDIGO,
		// Misc.
		TAN,
		CHOCOLATE,
		CORAL,
		SEAMETAL,
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
			case BLUE:
				return sf::Color::Blue;
			case YELLOW:
				return sf::Color::Yellow;
			case CYAN:
				return sf::Color::Cyan;
			case MAGENTA:
				return sf::Color::Magenta;
			case WHITE:
				return sf::Color::White;
			// Custom colors
			// Grays
			case LTGREY:
			case LTGRAY:
				return sf::Color(190, 190, 190);
			case GREY:
			case GRAY:
				return sf::Color(128, 128, 128);
			case DKGREY:
			case DKGRAY:
				return sf::Color(80, 80, 80);
			case SLATE:
				return sf::Color(50, 50, 50);
			// Mids
			case MIDRED:
				return sf::Color(127, 6, 22);
			case MIDGREEN:
				return sf::Color(30, 160, 18);
			case MIDBLUE:
				return sf::Color(13, 101, 192);
			case ORANGE:
				return sf::Color(255, 140, 0);
			case TEAL:
				return sf::Color(0, 128, 128);
			case PURPLE:
				return sf::Color(158, 0, 187);
			// Darks
			case BURGUNDY:
				return sf::Color(63, 15, 33);
			case DKGREEN:
				return sf::Color(25, 77, 46);
			case DKBLUE:
				return sf::Color(14, 9, 154);
			case BROWN:
				return sf::Color(126, 62, 16);
			case NAVY:
				return sf::Color(24, 46, 118);
			case VIOLET:
				return sf::Color(85, 28, 202);
			// Pastel
			case PINK:
				return sf::Color(255, 126, 255);
			case LIME:
				return sf::Color(182, 255, 0);
			case SKYBLUE:
				return sf::Color(0, 160, 255);
			case IVORY:
				return sf::Color(249, 223, 175);
			case SEAFOAM:
				return sf::Color(163, 255, 212);
			case INDIGO:
				return sf::Color(138, 148, 255);
			// Misc.
			case TAN:
				return sf::Color(214, 155, 91);
			case CHOCOLATE:
				return sf::Color(78, 42, 29);
			case CORAL:
				return sf::Color(255, 96, 81);
			case SEAMETAL:
				return sf::Color(96, 140, 132);
			// Default to white
			default:
				return sf::Color::White;
		}
	}


	// Convert from string to df::Color
	// This could be done more intelligently with a map
	static df::Color parseColor(std::string color_string)
	{
		// Default Colors
		if (color_string == "black") {
			return BLACK;
		} else if (color_string == "red") {
			return RED;
		} else if (color_string == "green") {
			return GREEN;
		} else if (color_string == "blue") {
			return BLUE;
		} else if (color_string == "yellow") {
			return YELLOW;
		} else if (color_string == "cyan") {
			return CYAN;
		} else if (color_string == "magenta") {
			return MAGENTA;
		} else if (color_string == "white") {
			return WHITE;
		// Custom Colors
		// Grays
		} else if (color_string == "ltgray" || color_string == "ltgrey") {
			return LTGREY;
		} else if (color_string == "gray" || color_string == "grey") {
			return GREY;
		} else if (color_string == "dkgray" || color_string == "dkgrey") {
			return DKGREY;
		} else if (color_string == "slate") {
			return SLATE;
		// Mids
		} else if (color_string == "midred") {
			return MIDRED;
		} else if (color_string == "midgreen") {
			return MIDGREEN;
		} else if (color_string == "midblue") {
			return MIDBLUE;
		} else if (color_string == "orange") {
			return ORANGE;
		} else if (color_string == "teal") {
			return TEAL;
		} else if (color_string == "purple") {
			return PURPLE;
		// Darks
		} else if (color_string == "burgundy") {
			return BURGUNDY;
		} else if (color_string == "dkgreen") {
			return DKGREEN;
		} else if (color_string == "dkblue") {
			return DKBLUE;
		} else if (color_string == "brown") {
			return BROWN;
		} else if (color_string == "navy") {
			return NAVY;
		} else if (color_string == "violet") {
			return VIOLET;
		// Pastels
		} else if (color_string == "pink") {
			return PINK;
		} else if (color_string == "lime") {
			return LIME;
		} else if (color_string == "skyblue") {
			return SKYBLUE;
		} else if (color_string == "ivory") {
			return IVORY;
		} else if (color_string == "seafoam") {
			return SEAFOAM;
		} else if (color_string == "indigo") {
			return INDIGO;
		// Misc.
		} else if (color_string == "tan") {
			return TAN;
		} else if (color_string == "chocolate") {
			return CHOCOLATE;
		} else if (color_string == "coral") {
			return CORAL;
		} else if (color_string == "seametal") {
			return SEAMETAL;
		// Other
		} else {
			return UNDEFINED_COLOR;
		}
	}
}