#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "SceneTutorial.h"
#include "SceneOpening.h"
#include "SceneOption.h"
#include "Sound.h"
#include "Pad.h"
#include "game.h"

typedef enum 
{
	eMenu_Game,         //ゲーム
	eMenu_Tutorial,		//チュートリアル
	eMenu_Config,       //設定
	eMenu_End,			//終了
	eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Game;    //現在の選択状態(初期はゲーム選択中)

namespace
{
	// 文字色
	const int kFontColor = GetColor(125, 125, 125);
	const int kFontSelectColor = GetColor(255, 255, 255);
}

void SceneTitle::init()
{
}

SceneBase* SceneTitle::update()
{	
	if(Pad::isTrigger(PAD_INPUT_2))
	{
		switch (NowSelect)
		{
		case eMenu_Game:
			return (new SceneMain);
		case eMenu_Tutorial:
			return (new SceneTutorial);
			break;
		case eMenu_End:
			DxLib_End();
			break;
		case eMenu_Config:
			/*return (new SceneOption);*/
			break;
		default:
			break;
		}
		
	}
	//上
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
		Sound::play(Sound::SoundId_Select);
	}
	//下
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
		Sound::play(Sound::SoundId_Select);
	}
	
	return this;
}

void SceneTitle::draw()
{
	int y = 0;
	DrawString(200, 150, "", GetColor(255, 255, 255));
	DrawString(200, 170, "上下キーで選択し、2ボタンを押して下さい。", GetColor(255, 255, 255));
	if (select1)
	{
		DrawString(Game::kScreenWidth / 2 - 25, Game::kScreenHight / 2 - 30,
			"ゲーム", kFontSelectColor);
	}
	else
	{
		DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 - 30,
			"ゲーム", kFontColor);
	}
	if (select2)
	{
		DrawString(Game::kScreenWidth / 2 - 25, Game::kScreenHight / 2,
			"チュートリアル", kFontSelectColor);
	}
	else
	{
		DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2,
			"チュートリアル", kFontColor);
	}
	if (select3)
	{
		DrawString(Game::kScreenWidth / 2 - 25, Game::kScreenHight / 2 + 30,
			"操作方法", kFontSelectColor);
	}
	else
	{
		DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 + 30,
			"操作方法", kFontColor);
	}
	if (select4)
	{
		DrawString(Game::kScreenWidth / 2 - 25, Game::kScreenHight / 2 + 60,
			"終了", kFontSelectColor);
	}
	else
	{
		DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 + 60,
			"終了", kFontColor);
	}

	//選んだ項目によって座標や色などを変えているのでコードが長くなる
	switch (NowSelect)
	{//現在の選択状態に従って処理を分岐
	case eMenu_Game://ゲーム選択中なら
		y = 258;    //ゲームの座標を格納
		select1 = true;
		select2 = false;
		select3 = false;
		select4 = false;
		break;
	case eMenu_Tutorial:
		y = 288;
		select2 = true;
		select1 = false;
		select3 = false;
		select4 = false;
		break;
	case eMenu_Config:
		y = 318;
		select3 = true;
		select1 = false;
		select2 = false;
		select4 = false;
		break;
	case eMenu_End:
		y = 348;
		select4 = true;
		select2 = false;
		select3 = false;
		select1 = false;
		break;
	}

	DrawString(Game::kScreenWidth / 2 - 70, y, "⇒", GetColor(255, 0, 255));
}