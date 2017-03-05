#include "GridView.h"

USING_NS_CC;
using namespace cocos2d::ui;




Padding::Padding()
{ 
	top = left = right = bottom = 0; 
}

Padding::Padding(float top, float left)
{
	this->top = top;
	this->left = left;
	right = bottom = 0;
}

Padding::Padding(float top, float left, float right, float bottom)
{
	this->top = top;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
}

Padding::~Padding(){}

const Padding Padding::ZERO = Padding(0, 0);


GridView::GridView(){ };
GridView::~GridView(){};





