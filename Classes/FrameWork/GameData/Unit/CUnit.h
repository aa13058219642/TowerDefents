#pragma once
#include "GalaxyBase.h"
#include "Ability.h"
#include "CGameData.h"

namespace cocosgalaxy
{
	class CWeapon;
	class CActor;
	class CBehavior;
	class CEffect;
	class CSkill;
	class CModification;

	class CUnit : public CGameData
	{
	public:
		/* ----属性---- */

		int ID;
		AbilityEx<float> HP;
		AbilityEx<float> MP;
		AbilityEx<float> AP;
		Ability<float> HP_RegenRate;
		Ability<float> MP_RegenRate;
		Ability<float> AP_RegenRate;
		Ability<float> Speed;
		int Radius;
		//Ability<Cost> KillResource;
		//Ability<Cost> CreateCost;
		Ability<float> KillEXP;
		float EXP;
		Ability<float> DamageDefents[DamageTypeCount];

		/* ----方法---- */

		CUnit();
		~CUnit();

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
		virtual void onAttack(CUnit* target);
		virtual void onBeAttack(int damage, EDamageType damageType);
		virtual void onMissTarget(CUnit* target);

		virtual void addEffect(CEffect* effect);
		virtual void addSkill(CSkill* skill);
		virtual void addBehavior(CBehavior* behavior);
		virtual void applyAction(Name actionName, float playtime = 0);
		virtual void applyAEffect(Name effectName, float playtime = 0);

		virtual void setType(UnitType type);
		virtual UnitType getType();

		void setState(EUnitState state);
		EUnitState getState();

		virtual void setWeapon(CWeapon* weapon);
		virtual CWeapon* getWeapon();

		virtual void setTarget(int targetID);
		virtual CUnit* getTarget();

	protected:
		/* ----属性---- */
		Name m_name;
		UnitType m_type;
		EUnitState m_state;
		Point m_pos;
		CWeapon* m_weapon;
		Point m_targetPos;
		int m_targetID;

		std::list<CEffect*> effects;
		std::list<CSkill*> skills;
		std::list<CBehavior*> m_behaviors;
		std::list<CModification> m_modification;


		Name m_actorName;
		CActor* m_actor;

		/* ----方法---- */
		virtual void onBindSprite();
		virtual void onMove();
		virtual void onHitTarget();
		virtual void onDead();
		virtual void onDeaded();
	private:
		void updateModification();
	};

}