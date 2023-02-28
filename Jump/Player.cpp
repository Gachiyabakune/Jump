#include "Player.h"
#include "game.h"
#include "Pad.h"
#include "Map.h"
#include "Sound.h"
#include <DxLib.h>

Player::Player() : 
	x(0),
	y(0),
	pmap(nullptr),
	moveFlag(false),
	jumpAfterInterval(true),
	boundFlag(false),
	jumpFlag(false),
	revers(false),
	idel(true),
	clearFlag(false),
	charge(false),
	jumpPower(0)
{
}

Player::~Player()
{
}

void Player::init()
{
	//キャラのサイズ
	m_size = 30;
	// プレイヤーの座標を初期化
	x = Game::kScreenWidth - MapSize * 12;
	y = Game::kScreenHight * MapStage - MapSize;

	// プレイヤーの落下速度を初期化
	fallSpeed = 0.0f;

	//キャラクター
	LoadDivGraph("data/texture.png",
		CharChipAll,
		CharChipX, CharChipY,
		48, 48,
		Cchip);
}

void Player::updata()
{
	// プレイヤーの移動処理
	float MoveX, MoveY;

	// 移動量の初期化
	MoveX = 0.0f;
	MoveY = 0.0f;

	//-----左右の移動を見る-----
	bool walk = false;		//歩いているかどうか
	
	//左を押している時かつジャンプ中でもない時
	if ((Pad::isPress(PAD_INPUT_LEFT) && !moveFlag ))
	{
		//動いでいるのでidel状態にはしない
		idel = false;
		MoveX -= MoveSpeed;
		revers = false;
		walk = true;
	}

	//右を押している時かつジャンプ中でもない時
	if ((Pad::isPress(PAD_INPUT_RIGHT) && !moveFlag ))
	{
		//動いでいるのでidel状態にはしない
		idel = false;
		MoveX += MoveSpeed;
		revers = true;
		walk = true;
	}
	//ジャンプ方向で左が選択された場合
	if (directionJump == 1)
	{
		if (!boundFlag)
		{
			MoveX -= MoveSpeed;	//バウンドしない間は左方向に
			revers = false;
		}
		else
		{
			MoveX += MoveSpeed;	//バウンドすると逆方向に
			revers = true;
		}
	}
	//ジャンプ方向で右が選択された場合
	else if (directionJump == 2)
	{
		if (!boundFlag)
		{
			MoveX += MoveSpeed;	//バウンドしない間は右方向に
			revers = true;
		}
		else
		{
			MoveX -= MoveSpeed;	//バウンドすると逆方向に
			revers = false;
		}
	}
	//ジャンプ処理
	jump(MoveX, MoveY);
	//キャラクターのアニメーション
	cAnimation(walk);

	//デバック用
#ifdef _DEBUG
	if (Pad::isPress(PAD_INPUT_4))
	{
		y -= 10;
	}
	else
	{
		// 重力
		fallSpeed += Gravity;
	}
#else
	// 重力
	fallSpeed += Gravity;
#endif
	// 落下速度を移動量に加える
	MoveY = fallSpeed;

	//lineYにY座標のoffset込みの数値を代入
	lineY = (int)(y - m_size * 0.5f + pmap->getoffset());

	// 移動量に基づいてキャラクタの座標を移動
	movePlayer(MoveX, MoveY);
}

void Player::draw()
{
	//キャラクター描画
	//入力した方向でキャラが向いている方向を変える
	if (revers)
	{
		DrawGraph((int)(x - 48 * 0.5f),
			(int)(y - 48 * 0.5f + pmap->getoffset()),
			Cchip[chipNum], TRUE);
	}
	else
	{
		DrawTurnGraph((int)(x - 48 * 0.5f),
			(int)(y - 48 * 0.5f + pmap->getoffset()),
			Cchip[chipNum], TRUE);
	}
#ifdef _DEBUG
	//四角 飛べるときは赤色,飛べない時は黄色
	if (!jumpFlag)
	{
		DrawBox((int)(x - m_size * 0.5f),
			(int)(y - m_size * 0.5f + pmap->getoffset()),
			(int)(x - m_size * 0.5f) + m_size,
			(int)(y - m_size * 0.5f + pmap->getoffset()) + m_size,
			GetColor(255, 0, 0), false);
	}
	else
	{

		DrawBox((int)(x - m_size * 0.5f),
			(int)(y - m_size * 0.5f + pmap->getoffset()),
			(int)(x - m_size * 0.5f) + MapSize,
			(int)(y - m_size * 0.5f + pmap->getoffset()) + MapSize,
			GetColor(255, 255, 0), false);
	}

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", lineY);	//Y座標	
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", (int)(x - m_size * 0.5f));	//X座標
	DrawFormatString(0, 40, GetColor(255, 255, 255), "dir : %d", direction);	//Y座標	
	DrawFormatString(0, 60, GetColor(255, 255, 255), "dirJ : %d", directionJump);	//Y座標	
	
	DrawFormatString(0, 80, GetColor(255, 255, 255), " Jpower : %d", jumpPower);	//ジャンプパワー
	DrawFormatString(0, 200, GetColor(255, 255, 255), "%d", chipNum);	//

	SetFontSize(32);
	//DrawString(0, 80, "Aボタンで溜め、溜めている間に十字キーで\n飛ぶ方向を決定\nため段階でジャンプ力変化", GetColor(255, 255, 255));	//真上に飛ぶ
	SetFontSize(16);
#endif
}

