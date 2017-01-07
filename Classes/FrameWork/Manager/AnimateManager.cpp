#include "AnimateManager.h"

#include "json/rapidjson.h"
#include "json/document.h"

using namespace cocosgalaxy;

struct cocosgalaxy::AnimateData {
	//string name;
	double delay;
	int framecount;
	int repeat;
	struct Framedata {
		std::string name;
		Vec2 offset;
		Framedata(void) :name(""), offset(0,0){}
	};
	std::vector<Framedata> framedata;
	AnimateData(void) :/*name(""),*/ delay(0), framecount(0), repeat(1){}
};

AnimateManager* AnimateManager::p_myinstance = nullptr;

AnimateManager* AnimateManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new AnimateManager();
	}
	return p_myinstance;
}

AnimateManager::AnimateManager()
{
}

AnimateManager::~AnimateManager()
{
}

Animation* AnimateManager::createAnimation(const Name& animateName)
{
	CCASSERT(animateData.find(animateName) != animateData.end(), string("Animate :[" + animateName + "] NOT found").c_str());

	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameVec;
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	const AnimateData& data = animateData[animateName];

	for (int i = 0; i < data.framecount; ++i)
	{
		frame = frameCache->getSpriteFrameByName(data.framedata[i].name);
		CCASSERT(frame != nullptr, string("SpriteFrame :[" + data.framedata[i].name + "] NOT found").c_str());

		//根据缩放比例调整偏移
		float scale = Director::getInstance()->getContentScaleFactor();
		Vec2 vec = (frame->getOffsetInPixels() + data.framedata[i].offset)/scale;
		frame->setOffset(vec);
		frameVec.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(frameVec, data.delay, data.repeat);
}


void AnimateManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void AnimateManager::LoadResource(const vector<Name>& resNameList)
{

	//1.打开文件
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/Animate.json");
	CCASSERT(!data.isNull(), "[Animate.json] Lost!");

	//2.载入json
	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("animatedata"), "illegal [Animate.json]");

	//3.读取json数据
	std::map<string,AnimateData> animatedata;
	for (int i = 0; i < (int)root["animatedata"].Size(); i++) {
		JsonNode jNode = root["animatedata"][i];
		string name = jNode["name"].GetString();
		//animatedata[i].name = root["animatedata"][i]["name"].GetString();
		animatedata[name].delay = jNode["delay"].GetDouble();
		animatedata[name].repeat = jNode["repeat"].GetInt();

		int size = jNode["framedata"].Size();
		CCASSERT(size != 0, "framecount must NOT equal 0");
		animatedata[name].framedata.resize(size);
		animatedata[name].framecount = size;
		//animatedata[name].framecount = root["animatedata"][i]["framecount"].GetInt();
		//CCASSERT(animatedata[name].framecount != 0 && size != 0, "framecount must NOT equal 0");
		for (int j = 0; j<size; j++) {
			JsonNode node = jNode["framedata"][j];
			animatedata[name].framedata[j].name = node["name"].GetString();
			animatedata[name].framedata[j].offset.x = node["x"].GetDouble();

			//此处翻转Y轴（cocos的原点在左下角，偏移是相对图片左上角的）
			animatedata[name].framedata[j].offset.y = -node["y"].GetDouble();
		}
	}
	
	//4.载入需要的animateData
	AnimationCache* animationCache = AnimationCache::getInstance();
	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;
	if (fullLoad)
	{
		for (auto& var : animatedata)
		{
			string name = var.first;
			this->animateData[name] = animatedata[name];
			if (animatedata[name].delay > 0 && animatedata[name].framecount > 1)
				animationCache->addAnimation(createAnimation(name), name);
		}
	}
	else
		for (string name : resNameList)
		{
			CCASSERT(animatedata.find(name) != animatedata.end(), string(name + "animateData NOT exists").c_str());
			this->animateData[name] = animatedata[name];
			if (animatedata[name].delay > 0 && animatedata[name].framecount > 1)
				animationCache->addAnimation(createAnimation(name), name);
		}
}

void AnimateManager::FreeAllResource()
{
	animateData.clear();
	AnimationCache::getInstance()->destroyInstance();
}

void AnimateManager::FreeResource(const vector<Name>& resName)
{
	AnimationCache* animationCache = AnimationCache::getInstance();

	for (auto name : resName)
	{
		animateData.erase(name);
		animationCache->removeAnimation(name);
	}
}

void AnimateManager::playAnimate(const Name& animateName, Sprite* sprite, float playtime, CallFunc* callFunc)
{
	CCASSERT(sprite != nullptr, "[AnimateManager::createAnimate]: Sprite is null");
	CCASSERT(animateData.find(animateName) != animateData.end(), string("[AnimateManager::createAnimate] Animate [" + animateName + "] NOT found").c_str());
	
	if (animateData[animateName].framecount > 1)
	{
		//播放一段时间的动画
		Animation* animation = AnimationCache::getInstance()->getAnimation(animateName);
		ActionInterval* action = Animate::create(animation);
		if (callFunc != nullptr)
		{
			if (playtime > 0)
			{
				ActionInterval* action2 = Sequence::create(DelayTime::create(playtime), callFunc, NULL);
				action = Spawn::createWithTwoActions(action, action2);
			}
			else
				action = Sequence::create(action, DelayTime::create(.01f), callFunc, NULL);
		}
		sprite->runAction(action);
	}
	else
	{
		//单帧动画
		auto& data = animateData[animateName];
		SpriteFrame* s = SpriteFrameCache::getInstance()->getSpriteFrameByName(data.framedata[0].name)->clone();
		s->setOffset(data.framedata[0].offset / Director::getInstance()->getContentScaleFactor());
		sprite->setSpriteFrame(s);
		if (playtime > 0 && callFunc != nullptr)
			sprite->runAction(Sequence::create(DelayTime::create(playtime), callFunc, NULL));
	}
}


