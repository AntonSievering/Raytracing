#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

// GLM
#include <glm/glm.hpp>

// link with opengl32.lib, SDL2.lib & glew32s.lib
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")

// STL
#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <array>
#include <map>

#include "Defines.h"
#include "vec2d.h"
#include "vec3d.h"
#include "Pixel.h"
#include "Sprite.h"
#include "Camera.h"
#include "Shader.h"
#include "util.h"

// STB Image
#ifdef STB_IMAGE_IMPLEMENTATION
	#undef STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

struct SpriteShader
{
	Engine::Shader *shader;
	int colorUniformLocation;
	int textureUniformLocation;
};

namespace Engine
{
	class PixelEngine
	{
		using sys_clock = std::chrono::system_clock;
		using sys_clock_t = std::chrono::time_point<sys_clock>;

	private:
		// SDL Window which OpenGL is filling
		SDL_Window   *m_window;
		SDL_GLContext m_glContext;

		// Timing
		sys_clock_t m_tStart, m_tEnd;
		float m_fTimeToSetTitle;
		const float m_fTimeUpdateTitle = 1.0f;
		uint64_t m_nFPS;
		uint64_t m_nFramesSinceUpdate = 0;
		float m_fTimeSinceStart;
		float m_fElapsedTime;

		// input
		std::array<HWKey, 85>   m_vKeyStates;
		std::map<uint32_t, Key> m_mapKeys;
		float m_fWheelMovement = 0.0f;

		uint32_t m_nLehmerSeed = 0;

		vf2d m_relativeMouseMovement = { 0.0f, 0.0f };

	protected:
		// Grafics Card information:
		std::string m_sOpenGLVersion;
		std::string m_sGraficsCard;
		std::string m_sGraficsCardVendor;

		vi2d  m_vScreenSize;
		float m_fAspectRatio;
		vf2d  m_vMousePos;
		std::string m_sAppName = "Untitled (define m_sAppName to rename this title)";
			
	public:
		PixelEngine()                                      noexcept;

	public:
		bool SetRefreshRate(int16_t refresh)               noexcept;

	public:
		// Need to be overriden
		virtual bool OnUserCreate()                        noexcept;
		virtual bool OnUserUpdate(float fElapsedTime)      noexcept;
		virtual bool OnUserDestroy()                       noexcept;

	public:
		bool     Construct(vu2d size, FullscreenMode fullscreen, RefreshRate refresh) noexcept; // Prepares the Engine, returns true when succeeds
		void     Start()                                   noexcept;                            // Starts the Engine
		void     Clear(const Pixel &col)                   noexcept;                            // Clears the screen to the specified color
		
		HWKey    GetKey(const Key &key)              const noexcept;	                        // Returns the key states of the requested Key
		bool     KeyIsPressedOrHeld(const Key &key)  const noexcept;                            // Returns whether the Key is pressed or held
		vf2d     GetMouse()                          const noexcept;	                        // Returns the x and y mouse position in OpenGL space
		float    GetMouseX()                         const noexcept;	                        // Returns the x mouse position in OpenGL space
		float    GetMouseY()                         const noexcept;	                        // Returns the y mouse position in OpenGL space
		float    GetMouseWheel()                     const noexcept;                            // Returns the normalized mouse wheel movement
		uint64_t GetFPS()                            const noexcept;	                        // Returns the current FPS
		vf2d     GetRelativeMouse()                  const noexcept;                            // Returns the mouse movement since the last frame
		float    GetRelativeMouseX()                 const noexcept;                            // Returns the relative x mouse movement
		float    GetRelativeMouseY()                 const noexcept;                            // Returns the relative y mouse movement
		void     HideMouse(const bool &bHide)              noexcept;                            // Returns 1: hides the mouse, 0: shows it
		bool     GetHideMouseStatus()                const noexcept;                            // Returns whether the mouse is currently hided

		vf2d     toOpenGL(const vf2d &pos)           const noexcept;	                        // Translates screen to OpenGL space

		float    GetElapsedTime()                    const noexcept;                            // Returns the elapsed time
		float    GetTimeSinceStart()                 const noexcept;                            // Returns the time since the start of the engine

		uint32_t Lehmer()                                  noexcept;                            // a very fast 32-bit random number method
		float    LehmerF()                                 noexcept;                            // a very fast floating point 32-bit random number method
		uint32_t random()                                                                noexcept;
		uint32_t random(const uint32_t &nUpperLimit)                                     noexcept;
		uint32_t random(const uint32_t &nLowerLimit, const uint32_t &nUpperLimit)        noexcept;
		float    randomf()                                                               noexcept;
		float    randomf(const float &fUpperLimit)                                       noexcept;
		float    randomf(const float &fLowerLimit, const float &fUpperLimit)             noexcept;

	private:
		void MainGameLoop()                                noexcept;
		bool ScanHardware()                                noexcept;
		void UpdateTitle ()                                noexcept;
	};
}
