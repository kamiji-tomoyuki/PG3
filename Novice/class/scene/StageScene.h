#pragma once
#include "../IScene.h"
#include "Novice.h"
#include "../object/Player.h"
#include "../object/Enemy.h"

class StageScene : public IScene
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

private:
	std::unique_ptr<Player> player_;
	std::unique_ptr<Enemy> enemy_;

	bool isClear = false;
};