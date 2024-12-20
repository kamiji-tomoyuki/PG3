#pragma once
#include <fstream>
#include "wrl.h"

#include <AudioStruct.h>

// オーディオ
class Audio
{
#pragma region シングルトンインスタンス
private:
	static Audio* instance;

	Audio() = default;
	~Audio() = default;
	Audio(Audio&) = delete;
	Audio& operator = (Audio&) = delete;

public:
	// シングルトンインスタンスの取得
	static Audio* GetInstance();
	// 終了
	void Finalize();
#pragma endregion シングルトンインスタンス

public:
	// 初期化
	void Initialize();

	// 音声データ読み込み
	SoundData LoadWav(const char* filename);

	// 音声データの解放
	void SoundUnload(Microsoft::WRL::ComPtr<IXAudio2> xAudio2, SoundData* soundData);

	// サウンド再生
	void PlayWave(const SoundData& soundData, bool loop, float volume);
	// サウンド停止
	void SoundStop(IXAudio2SourceVoice* pSourceVoice);

	// ボリュームを設定
	void SetVolume(float volume);

public:
	// xAudioの取得
	Microsoft::WRL::ComPtr<IXAudio2> GetXAudio2() const { return xAudio2_; }

private:
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;
	IXAudio2MasteringVoice* masterVoice_;

	IXAudio2SourceVoice* pSourceVoice_;

	HRESULT hr;
};

