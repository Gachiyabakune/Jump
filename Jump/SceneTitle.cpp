#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Pad.h"
#include "game.h"

typedef enum 
{
	eMenu_Game,         //ゲーム
	eMenu_Config,       //設定
	eMenu_End,			//終了
	eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Game;    //現在の選択状態(初期はゲーム選択中)

void SceneTitle::init()
{
	m_isEnd = false;
	m_interval = 0;
}

SceneBase* SceneTitle::update()
{
	//ゲームスタート
	//if (Pad::isTrigger(PAD_INPUT_1))
	
	if(CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		switch (NowSelect)
		{
		case eMenu_Game:
			return (new SceneMain);
		case eMenu_End:
			DxLib_End();
			printfDx("aaa");
		case eMenu_Config:
		
			SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

			//ポーズウィンドウセロファン(黒い)
			DrawBox(40, 40, 600, 440, GetColor(0,255,0), true);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//通常描画に戻す

			//ポーズ中メッセージ
			DrawString(40 + 10, 40 + 10, "Pausing...", 0xffff88);

			//ポーズウィンドウ枠線
			DrawBox(40, 40, 600, 440, GetColor(0, 255, 255), false);
		default:
			break;
		}
		
	}
	//上
	if (Pad::isTrigger(PAD_INPUT_UP)&& m_interval == 0)
	{
		NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
		m_interval = 10;
	}
	//下
	if (Pad::isTrigger(PAD_INPUT_DOWN)&& m_interval == 0)
	{
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
		m_interval = 10;
	}
	//インターバル
	if (m_interval != 0)
	{
		m_interval--;
	}
	
	return this;
}

void SceneTitle::draw()
{
	int y = 0;
	DrawString(200, 150, "メニュー画面です。", GetColor(255, 255, 255));
	DrawString(200, 170, "上下キーを押し、エンターを押して下さい。", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 - 30,
		"ゲーム", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2,
		"オプション", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 + 30,
		"終了", GetColor(255, 255, 255));
	switch (NowSelect)
	{//現在の選択状態に従って処理を分岐
	case eMenu_Game://ゲーム選択中なら
		y = 258;    //ゲームの座標を格納
		break;
	case eMenu_Config:
		y = 288;
		break;
	case eMenu_End://設定選択中なら
		y = 318;
		//設定の座標を格納
		break;
	}

	DrawString(Game::kScreenWidth / 2 - 70, y, "■", GetColor(255, 0, 255));
}