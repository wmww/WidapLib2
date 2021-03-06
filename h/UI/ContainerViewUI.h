
#pragma once

#include "ViewUI.h"
#include <list>

namespace widap
{

class ContainerViewUI: public ViewUI
{

///for subclasses to override

public:
	//be sure you call these in the functions that override them
	virtual void update();
	virtual void drawBknd();
	virtual void draw();

protected:
	
	//sets the rects of all the children
	virtual void setChildRects()=0;
	
	
///for subclasses to use

protected:
	
	std::list<ViewUI*> children;
	
	virtual void addChildToList(ViewUI * childIn);
	virtual void removeChildFromList(const std::list<ViewUI*>::const_iterator& i);
	virtual void removeChildFromList(ViewUI * childIn);
	
///internal

public:
	
	ThemeUI::Container theme=getThemeUI().container;
	
	ContainerViewUI();
	
	bool contentsChanged()
	{
		if (!setDim(calcDim()))
		{
			setChildRects();
			return false;
		}
		else
			return true;
	}
	
protected:
	
	void rectChanged() {setChildRects();};
	bool calcAndSetDimRecursive();
	
private:
	
	void ioChanged();
};

}

