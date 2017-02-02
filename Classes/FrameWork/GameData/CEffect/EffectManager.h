#pragma once
#include "CEffect.h"
#include "ResourceLoader.h"
#include "CWeapon.h"
#include "EffectCreator.h"

namespace cocosgalaxy
{
	class EffectManager :public ResourceLoader
	{
	public:
		//µ¥ÀýÄ£Ê½
		static EffectManager* getInstance();
		~EffectManager();

		void init(EffectCreator* effectCreator = nullptr);

		virtual void LoadResource();
		virtual void LoadResource(const vector<Name>& resNameList);
		virtual void FreeAllResource();
		virtual void FreeResource(const vector<Name>& resName);

		CEffect* createCEffect(string key, int parentID = -1, int targetID = -1);
		CEffect* createHitEffect(CWeapon* weapon, int parentID, int targetID);

		bool findEffect(const string& key);
	private:
		static EffectManager* p_myinstance;

		bool isInit;
		EffectCreator* effectCreator;
		std::map<string, CEffect*> m_effectlist;

		EffectManager();
	};
}


