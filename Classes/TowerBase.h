#pragma once
#include "stdfax.h"
#include "GameObject.h"
 
class TowerBase : public GameObject
{
public:
	TowerBase();
	~TowerBase();

	static TowerBase* create(Point pos, bool isDebug = false);
	bool init(Point pos, bool isDebug = false);

	/*»æÖÆÂÖÀª*/
	virtual void drawMyOutLine(DrawNode* drawNode);
	void upgrade();

	int type=0;
private:
	virtual void onAttack(float dt);


};

