#pragma once

namespace Game
{
#ifdef _DEBUG
	//ウィンドウモード設定
	constexpr bool kWindowmode = true;
#else
	//ウィンドウモード設定
	constexpr bool kWindowmode = false;
#endif
	const char* const kTitleText = "ＧＡＭＥ";
	//ウィンドウサイズ
	constexpr int kScreenWidth = 768;	//768 or 1024
	constexpr int kScreenHight = 576;
	//カラーモード
	constexpr int kColorDepth = 32;   //32 or 16
};