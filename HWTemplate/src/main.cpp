// 当ライブラリで必須になるインクルードファイル
// "DxLib.h" もincludeされる
#include "HandlerWaltanForDxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DXライブラリの初期化処理も兼ねている
	if (HandlerWaltan::Instance().Init() == -1)
	{
		return 0;
	}


#ifdef _DEBUG

	// 幅: 1920, 高さ: 1080, ビット深度: 32
	SetGraphMode(1920, 1080, 32);
	ChangeWindowMode(TRUE);
	// デバッグモードで起動
	HandlerWaltan::debugMode = true;

#else

	// 幅: 1920, 高さ: 1080, ビット深度: 32
	SetGraphMode(1920, 1080, 32);
	// ウインドウモードで起動
	ChangeWindowMode(FALSE);
	// 非デバッグモードで起動
	HandlerWaltan::debugMode = false;

#endif // DEBUG


	SetUseZBuffer3D(TRUE);     // デプスバッファ（Zバッファ）を有効にする
	SetWriteZBuffer3D(TRUE);   // Zバッファへの書き込みを有効にする

	//! ハンドラーやライフサイクルに基づいたタイミングでメソッドを自動的に呼び出すオブジェクト
	//! シングルトンで設計されているため、以下の方法以外でインスタンスを取得することはできない
	HandlerWaltan& HW = HandlerWaltan::Instance();

	//! オブジェクトの生成(unityでいうところのGameObjectの生成)
	HWGameObject* obj = new HWGameObject();

	//! コンストラクタの引数で名前やプライオリティの初期設定も可能(指定しなかった場合は名前は"hwObj",
	//! プライオリティは 0 になる)
	// HWGameObject* obj = new HWGameObject("obj");
	// HWGameObject* obj = new HWGameObject(20);
	// HWGameObject* obj = new HWGameObject("obj", 20);


	// メインループ
	while (ProcessMessage() == 0)
	{
		//裏画面消す
		ClearDrawScreen();
		//描画先を裏画面に
		SetDrawScreen(DX_SCREEN_BACK);

		// ESCAPEキーの入力で終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;


		// 全てのUpdateメソッドを全て呼び出す
		HW.Update();

		DrawFormatString(0, 0, GetColor(255, 255, 255), "Escape key to exit");

		//裏画面を表画面にコピー
		ScreenFlip();
	}

	// ソフトの終了 
	HandlerWaltan::End();

	return 0;
}