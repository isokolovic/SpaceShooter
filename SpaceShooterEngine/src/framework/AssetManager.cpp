#include "framework/AssetManager.h"

namespace ss
{
	unique<AssetManager> AssetManager::assetManager{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!assetManager) {
			assetManager = std::move(unique<AssetManager>{new AssetManager});
		}

		return *assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		auto found = mLoadedTextureMap.find(path);

		if (found != mLoadedTextureMap.end()) {
			return found->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(mRootDirectory + path)) {
			mLoadedTextureMap.insert({ path, newTexture });

			return newTexture;
		}

		return shared<sf::Texture>{nullptr};
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& path)
	{
		auto found = mLoadedFontMap.find(path);

		if (found != mLoadedFontMap.end()) {
			return found->second;
		}

		shared<sf::Font> newFont{ new sf::Font };
		if (newFont->loadFromFile(mRootDirectory + path)) {
			mLoadedFontMap.insert({ path, newFont });

			return newFont;
		}

		return shared<sf::Font>{nullptr};
	}

	void AssetManager::CleanCycle()
	{
		for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();) {
			if (iter->second.unique()) //Nobody is holding a Texture shared pointer
			{
				LOG("Cleaning texture: %s", iter->first.c_str());
				iter = mLoadedTextureMap.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		for (auto iter = mLoadedFontMap.begin(); iter != mLoadedFontMap.end();) {
			if (iter->second.unique())
			{
				LOG("Cleaning font: %s", iter->first.c_str());
				iter = mLoadedFontMap.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void AssetManager::SetAssetRootDirectory(std::string& directory)
	{
		mRootDirectory = directory;
	}

	AssetManager::AssetManager()
		: mRootDirectory{}
	{
	}
}