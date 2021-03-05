#pragma once
#include <SDL.h>
#include "Shader.h"
#include "Pixel.h"
#include "vec2d.h"
#include "vec3d.h"


namespace Engine
{
	// Fullscreen modes
	enum class FullscreenMode
	{
		WINDOWED          = 0,
		FULLSCREEN        = SDL_WINDOW_FULLSCREEN,
		FULLSCREEN_WINDOW = SDL_WINDOW_FULLSCREEN_DESKTOP
	};

	// Refresh rate modes
	enum class RefreshRate
	{
		REFRESH_RATE_GSYNC_FREESYNC = -1,
		REFRESH_RATE_UNLIMITED      =  0,
		REFRESH_RATE_VSYNC          =  1
	};

	// keyboard buttons
	enum class Key
	{
		MOUSE_LEFT = 0, MOUSE_RIGHT, MOUSE_MIDDLE,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		K0, K1, K2, K3, K4, K5, K6, K7, K8, K9, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9, NP_ENABLE, NP_DIVIDE, NP_MULITPLY, NP_MINUS, NP_PLUS, NP_ENTER, NP_DEL,
		ESCAPE, CIRCUMFLEX, TAB, CAPS_LOCK, LSHIFT, LCTRL, WINDOWS, ALT, SPACE, ALT_GR, RCTRL, RSHIFT, RETURN, BACKSPACE, APOSTROPHE, QUESTION_MARK,
		ARROW_RIGHT, ARROW_LEFT, ARROW_DOWN, ARROW_UP
	};

	struct HWKey
	{
		bool bPressed;
		bool bHeld;
		bool bReleased;
	};

	// 2D Vertex with texture Coordinates
	struct Vertex2D
	{
		float x, y;
		float u, v;
	};

	// 2D Vertex used for static color shapes
	struct Vertex2DC
	{
		float x, y;
	};

	struct Vertex
	{
		Engine::vf3d pos;
		Engine::vf3d normal;
	};

	// some standard color values
	// Pink colors
	static const Pixel
		BLACK  (  0,   0,   0), BLANK       (  0,   0,   0, 0), WHITE            (255, 255, 255),
		GREY   (192, 192, 192), DARK_GREY   (128, 128, 128   ), VERY_DARK_GREY   ( 64,  64,  64),
		RED    (255,   0,   0), DARK_RED    (128,   0,   0   ), VERY_DARK_RED    ( 64,   0,   0),
		YELLOW (255, 255,   0), DARK_YELLOW (128, 128,   0   ), VERY_DARK_YELLOW ( 64,  64,   0),
		GREEN  (  0, 255,   0), DARK_GREEN  (  0, 128,   0   ), VERY_DARK_GREEN  (  0,  64,   0),
		CYAN   (  0, 255, 255), DARK_CYAN   (  0, 128, 128   ), VERY_DARK_CYAN   (  0,  64,  64),
		BLUE   (  0,   0, 255), DARK_BLUE   (  0,   0, 128   ), VERY_DARK_BLUE   (  0,   0,  64),
		MAGENTA(255,   0, 255), DARK_MAGENTA(128,   0, 128   ), VERY_DARK_MAGENTA( 64,   0,  64);
}
