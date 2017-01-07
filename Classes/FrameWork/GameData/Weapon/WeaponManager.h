#pragma once
#include "stdfax.h"
#include "CWeapon.h"
#include "ResourceLoader.h"

namespace cocosgalaxy
{
	class WeaponManager :public ResourceLoader
	{
	public:
		//µ¥ÀýÄ£Ê½
		static WeaponManager* getInstance();
		~WeaponManager();

		virtual void LoadResource();
		virtual void LoadResource(const vector<Name>& resNameList);
		virtual void FreeAllResource();
		virtual void FreeResource(const vector<Name>& resName);

		CWeapon* getWeapon(const string& weaponName);

	private:
		static WeaponManager* p_myinstance;
		map<Name, CWeapon*> m_weapon;

		WeaponManager();
	};
}


