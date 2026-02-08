#include "h/HWInspector.h"

bool HWInspector::active = false;
std::map <std::string,Window> HWInspector::window;
Window* HWInspector::clickedWindow = nullptr;


void HWInspector::CreateInspector(const std::string& name)
{
	window[name] = Window(window.size() + 1);
	window[name].active = true;
	window[name].height = WINDOW_SIZE_Y;
	window[name].width = WINDOW_SIZE_X;
	window[name].position = VGet(0, 200, 0);
}

void HWInspector::Register(const std::string& inspectorName, const std::string& name, void* data, InspectorItem::Type type)
{
	// 登録するパラメータの作成
	InspectorItem item
	{
		name,
		(void*)data,
		type,
		-1,
		false
	};
	if (type == InspectorItem::INT || type == InspectorItem::FLOAT)
	{
		item.inputHandle = MakeKeyInput(10, TRUE, TRUE, TRUE);
	}

	// インスペクターウィンドウが存在しなければ作成
	if (window.find(inspectorName) == window.end())
	{
		CreateInspector(inspectorName);
	}
	window[inspectorName].items.push_back(item);
}

void HWInspector::Deregister(const std::string& inspectorName, const std::string& name)
{
	if (window.find(inspectorName) == window.end())
	{
		return;
	}
	
	for (auto it = window[inspectorName].items.begin(); it != window[inspectorName].items.end(); ) {
		if (it->name == name) {
			it = window[inspectorName].items.erase(it); // 削除後の次の要素を指すイテレータが返る
		}
		else {
			++it;
		}
	}
}

void HWInspector::Update()
{
	if (!active) return;

	static int prevMouse = GetMouseInput();
	int mouse = GetMouseInput();

	// 左クリックした際に、いずれかのインスペクターウィンドウに重なっているかを判定
	if ((!(prevMouse & MOUSE_INPUT_LEFT) && (mouse & MOUSE_INPUT_LEFT))
		&& !clickedWindow)
	{
		//! マウス座標
		int mx, my;
		GetMousePoint(&mx, &my);

		for (auto it = window.rbegin(); it != window.rend(); ++it)
		{
			if (!it->second.active) continue;

			// 別ウィンドウをクリックした際、コールバックを呼び出すためにbreakしない
			if (mx >= it->second.position.x && mx <= it->second.position.x + it->second.width &&
				my >= it->second.position.y && my <= it->second.position.y + it->second.height &&
				!clickedWindow)
			{
				clickedWindow = &it->second;
				clickedWindow->OnMouseDown(mx, my);
			}
			else
			{
				it->second.OnMouseOut();
			}
		}
	}

	// 左クリックを離した際に、クリックされているウィンドウがあればそれを解放
	if (!(mouse & MOUSE_INPUT_LEFT) && clickedWindow)
	{
		clickedWindow->OnMouseUp();
		clickedWindow = nullptr;
	}

	for (auto it = window.begin(); it != window.end(); ++it)
	{
		if (!it->second.active) continue;

		// 描画処理
		it->second.Render();
	}

	// マウスの状態を保存
	prevMouse = mouse;
}
