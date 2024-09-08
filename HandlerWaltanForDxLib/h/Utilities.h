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
	~PoolAllocator(){}

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


/**
 * @class		InputSystem
 * @brief		入力の検知、入力時にコールバック関数を呼ぶクラス
 */
class InputSystem
{
private:

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
	std::map<std::string, std::vector<std::atomic<KeyInfo>>> keyMap;

	/**
	 * @brief		キーチェックを別スレッドで回す
	 * @History		24/09/07 作成(Suzuki N)
	 */
	std::thread keyCheck;


public:

	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	InputSystem() : active(true)
	{
	}

	/**
	 * @brief		ステージにキーを登録する
	 * @detail		{} で複数入力可能
	 * @param[in]	std::string	登録するキー	
	 * @param[in]	int			キーコード
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyMap(std::string _key, int _inputKey)
	{
		//! 登録するキー情報の初期化宣言
		KeyInfo keyInfo =
		{
			_inputKey,
			0,
			InputState::Waiting,
		};

		// キーが既に存在している場合は要素を追加する

	}

	/**
	 * @brief		ステージにキーを登録する
	 * @detail		{} で複数入力可能
	 * @param[in]	std::string		 登録するキー
	 * @param[in]	std::vector<int> キーコード
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyMap(std::string _key, std::vector<int> _inputKey)
	{
		for (int i = 0; i < _inputKey.size(); ++i)
		{
			//! 登録するキー情報の初期化宣言
			KeyInfo keyInfo =
			{
				_inputKey[i],
				0,
				InputState::Waiting,
			};

			// キーが既に存在している場合は要素を追加する
//			auto it = keyMap.find(_key);
//			if (it != keyMap.end())
//				it->second.push_back(keyInfo);
//			else
//				keyMap[_key].push_back(keyInfo);
		}
	}

	/**
	 * @brief		キーマップに登録されているキーを監視する
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void KeyCheckAsync()
	{
	}
};
