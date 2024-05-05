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
		return LoadAsset(path, mLoadedTextureMap);
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& path)
	{
		return LoadAsset(path, mLoadedFontMap);
	}

	void AssetManager::CleanCycle()
	{
		CleanUniqueref(mLoadedFontMap);
		CleanUniqueref(mLoadedTextureMap);
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