void Player::jump(float MoveX, float MoveY)
{
	// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
	if (!jumpFlag)
	{
		if (Pad::isPress(PAD_INPUT_1))
		{
			//ためている間は動けなくする
			moveFlag = true;
			//動いでいるのでidel状態にはしない
			idel = false;
			//ジャンプパワーチャージ
			jumpPower++;
			charge = true;	//チャージしている	
			//ジャンプ中にどの方向に飛ぶのかを決定
			if (Pad::isTrigger(PAD_INPUT_LEFT))
			{
				direction = 1;	//左に飛ぶなら1
				revers = false;	//キャラの反転
			}
			if (Pad::isTrigger(PAD_INPUT_RIGHT))
			{
				direction = 2;	//右に飛ぶなら2
				revers = true;	//キャラの反転
			}
		}
		//ボタンを離した時かカウントがたまると強制ジャンプ
		if (Pad::isRelase(PAD_INPUT_1) || jumpPower == ChargeTimeLvMax)
		{
			//ため段階が短いと小ジャンプ
			if (ChargeTimeLv1 >= jumpPower)
			{
				fallSpeed = -JumpPowerLv1;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//レベル2ジャンプ
			else if (ChargeTimeLv2 >= jumpPower && jumpPower > ChargeTimeLv1)
			{
				fallSpeed = -JumpPowerLv2;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//レベル3ジャンプ
			else if (ChargeTimeLv3 >= jumpPower && jumpPower >= ChargeTimeLv2)
			{
				fallSpeed = -JumpPowerLv3;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
				}
			//レベル4ジャンプ
			else if (ChargeTimeLv4 >= jumpPower && jumpPower >= ChargeTimeLv3)
			{
				fallSpeed = -JumpPowerLv4;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//レベル5ジャンプ
			else if (ChargeTimeLvMax > jumpPower && jumpPower >= ChargeTimeLv4)
			{
				fallSpeed = -JumpPowerLv5;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//レベルMaxジャンプ
			else if (ChargeTimeLvMax == jumpPower)
			{
				fallSpeed = -JumpPowerLvMax;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}

			jumpFlag = true;				//ジャンプ中にフラグを変更
			jumpAfterInterval = false;		//ジャンプ後のインターバル
			charge = false;					//チャージモーションを解除
			jumpPower = 0;					//ジャンプパワーを元に戻す
			jumpMotion = true;

			Sound::play(Sound::SoundId_Jump);
			}
		}
	//飛んでいないときに必要な情報を初期化する
	if (!jumpFlag && !jumpAfterInterval)
	{
		//Sound::play(Sound::SoundId_fall);
		moveFlag = false;
		directionJump = 0;
		direction = 0;
		jumpAfterInterval = true;
		boundFlag = false;
		jumpMotion = false;
	}
}

void Player::cAnimation(bool walk)
{
	//idel状体
	if (idel)
	{
		IdelInterval++;
		if (chipNum > 9)
		{
			chipNum = 0;
		}
		if (IdelInterval == 10)
		{
			chipNum++;
			IdelInterval = 0;
		}
	}
	//WALK
	else if (walk)
	{
		if (chipNum < 72 || chipNum == 107)
		{
			chipNum = 72;
		}
		else if (chipNum == 79)
		{
			chipNum = 72;
		}
		if (IdelInterval == 6)
		{
			chipNum++;
			IdelInterval = 0;
		}
		IdelInterval++;
	}
	//ジャンプ前チャージ
	else if (charge)
	{
		chipNum = 107;
	}
	//ジャンプ中
	else if (jumpMotion)
	{
		chipNum = 57;
	}
	else
	{
		chipNum = 0;
	}
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
	if (pmap->GetChipParam(afterX, afterY) == 10 || pmap->GetChipParam(afterX, afterY) == 2)
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
			if (!boundFlag)
			{
				boundFlag = true;
			}
			else
			{
				boundFlag = false;
			}
			// 左辺に当たったと返す
			return 1;
		}

		// 右辺に当たっていた場合
		if (MoveX < 0.0f)
		{
			// 移動量を補正する
			MoveX = blockRightX - X + 1.0f;
			//壁に当たると反射フラグをオン
			if (!boundFlag)
			{
				boundFlag = true;
			}
			//もう一回当たると元に戻す
			else
			{
				boundFlag = false;
			}
			// 右辺に当たったと返す
			return 2;
		}

		// ここに来たら適当な値を返す
		return 4;
	}

	/*------クリアの時(3に当たった時)フラグを返す------*/
	if (pmap->GetChipParam(afterX, afterY) == 10 || pmap->GetChipParam(afterX, afterY) == 3)
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
			clearFlag = true;	//クリアにする
		}

		// 下辺に当たっていた場合
		if (MoveY < 0.0f)
		{
			clearFlag = true;
		}

		// 左辺に当たっていた場合
		if (MoveX > 0.0f)
		{
			clearFlag = true;
		}

		// 右辺に当たっていた場合
		if (MoveX < 0.0f)
		{
			clearFlag = true;
		}

		// ここに来たら適当な値を返す
		return 4;
	}
	// どこにも当たらなかったと返す
	return 0;
}
