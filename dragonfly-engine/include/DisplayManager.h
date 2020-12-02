#pragma once
#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Vector.h"
#include "Manager.h"

namespace df {

	// Two-letter access macro
#define DM DisplayManager::getInstance()

	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar|sf::Style::Close;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";
	const int DEFAULT_CHARACTER_SIZE = 32;

	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};

	class DisplayManager : public Manager {

	private:
		DisplayManager();						// Private (a singleton)
		DisplayManager(DisplayManager const&);	// Don’t allow copy
		void operator=(DisplayManager const&);	// Don’t allow assignment
		sf::Color m_background_color;	// Background color for screen
		sf::Font m_font;	// Font used for ASCII graphics
		sf::RenderWindow * m_p_window;	// Pointer to SFML window
		float m_character_scale_x;		// The height factor of a text character
		float m_character_scale_y;		// The width factor of a text character
		int m_window_horizontal_pixels;	// Horizontal pixels in window
		int m_window_vertical_pixels;	// Vertical pixels in window
		int m_window_horizontal_chars;	// Horizontal ASCII spaces in window
		int m_window_vertical_chars;	// Vertical ASCII spaces in window
		std::string m_window_title;		// Title displayed on the window

	public:
		~DisplayManager();

		static DisplayManager& getInstance();

		// Open graphics window, ready for text−based display
		// Return 0 if ok, else −1
		int startUp();

		// Close graphics window
		void shutDown();
		
		// WINDOW FUNCTIONS

		// Set the window’s horizontal maximum (in characters)
		// USABLE ONLY WHILE SHUT DOWN
		int setHorizontal(int new_horizontal_chars);

		// Return window’s horizontal maximum (in characters)
		int getHorizontal() const;
		
		// Set the window’s vertical maximum (in characters)
		// USABLE ONLY WHILE SHUT DOWN
		int setVertical(int new_vertical_chars);

		// Return window’s vertical maximum (in characters)
		int getVertical() const;
		
		// Set the window’s horizontal maximum (in pixels)
		// USABLE ONLY WHILE SHUT DOWN
		int setHorizontalPixels(int new_horizontal_pixels);

		// Return window’s horizontal maximum (in pixels)
		int getHorizontalPixels() const;
		
		// Set the window’s vertical maximum (in pixels)
		// USABLE ONLY WHILE SHUT DOWN
		int setVerticalPixels(int new_vertical_pixels);

		// Return window’s vertical maximum (in pixels)
		int getVerticalPixels() const;
		
		// Set the window’s title
		// USABLE ONLY WHILE SHUT DOWN
		int setWindowTitle(std::string new_title);

		// Return pointer to SFML graphics window
		sf::RenderWindow* getWindow() const;

		// TEXT FUNCTIONS

		// Create a new piece of text using the current formatting settings
		sf::Text makeText(std::string text, Color color=WHITE) const;
		sf::Text makeText(char text, Color color=WHITE) const;
		
		// DRAWING FUNCTIONS

		// Set defauly background color
		// Return 0 if ok, -1 if false
		int setBackgroundColor(Color color);

		// Draw character at window character location (x, y) with color
		// Return 0 if ok, else −1
		int drawCh(Vector world_pos, char ch, Color color=WHITE) const;

		// Draw string at window location (x, y) with default color
		// Justified left, center or right
		// Return 0 if ok, else −1.
		int drawString(Vector pos, std::string str, Justification just, Color color=WHITE) const;

		// Render current window buffer
		// Return 0 if ok, else −1
		int swapBuffers();

		// UTILITY FUNCTIONS

		// Compute character height, based on window size and font
		float charHeight() const;
		
		// Compute character width, based on window size and font
		float charWidth() const;
		
		// Convert ASCII spaces (x, y) to window pixels (x, y)
		Vector spacesToPixels(Vector spaces) const;
		
		// Convert window pixels (x, y) to ASCII spaces (x, y)
		Vector pixelsToSpaces(Vector pixels) const;
	};
}