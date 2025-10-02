#pragma once
#include "Utilities.h"


/**
* @author   NZ
* @date     25/09/19
* @note		GUIインスペクターの定義
*/


#define WINDOW_BACK_COLOR GetColor(50, 50, 50)

#define WINDOW_TEXT_OFFSET_X 10
#define WINDOW_TEXT_OFFSET_Y 5

// 角の丸み
#define WINDOW_ROUNDEDCORNERE 10

#define WINDOW_HEADING_SIZE 25
#define ITEM_COLLISION_SIZE 25

#define WINDOW_HEADING_COLOR_1 GetColor(10, 10, 255)
#define WINDOW_HEADING_COLOR_1_HIGHTLIGHTS GetColor(10, 10, 170)

#define WINDOW_SIZE_X 200
#define WINDOW_SIZE_Y 300


/**
 * @class	InspectorItem
 * @brief	インスペクターに登録されるパラメータ群
 */
struct InspectorItem 
{
	std::string name;
	void* data;
	enum Type { INT, FLOAT } type;
	int inputHandle;
	bool isSelect;
};

/**
 * @class	Window
 * @brief	インスペクターウィンドウ
 */
class Window
{
public:

	//! 登録されているパラメータ
	std::vector<InspectorItem> items;
	//! インスペクターの描画の有効/無効
	bool active;
	//! インスペクターのサイズY
	int height;
	//! インスペクターのサイズX
	int width;
	//! インスペクターの座標
	VECTOR position;
	//! インスペクターID
	int id;
	//! クリックされているか
	bool isClicked;
	//! クリックされた座標と、ウィンドウの座標との差分
	int clickOffsetX;
	int clickOffsetY;


	Window()
	{ }
	Window(int _id)
		: active(false)
		, height(WINDOW_SIZE_Y)
		, width(WINDOW_SIZE_X)
		, position(VGet(0, 0, 0))
		, id(_id)
		, isClicked(false)
		, clickOffsetX(0)
		, clickOffsetY(0)
	{}

	void Render()
	{
		// ウィンドウがクリックされている場合、マウス座標に追従して移動
		if (isClicked)
		{
			int mx, my;
			GetMousePoint(&mx, &my);
			position.x = mx - clickOffsetX;
			position.y = my - clickOffsetY;
		}

		//
		// ウィンドウの描画
		//

		// 背景
		DrawRoundRect(position.x, position.y,
			position.x + width, position.y + height,
			WINDOW_ROUNDEDCORNERE, WINDOW_ROUNDEDCORNERE, // 角の丸み
			WINDOW_BACK_COLOR, TRUE);

		// 見出し
		DrawRoundRect( position.x, position.y,
			position.x + width, position.y + WINDOW_HEADING_SIZE,
			WINDOW_ROUNDEDCORNERE, WINDOW_ROUNDEDCORNERE, // 角の丸み
			isClicked == true ? WINDOW_HEADING_COLOR_1_HIGHTLIGHTS : WINDOW_HEADING_COLOR_1,
			TRUE);
		DrawBox(position.x, position.y + WINDOW_ROUNDEDCORNERE, // 底辺のみ角の丸みを消す
			position.x + width, position.y + WINDOW_HEADING_SIZE,
			isClicked == true ? WINDOW_HEADING_COLOR_1_HIGHTLIGHTS : WINDOW_HEADING_COLOR_1,
			TRUE);

		// 見出しテキスト
		DrawFormatString(position.x, position.y + WINDOW_TEXT_OFFSET_Y,
			GetColor(255, 255, 255),
			"  config %d", id);


		//
		// 登録されているパラメータの描画
		//


		for (int i = 0; i < items.size(); ++i)
		{
			int textPosX = position.x + WINDOW_TEXT_OFFSET_X;
			int textPosY = position.y + WINDOW_HEADING_SIZE + WINDOW_TEXT_OFFSET_Y + (20 * i);

			// パラメータ名
			DrawFormatString(textPosX, textPosY,
				GetColor(255, 255, 255),
				"%s", items[i].name.c_str());

			// パラメータ値
			switch (items[i].type)
			{
			case InspectorItem::INT:
				if (items[i].isSelect)
				{
					DrawKeyInputString(textPosX + 100, textPosY,
						items[i].inputHandle);
					if(CheckKeyInput(items[i].inputHandle) > 0)
					{
						items[i].isSelect = false;
						*static_cast<int*>(items[i].data) = GetKeyInputNumber(items[i].inputHandle);
						SetKeyInputString("", items[i].inputHandle); // 入力欄を空にする
					}
				}
				else
				{
					DrawFormatString(textPosX + 100, textPosY,
						GetColor(255, 255, 255),
						"%d", *(int*)items[i].data);
				}
				break;
			case InspectorItem::FLOAT:
				if (items[i].isSelect)
				{
					DrawKeyInputString(textPosX + 100, textPosY,
						items[i].inputHandle);
					if (CheckKeyInput(items[i].inputHandle) > 0)
					{
						items[i].isSelect = false;
						char buf[10];
						GetKeyInputString(buf, items[i].inputHandle);

						*static_cast<float*>(items[i].data) = std::stof(buf);
						SetKeyInputString("",items[i].inputHandle); // 入力欄を空にする
					}
				}
				else
				{
					DrawFormatString(textPosX + 100, textPosY,
						GetColor(255, 255, 255),
						"%.2f", *(float*)items[i].data);
				}
				break;
			}
		}
	}

