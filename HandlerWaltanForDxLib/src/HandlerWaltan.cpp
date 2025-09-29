﻿#include "h/HandlerWaltan.h"


/**
* @author   NZ
* @date     24/07/29
* @note		HandlerWaltanの実装ファイル
*/


// 静的メンバ変数の初期化 ------------------------------------------------------------------------------------------------

bool HandlerWaltan::debugMode = false;
std::vector<InputSystem*> InputSystem::inputSystemVec;

int HWUtility::ScreenSizeX = -1;
int HWUtility::ScreenSizeY = -1;

float Time::deltaTime = 0.0f;
float Time::lastTime = 0.0f;
int Time::targetFPS = -1;  // デフォルトは-1
float Time::targetFrameTime = 1.0f / 60.0f;  // 60FPSなら1フレームあたり約0.01666秒
bool Time::debugMode = false;
int Time::frameCount = 0;  // フレーム数の初期化
float Time::elapsedTime = 0.0f;  // 経過時間の初期化
unsigned int Time::color = GetColor(255,0,255);

//------------------------------------------------------------------------------------------------------------------------


#pragma region publucメソッド


void HandlerWaltan::Update()
{
    Time::Update();

    // 削除リストを参照し、カウントが0になったオブジェクトは削除する
    for (auto it = HWGameObject::destroyList.begin(); it != HWGameObject::destroyList.end(); )
    {
        if (it->time <= GetNowCount()) 
        {

            delete it->object;  
            it->object = nullptr;
            it = HWGameObject::destroyList.erase(it);  
        }
        else 
            ++it;
    }

    //! DotweenのUpdateを呼び出す
    HWDotween::Update();

    //! インスタンス化された全てのGameObject
    auto gameObjects = HWGameObject::GetGameObjects();

    // TransformのUpdateメソッドを呼び出す
    for (auto obj : gameObjects)
        if(obj->active.load())
            obj->CallTransformUpdate();

    // インスタンス化されたInputSystemのUpdateメソッドを呼ぶ
    for (auto it = InputSystem::inputSystemVec.begin(); it != InputSystem::inputSystemVec.end(); ++it)
    {
        if ((*it)->active)
            (*it)->Update();
    }

    // インスタンス化された全てのHWGameObjectのUpdateメソッドを呼び出す
    for (auto obj : gameObjects)
        if(obj->active.load())
            obj->CallAllUpdates();

    // インスタンス化された全てのHWGameObjectのLateUpdateメソッドを呼び出す
    for (auto obj : gameObjects)
        if(obj->active.load())
            obj->CallAllLateUpdates();

    // あたり判定を確認
    CollisionWaltan::Instance().Update();

    // シーンの更新
	HWSceneManager::Update();


    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();

    // Effekseerにより再生中のエフェクトを描画する。
    DrawEffekseer3D();

    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();

	// インスペクターの更新
	HWInspector::Update();

    // フレーム終了時に次のフレームまで待機（FPS固定）
    if(Time::targetFPS != -1)
    {
        Time::WaitForNextFrame();
        if (Time::debugMode)
            Time::ShowFPS();
    }
}


#pragma endregion

#pragma region privateメソッド


HandlerWaltan::HandlerWaltan()
{
}


HandlerWaltan::~HandlerWaltan()
{

}


#pragma endregion

#pragma region staticメソッド


HandlerWaltan& HandlerWaltan::Instance()
{
    // シングルトンインスタンスを生成
    static HandlerWaltan instance;
    return instance;
}

int HandlerWaltan::Init(int _particle)
{
    // DXライブラリとEffekseerの初期化

    // DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
    // Effekseerを使用するには必ず設定する。
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
        // エラーコードを返す
        return -1;

    // Effekseerを初期化する。
    // 引数には画面に表示する最大パーティクル数を設定する。
    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }

    // カーソルの表示
    SetMouseDispFlag(TRUE);

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    // ただし、DirectX11を使用する場合は実行する必要はない。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Zバッファを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetUseZBuffer3D(TRUE);

    // Zバッファへの書き込みを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetWriteZBuffer3D(TRUE);

    GetWindowSize(&HWUtility::ScreenSizeX, &HWUtility::ScreenSizeY);

    return 0;
}

void HandlerWaltan::End()
{
    // Effekseerを終了する。
    Effkseer_End();

    DxLib_End();				// ＤＸライブラリ使用の終了処理
}

#pragma endregion



