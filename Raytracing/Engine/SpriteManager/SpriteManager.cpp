#include "SpriteManager.h"

namespace Engine
{
	SpriteManager::SpriteManager() noexcept
	{
		m_sprites = SpriteMap();
	}

	SpriteManager::~SpriteManager() noexcept
	{
		for (const SpriteEntry &vEntry : m_sprites)
			delete vEntry.second;
	}

	bool SpriteManager::contains(const string &sFilename) const noexcept
	{
		return m_sprites.contains(sFilename);
	}

	void SpriteManager::load(const string &sFilename) noexcept
	{
		auto ReplaceInString = [](string str)
		{
			for (size_t i = 0; i < str.size(); i++)
				if (str.at(i) == '\\')
					str.at(i) = '/';
			return str;
		};

		string filename = ReplaceInString(sFilename);

		if (!contains(filename))
			m_sprites.insert(std::make_pair(filename, new Sprite(filename)));
	}

	Sprite *SpriteManager::query(string sFilename) const noexcept
	{
		if (m_sprites.contains(sFilename))
			return m_sprites.at(sFilename);

		std::cout << "file " << sFilename << " not loaded\n";

		return nullptr;
	}

	void SpriteManager::load_dir(const string &sFilename) noexcept
	{
		try
		{
			for (cdir_en &entry : dir_it(sFilename))
				load(entry.path().string());
		}
		catch (...)
		{
			std::cout << "Error with the folder " << sFilename << "." << std::endl;
		}
	}

	void SpriteManager::cleanup() noexcept
	{
		for (const SpriteEntry &entry : m_sprites)
			delete entry.second;
		m_sprites.clear();
	}
}
