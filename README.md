<div id="top"></div>

## 使用技術一覧

<!-- シールド一覧 -->

</p>

## 目次

1. [プロジェクトについて](#プロジェクトについて)
2. [環境](#環境)
3. [導入方法](#導入方法)
4. [使い方](#使い方)

<br>

<b> APIリファレンス </b>

1. [HWGameObject](#hwgameobject)
2. [HWComponent](#hwcomponent)
3. [HWTransform](#hwtransform)
4. [HWCapsuleCollider](#hwcapsulecollider)
5. [HWRenderer](#hwrenderer)
6. [HWAnimator](#hwanimator)
7. [HWEffect](#hweffect)
8. [InputSystem](#inputsystem)
9. [PoolAllocator](#poolallocator)
10. [CsvLoader](#csvloader)



<!-- READMEの作成方法のテンプレート -->
<br />
<div align="right">
    <a href="https://qiita.com/shun198/items/c983c713452c041ef787"><strong>READMEのテンプレート »</strong></a>
</div>
</><br />
<!-- プロジェクト名を記載 -->


## プロジェクトについて

<h3> 【概要】 </h3>
C++でのゲーム開発をUnityライクに行えるようになるライブラリ<br>
既存のコンポーネントだけでモデル描画、アニメーション制御、当たり判定の付与などが可能なほか、
HWComponentをpublicで継承することによって、コンポーネントの自作も可能。<br>
<br>
<h3> 【Unityとの差別点】 </h3>
アニメーションの再生開始時、終了時に呼ばれるコールバックが事前に用意されているため、メンバ変数にコールバックを登録するだけで設定できる。


<!-- プロジェクトの概要を記載 -->

  <p align="left">
    <br />
    <!-- プロジェクト詳細にBacklogのWikiのリンク -->
    <a href="Backlogのwikiリンク"><strong>プロジェクト詳細 »</strong></a>
    <br />
    <br />

<p align="right">(<a href="#top">トップへ</a>)</p>

## 環境

<!-- 言語、フレームワーク、ミドルウェア、インフラの一覧とバージョンを記載 -->

| 言語・フレームワーク  | バージョン |
| --------------------- | ---------- |
| C++                   | 14         |
| DXライブラリ           | 3.24d      |


現状、開発環境はVisualStudio2022を想定しています。

<p align="right">(<a href="#top">トップへ</a>)</p>


## 導入方法

<!-- 導入方法 -->

<b> <Visual Studio Community 2022 の場合> </b>

プロジェクトの作成 と プロジェクトへ新規プログラムファイルを作成・追加 までは <a href="https://dxlib.xsrv.jp/use/dxuse_vscom2022.html"><strong>こちら</strong></a> を参照してください。

<br>

<b> 1.ＤＸライブラリ と 当ライブラリ を使用するためのプロジェクトの設定を行う </b>

<body>

 	①　Visual Studio Community 2022 のメニューの
	　　『プロジェクト(P)』→『(プロジェクト名) のプロパティ(E)...』を選んで、プロジェクトのプロパティダイアログを開きます。
   
	②　次にダイアログの左上にある『構成(C):』と書かれている項目を『アクティブ(Debug)』から『すべての構成』に、
	　　『構成(C):』の右側にある『プラットフォーム(P):』と書かれている項目を『アクティブ(x64)』から
	　　『すべてのプラットフォーム』変更します。

	③　次にダイアログの左側のリストから『構成プロパティ』→『詳細』を選びます。

	④　次にダイアログ右側に表示されている『文字セット』の項目を
	　　『マルチ バイト文字セットを使用する』に変更したあと、ダイアログ右下にある『適用(A)』ボタンを押します。

	⑤　次に左側のリストから『構成プロパティ』→『Ｃ／Ｃ＋＋』→『全般』を選びます。

	⑥　次に右側に表示されている『追加のインクルードディレクトリ』の項目にＤＸライブラリのパッケージ内に
	　　入っている『プロジェクトに追加すべきファイル/HandlerWaltamForDxLib』と、
   	　 『プロジェクトに追加すべきファイル/プロジェクトに追加すべきファイル_VC用』フォルダのパスを入力してから、
	　　再度ダイアログ右下にある『適用(A)』ボタンを押します。

	⑦　次に左側のリストから『構成プロパティ』→『リンカー』→『全般』を選びます。
	
	⑧　次に右側に表示されている『追加のライブラリディレクトリ』の項目に⑥と全く同じＤＸライブラリの
	　　パッケージ内に入っている『プロジェクトに追加すべきファイル/HandlerWaltamForDxLib』と
           『プロジェクトに追加すべきファイル/プロジェクトに追加すべきファイル_VC用』フォルダのパスを
	　　入力してから、再度ダイアログ右下にある『適用(A)』ボタンを押します。

	⑩　次にダイアログの左上にある『構成(C):』と書かれている項目を『すべての構成』から
	　　『Release』に変更します。

	⑪　左側のリストから今度は『構成プロパティ』→『Ｃ／Ｃ＋＋』→『コード生成』を選びます。

	⑫　ダイアログ右側に表示されている『ランタイム ライブラリ』の項目を
	　　『マルチスレッド(/MT)』に変更したあと、ダイアログ右下にある『適用(A)』ボタンを押します。

	⑬　ダイアログの左上にある『構成(C):』と書かれている項目を『Release』から
	　　『Debug』に変更します。

	⑭　ダイアログ右側に表示されている『ランタイム ライブラリ』の項目を
	　　今度は『マルチスレッド デバッグ(/MTd)』に変更します。

	⑮　最後にダイアログの下の方にある『ＯＫ』を押してダイアログを閉じます。


</body>

    
<p align="right">(<a href="#top">トップへ</a>)</p>


## 使い方

<body>

 	#pragma comment(lib,"プロジェクトに追加すべきファイル/HandlerWaltanForDxLib_d.lib")

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
	
		
			//裏画面を表画面にコピー
			ScreenFlip();
		}
		
		// ソフトの終了 
		HandlerWaltan::End();
	
		return 0;				
	}
 
</body>

<!-- プロジェクトの概要を記載 -->


<p align="right">(<a href="#top">トップへ</a>)</p>



<!-- ここから自作ライブラリのリファレンス -->

## HWGameObject

<b> <説明> </b>

アタッチされているコンポーネントの管理
オブジェクトの設定

<br />
<br />


<b> <オブジェクトの設定> </b>

<body>

	@brief		オブジェクトの名前
	std::string name

 	@brief		オブジェクトのタグ
	int tag

 	@brief		アクティブ
	bool active

	@brief		ハンドラーやUpdateメソッドの優先順位(降順)
	int priority

	@brief		座標が親オブジェクトの影響を受けるか
	bool isAffect; 
	
	@brief		Transformコンポーネント
	HWTransform* transform

</body>

<b> <コンポーネント付与、取得の関数> </b>

<body>

	@brief		コンポーネントを追加する
 	@detail		テンプレートにコンポーネントを指定
  	@param[in]	引数が存在するコンポーネントの場合は指定
	@return		アタッチされたコンポーネントのインスタンス
 	template<class T>
	T* AddComponent()

 	@brief		指定のコンポーネントを返す
	@return		アタッチされていた場合はインスタンスを返し、それ以外ならnullPtrを返す
	template<class T>
	T* GetComponent()

</body>

<b> <コンストラクタ> </b>

<body>

	@brief		コンストラクタ
	HWGameObject()
 
	@brief		コンストラクタ(名前の初期化宣言)
	@param[in]	std::string オブジェクト名	
	HWGameObject(const std::string&)

	@brief		コンストラクタ(プライオリティの初期化宣言)
	@param[in]	int プライオリティ
	HWGameObject(const int)

	@brief		コンストラクタ(名前とプライオリティの初期化宣言)
	@param[in]	std::string オブジェクト名
	@param[in]	int	プライオリティ
	HWGameObject(const std::string&, const int)

	@brief		コピーコンストラクタ
	@param[in]	HWGameObject& コピー元のHWGameObject
	HWGameObject(const HWGameObject&)


<b> <Getter関数> </b>


	@brief		全ての子オブジェクトを取得する
	@detail		引数で特定のインデックスの子オブジェクトを取得できる
	@return		const std::vector<HWGameObject*>& 全ての子オブジェクトを取得する
	std::vector<HWGameObject*>& GetChildren()

	@brief		子オブジェクトを取得する
	@detail		引数で特定のインデックスの子オブジェクトを取得できる
	@return		const std::vector<HWGameObject*>& 全ての子オブジェクトを取得する
	HWGameObject* GetChild(const int _index)

	@brief		親オブジェクトを取得する
	@return		HWGameObject* 親オブジェクト 
	HWGameObject* Parent()	


 <b> <Setter関数> </b>


	@brief		親オブジェクトを設定する
	@param[in]	const int 取得する子オブジェクトのインデックス
	@param[in]	const bool 座標が親の影響を受けるか
	void SetParent(HWGameObject* _parent, const bool _isAffect = true);


  <b> <Static関数> </b>

	@param[in]	HWGameObject* 削除するオブジェクト
	@param[in]	int	      何秒後に削除するか 
	static void Destroy(HWGameObject* _obj, float delay = 0.0f);
 
</body>

<p align="right">(<a href="#top">トップへ</a>)</p>





<!------------------------------------------------------------------------------------------------------------------>





## HWComponent

<b> <説明> </b>

すべてのコンポーネントの基底クラス


<br />
<br />

<b> <オーバーライド関数> </b>

<body>

	@brief		HWGameObjectにアタッチされた瞬間に働く
 	@detail		コンポーネントの初期化処理はなるべくコンストラクタではなくこちらで行う
	virtual void Awake()

 	@brief		最初のUpdateメソッドの直前に働く
	@detail		仮想関数
	virtual void Start() {}

 	@brief		毎フレーム呼ばれるメソッド
	virtual void Update()


 <b> <非トリガーコリジョン接触時のコールバック関数> </b>


 	@brief		コライダー衝突時に働くメソッド
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnCollisionEnter(HWCollider&)

 	@brief		コライダー衝突中に働くメソッド
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnCollisionStay(HWCollider&)

	@brief		コライダー衝突が解除時に働くメソッド (コライダーがトリガーの場合)
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnCollisionExit(HWCollider&)


 <b> <トリガーコリジョン接触時のコールバック関数> </b>


  	@brief		コライダー衝突時に働くメソッド (コライダーがトリガーの場合)
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnTriggerEnter(HWCollider&)

 	@brief		コライダー衝突中に働くメソッド (コライダーがトリガーの場合)
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnTriggerStay(HWCollider&)

	@brief		コライダー衝突が解除時に働くメソッド (コライダーがトリガーの場合)
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnTriggerExit(HWCollider&)


  <b> <継承されるメンバ変数> </b>


	@brief		このコンポーネントがアタッチされているHWGameObject
	HWGameObject* gameObject

	@brief		HWGameObjectにアタッチされているHWTransform
	HWTransform* transform

	@brief		複数アタッチ可能なコンポーネントか
	bool isMultiplePossession

	@brief		コンポーネントのアクティブ
	bool active

	@brief		ハンドラーやUpdateメソッドの優先順位(降順)
	int priority

</body>

<p align="right">(<a href="#top">トップへ</a>)</p>





<!------------------------------------------------------------------------------------------------------------------>





## HWTransform

<b> <説明> </b>

座標、回転などを管理するコンポーネント

オブジェクトの正面ベクトルや、移動ベクトルの設定

<br />
<br />

  <b> <平行移動、回転、拡縮> </b>


	@brief		グローバル座標
	VECTOR position

	@brief		グローバル回転
	VECTOR rotate

	@brief		グローバル拡縮
	VECTOR scale


  <b> <メンバ変数> </b>


	@brief		移動ベクトル
	VECTOR velocity

	@brief		正面ベクトル
	VECTOR forward


   <b> <メンバ関数> </b>


	@brief		目標のほうを向く
 	@param@[in]	const VECTOR& 目標
	void LookAt(const VECTOR&)

</body>
<p align="right">(<a href="#top">トップへ</a>)</p>





<!------------------------------------------------------------------------------------------------------------------>





## HWCapsuleCollider

<b> <説明> </b>

カプセル型の当たり判定コンポーネント

自身で始点と終点を定めない場合は、自動でHWGameObjectの座標を原点に height 分の高さを持つコライダーを構築する

<br />
<br />

  <b> <コライダーの設定> </b>


	@brief		コライダーの高さ (自身で始点と終点を設定した場合、無効化される)
	float height

	@brief		コライダーの半径
	float radius

	@brief		コライダーの始点
	VECTOR UsStartPos

	@brief		コライダーの終点
	VECTOR UsEndPos


</body>
<p align="right">(<a href="#top">トップへ</a>)</p>





<!------------------------------------------------------------------------------------------------------------------>



## HWRenderer

<b> <説明> </b>

モデルの描画を行うコンポーネント


<br />
<br />

<b> <コンストラクタ> </b>


	@brief		HWRendererのコンストラクタ
	@detail		引数でモデルファイルのパスか、モデルハンドルを指定可
	HWRenderer()

	@brief		HWRendererのコンストラクタ
	@detail		モデルファイルのパスでも可
	@param[in]	int モデルハンドル
	HWRenderer(const int)

	@brief		HWRendererのコンストラクタ
	@detail		モデルファイルのパスでも可
	@param[in]	std::string 読み込むモデルのMV1ファイルのパス
	HWRenderer(const std::string&)


<b> <Getter関数> </b>


	@brief		モデルハンドルを取得する
	@return		int モデルハンドル
	int GetModelHandle()


<b> <Setter関数> </b>


	@brief		モデルハンドルを変更する(モデルの外見を変更する時など)
	@param[in]	int 新たなモデルハンドル 
	void SetModelHandle(const int _modelHandle)



<p align="right">(<a href="#top">トップへ</a>)</p> 



<!------------------------------------------------------------------------------------------------------------------>



## HWAnimator

<b> <説明> </b>

モデルのアニメーション制御用コンポーネント

先にHWRendererをアタッチするようにしてください

AnimLoad関数を実行すると AnimInfo 型で参照が返ってくるので、その値を操作することでアニメーションの設定が行えます

<br />
<br />

  <b> <AnimInfoクラス> </b>

	@brief		アニメーションをアタッチするモデル
	int modelHandle

	@brief		アニメーションのハンドル
	int animHandle

	@brief		animModelの登録したアニメーションのインデックス
	int animIndex

	@brief		Modelにアタッチした時のインデックス
	int attachIndex

	@brief		アニメーションファイル
	std::string filePath

	@brief		ループするか
	bool isLoop

	@brief		中断可能か
	bool interruption

	@brief		再生速度
	float playSpeed

	@brief		総再生時間
	float totalTime



  <b> <アニメーション制御の変数> </b>


	@brief		再生を停止
	bool isStop

	@brief		ブレンドのスピード
	float blendSpeed


  <b> <アニメーション制御の関数> </b>


	@brief		アニメーションをロードする ※ロードするアニメーションはアニメーションが一つしかついていないこと
	@param[in]	const std::string& 	アニメーションファイルのパス
	@param[in]	const int		読み込むアニメーションID
	@return		AnimInfo&	 	アニメーション情報(戻り値からパラメータを操作する)
	AnimInfo& AnimLoad(const std::string&, const int = 0)

	@brief		再生するアニメーションを指定
	@param[in]	const int 再生するアニメーションID
	void AnimChange(const int)


  <b> <Getter関数> </b>


	@brief		アニメーション情報を格納しているコンテナを取得する
	@return		const std::vector<std::unique_ptr<AnimInfo>>&	アニメーション情報を格納しているコンテナ
	const std::vector<std::unique_ptr<AnimInfo>>& GetAnimInfoVec()

	@brief		再生しているアニメーション1のインデックスを取得する
	@return		const int 再生中のアニメーションインデックス1
	const int GetPlayAnimId()

	@brief		ブレンドしているアニメーション1のインデックスを取得する
	@return		const int ブレンド中のアニメーションインデックス1
	const int GetBlendAnimId()

  <b> <Setter関数> </b>


	@brief		アニメーションの再生が終了した時に自動再生されるdefaultアニメーション(Idolアニメーションなど)
	@param[in]	const int デフォルトのアニメーションID
	void SetDefaultAnimId(const int) 

</body>

<p align="right">(<a href="#top">トップへ</a>)</p>



<!------------------------------------------------------------------------------------------------------------------>

## HWEffect

<b> <説明> </b>

Effekseerで作成したエフェクトを再生するコンポーネント

<br />
<br />

<b> <列挙体> </b>

	 @brief	再生終了時のアクション
	{
		//! 何もしない(0)
		None,
		//! ループする(1)
		Loop,
		//! 削除する(2)
		Destroy,
		//! 非アクティブにする(3)
		Disable,
		//! コールバック関数を呼ぶ(4)
		Callback,
	}


<b> <メンバ変数> </b>

	@brief		再生終了時のアクション
	StopAction stopAction;	

 
<b> <Getter関数> </b>

	@brief		再生状況を取得する
	@return		bool 再生中か 	
	bool IsPlay() { return isPlay; }

	@brief		エフェクトの再生速度を取得する
	@return		float 再生速度
	float GetPlaySpeed()

	@brief		再生中のエフェクトハンドル
	@return		int エフェクトハンドル
	int GetPlayEffectHandle()


<b> <Setter関数> </b>

	@brief		エフェクトを再生する
	void Play()

	@brief		再生を停止する
	void Stop()

	@brief		エフェクトの再生速度を設定する
	@rparam[in]	const float 再生速度
	void SetPlaySpeed(float _speed)

	@brief		エフェクト再生終了時に呼ばれるコールバック関数を登録する
	@rparam[in]	std::function<void()> 登録するコールバック関数
	void SetCallBack(std::function<void()> _callBack)

	@brief		エフェクトのカラーを設定する
	@rparam[in]	const Color& カラー
	void SetColor(const int r, const int g, const int b, const int a)


<p align="right">(<a href="#top">トップへ</a>)</p> 



<!------------------------------------------------------------------------------------------------------------------>


## InputSystem

<b> <説明> </b>

キー入力を検知し、入力時に設定したコールバック関数を呼び出すクラス


<br />
<br />

<b> <列挙体> </b>

	@brief	InputSystemの入力パラメータ
	enum class InputState
	{
		//! 入力待ち(0)
		Waiting,
		//! 入力した瞬間(1)
		Started,	
		//! 入力中(2)
		Performed,
		//! 入力終了(3)
		Canceled,
	}

	@brief	入力を取るコンソール
	enum class InputType
	{
		//! キーボード(0)
		Key,
		//! キーボード or Pad1(1)
		Key_Pad1,	
		//! Pad1(2)
		Pad1,
		//! Pad2(3)
		Pad2,
		//! Pad3(4)
		Pad3,
		//! Pad4(5)
		Pad4,
	}

<br />
<br />

<b> <コールバック時の引数> </b>

InputActionクラスのメンバクラスのため、記述するときは　InputAction::CCallBackContext にしてください

	@brief	コールバックで渡す情報
	struct CallBackContext
	{
		//! InputActionのパラメータ
		const InputState state;
		//! 入力したときの時間(ms)
		const unsigned int inputTime;
		//! 登録されているキー
		const std::vector<KeyInfo> key;
	}

<br />
<br />

<b> <キーコード追加> </b>

<body>
	
	@brief		マップにキーを登録する
	@detail		{} で複数入力可能
	@param[in]	const std::string	登録するキー
	@param[in]	const int		キーコード
	@param[in]	const InputType&	入力を見るコンソールの種類
	void AddKeyCode(const std::string& _key, const int _inputKey, const InputType& _inputType = InputType::Key)

 	@brief		マップにキーを登録する
	@detail		{} で複数入力可能
	@param[in]	const std::string&	 登録するキー
	@param[in]	const std::vector<int>&  キーコード
	@param[in]	const InputType&	入力を見るコンソールの種類
	void AddKeyCode(const std::string& _key, const std::vector<int>& _inputKey, const InputType& _inputType = InputType::Key)


 <b> <コールバック関数追加> </b>


	@brief		InputActionにコールバック関数を登録する
	@param[in]	const std::string&	登録するキー
	@param[in]	const std::function<void(InputAction::CallBackContext&)> 登録するコールバック関数
	@return		int			登録したコールバック関数のID
	int AddCallBack(const std::string& _key, const std::function<void(const InputAction::CallBackContext&)> _callBack)


<b> <キーコード削除> </b>


 	 @brief		マップに登録したキーコードを削除する
	 @detail	{} で複数入力可能
	 @param[in]	const std::string&	削除するキーの存在するキーマップ
	 @param[in]	const int		削除するキーコード
	 @param[in]	const InputType&	削除するキーのコンソールの種類
	 void DeleteKeyCode(const std::string& _key, const int _inputKey, const InputType& _inputType)

	@brief		マップに登録したキーコードを削除する
	@detail		{} で複数入力可能
	@param[in]	const std::string&	削除するキーの存在するキーマップ
	@param[in]	const std::vector<int>&	削除するキーコード
	@param[in]	const InputType&	削除するキーのコンソールの種類
	void DeleteKeyCode(const std::string& _key, const std::vector<int>& _inputKey, const InputType& _inputType) 


<b> <コールバック関数削除> </b>


 	@brief		InputActionにコールバック関数を登録する
	@param[in]	const std::string&	削除するキーの存在するキーマップ
	@param[in]	const int		削除するコールバック関数のID
	void DeleteCallBack(const std::string& _key, const int _id)


<b> <キーマップ削除> </b>


 	@brief		登録されているキーマップを削除する
	@param[in]	const std::string& _key	削除するキーマップのキー
	void DeleteKeyMap(const std::string& _key)
 
</body>

<b> <テストプロジェクト> </b>

<body>

	#include "HandlerWaltanForDxLib.h"

 	// プログラムは WinMain から始まります
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		// DXライブラリの初期化処理も兼ねている
		if (HandlerWaltan::Instance().Init() == -1)
		{
			return 0;
		}

		// Windowモードで起動
		SetGraphMode(840, 480, 16);
		ChangeWindowMode(true);

		//! ハンドラーやライフサイクルに基づいたタイミングでメソッドを自動的に呼び出すオブジェクト
		//! シングルトンで設計されているため、以下の方法以外でインスタンスを取得することはできない
		HandlerWaltan& HW = HandlerWaltan::Instance();


		//! InputSystem
		InputSystem* input = new InputSystem();

  		// アクション名と登録するキーを指定
		input->AddKeyCode("map1", KEY_INPUT_RETURN, InputType::Key);
		// アクション時に呼ばれるコールバック関数を登録
		input->AddCallBack("map1", [](InputAction::CallBackContext& _context)
		{
   		}

		// ソフトの終了 
		HandlerWaltan::End();
	}

</body>

<p align="right">(<a href="#top">トップへ</a>)</p>



<!------------------------------------------------------------------------------------------------------------------>



## PoolAllocator

<b> <説明> </b>

事前にメモリを確保しておくことによって動的にメモリを確保する効率を上げるためのクラス


<br />
<br />

<b> <テンプレート> </b>


	template<class T, size_t MAXSIZE>


<b> <メソッド> </b>


	@brief		メモリを確保する
	@return		確保したメモリ
	T* Alloc()

	@brief		メモリを解放する
	@param[in]	T* Allocで確保したメモリ
	void Free(T* _addr)
 

<p align="right">(<a href="#top">トップへ</a>)</p> 



<!------------------------------------------------------------------------------------------------------------------>



## CsvLoader

<b> <説明> </b>

csvファイルを読み込む

静的クラスのため、インスタンスは作成不可

<br />
<br />

<b> <メソッド> </b>


	@brief		csvファイルを読み込み、行区切り、カンマ区切りで文字列を返す
	@param[in]	std::string	読み込むcsvファイルのパス
	@return		std::vector<std::vector<std::string>> 読み込んだ文字列を返す(1次元 = 行, 2次元 = カンマ区切り)
	static std::vector<std::vector<std::string>> Load(const std::string _filePath)


<p align="right">(<a href="#top">トップへ</a>)</p> 



<!------------------------------------------------------------------------------------------------------------------>




<!------------------------------------------------------------------------------------------------------------------>

<!-- ## InputSystem ->

<b> <説明> </b>

コンポーネント


<br />
<br />

<b> <メソッド> </b>


<b> <メソッド1> </b>



<p align="right">(<a href="#top">トップへ</a>)</p> 



<!------------------------------------------------------------------------------------------------------------------>




