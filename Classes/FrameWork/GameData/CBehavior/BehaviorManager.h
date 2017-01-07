#pragma once
#include "CBehavior.h"
#include "ResourceLoader.h"

namespace cocosgalaxy
{
	class BehaviorManager :public ResourceLoader
	{
	public:
		//µ¥ÀýÄ£Ê½
		static BehaviorManager* getInstance();
		~BehaviorManager();

		virtual void LoadResource();
		virtual void LoadResource(const vector<Name>& resNameList);
		virtual void FreeAllResource();
		virtual void FreeResource(const vector<Name>& resName);

		CBehavior* createBehavior(string key, int parentID = -1, int targetID = -1);
	private:
		BehaviorManager();
		static BehaviorManager* p_myinstance;

		map<Name, CBehavior*> m_behaviorList;


		CBehavior* loadBeahaviorBuff(JsonNode jNode);
	};

}

