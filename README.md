<div id="top"></div>

## 使用技術一覧

<!-- シールド一覧 -->

</p>

## 目次

1. [プロジェクトについて](#プロジェクトについて)
2. [環境](#環境)

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

	/**
	 * @brief		コンポーネントを追加する
	 * @param[in]		アタッチするコンポーネント
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void AddMyComponent(unique_ptr<MyComponent> _component)


 	/**
	 * @brief		指定のコンポーネントを返す
	 * @return		アタッチされていた場合はインスタンスを返し、それ以外ならnullPtrを返す
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
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

	/**
	 * @brief		アタッチされているmyGameObjectを返す
	 * @return		コンポーネントがアタッチされているmyGameObject
	 * @date		24/06/17
	 */
	MyGameObject* GetMyGameObject()


 	/**
	 * @brief		myGameObjectにアタッチされた瞬間に働く
	 * @ditail		仮想関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Start()


 	/**
	 * @brief		毎フレーム呼ばれるメソッド
	 * @ditail		仮想関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Update()


 	/**
	 * @brief		コライダー衝突時に働くメソッド
	 * @ditail		仮想関数
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionEnter()


 	/**
	 * @brief		コライダー衝突中に働くメソッド
	 * @ditail		仮想関数
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionStay()


	/**
	 * @brief		コライダー衝突が解除時に働くメソッド
	 * @ditail		仮想関数
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
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