	void OnMouseDown(int _mx, int _my)
	{
		// 見出し部分がクリックされた場合は移動処理
		if (_my > position.y && _my < position.y + WINDOW_HEADING_SIZE)
		{
			isClicked = true;

			// クリックされた座標と、ウィンドウの座標との差分を保存
			clickOffsetX = _mx - position.x;
			clickOffsetY = _my - position.y;

			// 入力欄の選択を解除
			OnMouseOut();
		}

		for (int i = 0; i < items.size(); ++i)
		{
			if (_my > position.y + WINDOW_HEADING_SIZE + ITEM_COLLISION_SIZE * i &&
				_my < position.y + WINDOW_HEADING_SIZE + ITEM_COLLISION_SIZE * (i + 1))
			{
				SetActiveKeyInput(items[i].inputHandle);
				items[i].isSelect = true;

				for (auto& item : items)
				{
					if (&item != &items[i])
					{
						item.isSelect = false;
						SetKeyInputString("", item.inputHandle); // 他の入力欄を空にする
					}
				}
				break;
			}
		}
	}

	void OnMouseUp()
	{
		isClicked = false;

		clickOffsetX = clickOffsetY = 0;
	}

	void OnMouseOut()
	{
		for (auto& item : items)
		{
			item.isSelect = false;
			SetKeyInputString("", item.inputHandle); // 他の入力欄を空にする
		}
	}
};


/**
 * @class	HWInspector
 * @brief	GUIインスペクター
 */
class HWInspector
{
	friend class HandlerWaltan;

public:

	/*     メンバ変数     */

	//! ウィンドウ全ての描画の有効/無効
	static bool active;
	//! 作成されたウィンドウ
	static std::map<std::string,Window> window;
	
	/*     メソッド     */

	/**
	 * @brief		ウィンドウの作成
	 * @param[in]	name	ウィンドウ名
	 * @author		NZ
	 * @date		25/09/19
	 */
	static void CreateInspector(const std::string& name);

	/**
	 * @brief		インスペクターへの登録
	 * @param[in]	inspectorName	登録するインスペクター名
	 * @param[in]	name	パラメータ名
	 * @param[in]	data	パラメータのアドレス
	 * @param[in]	type	パラメータの型
	 * @author		NZ
	 * @date		25/09/19
	 */
	static void Register(const std::string& inspectorName, const std::string& name, 
		void* data, InspectorItem::Type type);

	/**
	 * @brief		インスペクターの描画
	 * @author		NZ
	 * @date		25/09/19
	 */
	static void Update();


private:

	//! クリックされているウィンドウ
	static Window* clickedWindow;
};