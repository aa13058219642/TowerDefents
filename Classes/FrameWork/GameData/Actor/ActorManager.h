#pragma once
#include "stdfax.h"
#include "Actor.h"
#include "ResourceLoader.h"



class ActorManager :public ResourceLoader
{
public:
	//单例模式
	static ActorManager* getInstance();
	~ActorManager();

	void init(Layer* layer);

	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);

	Actor* createActor(int id, Name name);
	void playAction(int actorID, Name actionName, float playtime = 0);
	/*移除一个演员（播放死亡动画）*/
	void removeActor(int id);
	/*移除一个演员（立刻，无动画）*/
	void destoryActor(int id);


private:
	static ActorManager* p_myinstance;
	Layer* m_layer;

	map<int, Actor*> m_actorlist;
	map<Name, ActorData> m_actordata;

	ActorManager();
};






















