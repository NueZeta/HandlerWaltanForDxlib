#pragma once
#include "Utilities.h"


/**
* @author   Suzuki N
* @date     24/09/11
* @note		InputSystem関係をまとめたヘッダーファイル
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
* @enum		InputType
* @brief	入力を取るコンソール
*/
enum class InputType
{
	//! キーボード(0)
	Key,
	//! キーボード or Pad1(1)
	Key_Pad1 = DX_INPUT_KEY_PAD1,
	//! Pad1(2)
	Pad1 = DX_INPUT_PAD1,
	//! Pad2(3)
	Pad2 = DX_INPUT_PAD2,
	//! Pad3(4)
	Pad3 = DX_INPUT_PAD3,
	//! Pad4(5)
	Pad4 = DX_INPUT_PAD4,
};

/**
* @struct	KeyInfo
* @brief	キー情報
*/
struct KeyInfo
{
	//! キーコード
	unsigned int keyCode;
	//! コンソールの種類
	InputType inputType;
	//! 入力時間
	unsigned int inputTime;
	//! ボタン入力のパラメータ
	InputState inputState;
};

/**
 * @class	InputAction
 * @brief	アクションマップの情報
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
		const unsigned int inputTime;
		//! 登録されているキー
		const std::vector<KeyInfo> key;
		//! DInputの入力
		DINPUT_JOYSTATE dInput;
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
	std::unordered_map<int, std::function<void(const CallBackContext&)>> callBacks;

	/**
	 * @brief		InputActionのパラメーター
	 * @History		24/09/10 作成(Suzuki N)
	 */
	InputState inputState;

	/**
	 * @brief		登録したコールバック関数のID
	 * @History		24/10/02 作成(Suzuki N)
	 */
	int nextId;


private:
	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction() : inputState(InputState::Waiting), nextId(0)
	{
	}

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction(const unsigned int _keyCode, const InputType& _inputType) : inputState(InputState::Waiting), nextId(0)
	{
		AddKeyCode(_keyCode, _inputType);
	}

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction(const std::vector<unsigned int> _keyCodeVec, const InputType& _inputType) : inputState(InputState::Waiting), nextId(0)
	{
		AddKeyCode(_keyCodeVec, _inputType);
	}

public:

	/**
	 * @brief		アクションマップのステータスを返す
	 * return		InputStatus	アクションマップのステータス
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
	 * @brief		アクションマップのステータスを変更する
	 * param[in]	InputStatus	アクションマップのステータス
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void SetInputState(const InputState _state) { inputState = _state; }

	/**
	 * @brief		登録されたコールバック関数をすべて呼び出す
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void CallCallbacks(const InputAction::CallBackContext& _context)
	{
		for (auto it = callBacks.begin(); it != callBacks.end(); ++it)
			if(it->second)
				(it->second)(_context);
	}

	/**
	 * @brief		キーコードを追加する
	 * @detail		{} で複数選択可能
	 * @param[in]	int 追加するキーコード
	 * @param[in]	const InputType& 入力を見るコンソールの種類
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddKeyCode(const unsigned int _keyCode, const InputType& _inputType)
	{
		//! 登録するキー情報の初期化宣言
		KeyInfo keyInfo =
		{
			_keyCode,
			_inputType,
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
	 * @param[in]	const InputType& 入力を見るコンソールの種類
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddKeyCode(const std::vector<unsigned int> _keyCodeVec, const InputType& _inputType)
	{
		for (auto it = _keyCodeVec.begin(); it != _keyCodeVec.end(); ++it)
		{
			//! 登録するキー情報の初期化宣言
			KeyInfo keyInfo =
			{
				*it,
				_inputType,
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
	 * @return		const int	登録したコールバック関数のID
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	int AddCallBack(const std::function<void(const InputAction::CallBackContext&)> _callBack)
	{
		callBacks[nextId] = _callBack;
		return nextId++;
	}

	/**
	 * @brief		コールバック関数を削除する
	 * @param[in]	std::string	削除するキーの存在するキーマップ
	 * @param[in]	const int	削除するコールバック関数のID
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void DeleteCallBack(const int _id)
	{
		// キーコードが存在していれば削除する
		for (auto& it : callBacks)
			if(it.first == _id)
				it.second = nullptr;
	}
};

// 前方宣言
class HandlerWaltan;

/**
 * @class	InputSystem
 * @brief	入力の検知、入力時にコールバック関数を呼ぶクラス
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
	 * @brief		キーマップ
	 * @History		24/09/07 作成(Suzuki N)
	 */
	std::unordered_map<std::string, InputAction*> keyMap;

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
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	~InputSystem()
	{
		// keyMapを削除
		for (auto ptr : keyMap)
			delete ptr.second;
		keyMap.clear();

		// 登録していたInputSystemの登録情報を消す
		auto it = std::find(inputSystemVec.begin(), inputSystemVec.end(), this);
		if (it != inputSystemVec.end())
			inputSystemVec.erase(it);
	}

	/**
	 * @brief		Activeを変更する
	 * @param[in]	bool 変更後のbool値
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void SetActive(const bool _active) { active = _active; }


	/**
	 * @brief		特定のキーマップを取得する
	 * @param[in]	const string& キー
	 * @return		const InputAction& キー入力 
	 * @author		Suzuki N
	 * @date		24/10/30
	 */
	const InputAction& GetKeyMap(const std::string& _key) { return *keyMap[_key]; }



