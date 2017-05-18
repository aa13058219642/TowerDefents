#pragma once
#include "GalaxyBase.h"
#include "Ability.h"
#include "CCostUnit.h"
#include "CGameData.h"

//class CEffect;

namespace cocosgalaxy
{
	class CWeapon : public CGameData
	{
	public:

		/*攻击固定花费  实际花费=CostBase + ((Damage.Max - Damage.Min)*CostDamageRangeRate + Damage.Min)*TargetCount*CostDamageRate */
		CCostUnit CostBase;
		/*攻击伤害花费  实际花费=CostBase + ((Damage.Max - Damage.Min)*CostDamageRangeRate + Damage.Min)*TargetCount*CostDamageRate  */
		CCostUnit CostDamageRate;
		/*攻击伤害花费修正  实际花费=CostBase + ((Damage.Max - Damage.Min)*CostDamageRangeRate + Damage.Min)*TargetCount*CostDamageRate */
		Ability<float> CostDamageRangeRate;

		/*命中率*/
		Ability<float> chance;
		/*射程*/
		Ability<float> Range;
		/*CD*/
		AbilityEx<float> ColdDown;
		/*最大同时攻击目标*/
		Ability<int> TargetCount;
		/*目标过滤*/
		UnitType Filter;
		/*伤害类型*/
		AbilityKey<EDamageType> DamageType;
		/*伤害*/
		AbilityEx<float> Damage;


		/*爆炸范围*/
		Ability<float> BoomRange;
		/*攻击附带效果*/
		AbilityKey<std::string> attack_Effect;
		/*命中效果动画*/
		AbilityKey<std::string> attack_Animate;
		/*暴击率*/
		Ability<float> criticalChance;
		/*暴击伤害倍率*/
		Ability<float> criticalMultiplier;
		/*暴击附带效果(暴击时，攻击附带效果与暴击附带效果一起发动)*/
		AbilityKey<std::string> critical_Effect;
		/*暴击效果动画*/
		AbilityKey<std::string> critical_Animate;

		/*演员名称*/
		AbilityKey<std::string> ActorName;
		/*前摇时间*/
		float beforing_Delay;
		/*施放时间*/
		float using_Delay;
		/*后摇时间*/
		float aftering_Delay;
		/*前摇动画*/
		std::string beforing_Animate;
		/*施放动画*/
		std::string using_Animate;
		/*后摇动画*/
		std::string aftering_Animate;

		/*子弹类型*/
		//BulletType bulletType;
		/*是否追踪目标*/
		bool IsTrackTarget;
		/*是否面向目标*/
		bool IsFaceToTarget;
		/*子弹移动速度*/
		float BulletSpeed;

		CWeapon();
		~CWeapon();
		CWeapon* clone();

		void clearAbility();

		//CWeapon* getCurWeapon();
		//template <typename T>
		//void Upgrade(EWeapon_Upgradable type, T value);
		//void Downgrade();


	private:


	};

}