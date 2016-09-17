#include "DebugDraw.h"


DebugDraw* DebugDraw::p_myinstance = nullptr;
bool DebugDraw::isDebug = true;

DebugDraw::DebugDraw()
{

}

DebugDraw* DebugDraw::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new DebugDraw();
		if (p_myinstance && p_myinstance->init())
		{
			p_myinstance->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(p_myinstance);
		}
	}
	return p_myinstance;
}

bool DebugDraw::init()
{
	if (isDebug){

		debugLabel = Label::createWithTTF("debugdata:", "fonts/arial.ttf", 16);
		debugLabel->setColor(Color3B::RED);
		debugLabel->setAnchorPoint(Point(0, 0));
		debugLabel->setPosition(0, 200);
		this->addChild(debugLabel, 9999);

		debugDrawNode = DrawNode::create();
		this->addChild(debugDrawNode);
	}

	return true;
}

DrawNode* DebugDraw::getDrawNode()
{
	return this->debugDrawNode;
}

Label* DebugDraw::getLabel()
{
	return this->debugLabel;
}