#pragma region キーコード追加

	/**
	 * @brief		マップにキーを登録する
	 * @detail		{} で複数入力可能
	 * @param[in]	std::string&	登録するキー
	 * @param[in]	const int		キーコード
	 * @param[in]	const InputType& 入力を見るコンソールの種類
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyCode(const std::string& _key, const unsigned int _inputKey, const InputType& _inputType = InputType::Key)
	{
		// キーが既に存在している場合は要素を追加する
		auto it = keyMap.find(_key);
		// 存在していた場合
		if (it != keyMap.end())
		{
			if (it->second->keyInfoVec.size() > 0)
				// キーコードがすでに登録済みでなければ
				for (auto it2 = it->second->keyInfoVec.begin(); it2 != it->second->keyInfoVec.end(); ++it2)
					if (it2->keyCode == _inputKey)
						return;

			it->second->AddKeyCode(_inputKey, _inputType);
		}
		// 存在していなかった場合は、新たにアクションマップを作成する
		else
			keyMap[_key] = new InputAction(_inputKey, _inputType);
	}

	/**
	 * @brief		マップにキーを登録する
	 * @detail		{} で複数入力可能
	 * @param[in]	const std::string&		 登録するキー
	 * @param[in]	const std::vector<int>&  キーコード
	 * @param[in]	const InputType& 入力を見るコンソールの種類
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyCode(const std::string& _key, const std::vector<unsigned int>& _inputKey, const InputType& _inputType = InputType::Key)
	{
		// キーが既に存在している場合は要素を追加する
		auto it = keyMap.find(_key);
		// 存在していた場合
		if (it != keyMap.end())
		{
			if (it->second->keyInfoVec.size() > 0)
				// キーコードがすでに登録済みでなければ
				for (auto it2 = it->second->keyInfoVec.begin(); it2 != it->second->keyInfoVec.end(); ++it2)
					for (auto keyIt = _inputKey.begin(); keyIt != _inputKey.end(); ++keyIt)
						if (it2->keyCode == *keyIt)
							break;

			it->second->AddKeyCode(_inputKey, _inputType);
		}
		// 存在していなかった場合は、新たにアクションマップを作成する
		else
			keyMap[_key] = new InputAction(_inputKey, _inputType);
	}

#pragma endregion

#pragma region キーコード削除

	/**
	 * @brief		マップに登録したキーコードを削除する
	 * @detail		{} で複数入力可能
	 * @param[in]	const std::string&	削除するキーの存在するキーマップ
	 * @param[in]	const int			削除するキーコード
	 * @param[in]	const InputType&	削除するコンソールの種類
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void DeleteKeyCode(const std::string& _key, const unsigned int _inputKey, const InputType& _inputType)
	{
		// キーマップが存在しない場合はそのまま終了
		auto keyMapIt = keyMap.find(_key);
		if (keyMapIt == keyMap.end())
			return;

		// キーコードが存在していれば削除する
		for (auto it = keyMapIt->second->keyInfoVec.begin(); it != keyMapIt->second->keyInfoVec.end(); ++it)
			if (it->keyCode == _inputKey && it->inputType == _inputType)
			{
				keyMapIt->second->keyInfoVec.erase(it);
				break;
			}
	}

	/**
	 * @brief		マップに登録したキーコードを削除する
	 * @detail		{} で複数入力可能
	 * @param[in]	const std::string&			削除するキーの存在するキーマップ
	 * @param[in]	const std::vector<int>&		削除するキーコード
	 * @param[in]	const InputType&			削除するコンソールの種類
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void DeleteKeyCode(const std::string& _key, const std::vector<unsigned int> _inputKey, const InputType& _inputType)
	{
		// キーマップが存在しない場合はそのまま終了
		auto keyMapIt = keyMap.find(_key);
		if (keyMapIt == keyMap.end())
			return;

		for(auto keyCodeIt = _inputKey.begin(); keyCodeIt != _inputKey.end(); ++keyCodeIt)
		{
			// キーコードが存在していれば削除する
			for (auto it = keyMapIt->second->keyInfoVec.begin(); it != keyMapIt->second->keyInfoVec.end(); ++it)
				if (it->keyCode == *keyCodeIt && it->inputType == _inputType)
				{
					keyMapIt->second->keyInfoVec.erase(it);
					break;
				}
		}
	}

#pragma endregion

#pragma region コールバック追加

	/**
	 * @brief		InputActionにコールバック関数を登録する
	 * @param[in]	std::string&	登録するキー
	 * @param[in]	std::function<void(InputAction::CallBackContext&)> 登録するコールバック関数
	 * @return		int	登録したコールバック関数のID
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	int AddCallBack(const std::string& _key, const std::function<void(const InputAction::CallBackContext&)> _callBack)
	{
		//! 登録したコールバック関数のID
		int id = -1;

		// キーが既に存在している場合は要素を追加する
		auto it = keyMap.find(_key);
		// 存在していた場合
		if (it != keyMap.end())
			id = it->second->AddCallBack(_callBack);
		// 存在していなかった場合は、新たにアクションマップを作成する
		else
		{
			keyMap[_key] = new InputAction();
			id = keyMap[_key]->AddCallBack(_callBack);
		}

		// 登録したIDを返す
		return id;
	}

#pragma endregion

#pragma region コールバック削除

	/**
	 * @brief		InputActionにコールバック関数を登録する
	 * @param[in]	std::string	削除するキーの存在するキーマップ
	 * @param[in]	const int	削除するコールバック関数のID
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void DeleteCallBack(const std::string& _key, const int _id)
	{
		// キーマップが存在しない場合はそのまま終了
		auto keyMapIt = keyMap.find(_key);
		if (keyMapIt == keyMap.end())
			return;

		// キーコードが存在していれば削除する
		keyMapIt->second->DeleteCallBack(_id);
	}

#pragma endregion

#pragma region キーマップ削除

	/**
	 * @brief		登録されているキーマップを削除する
	 * @param[in]	std::string& _key 削除するキーマップのキー
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	void DeleteKeyMap(const std::string& _key)
	{
		// キーマップが存在しない場合はそのまま終了
		auto keyMapIt = keyMap.find(_key);
		if (keyMapIt == keyMap.end())
			return;

		// 削除処理
		keyMap.erase(keyMapIt);
	}

#pragma endregion



private:

	/**
	 * @brief		アクションマップに登録されているキーを監視する
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void KeyCheck()
	{
		// 登録されているキーの入力状態を監視
		for (auto it = keyMap.begin(); it != keyMap.end(); ++it)
		{
			//! このアクションマップ内で入力があったか
			bool isInput = false;
			//! 入力時間
			unsigned int inputTime = 0;			
			//! DInputの入力
			DINPUT_JOYSTATE dInput;
			// 初期化
			memset(&dInput, NULL, sizeof(DINPUT_JOYSTATE));

			for (auto it2 = it->second->GetKeyInfoRef().begin(); it2 != it->second->GetKeyInfoRef().end(); ++it2)
			{
				//! DInputの入力があった場合、入力があったことにする
				bool isDInput = false;
				// DInputの入力を取得する
				// 入力タイプが KEY or Pad1 の場合はPad1の入力を取得する 
				if(it2->inputType != InputType::Key && it2->keyCode == PAD_INPUT_DINPUT)
				{
					GetJoypadDirectInputState(it2->inputType == InputType::Key_Pad1 ? (int)InputType::Pad1 : (int)it2->inputType, &dInput);					

					//
					// パッドの入力があったかを調べる
					// 
					if (dInput.X != NULL || dInput.Y != NULL || dInput.Z != NULL || dInput.Rx != NULL || dInput.Ry != NULL || dInput.Rz != NULL ||
						dInput.Slider[0] != NULL || dInput.Slider[1] != NULL)
						isDInput = true;
					if(!isDInput)
						for (int i = 0; i < 4; ++i)
							if (dInput.POV[i] != 0xffffffff) isDInput = true;
					if (!isDInput)
						for (int i = 0; i < 32; ++i)
							if (dInput.Buttons[i] != 0) isDInput = true;
				}

				// 登録されたキーの入力状態を確認
				if ((it2->inputType == InputType::Key && CheckHitKey(it2->keyCode)) ||
					(GetJoypadInputState((int)it2->inputType) & it2->keyCode) ||
					(it2->keyCode == PAD_INPUT_DINPUT && isDInput))
				{
					// 入力があった
					isInput = true;

					// キーの入力状態でパラメーターを変える
					switch (it2->inputState)
					{
					case InputState::Waiting:
						it2->inputState = InputState::Started;
						// 実行時間を保管
						inputTime = it2->inputTime = GetNowCount();
						break;

					case InputState::Started:
						// 入力中にパラメーターを変更
						it2->inputState = InputState::Performed;
						inputTime = it2->inputTime;
						break;

					case InputState::Performed:
						// 押下状態の継続なため、パラメーターの変更はなし
						inputTime = it2->inputTime;
						break;

					case InputState::Canceled:
						it2->inputState = InputState::Started;
						// 実行時間を保管
						inputTime = it2->inputTime = GetNowCount();
						break;
					}
				}
				// 入力がなかった
				else
				{
					// キーの入力状態でパラメーターを変える
					switch (it2->inputState)
					{
					case InputState::Waiting:
						inputTime = it2->inputTime;
						// 待機状態を継続しているため、変更なし
						break;

					case InputState::Started:
						// 入力終了のパラメーターに変更
						it2->inputState = InputState::Canceled;
						inputTime = it2->inputTime;
						break;

					case InputState::Performed:
						// 入力終了のパラメーターに変更
						it2->inputState = InputState::Canceled;
						inputTime = it2->inputTime;
						break;

					case InputState::Canceled:
						// 入力待機のパラメーターに変更
						it2->inputState = InputState::Waiting;
						inputTime = it2->inputTime;
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
				it->second->CallCallbacks({ it->second->GetInputState(),inputTime, it->second->GetKeyInfoVec(), dInput});
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
					it->second->CallCallbacks({ it->second->GetInputState(),inputTime, it->second->GetKeyInfoVec(), dInput });
					break;
				case InputState::Performed:
					it->second->SetInputState(InputState::Canceled);
					// 登録されたコールバック関数をすべて呼び出す
					it->second->CallCallbacks({ it->second->GetInputState(),inputTime, it->second->GetKeyInfoVec(),dInput });
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