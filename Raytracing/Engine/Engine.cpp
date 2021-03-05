#define STB_IMAGE_IMPLEMENTATION
#include "Engine.h"

namespace Engine
{
	PixelEngine::PixelEngine() noexcept
	{
		m_window    = nullptr;
		m_glContext = SDL_GLContext();

		m_sAppName = std::string();
		m_fElapsedTime    = 0.0f;
		m_fTimeSinceStart = 0.0f;
		m_nFPS            =    0;
	}

	bool PixelEngine::Construct(vu2d size, FullscreenMode fullscreen, RefreshRate refresh) noexcept
	{
		// Init SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,    32);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);

		// Create window & GLContext
		m_window = SDL_CreateWindow("C++ Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_OPENGL | (uint32_t)fullscreen);
		if (m_window == nullptr)
			return false;

		m_glContext = SDL_GL_CreateContext(m_window);
		SetRefreshRate((int16_t)refresh);

		// get the screen size
		if (fullscreen == FullscreenMode::FULLSCREEN_WINDOW)
		{
			SDL_DisplayMode dm;
			SDL_GetCurrentDisplayMode(0, &dm);
			m_vScreenSize.x = dm.w;
			m_vScreenSize.y = dm.h;
		}
		else
		{
			m_vScreenSize = size;
		}
		m_fAspectRatio = (float)m_vScreenSize.x / (float)m_vScreenSize.y;

		// Init glew
		if (glewInit() != GLEW_OK)
			return false;

		// get some information about the user
		m_sOpenGLVersion     = (const char *)glGetString(GL_VERSION);
		m_sGraficsCard       = (const char *)glGetString(GL_RENDERER);
		m_sGraficsCardVendor = (const char *)glGetString(GL_VENDOR);

		
		for (uint32_t i = 0; i < m_vKeyStates.size(); i++)
			m_vKeyStates.at(i) = HWKey();
		
		m_mapKeys =
		{
			{ 0, Engine::Key::MOUSE_LEFT }, { 1, Engine::Key::MOUSE_RIGHT }, { 2, Engine::Key::MOUSE_MIDDLE },
			{ 97,  Engine::Key::A }, { 98,  Engine::Key::B }, { 99,  Engine::Key::C }, { 100, Engine::Key::D }, { 101, Engine::Key::E }, { 102, Engine::Key::F }, { 103, Engine::Key::G }, { 104, Engine::Key::H },	{ 105, Engine::Key::I },
			{ 106, Engine::Key::J }, { 107, Engine::Key::K }, { 108, Engine::Key::L }, { 109, Engine::Key::M }, { 110, Engine::Key::N }, { 111, Engine::Key::O }, { 112, Engine::Key::P }, { 113, Engine::Key::Q }, { 114, Engine::Key::R },
			{ 115, Engine::Key::S }, { 116, Engine::Key::T }, { 117, Engine::Key::U }, { 118, Engine::Key::V }, { 119, Engine::Key::W }, { 120, Engine::Key::X }, { 121, Engine::Key::Y }, { 122, Engine::Key::Z },
			
			{ 48,  Engine::Key::K0 }, { 49,  Engine::Key::K1 }, { 50,  Engine::Key::K2 }, { 51,  Engine::Key::K3 }, { 52,  Engine::Key::K4 }, { 53,  Engine::Key::K5 }, { 54,  Engine::Key::K6 }, { 55,  Engine::Key::K7 }, { 56,  Engine::Key::K8 }, { 57,  Engine::Key::K9 },
			
			{ 1073741882, Engine::Key::F1            }, { 1073741883, Engine::Key::F2          }, { 1073741884, Engine::Key::F3           }, { 1073741885, Engine::Key::F4        }, { 1073741886, Engine::Key::F5          }, { 1073741887, Engine::Key::F6  },
			{ 1073741889, Engine::Key::F7            }, { 1073741890, Engine::Key::F8          }, { 1073741891, Engine::Key::F9           }, { 1073741892, Engine::Key::F10       }, { 1073741893, Engine::Key::F11         }, { 1073741894, Engine::Key::F12 },
			
			{ 1073741907, Engine::Key::NP_ENABLE     }, { 1073741908, Engine::Key::NP_DIVIDE   }, { 1073741909,  Engine::Key::NP_MULITPLY }, { 1073741910,  Engine::Key::NP_MINUS },
			{ 1073741911, Engine::Key::NP_PLUS       }, { 1073741912, Engine::Key::NP_ENTER    }, { 1073741923,  Engine::Key::NP_DEL      },
			
			{ 27,         Engine::Key::ESCAPE        }, { 94,         Engine::Key::CIRCUMFLEX  }, { 9,           Engine::Key::TAB         }, { 1073741881, Engine::Key::CAPS_LOCK }, { 1073742049,  Engine::Key::LSHIFT     },
			{ 1073742048, Engine::Key::LCTRL         }, { 1073742051, Engine::Key::WINDOWS     }, { 1073742050,  Engine::Key::ALT         }, { 32,         Engine::Key::SPACE     }, { 1073742054,  Engine::Key::ALT_GR     },
			{ 1073742052, Engine::Key::RCTRL         }, { 1073742053, Engine::Key::RSHIFT      }, { 13,          Engine::Key::RETURN      }, { 8,          Engine::Key::BACKSPACE }, { 180,  Engine::Key::APOSTROPHE        },
			{ 223,        Engine::Key::QUESTION_MARK }, { 1073741903, Engine::Key::ARROW_RIGHT }, { 1073741904,  Engine::Key::ARROW_LEFT  }, { 1073741906, Engine::Key::ARROW_UP  }, { 1073741905,  Engine::Key::ARROW_DOWN }
		};

		// enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// seed is a random idx in RAM
		m_nLehmerSeed = (uint32_t)this;

		return true;
	}
	
	bool PixelEngine::SetRefreshRate(int16_t refresh) noexcept
	{
		return SDL_GL_SetSwapInterval(refresh) == 0;
	}

	bool PixelEngine::OnUserCreate() noexcept
	{
		return true;
	}
	bool PixelEngine::OnUserUpdate(float fElapsedTime) noexcept
	{
		return true;
	}
	bool PixelEngine::OnUserDestroy() noexcept
	{
		return true;
	}
	
	void PixelEngine::Start() noexcept
	{
		// call OnUserCreate()
		if (!OnUserCreate())
			return;

		m_tStart = sys_clock::now();
		m_fTimeSinceStart = 0.0f;
		m_fElapsedTime    = 0.0f;
		m_nFPS            =    0;

		MainGameLoop();
	}

	void PixelEngine::Clear(const Pixel &col) noexcept
	{
		glClearColor((float)col.r / 255.0f, (float)col.g / 255.0f, (float)col.b / 255.0f, (float)col.a / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	HWKey PixelEngine::GetKey(const Key &key) const noexcept
	{
		return m_vKeyStates.at((std::size_t)key);
	}
	bool PixelEngine::KeyIsPressedOrHeld(const Key &key) const noexcept
	{
		return GetKey(key).bPressed || GetKey(key).bHeld;
	}

	vf2d PixelEngine::GetMouse() const noexcept
	{
		return m_vMousePos;
	}

	float PixelEngine::GetMouseX() const noexcept
	{
		return m_vMousePos.x;
	}
	
	float PixelEngine::GetMouseY() const noexcept
	{
		return m_vMousePos.y;
	}
	
	float PixelEngine::GetMouseWheel() const noexcept
	{
		return m_fWheelMovement;
	}

	uint64_t PixelEngine::GetFPS() const noexcept
	{
		return m_nFPS;
	}

	vf2d PixelEngine::GetRelativeMouse() const noexcept
	{
		return m_relativeMouseMovement;
	}

	float PixelEngine::GetRelativeMouseX() const noexcept
	{
		return m_relativeMouseMovement.x;
	}

	float PixelEngine::GetRelativeMouseY() const noexcept
	{
		return m_relativeMouseMovement.y;
	}

	void PixelEngine::HideMouse(const bool &bHide) noexcept
	{
		SDL_SetRelativeMouseMode((SDL_bool)bHide);
	}

	bool PixelEngine::GetHideMouseStatus() const noexcept
	{
		return SDL_GetRelativeMouseMode();
	}

	vf2d PixelEngine::toOpenGL(const vf2d &pos) const noexcept
	{
		return (((pos * 2) / m_vScreenSize) - vf2d(1.0f, 1.0f)) * vf2d(1.0f, -1.0f);
	}

	float PixelEngine::GetElapsedTime() const noexcept
	{
		return m_fElapsedTime;
	}

	float PixelEngine::GetTimeSinceStart() const noexcept
	{
		return m_fTimeSinceStart;
	}

	uint32_t PixelEngine::Lehmer() noexcept
	{
		return Lehmer32(m_nLehmerSeed);
	}
	float PixelEngine::LehmerF() noexcept
	{
		return Lehmer32f(m_nLehmerSeed);
	}

	uint32_t PixelEngine::random() noexcept
	{
		return Lehmer32(m_nLehmerSeed);
	}

	uint32_t PixelEngine::random(const uint32_t &nUpperLimit) noexcept
	{
		return random() % nUpperLimit;
	}

	uint32_t PixelEngine::random(const uint32_t &nLowerLimit, const uint32_t &nUpperLimit) noexcept
	{
		return nLowerLimit + random(nUpperLimit - nLowerLimit);
	}

	float PixelEngine::randomf() noexcept
	{
		return Lehmer32f(m_nLehmerSeed);
	}

	float PixelEngine::randomf(const float &fUpperLimit) noexcept
	{
		return fUpperLimit * randomf();
	}

	float PixelEngine::randomf(const float &fLowerLimit, const float &fUpperLimit) noexcept
	{
		return fLowerLimit + randomf(fUpperLimit - fLowerLimit);
	}

	void PixelEngine::MainGameLoop() noexcept
	{
		while (true)
		{
			// Handle input
			UpdateTitle();

			if (!ScanHardware() || !OnUserUpdate(m_fElapsedTime))
			{
				if (OnUserDestroy())
					return;
			}

			SDL_GL_SwapWindow(m_window);

			// Timing
			m_tEnd = sys_clock::now();
			uint64_t nNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(m_tEnd - m_tStart).count();
			m_fElapsedTime = (float)nNanos / 1e9f;
			m_tStart = m_tEnd;
		}
	}
	bool PixelEngine::ScanHardware() noexcept
	{
		m_relativeMouseMovement = vf2d();

		auto UpdateKey = [&](HWKey *key)
		{
			if (key->bPressed)
			{
				key->bHeld = true;
				key->bPressed = false;
			}
			key->bReleased = false;
		};

		for (uint32_t i = 0; i < m_vKeyStates.size(); i++)
			UpdateKey(&m_vKeyStates.at(i));

#ifndef _WIN64
		// not fast, but works
		// x86 build is not recommended anyways, so who cares
		auto MapContains = [&](const std::map<uint32_t, Key>& map, const uint32_t& val)
		{
			for (const std::pair<uint32_t, Key> &entry : map)
				if (entry.first == val)
					return true;

			return false;
		};
#endif
		
		// reset mouse wheel movement
		m_fWheelMovement = 0.0f;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return false;
			}
			// Key pressed
			else if (event.type == SDL_KEYDOWN)
			{
				uint32_t nKey = event.key.keysym.sym;

#ifdef _WIN64
				if (m_mapKeys.contains(nKey))
#else
				// x86 std::map has no "contains" member function
				if (MapContains(m_mapKeys, nKey))
#endif
				{
					uint32_t index = (std::size_t)m_mapKeys.at(nKey);
					HWKey *key = &m_vKeyStates.at(index);

					if (!key->bHeld)
						key->bPressed = true;
				}
#ifdef DO_DEBUG_MESSAGES
				else
				{
					std::cout << "Key " << nKey << " is not implemented yet" << std::endl;
				}
#endif
			}
			// Key released
			else if (event.type == SDL_KEYUP)
			{
				uint32_t nKey = event.key.keysym.sym;

#ifdef _WIN64
				if (m_mapKeys.contains(nKey))
#else
				// x86 std::map has no "contains" member function
				if (MapContains(m_mapKeys, nKey))
#endif
				{
					HWKey *key = &m_vKeyStates.at((std::size_t)m_mapKeys.at(nKey));

					key->bReleased = true;
					key->bHeld = false;
				}
#ifdef DO_DEBUG_MESSAGES
				else
				{
					std::cout << "Key " << nKey << " is not implemented yet" << std::endl;
				}
#endif
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					m_vKeyStates.at(0).bPressed = true;
					break;
				case SDL_BUTTON_RIGHT:
					m_vKeyStates.at(1).bPressed = true;
					break;
				case SDL_BUTTON_MIDDLE:
					m_vKeyStates.at(2).bPressed = true;
					break;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					m_vKeyStates.at(0).bHeld     = false;
					m_vKeyStates.at(0).bReleased = true;
					break;
				case SDL_BUTTON_RIGHT:
					m_vKeyStates.at(1).bHeld     = false;
					m_vKeyStates.at(1).bReleased = true;
					break;
				case SDL_BUTTON_MIDDLE:
					m_vKeyStates.at(1).bHeld     = false;
					m_vKeyStates.at(2).bReleased = true;
					break;
				}
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				m_relativeMouseMovement = { (float)event.motion.xrel, (float)event.motion.yrel };
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				if (event.wheel.y > 0)
					m_fWheelMovement = 1.0f;
				else
					m_fWheelMovement = -1.0f;
			}
		}
		
		int x, y;
		SDL_GetMouseState(&x, &y);

		m_vMousePos = toOpenGL(vf2d(x, y));

		return true;
	}
	
	void PixelEngine::UpdateTitle() noexcept
	{
		m_fTimeToSetTitle -= m_fElapsedTime;
		m_nFramesSinceUpdate++;

		if (m_fTimeToSetTitle < 0.0f)
		{
			SDL_SetWindowTitle(m_window, ("C++ Engine - " + m_sAppName + " - " + std::to_string(m_nFramesSinceUpdate) + "fps").c_str());
			
			m_nFPS = m_nFramesSinceUpdate;
			m_nFramesSinceUpdate = 0;
			m_fTimeToSetTitle = m_fTimeUpdateTitle;
		}
	}
}
