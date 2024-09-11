#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <chrono>
#include <thread>
#include <future>
#include <cstdio>
#include <cstdint>
#include "Syslog.h"
#include "DxLib.h"


/**
* @author   Suzuki N
* @date     24/07/20
* @note		汎用的なクラスの定義をまとめたヘッダーファイル
*/


/**
* @enum		InputState
* @brief	InputSystemの入力パラメータ
*/
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
};

/**
* @struct	KeyInfo
* @brief	キー情報
*/
struct KeyInfo
{
	//! キーコード
	int keyCode;
	//! 入力時間
	unsigned int inputTyme;
	//! ボタン入力のパラメータ
	InputState inputState;
};

/**
 * @class		InputAction
 * @brief		キーマップの情報
 */
class InputAction
{
	friend class InputSystem;

public:
	/**
	* @struct	CallBackContext
	* @brief	コールバックで渡す情報
	*/
	struct CallBackContext
	{
		//! InputActionのパラメータ
		const InputState state;
		//! 入力したときの時間(ms)
		const unsigned int inputTyme;
	};

private:
	/*     メンバ変数     */

	/**
	 * @brief		キー情報
	 * @History		24/09/10 作成(Suzuki N)
	 */
	std::vector<KeyInfo> keyInfoVec;

	/**
	 * @brief		登録されたコールバック関数
	 * @History		24/09/10 作成(Suzuki N)
	 */
	std::vector<std::function<void(CallBackContext&)>> callBacks;

	/**
	 * @brief		InputActionのパラメーター
	 * @History		24/09/10 作成(Suzuki N)
	 */
	InputState inputState;


private:
	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction() : inputState(InputState::Waiting)
	{
	}

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction(const int _keyCode) : inputState(InputState::Waiting)
	{
		AddKeyCode(_keyCode);
	}

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction(const std::vector<int> _keyCodeVec) : inputState(InputState::Waiting)
	{
		AddKeyCode(_keyCodeVec);
	}

public:

	/**
	 * @brief		キーマップのステータスを返す
	 * return		InputStatus	キーマップのステータス
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputState GetInputState() { return inputState; }

	/**
	 * @brief		キー情報を返す
	 * return		std::vector<KeyInfo>	登録されたキー情報
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	std::vector<KeyInfo> GetKeyInfoVec() { return keyInfoVec; }

private:

	/**
	 * @brief		キー情報を返す
	 * return		std::vector<KeyInfo>	登録されたキー情報
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	std::vector<KeyInfo>& GetKeyInfoRef() { return keyInfoVec; }

	/**
	 * @brief		キーマップのステータスを変更する
	 * param[in]	InputStatus	キーマップのステータス
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void SetInputState(InputState _state) { inputState = _state; }

	/**
	 * @brief		登録されたコールバック関数をすべて呼び出す
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void CallCallbacks(InputAction::CallBackContext _context)
	{
		for (auto it = callBacks.begin(); it != callBacks.end(); ++it)
			(*it)(_context);
	}

	/**
	 * @brief		キーコードを追加する
	 * @detail		{} で複数選択可能
	 * @param[in]	int 追加するキーコード
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddKeyCode(const int _keyCode)
	{
		//! 登録するキー情報の初期化宣言
		KeyInfo keyInfo =
		{
			_keyCode,
			0,
			InputState::Waiting,
		};

		// キー情報を登録
		keyInfoVec.push_back(keyInfo);
	}

	/**
	 * @brief		キーコードを追加する
	 * @detail		{} で複数選択可能
	 * @param[in]	std::vector<int> 追加するキーコード
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddKeyCode(const std::vector<int> _keyCodeVec)
	{
		for (auto it = _keyCodeVec.begin(); it != _keyCodeVec.end(); ++it)
		{
			//! 登録するキー情報の初期化宣言
			KeyInfo keyInfo =
			{
				*it,
				0,
				InputState::Waiting,
			};

			// キー情報を登録
			keyInfoVec.push_back(keyInfo);
		}
	}

	/**
	 * @brief		コールバック関数を追加する
	 * @param[in]	std::function<void(InputAction::CallBackContext&>)> 追加するコールバック関数
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddCallBack(const std::function<void(InputAction::CallBackContext&)> _callBack)
	{
		callBacks.push_back(_callBack);
	}
};


/**
 * @class		PoolAllocator
 * @brief		メモリ管理を高速化するためのメモリアロケーター
 */
template<class T, size_t MAXSIZE>
class PoolAllocator
{
public:

