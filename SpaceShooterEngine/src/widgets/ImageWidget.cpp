#include "framework/AssetManager.h"
#include "widgets/ImageWidget.h"

namespace ss
{
	ImageWidget::ImageWidget(const std::string& imagePath)
		: mTexture{ AssetManager::Get().LoadTexture(imagePath) },
		mSprite{ *(mTexture.get()) }
	{
	}

	void ImageWidget::SetImage(const shared<sf::Texture>& newTexture)
	{
		if (newTexture)
		{
			mTexture = newTexture;
			mSprite.setTexture(*(mTexture.get()));
		}
	}

	void ImageWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
	}

	void ImageWidget::RotationUpdated(float newRotation)
	{
		mSprite.setRotation(newRotation);
	}

	void ImageWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mSprite);
	}
}