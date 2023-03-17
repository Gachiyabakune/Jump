#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Map.h"
#include "game.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();


	virtual void init();
	virtual void end() {}

	virtual SceneBase* update();
	virtual void draw();

private:
	//フェードインの時のUpdate関数
	void FadeInUpdate();
	//通常状態のUpdate関数
	void NormalUpdate();
	//クリア後のUpdate関数
	void ClearUpdate();
	//フェードアウトの時のUpdate関数
	void FadeOutUpdate();

	virtual void drawClear();	//クリア後のdraw処理

	void refreshScore();
	int getHiScore();
private:
	Player* player = new Player;
	Map* map = new Map;
	enum class Seq
	{
		SeqFadeIn,			//フェード中
		SeqUpdata,			//通常のupdata
		SeqClearUpdata,		//クリア後のupdata
		SeqFadeOut,		//フェードアウト
	};
	// 現在のゲームシーケンス
	Seq m_seq;

	//フェード関係
	static constexpr int fade_interval = 60;
	int fadeTimer = fade_interval;		//フェードタイマー
	int fadeValue = 255;				//黒短形のブレンド具合

	//かかった時間
	int m_timeTaken;
	int temp;
	int m_timer;
	//フォント関係
	int textHeight;
	int textWidth;
	int textDispWidth;
	int fontHandle;

	// 文字列グラフィックを生成
	int handle;

	//スコア
	int hiscore;

	//シーン切り替え
	bool changeScene;
};