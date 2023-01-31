#include "Player.h"
#include "game.h"
#include "Pad.h"
#include "Map.h"
#include <DxLib.h>

#define G                (0.3F)                         // キャラに掛かる重力加速度
#define JUMP_POWER       (10.0f)                         // キャラのジャンプ力
#define SPEED            (5.0f)                         // キャラの移動スピード

Player::Player() : 
	x(0),
	y(0),
	pmap(nullptr)
{
}

Player::~Player()
{
}

void Player::init()
{
	m_size = 32;
	// プレイヤーの座標を初期化
	x = Game::kScreenWidth - 32 * 18;
	y = Game::kScreenHight - 32 * 10;

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
		//idel = false;
		MoveX -= SPEED;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		//idel = false;
		MoveX += SPEED;
	}
	// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
	if (jumpFlag == false)
	{
		if (Pad::isRelase(PAD_INPUT_1))
		{
			//idel = false;
			fallSpeed = -JUMP_POWER;
			jumpFlag = TRUE;
		}
	}
	// 重力
	fallSpeed += G;

	// 落下速度を移動量に加える
	MoveY = fallSpeed;

	// 移動量に基づいてキャラクタの座標を移動
	movePlayer(MoveX, MoveY);
}

void Player::draw()
{
	DrawGraph((int)(x - m_size * 0.5f),
		(int)(y - m_size * 0.5f + pmap->getoffset()), Cchip[0], TRUE);
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
	if (pmap->GetChipParam(x - m_size * 0.5f, y + m_size * 0.5f + 1.0f) == 5)
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
