#pragma once
#include "stdfax.h"
#include "ResourceLoader.h"

struct AnimateData;

class AnimateManager : public ResourceLoader
{
public:
	//µ¥ÀýÄ£Ê½
	static AnimateManager* getInstance();
	~AnimateManager();

	virtual void LoadResource();
	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);

	void playAnimate(const Name& animateName, Sprite* sprite, float playtime = 0, CallFunc* callFunc = nullptr);


private:
	AnimateManager();
	static AnimateManager* p_myinstance;
	std::map<Name, AnimateData> animateData;

	Animation* createAnimation(const Name& animateName);
};

