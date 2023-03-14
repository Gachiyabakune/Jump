#pragma once

// サウンド関連処理
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		SoundId_BgmMain,	// 難しいステージのBGM
		SoundId_BgmEasy,	// かんたんなステージのBGM
		//SoundId_BgmClear,	// クリア後ののBGM
		//SoundId_Title,		//タイトル画面のBGM

		// 効果音
		SoundId_Jump,		// ジャンプするとき
		SoundId_Select,		// 選択画面で選んでいるとき
		SoundId_Decision,	// 選択画面で決定したとき
		//SoundId_Clear,		//クリアしたときの音

		SoundId_Num
	}SoundId;

	// ロード、アンロード
	void load();
	void unload();

	// BGMの再生
	void startBgm(SoundId id, int volume = 255);
	void stopBgm(SoundId id);

	// 効果音の再生
	void play(SoundId id);

	// 音量設定	0~255
	void setVolume(SoundId id, int volume);
}
