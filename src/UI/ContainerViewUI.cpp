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
}

void ContainerViewUI::update()
{
	for (std::list<ViewUI*>::const_iterator i=children.begin(); i!=children.end(); i++)
	{
		if ((*i)->getIfActive())
			(*i)->update();
	}
}

void ContainerViewUI::addChildToList(ViewUI * childIn)
{
	children.push_back(childIn);
	childIn->setIO(surface, input);
	childIn->setActive(true);
	
	((ContainerViewUI*)childIn)->parent=this;
	//thats right, I cast childIn to a type its not so I can get at a protected member of the base class
	//You think thats one of the worst C++ hacks you've ever seen? Well, fuck you!
	
	childIn->calcAndSetDim();
	
	childChanged();
}

void ContainerViewUI::removeChildFromList(const std::list<ViewUI*>::const_iterator& i)
{
	(*i)->setActive(false);
	((ContainerViewUI*)(*i))->parent=nullptr;
	(*i)->setIO(nullptr, nullptr);
	(*i)->calcAndSetDim();
	
	children.erase(i);
	
	childChanged();
}

void ContainerViewUI::removeChildFromList(ViewUI * childIn)
{
	if (children.size()<1)
	{
		err << "children list is empty when attempt was made to remove child" << err;
		return;
	}
	
	std::list<ViewUI*>::const_iterator i=children.end();
	--i;
	
	while ((*i)!=childIn)
	{
		if (i==children.begin())
		{
			err << "attempted to remove child frim ViewUI, but couldn't find it" << err;
			return;
		}
		
		--i;
	}
	
	removeChildFromList(i);
}

void ContainerViewUI::ioChanged()
{
	for (std::list<ViewUI*>::const_iterator i=children.begin(); i!=children.end(); i++)
	{
		(*i)->setIO(surface, input);
	}
}

}


