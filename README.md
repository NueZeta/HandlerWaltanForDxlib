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

1. [MyGameObject](#mygameobject)
2. [MyComponent](#mycomponent)
3. [MyTransform](#mytransform)
4. [MyCollider](#mycollider)
5. [MyAnimator](#myanimator)



<!-- READMEの作成方法のテンプレート -->
<br />
<div align="right">
    <a href="https://qiita.com/shun198/items/c983c713452c041ef787"><strong>READMEのテンプレート »</strong></a>
</div>
\</><br />
<!-- プロジェクト名を記載 -->


## プロジェクトについて

来年に製作する予定の自作エンジンに向けて、unityと同じ感覚で使えるコンポーネント思考の
ライブラリを製作する。

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
	　　入っている『プロジェクトに追加すべきファイル』フォルダのパスを入力してから、
	　　再度ダイアログ右下にある『適用(A)』ボタンを押します。
	　　（ パスの例→　　c:\HandlerWaltanForDxlib\プロジェクトに追加すべきファイル
	　　尚、ＤＸライブラリをマイドキュメントフォルダに入れるとこれらのパス指定が面倒になりますので
	　　ＤＸライブラリはなるべく浅いフォルダに入れておくことをお勧めします ）

	⑦　次に左側のリストから『構成プロパティ』→『リンカー』→『全般』を選びます。
	
	⑧　次に右側に表示されている『追加のライブラリディレクトリ』の項目に⑥と全く同じＤＸライブラリの
	　　パッケージ内に入っている『プロジェクトに追加すべきファイル』フォルダのパスを
	　　入力してから、再度ダイアログ右下にある『適用(A)』ボタンを押します。

   	⑨ 　次に左側のリストから『リンカー』→『入力』を選びます。
      　　　パッケージ内に入っている『追加の依存ファイル』に『プロジェクトに追加すべきファイル』フォルダのパスに
	 　『¥HandlerWaltanForDxLib.lib』を足したものを入力してください。

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

## MyGameObject

<b> <説明> </b>

アタッチされているコンポーネントの管理

コンポーネントのアタッチ、デタッチ

<br />
<br />

<b> <メソッド> </b>

<body>

	@brief		オブジェクトの名前
	std::string name;

	@brief		ハンドラーやUpdateメソッドの優先順位(降順)
  	※初期値は 0
	int priority;
	

	@brief		コンポーネントを追加する
	@param[in]	アタッチするコンポーネント
	void AddMyComponent(unique_ptr<MyComponent> _component)


 	@brief		指定のコンポーネントを返す
	@return		アタッチされていた場合はインスタンスを返し、それ以外ならnullPtrを返す
	template<typename T>
	T* GetMyComponent()

</body>



<p align="right">(<a href="#top">トップへ</a>)</p>



## MyComponent

<b> <説明> </b>

すべてのコンポーネントの基底クラス


<br />
<br />

<b> <メソッド> </b>

<body>

	@brief		アタッチされているmyGameObjectを返す
	@return		コンポーネントがアタッチされているmyGameObject
	MyGameObject* GetMyGameObject()


	@brief		myGameObjectにアタッチされた瞬間に働く
	@ditail		仮想関数
	virtual void Start()


 	@brief		毎フレーム呼ばれるメソッド
	@ditail		仮想関数
	virtual void Update()


 	@brief		コライダー衝突時に働くメソッド
	@ditail		仮想関数
	virtual void OnCollisionEnter()


 	@brief		コライダー衝突中に働くメソッド
	@ditail		仮想関数
	virtual void OnCollisionStay()


	@brief		コライダー衝突が解除時に働くメソッド
	@ditail		仮想関数
	virtual void OnCollisionExit()

</body>

<p align="right">(<a href="#top">トップへ</a>)</p>



## MyTransform

<b> <説明> </b>

座標、回転などを管理するコンポーネント

<br />
<br />

<b> <メソッド> </b>

<body>



</body>

<p align="right">(<a href="#top">トップへ</a>)</p>



## MyCollider



<p align="right">(<a href="#top">トップへ</a>)</p>



## MyAnimator



<p align="right">(<a href="#top">トップへ</a>)</p>




