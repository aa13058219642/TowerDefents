#pragma once
#include "ResourceLoader.h"
#include "Bullet.h"

class BulletManager :public ResourceLoader
{
public:
	//单例模式
	static BulletManager* getInstance();
	~BulletManager();

	virtual void LoadResource();
	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);


	Bullet* CreateBullet(string bulletName);

private:
	BulletManager();
	static BulletManager* p_myinstance;

	std::map<Name, Bullet*> bulletlist;

};



