#pragma once
#include "SceneBase.h"
class SceneOpening : public SceneBase
{
public:
	SceneOpening();
	virtual ~SceneOpening() {}


	virtual void init() override;
	virtual void end()override;

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	//フェードインの時のUpdate関数
	void FadeInUpdate();
	//通常状態のUpdate関数
	void NormalUpdate();
	//フェードアウトの時のUpdate関数
	void FadeOutUpdate();

	enum class Seq
	{
		SeqFadeIn,		//フェードイン
		SeqUpdata,		//通常のupdata
		SeqFadeOut,		//フェードアウト
	};
	// 現在のゲームシーケンス
	Seq m_seq;

private:
	static constexpr int fade_interval = 60;
	int fadeTimer = fade_interval;		//フェードタイマー
	int fadeValue = 255;				//黒短形のブレンド具合
	
	// タイトル
	int m_titleHandle;
	// テキスト点滅用フレームカウント
	int m_textBlinkFrame;
	//フォントの座標
	int m_fontX;
	int m_fontY;
	//フォントを上下移動させるためのsin
	float sinRate;
	//次のシーンに行けるか
	bool chageScene;
};