	/*     メンバ変数     */

	union Block
	{
		char pool[sizeof(T)];
		Block* nextBlock;
	};

	/**
	 * @brief		メモリプール
	 * @History		24/09/01 作成(Suzuki N)
	 */
	Block block[MAXSIZE];

	/**
	 * @brief		空きメモリブロックの戦闘
	 * @History		24/09/01 作成(Suzuki N)
	 */
	Block* freeBlockHead;


public:

	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	PoolAllocator()
	{
		// メモリブロック同士を連結する
		for (size_t i = 0; i < MAXSIZE - 1; ++i)
			block[i]->nextBlock = &block[i + 1];
		// 末尾は nullptr
		block[MAXSIZE - 1].nextBlock = nullptr;

		// 空きメモリの先頭の初期値は block の先頭
		freeBlockHead = block;
	}

	/**
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	~PoolAllocator() {}

	/**
	 * @brief		メモリを確保する
	 * @return		確保したメモリ
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	T* Alloc()
	{
		// 空きメモリブロックがない場合、nullptr を返す
		if (freeBlockHead == nullptr)
			return nullptr;

		//! 確保したメモリ
		T* ret = reinterpret_cast<T*>(freeBlockHead);
		// 空きメモリブロックを更新
		freeBlockHead = freeBlockHead->nextBlock;

		// 動的にコンストラクタを呼ぶ
		return new(ret) T();
	}

	/**
	 * @brief		メモリを解放する
	 * @param[in]	T* Allocで確保したメモリ
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	void Free(T* _addr)
	{
		if (_addr == nullptr)
			return;

		// 明示的にデストラクタを呼ぶ
		_addr->~T();

		//! 解放するアドレス
		Block* freeBlock = reinterpret_cast<Block*>(_addr);

		// 解放したブロックの後ろにfreeBlockHeadをつなげる
		freeBlockHead->nextBlock = freeBlock;
		// 空きメモリブロックを更新
		freeBlockHead = freeBlock;
	}
};


// 前方宣言
class HandlerWaltan;

/**
 * @class		InputSystem
 * @brief		入力の検知、入力時にコールバック関数を呼ぶクラス
 */
class InputSystem
{
private:

	friend class HandlerWaltan;

	/*     メンバ変数     */

	/**
	 * @brief		アクティブ
	 * @History		24/09/07 作成(Suzuki N)
	 */
	bool active;

	/**
	 * @brief		キーアクション
	 * @History		24/09/07 作成(Suzuki N)
	 */
	std::map<std::string, InputAction*> keyMap;

	/**
	 * @brief		生成されたInputSystemのインスタンス
	 * @History		24/09/10 作成(Suzuki N)
	 */
	static std::vector<InputSystem*> inputSystemVec;


public:

	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	InputSystem() : active(true)
	{
		inputSystemVec.push_back(this);
	}

