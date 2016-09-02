#include "../../h/UI/ContainerViewUI.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

void ContainerViewUI::draw()
{
	for (std::list<ViewUI*>::const_iterator i=children.begin(); i!=children.end(); i++)
	{
		if ((*i)->getIfActive())
			(*i)->draw();
	}
	
	drawFrame();
}

void ContainerViewUI::update()
{
	for (std::list<ViewUI*>::const_iterator i=children.begin(); i!=children.end(); i++)
	{
		if ((*i)->getIfActive())
			(*i)->update();
	}
	
	updateFrame();
}

void ContainerViewUI::addChild(ViewUI * childIn)
{
	children.push_back(childIn);
	childIn->setIO(surface, input);
	childIn->setActive(true);
	
	((ContainerViewUI *)childIn)->parent=this;
	//thats right, I cast childIn to a type its not so I can get at a protected member of the base class
	//You think thats one of the worst C++ hacks you've ever seen? Well, fuck you!
	
	childIn->calcAndSetDim();
	
	childChanged();
}

void ContainerViewUI::removeChild(ViewUI * childIn)
{
	std::list<ViewUI*>::const_iterator i=children.begin();
	
	while ((*i)!=childIn)
	{
		if (i==children.end())
		{
			err << "attempted to remove child frim ViewUI, but couldn't find it" << err;
			return;
		}
		
		++i;
	}
	
	childIn->setActive(false);
	((ContainerViewUI *)childIn)->parent=nullptr;
	childIn->setIO(nullptr, nullptr);
	childIn->calcAndSetDim();
	
	children.erase(i);
	
	childChanged();
}

void ContainerViewUI::ioChanged()
{
	for (std::list<ViewUI*>::const_iterator i=children.begin(); i!=children.end(); i++)
	{
		(*i)->setIO(surface, input);
	}
}

}


