#pragma once
#include "CActor.h"
#include "ResourceLoader.h"

namespace cocosgalaxy
{
	class ActorManager :public ResourceLoader
	{
	public:
		//单例模式
		static ActorManager* getInstance();
		~ActorManager();

		void init(Layer* layer);

		virtual void LoadResource();
		virtual void LoadResource(const vector<Name>& resNameList);
		virtual void FreeAllResource();
		virtual void FreeResource(const vector<Name>& resName);

		CActor* createActor(int id, Name name);
		void playAction(int actorID, Name actionName, float playtime = 0);
		/*移除一个演员（播放死亡动画）*/
		void removeActor(int id);
		/*移除一个演员（立刻，无动画）*/
		void destoryActor(int id);

		void destoryAllActor();
	private:
		static ActorManager* p_myinstance;
		Layer* m_layer;

		map<int, CActor*> m_actorlist;
		map<Name, ActorData> m_actordata;

		ActorManager();
		//int findActor(int id);
	};

}




















