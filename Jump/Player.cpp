#include "Player.h"
#include "game.h"
#include "Pad.h"
#include "Map.h"
#include <DxLib.h>

namespace
{
	constexpr float Gravity = 0.3f;			//重力
	constexpr float JumpPowerMax = 10.0f;	//最大ジャンプ力
	constexpr float JumpPowerMin = 8.0f;	//最小ジャンプ力
	constexpr float MoveSpeed = 5.0f;		//移動速度

	constexpr int ChargeTime = 10;			//ためジャンプ
}

Player::Player() : 
	x(0),
	y(0),
	pmap(nullptr),
	jumpPower(0)
{
}

Player::~Player()
{
}

void Player::init()
{
	m_size = 32;
	// プレイヤーの座標を初期化
	x = Game::kScreenWidth - 32 * 12;
	y = Game::kScreenHight * MapStage - MapSize;

	// プレイヤーの落下速度を初期化
	fallSpeed = 0.0f;

	// ジャンプ中フラグを倒す
	jumpFlag = false;

	//キャラクター
	LoadDivGraph("data/char.png",
		CharChipAll,
		CharChipX, CharChipY,
		MapSize, MapSize,
		Cchip);
}

void Player::updata()
{
	// プレイヤーの移動処理
	float MoveX, MoveY;

	// 移動量の初期化
	MoveX = 0.0f;
	MoveY = 0.0f;

	// 左右の移動を見る
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		MoveX -= MoveSpeed;
		//テスト用
		if (Pad::isPress(PAD_INPUT_6))
		{
			MoveX -= MoveSpeed;
		}
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		//テスト用
		if (Pad::isPress(PAD_INPUT_6))
		{
			MoveX += MoveSpeed;
		}
		MoveX += MoveSpeed;
	}
	// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
	if (jumpFlag == false)
	{
		if (Pad::isPress(PAD_INPUT_1))
		{
			//ジャンプパワーチャージ
			jumpPower++;
		}
		if (Pad::isRelase(PAD_INPUT_1))
		{
			//ため段階が短いと小ジャンプ
			if (ChargeTime >jumpPower)
			{
				fallSpeed = -JumpPowerMin;
				jumpPower = 0;
			}
			//長いと大ジャンプ
			if (jumpPower >= ChargeTime)
			{
				fallSpeed = -JumpPowerMax;
				jumpPower = 0;
			}
			jumpFlag = TRUE;
		}
	}
	// 重力
	fallSpeed += Gravity;

	// 落下速度を移動量に加える
	MoveY = fallSpeed;

	// 移動量に基づいてキャラクタの座標を移動
	movePlayer(MoveX, MoveY);
}

void Player::draw()
{
	//キャラクター描画
	DrawGraph((int)(x - m_size * 0.5f),
		(int)(y - m_size * 0.5f + pmap->getoffset()), Cchip[0], TRUE);

	//四角
	if (jumpFlag == false)
	{
		DrawBox((int)(x - m_size * 0.5f),
			(int)(y - m_size * 0.5f + pmap->getoffset()),
			(int)(x - m_size * 0.5f) + MapSize,
			(int)(y - m_size * 0.5f + pmap->getoffset()) + MapSize,
			GetColor(255, 0, 0), true);
	}
	else
	{

		DrawBox((int)(x - m_size * 0.5f),
			(int)(y - m_size * 0.5f + pmap->getoffset()),
			(int)(x - m_size * 0.5f) + MapSize,
			(int)(y - m_size * 0.5f + pmap->getoffset()) + MapSize,
			GetColor(255, 255, 0), true);
	}

	lineY = (int)(y - m_size * 0.5f + pmap->getoffset());
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", lineY);
}

