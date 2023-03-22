#pragma once
#include "SceneBase.h"

class SceneOption : public SceneBase
{
public:
	SceneOption();
	virtual ~SceneOption() {}


	virtual void init()override;
	virtual void end()override {}

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
	//フェード関係
	static constexpr int fade_interval = 60;
	int fadeTimer = fade_interval;		//フェードタイマー
	int fadeValue = 255;				//黒短形のブレンド具合

	//次のシーンに行けるか
	bool nextScene;

	//画像
	int backHandle;
	//フォント
	int explanationHandle;
};
