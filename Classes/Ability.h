#pragma once

class Ability
{
public:
	Ability();
	~Ability();

	int HP;			//HP
	int MaxHP;		//MaxHp
	int MP;			//MP
	int MaxMP;		//MaxMp
	int WAtk;		//物理攻击
	int MAtk;		//魔法攻击
	int WDef;		//物理防御
	int MDef;		//魔法防御
	int Speed;		//移动速度
	int Const;		//花费
	int Radius;		//自身半径
	int Range;		//攻击半径
	float Reload;	//攻击间隔
	//int 
};

