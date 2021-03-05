#pragma once
#include "../Sprite.h"
#include <map>

// Filesystem
#if _MSC_VER >= 1920 && _MSVC_LANG >= 201703L
	#include <filesystem>
	namespace fs = std::filesystem;
#else
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem::v1;
#endif


namespace Engine
{
	class SpriteManager
	{
		using SpriteMap = std::map<std::string, Engine::Sprite*>;
		using SpriteEntry = std::pair<std::string, Sprite*>;
		using dir_it = fs::directory_iterator;
		using cdir_en = const fs::directory_entry;
		using string = std::string;
		
	private:
		SpriteMap m_sprites;

	public:
		SpriteManager() noexcept;
		~SpriteManager() noexcept;

	public:
		bool contains(const string &sFilename) const noexcept;
		void load(const string &sFilename) noexcept;

		Sprite *query(string sFilename) const noexcept;
		void load_dir(const string &sFilename) noexcept;

		void cleanup() noexcept;
	};
}