	/**
	 * @brief		Activeを変更する
	 * @param[in]	bool 変更後のbool値
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void SetActive(bool _active) { active = _active; }

	/**
	 * @brief		マップにキーを登録する
	 * @detail		{} で複数入力可能
	 * @param[in]	std::string	登録するキー
	 * @param[in]	int			キーコード
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyCode(const std::string _key, int _inputKey)
	{
		// キーが既に存在している場合は要素を追加する
		auto it = keyMap.find(_key);
		// 存在していた場合
		if (it != keyMap.end())
			it->second->AddKeyCode(_inputKey);
		// 存在していなかった場合は、新たにインスタンスを作成する
		else
			keyMap[_key] = new InputAction(_inputKey);
	}

	/**
	 * @brief		マップにキーを登録する
	 * @detail		{} で複数入力可能
	 * @param[in]	std::string		 登録するキー
	 * @param[in]	std::vector<int> キーコード
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyCode(const std::string _key, std::vector<int> _inputKey)
	{
		// キーが既に存在している場合は要素を追加する
		auto it = keyMap.find(_key);
		// 存在していた場合
		if (it != keyMap.end())
			it->second->AddKeyCode(_inputKey);
		// 存在していなかった場合は、新たにインスタンスを作成する
		else
			keyMap[_key] = new InputAction(_inputKey);
	}

	/**
	 * @brief		InputActionにコールバック関数を登録する
	 * @param[in]	std::function<void(InputAction::CallBackContext&)> 登録するコールバック関数
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void AddCallBack(const std::string _key, std::function<void(InputAction::CallBackContext&)> _callBack)
	{
		// キーが既に存在している場合は要素を追加する
		auto it = keyMap.find(_key);
		// 存在していた場合
		if (it != keyMap.end())
			it->second->AddCallBack(_callBack);
		// 存在していなかった場合は、新たにインスタンスを作成する
		else
		{
			keyMap[_key] = new InputAction();
			keyMap[_key]->AddCallBack(_callBack);
		}
	}

private:

	/**
	 * @brief		キーマップに登録されているキーを監視する
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void KeyCheck()
	{
		// 登録されているキーの入力状態を監視
		for (auto it = keyMap.begin(); it != keyMap.end(); ++it)
		{
			//! このキーマップ内で入力があったか
			bool isInput = false;
			//! 入力時間
			unsigned int inputTyme = 0;

			for (auto it2 = it->second->GetKeyInfoRef().begin(); it2 != it->second->GetKeyInfoRef().end(); ++it2)
			{
				// 登録されたキーの入力状態を確認
				if (CheckHitKey((*it2).keyCode))
				{
					// 入力があった
					isInput = true;

					// キーの入力状態でパラメーターを変える
					switch ((*it2).inputState)
					{
					case InputState::Waiting:
						(*it2).inputState = InputState::Started;
						// 実行時間を保管
						inputTyme = (*it2).inputTyme = GetNowCount();	
						break;

					case InputState::Started:
						// 入力中にパラメーターを変更
						(*it2).inputState = InputState::Performed;
						inputTyme = (*it2).inputTyme;
						break;

					case InputState::Performed:
						// 押下状態の継続なため、パラメーターの変更はなし
						inputTyme = (*it2).inputTyme;
						break;

					case InputState::Canceled:
						(*it2).inputState = InputState::Started;
						// 実行時間を保管
						inputTyme = (*it2).inputTyme = GetNowCount();
						break;
					}
				}
				// 入力がなかった
				else
				{
					// キーの入力状態でパラメーターを変える
					switch ((*it2).inputState)
					{
					case InputState::Waiting:
						inputTyme = (*it2).inputTyme;
						// 待機状態を継続しているため、変更なし
						break;

					case InputState::Started:
						// 入力終了のパラメーターに変更
						(*it2).inputState = InputState::Canceled;
						inputTyme = (*it2).inputTyme;
						break;

					case InputState::Performed:
						// 入力終了のパラメーターに変更
						(*it2).inputState = InputState::Canceled;
						inputTyme = (*it2).inputTyme;
						break;

					case InputState::Canceled:
						// 入力待機のパラメーターに変更
						(*it2).inputState = InputState::Waiting;
						inputTyme = (*it2).inputTyme;
						break;
					}
				}
			}

			// 入力があった場合
			if (isInput)
			{
				// キーマップのInputStatusを変更する
				switch (it->second->GetInputState())
				{
				case InputState::Waiting:
					it->second->SetInputState(InputState::Started);
					break;
				case InputState::Started:
					it->second->SetInputState(InputState::Performed);
					break;
				case InputState::Performed:
					// 入力状態が継続なため、ステータスの変更なし
					break;
				case InputState::Canceled:
					it->second->SetInputState(InputState::Started);
					break;
				}
				// 登録されたコールバック関数をすべて呼び出す
				it->second->CallCallbacks({ it->second->GetInputState(),inputTyme, });
			}
			// 入力がなかった場合
			else
			{
				// キーマップのInputStatusを変更する
				switch (it->second->GetInputState())
				{
				case InputState::Waiting:
					// 入力状態が継続なため、ステータスの変更なし
					break;
				case InputState::Started:
					it->second->SetInputState(InputState::Canceled);
					// 登録されたコールバック関数をすべて呼び出す
					it->second->CallCallbacks({ it->second->GetInputState(),inputTyme, });
					break;
				case InputState::Performed:
					it->second->SetInputState(InputState::Canceled);
					// 登録されたコールバック関数をすべて呼び出す
					it->second->CallCallbacks({ it->second->GetInputState(),inputTyme, });
					break;
				case InputState::Canceled:
					it->second->SetInputState(InputState::Waiting);
					break;
				}
			}
		}
	}

	/**
	 * @brief		毎F呼ばれるメソッド
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void Update()
	{
		KeyCheck();
	}
};