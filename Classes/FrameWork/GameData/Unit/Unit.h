#pragma once
#include "stdfax.h"
#include "Ability.h"
#include "EnumConst.h"
#include "CWeapon.h"
#include "Modification.h"
class Actor;
class CEffect;
class CSkill;
class CBehavior;

class Unit
{
public:
	/* ----属性---- */
	
	int ID;
	AbilityValueEx<float> HP;
	AbilityValueEx<float> MP;
	AbilityValueEx<float> AP;
	Ability<float> Speed;
	int Radius;
	//Ability<Cost> KillResource;
	//Ability<Cost> CreateCost;
	Ability<float> KillEXP;
	float EXP;
	Ability<float> DamageDefents[DamageTypeCount];

	/* ----方法---- */

	Unit();
	~Unit();

	Point getPos();
	void setPos(Point pos);

	Name getActorName();
	void setActorName(Name actorName);
	void bindActor();

	/*判断坐标是否在RADIUS范围内*/
	bool isClickMe(Point pos);
	
	/*绘制轮廓*/
	virtual void drawMyOutLine(DrawNode* drawNode);

	virtual void update(float dt);


	virtual void onClick();
	virtual void onAttack(Unit* target);
	virtual void onBeAttack(int damage, EDamageType damageType);
	virtual void onMissTarget(Unit* target);

	virtual void addEffect(CEffect* effect);
	virtual void addSkill(CSkill* skill);
	virtual void addBehavior(CBehavior* behavior);
	virtual void applyAction(Name actionName, float playtime = 0);
	virtual void applyAEffect(Name effectName, float playtime = 0);

	virtual void setType(UnitType type);
	virtual UnitType getType();

	void setState(EUnitState state);
	EUnitState getState();

	void setWeapon(CWeapon* weapon);
	CWeapon* getWeapon();
protected:
	/* ----属性---- */
	Name m_name;
	UnitType m_type;
	EUnitState m_state;
	Point m_pos;
	CWeapon* m_weapon;

	std::list<CEffect*> effects;
	std::list<CSkill*> skills;
	std::list<CBehavior*> m_behaviors;
	std::list<Modification> m_modification;


	Name m_actorName;
	Actor* m_actor;

	/* ----方法---- */
	virtual void onBindSprite();
	virtual void onMove();
	virtual void onHitTarget();
	virtual void onDead();
	virtual void onDeaded();
private:
	void updateModification();
};

