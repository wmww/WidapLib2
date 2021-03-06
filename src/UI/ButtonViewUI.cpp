
#include "../../h/UI/ButtonViewUI.h"
#include "../../h/UI/ThemeUI.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

ButtonViewUI::ButtonViewUI()
{
	
}

void ButtonViewUI::setText(const string& textIn)
{
	text=textIn;
	contentsChanged();
}

V2d ButtonViewUI::calcDim()
{	
	if (surface)
	{
		return surface->text()->getBounds(text, theme.textUnselect.height)+theme.buffer*2;
	}
	else
		return V2d();
}

void ButtonViewUI::draw()
{
	if (!surface)
	{
		err << "called ButtonViewUI::draw() called with null surface" << err;
		return;
	}
	
	V2d low=getLow(), hgh=getHgh();
	
	surface->rect(low, hgh, clicked?theme.bkndSelect:theme.bkndUnselect);
	surface->text()->setStyle(clicked?theme.textSelect:theme.textUnselect);
	surface->text()->setPos(low, hgh, TextBase::CENTER_X, TextBase::CENTER_Y, TextBase::SHRINK_TO_BOUNDS);
	surface->text()->draw(text);
}

void ButtonViewUI::update()
{
	V2d low=getLow(), hgh=getHgh();
	
	if (input->mouseLoc().isInRect(low, hgh) && input->lClick())
	{
		clicked=true;
		if (clickAction)
			clickAction();
	}
	else
	{
		clicked=false;
	}
}

}

