#pragma once
#include "framework/Actor.h"

namespace ss
{
	class BackgroundLayer : public Actor
	{
	public:
		BackgroundLayer(World* owningWorld, const List<std::string>& assetPaths = {},
			const sf::Vector2f& minVel = sf::Vector2f{ 0.f, 50.f },
			const sf::Vector2f& maxVel = sf::Vector2f{ 0.f, 200.f },
			float sizeMin = 1.f,
			float sizeMax = 2.f,
			int mSpriteCount = 20,
			const sf::Color& colorTint = sf::Color{ 180, 180, 200, 255 });

		void SetAssets(const List<std::string>& assetPaths);
		void SetColorTint(const sf::Color& color);
		void SetSpriteCount(int newCount);
	private:
		void RefreshSprites();
		void RandomSpriteTexture(sf::Sprite& sprite);
		void RandomSpriteTransform(sf::Sprite& sprite, bool randomY = false);
		void RandomSpritePosition(sf::Sprite& sprite, bool randomY);
		void RandomSpriteRotation(sf::Sprite& sprite);
		void RandomSpriteSize(sf::Sprite& sprite);
		shared<sf::Texture> GetRandomTexture() const;
		sf::Vector2f mMinVelocity;
		sf::Vector2f mMaxVelocity;
		float mSizeMin;
		float mSizeMax;
		int mSpriteCount;
		sf::Color mTintColor;

		List<shared<sf::Texture>> mTextures;
		List<sf::Sprite> mSprites;
		List<sf::Vector2f> mVelocities;
	};
}