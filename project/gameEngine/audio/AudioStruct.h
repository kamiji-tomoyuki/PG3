#pragma once
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
//===== 構造体 =====
// チャンクヘッダ
struct ChunkHeader {
	char id[4];		 // チャンク毎のID
	int32_t size;	 // チャンクサイズ
};

// RIFFヘッダチャンク
struct RiffHeader {
	ChunkHeader chunk;	// "RIFF"
	char type[4];		// "WAVE"
};

// FMTチャンク
struct FormatChunk {
	ChunkHeader chunk;	// "fmt"
	WAVEFORMATEX fmt;	// 波形フォーマット
};

// 音声データ
struct SoundData {
	WAVEFORMATEX wfex;		// 波形フォーマット
	BYTE* pBuffer;			// バッファの先頭アドレス
	unsigned int bufferSize;// バッファサイズ
};