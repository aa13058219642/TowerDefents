#pragma once
#include "cocos2d.h"
#include <queue>


class LoadingScene : public cocos2d::Scene
{
public:
	LoadingScene();
	~LoadingScene();
	CREATE_FUNC(LoadingScene);
	static void replaceScene(LoadingScene* scene);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	typedef std::function<void()> LoadingCallback;

	/*开始载入资源时需要进行的回调*/
	void bindBeginFunction(LoadingCallback callback);

	/*在加载过程中需要进行的回调(每加载一个资源回调一次)*/
	void bindLoadFunction(LoadingCallback callback);

	/*全部加载完毕后需要进行的回调*/
	void bindFinishFunction(LoadingCallback callback);

	/*设置需要异步加载的texture的列表*/
	void setTextureLoadList(std::queue<std::string> list);

	/*设置需要异步加载的plist的列表*/
	void setPlistLoadList(std::queue<std::string> list);

	/*设置需要加载的audio的列表*/
	void setAudioLoadList(std::queue<std::string> list);

	/*设置需要处理的lambda的列表*/
	void setLambdaLoadList(std::queue<LoadingCallback> list);

	/*
	设置自动开始加载资源
	默认开启
	*/
	void setAutoStartLoad(bool isAuto);

	/*获取需要加载的资源总数*/
	int getResCount();

	/*获取已加载的资源总数*/
	int getLoadedCount();

	/*获取加载进度*/
	float getLoadingProgress();

	/*
	存储临时数据
	注意：lambda函数中不得使用前一场景中的局部变量，
	因为场景会在加载途中被释放，因此必须将数据存至buff data
	*/
	void setData(cocos2d::ValueMap data);

	/*
	获取临时数据
	注意：lambda函数中不得使用前一场景中的局部变量，
	因为场景会在加载途中被释放，因此必须将数据存至buff data
	*/
	cocos2d::ValueMap getData();



	/*
	开始载入资源
	默认时在onEnterTransitionDidFinish中（replaceScene后）自动开始加载
	*/
	void start();			

private:
	void doLoad(float dt);

	virtual void update(float dt);

	void callback_texture(cocos2d::Texture2D *texture);
	void callback_plist(cocos2d::Texture2D *texture);
	void callback_lambda();
	void callback_audio();

private:
	bool isLoading;
	bool isAutoStartLoad;

	int resCount;
	int loadedCount;

	cocos2d::ValueMap buffData;	// 临时数据中转,保存前一场景的必要数据，用于下一场景的初始化

	LoadingCallback onBegan;	
	LoadingCallback onLoad;
	LoadingCallback onFinish;	

	std::queue<LoadingCallback> q_lambda;
	std::queue<std::string> q_texture;
	std::queue<std::string> q_plist;
	std::queue<std::string> q_audio;

};
