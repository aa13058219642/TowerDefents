#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

LoadingScene::LoadingScene()
{
	onBegan =nullptr;	
	onLoad = nullptr;
	onFinish=nullptr;	

	isLoading = false;
	isAutoStartLoad = true;

	resCount = 0;
	loadedCount = 0;

}

LoadingScene::~LoadingScene(){}

void LoadingScene::replaceScene(LoadingScene* scene)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)scene));
}



bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Layer* layer = Layer::create();
	Size size = Director::getInstance()->getVisibleSize();
	layer->setPosition(Point(size.width / 2, size.height / 2));

	Sprite* sprite = Sprite::create("ui/loading.png");
	sprite->runAction(RepeatForever::create(EaseBackOut::create(RotateBy::create(1.0f, 60))));
	sprite->setColor(Color3B(102, 204, 255));
	layer->addChild(sprite);

	Sprite* sprite2 = Sprite::create("ui/loading2.png");
	layer->addChild(sprite2);

	this->addChild(layer);

	return true;
}

void LoadingScene::onEnterTransitionDidFinish()
{
	if (isAutoStartLoad && !isLoading)
	{
		start();
	}
}

void LoadingScene::setAutoStartLoad(bool isAuto)
{
	isAutoStartLoad = isAuto;
}

void LoadingScene::bindBeginFunction(LoadingCallback callback)
{
	onBegan = callback;
}

void LoadingScene::bindLoadFunction(LoadingCallback callback)
{
	onLoad = callback;
}

void LoadingScene::bindFinishFunction(LoadingCallback callback)
{
	onFinish = callback;
}

void LoadingScene::setTextureLoadList(std::queue<std::string> list)
{
	q_texture = list;
}

void LoadingScene::setPlistLoadList(std::queue<std::string> list)
{
	q_plist = list;
}

void LoadingScene::setAudioLoadList(std::queue<std::string> list)
{
	q_audio = list;
}

void LoadingScene::setLambdaLoadList(std::queue<LoadingCallback> list)
{
	q_lambda = list;
}

void  LoadingScene::setData(ValueMap data)
{
	buffData = data;
}

ValueMap LoadingScene::getData()
{
	return buffData;
}

int LoadingScene::getResCount()
{
	return resCount;
}

int LoadingScene::getLoadedCount()
{
	return loadedCount;
}

float LoadingScene::getLoadingProgress()
{
	return getLoadedCount() / (float)getResCount();
}


void LoadingScene::start()
{
	resCount = q_texture.size() + q_plist.size() + q_audio.size() + q_lambda.size();
	loadedCount = 0;


	if (onBegan)
	{
		onBegan();
	}

	this->scheduleOnce(schedule_selector(LoadingScene::doLoad), 2.0f);
	this->scheduleUpdate();

	isLoading = true;
}

void LoadingScene::doLoad(float dt)
{
	//log("LoadingScene::doLoad()");

	if (q_texture.size() > 0)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(q_texture.front(),CC_CALLBACK_1(LoadingScene::callback_texture, this)); // 异步加载小图
	}
	else if (q_plist.size() > 0)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(q_plist.front(),CC_CALLBACK_1(LoadingScene::callback_plist, this)); // 异步加载大图
	}
	else if (q_lambda.size() > 0)
	{
		q_lambda.front()();
		callback_lambda();
	}
	else if (q_audio.size() > 0)
	{ 
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(q_audio.front().c_str());
		callback_audio();
	}
}

void LoadingScene::update(float dt)
{
	if (isLoading && loadedCount >= resCount)
	{
		//结束后操作
		if (onFinish)
		{
			onFinish();
		}
		isLoading = false;

		log("LoadingScene: Finish !");
	}
}



void LoadingScene::callback_texture(Texture2D *texture)
{
	q_texture.pop();
	loadedCount++;

	if (onLoad)
	{
		onLoad();
	}

	doLoad(0);
}

void LoadingScene::callback_plist(Texture2D *texture)
{
	q_plist.pop();
	loadedCount++;

	if (onLoad)
	{
		onLoad();
	}

	doLoad(0);
}

void LoadingScene::callback_lambda()
{
	q_lambda.pop();
	loadedCount++;

	if (onLoad)
	{
		onLoad();
	}

	doLoad(0);
}

void LoadingScene::callback_audio()
{
	q_audio.pop();
	loadedCount++;

	if (onLoad)
	{
		onLoad();
	}

	doLoad(0);
}











