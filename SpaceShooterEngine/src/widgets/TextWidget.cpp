#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"

namespace ss
{
	TextWidget::TextWidget(const std::string& textStr, const std::string& fontPath, unsigned int charSize)
		: mFont{AssetManager::Get().LoadFont(fontPath)},
		mText{textStr, *(mFont.get()), charSize}
	{

	}

	void TextWidget::SetString(const std::string& newStr)
	{
		mText.setString(newStr);
	}

	void TextWidget::SetTextSize(unsigned int newSize)
	{
		mText.setCharacterSize(newSize);
	}

	void TextWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		mText.setPosition(newLocation);
	}

	void TextWidget::RotationUpdated(float newRotation)
	{
		mText.setRotation(newRotation);
	}

	void TextWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mText);
	}
}
