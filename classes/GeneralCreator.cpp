#include "GeneralCreator.h"
USING_NS_CC;

GCreator* s_SharedGeneralCreator = nullptr;

GCreator* GCreator::getInstance()
{
	if (s_SharedGeneralCreator == nullptr)
	{
		s_SharedGeneralCreator = new (std::nothrow) GCreator;
		CCASSERT(s_SharedGeneralCreator, "not enough memory");
		s_SharedGeneralCreator->visibleSize = Director::getInstance()->getVisibleSize();
		s_SharedGeneralCreator->origin = Director::getInstance()->getVisibleOrigin();
	}

	return s_SharedGeneralCreator;
}

// Print useful error message instead of segfaulting when files are not there.
void GCreator::problemLoading(const std::string filename)
{
    log("Error while loading: %s\n", filename.data());
    log("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

MenuItemImage* GCreator::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float x, const float y, const float anchorX, const float anchorY)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);

    if (item == nullptr || item->getContentSize().width <= 0 || item->getContentSize().height <= 0)
        problemLoading("'" + normalImage + "' and '" + selectedImage);
    else
    {
        item->setAnchorPoint({ anchorX, anchorY });
        item->setPosition(origin.x + x, origin.y + y);
    }

    return item;
}

Label* GCreator::createLabel(const std::string& text, const std::string& font, const float fontSize, const float x, const float y, const float anchorX, const float anchorY)
{
    //暂时只实现了TTF文本标签
    auto label = Label::createWithTTF(text, font, fontSize);
    if (label == nullptr)
        problemLoading("'" + font + "'");
    else
    {
        label->setAnchorPoint({ anchorX, anchorY });
        label->setPosition(origin.x + x, origin.y + y);
    }

    return label;
}

Sprite* GCreator::createSprite(const std::string& image, const float x, const float y, const float anchorX, const float anchorY)
{
    auto sprite = Sprite::create(image);
    if (sprite == nullptr)
        problemLoading(image);
    else
    {
        sprite->setAnchorPoint({ anchorX, anchorY });
        sprite->setPosition(origin.x + x, origin.y + y);
    }

    return sprite;
}
