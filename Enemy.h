#pragma once
class Enemy
{
public:
	// 初期化
	void Initialize();

	// 更新処理
	void Update();

	// 接近
	void Approach();
	// 射撃
	void Shoot();
	// 離脱
	void Leave();

private:
	// フェーズ関数テーブル
	static void (Enemy::* phaseTable[])();

private:
	// 行動
	enum class Phase
	{
		Approach,
		Shoot,
		Leave,
	};
	Phase phase_;
};