//-----------------------------------------
// キャラクタをマップとの当たり判定を考慮しながら移動する
//-----------------------------------------
int Player::movePlayer(float MoveX, float MoveY)
{
	float Dummy = 0.0f;
	float hsize;

	// キャラクタの左上、右上、左下、右下部分が当たり判定のある
	// マップに衝突しているか調べ、衝突していたら補正する

	// 半分のサイズを算出
	hsize = m_size * 0.5f;

	// 先ず上下移動成分だけでチェック。そのために移動量なしのDummy変数を渡しています
	//---------------------------------------------------------------------//
	// MoveX,MoveYは「参照」で渡しています。
	// この関数の中で、ぶつかった場合は移動量を補正して、壁にぶつかる前に止めます
	//---------------------------------------------------------------------//
	// 左下のチェック、もしブロックの上辺に着いていたら落下を止める
	if (mapHitCheck(x - hsize, y + hsize, Dummy, MoveY) == 3)
	{
		fallSpeed = 0.0f;
	}

	// 右下のチェック、もしブロックの上辺に着いていたら落下を止める
	if (mapHitCheck(x + hsize, y + hsize, Dummy, MoveY) == 3)
	{
		fallSpeed = 0.0f;
	}

	// 左上のチェック、もしブロックの下辺に当たっていたら落下させる
	if (mapHitCheck(x - hsize, y - hsize, Dummy, MoveY) == 4)
	{
		fallSpeed *= -1.0f;
	}

	// 右上のチェック、もしブロックの下辺に当たっていたら落下させる
	if (mapHitCheck(x + hsize, y - hsize, Dummy, MoveY) == 4)
	{
		fallSpeed *= -1.0f;
	}

	// 補正された上下移動成分を加算して実際に移動。あたってなかったらそのまま計算される
	y += MoveY;

	// 後に左右移動成分だけでチェック
	// 左下のチェック
	mapHitCheck(x - hsize, y + hsize, MoveX, Dummy);

	// 右下のチェック
	mapHitCheck(x + hsize, y + hsize, MoveX, Dummy);

	// 左上のチェック
	mapHitCheck(x - hsize, y - hsize, MoveX, Dummy);

	// 右上のチェック
	mapHitCheck(x + hsize, y - hsize, MoveX, Dummy);

	// 左右移動成分を加算
	x += MoveX;

	// 接地判定
		// キャラクタの左下と右下の下に地面があるか調べる
	if (pmap->GetChipParam(x + m_size * 0.5f - 16, y + m_size * 0.5f + 1.0f) == 5)
	{
		// 足場が無かったらジャンプ中にする
		jumpFlag = TRUE;
	}
	else
	{
		// 足場が在ったら接地中にする
		jumpFlag = FALSE;
	}

	// 終了
	return 0;
}

//-----------------------------------------
// マップとの当たり判定
// 戻り値 0:当たらなかった  1:左辺に当たった  2:右辺に当たった 3:上辺に当たった  4:下辺に当たった
// 注意：MoveX と MoveY、どっちか片方が０じゃないとまともに動作しません
// MoveX,MoveYは「参照」で渡しています。
// この関数の中で、ぶつかった場合は移動量を補正して、壁にぶつかる前に止めます
//-----------------------------------------
int Player::mapHitCheck(float X, float Y, float& MoveX, float& MoveY)
{
	float afterX, afterY;

	// 移動量を足す
	afterX = X + MoveX;
	afterY = Y + MoveY;

	// 当たり判定のあるブロックに当たっているかチェック
	if (pmap->GetChipParam(afterX, afterY) == 10)
	{
		float blockLeftX, blockTopY, blockRightX, blockBottomY;

		// 当たっていたら壁から離す処理を行う
		// ブロックの上下左右の座標を算出
		blockLeftX = (float)((int)afterX / MapSize) * MapSize;			// 左辺の X 座標
		blockRightX = (float)((int)afterX / MapSize + 1) * MapSize;		// 右辺の X 座標

		blockTopY = (float)((int)afterY / MapSize) * MapSize;			// 上辺の Y 座標
		blockBottomY = (float)((int)afterY / MapSize + 1) * MapSize;	// 下辺の Y 座標

		// 上辺に当たっていた場合
		if (MoveY > 0.0f)
		{
			// 移動量を補正する（
			MoveY = blockTopY - Y - 1.0f;

			// 上辺に当たったと返す
			return 3;
		}

		// 下辺に当たっていた場合
		if (MoveY < 0.0f)
		{
			// 移動量を補正する
			MoveY = blockBottomY - Y + 1.0f;

			// 下辺に当たったと返す
			return 4;
		}

		// 左辺に当たっていた場合
		if (MoveX > 0.0f)
		{
			// 移動量を補正する
			MoveX = blockLeftX - X - 1.0f;

			// 左辺に当たったと返す
			return 1;
		}

		// 右辺に当たっていた場合
		if (MoveX < 0.0f)
		{
			// 移動量を補正する
			MoveX = blockRightX - X + 1.0f;

			// 右辺に当たったと返す
			return 2;
		}

		// ここに来たら適当な値を返す
		return 4;
	}

	// どこにも当たらなかったと返す
	return 0;
}
