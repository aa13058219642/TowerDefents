#pragma once
#include "CSkillGeneric.h"



namespace cocosgalaxy
{
	class CSkillEffect : public CSkillGeneric
	{
	public:

		/*冷却时间*/
		float ColdDown;
		/*冷却时间剩余*/
		float ColdDowning;

		/*
			↓
			接近╋━━━━
			↓
			准备╋━━━━准备动画/效果
			↓准备时间
			前摇╋━━━━前摇动画
			↓前摇时间
			施放╋━━━━施放动画/效果
			↓持续时间
			后摇╋━━━━后摇动画/效果
			↓后摇时间
			冷却╋━━━━
			↓CD时间

			*/

		/*准备动画*/
		string preparing_Animate;
		/*前摇动画*/
		string beforing_Animate;
		/*施放动画*/
		string using_Animate;
		/*后摇动画*/
		string aftering_Animate;

		/*准备效果*/
		string preparing_Effect;
		/*施放效果*/
		string using_Effect;
		/*结束效果*/
		string aftering_Effect;

		/*准备时间*/
		float preparing_Delay;
		/*前摇时间*/
		float beforing_Delay;
		/*持续时间*/
		float using_Delay;
		/*后摇时间*/
		float aftering_Delay;


		/* ----方法---- */
		CSkillEffect();
		~CSkillEffect();

		virtual void update(float dt);
		virtual bool IsCanExecute();

	};
}
