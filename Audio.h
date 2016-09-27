#pragma once
#include "Headers.h"
#include "Helpers.h"
#include "WAVFileReader.h"

#include <xaudio2.h>

#pragma comment (lib, "Xaudio2.lib")

extern ComPtr<ID3D11Device>			gDevice;
extern ComPtr<ID3D11DeviceContext>	gContext;

class Audio {

public:

	Audio();
	void Create();
	void CreateSourceVoice();

	void Exit();


private:


	ComPtr<IXAudio2> m_xAudio2;
	//ComPtr<IXAudio2MasteringVoice> m_masterVoice;


	//ComPtr<IXAudio2SourceVoice> m_sourceVoice;
	IXAudio2SubmixVoice* subMix01;
	IXAudio2SubmixVoice* subMix02;

	XAUDIO2_BUFFER buffer1;
	IXAudio2SourceVoice* pSourceVoice;
	std::unique_ptr<uint8_t[]> waveFile;
	DirectX::WAVData waveData;



	XAUDIO2_BUFFER buffer2;
	IXAudio2SourceVoice* pSourceVoice2;
	std::unique_ptr<uint8_t[]> waveFile2;
	WAVData waveData2;

	XAUDIO2_SEND_DESCRIPTOR SFXSend;
	XAUDIO2_VOICE_SENDS SFXSendList;

	XAUDIO2_SEND_DESCRIPTOR SFXSend2;
	XAUDIO2_VOICE_SENDS SFXSendList2;

	float frequencyRatio;
};