#pragma once
class InputManager
{
#pragma region シングルトンインスタンス
private:
	static InputManager* instance;

	InputManager() = default;
	~InputManager() = default;
	InputManager(InputManager&) = delete;
	InputManager& operator = (InputManager&) = delete;

public:
	// シングルトンインスタンスの取得
	static InputManager* GetInstance();
	// 終了
	void Finalize();
#pragma endregion シングルトンインスタンス

public:
	void Init();
	void Update();

public:
	bool GetPreKey(char keyCode);
	bool GetKey(char keyCode);

private:
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
};

