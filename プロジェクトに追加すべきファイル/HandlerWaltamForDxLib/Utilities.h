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
 * @class	ReadOnly
 * @brief	読み取り専用にするラッパークラス	
 */
template<class T>
class ReadOnly
{
private:

	/*     メンバ変数     */

	/**
	 * @brief		値を保管するオブジェクト
	 * @History		24/09/14 作成(Suzuki N)
	 */
	T obj;


public:

	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @param[in]	T 初期値
	 * @author		Suzuki N
	 * @date		24/09/14
	 */
	ReadOnly(T _obj) : obj(_obj) {}

	/**
	 * @brief		関数呼び出しoperatorの定義
	 * @param[in]	T 初期値
	 * @author		Suzuki N
	 * @date		24/09/14
	 */
	operator T() const { return obj; }

	// 値の変更を禁止するため、代入operatorは削除
	ReadOnly& operator=(const T&) = delete;
};


/**
 * @class	PoolAllocator
 * @brief	メモリ管理を高速化するためのメモリアロケーター
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
