#pragma once
#include <iostream>
#include <fstream>
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


/**
 * @class	CsvLoader
 * @brief	csvファイルをカンマ区切りで読み込む
 * @detail	静的クラス
 */
class CsvLoader final
{
private:

	/*     メンバ変数     */


public:

	/*     メソッド     */

	// 静的クラスのため、コンストラクタとデストラクタを削除
	CsvLoader() = delete;
	~CsvLoader() = delete;


	/**
	 * @brief		csvファイルを読み込み、行区切り、カンマ区切りで文字列を返す
	 * @param[in]	std::string	読み込むcsvファイルのパス
	 * @return		std::vector<std::vector<std::string>> 読み込んだ文字列を返す(1次元 = 行, 2次元 = カンマ区切り)
	 * @author		Suzuki N
	 * @date		24/09/14
	 */
	static std::vector<std::vector<std::string>> Load(const std::string _filePath)
	{
		//! 戻り値
		std::vector<std::vector<std::string>> ret;

		// ファイルを読み込む
		std::ifstream file(_filePath);
		// ファイル読み込みに失敗した場合、そのまま終了
		if (!file)
			return ret;

		//! 行区切りで読み込んだ文字列
		std::string line;

		// 1行ずつ読み込む
		while (std::getline(file, line))
		{
			//! カンマ区切りで読み込んだ文字列
			std::vector<std::string> comma;
			//! 確認済みの文字列のindex
			size_t confirmed = 0;
			//! カンマを見つけたindex
			size_t commaPos = 0;
			
			// カンマ区切りで読み込む
			do
			{
				// 前回カンマを見つけたindexからカンマを見つける
				commaPos = line.find_first_of(',', confirmed);
				// カンマが見つからなかった場合はそのまま終了
				if (commaPos == std::string::npos)
				{
					// 前回のコンマの位置からコピー
					comma.push_back(line.substr(confirmed));
					break;
				}

				// 前回のコンマの位置から次のコンマの位置までの文字列をコピー
				comma.push_back(line.substr(confirmed, commaPos - confirmed));

				// 確認済みの文字列を更新
				confirmed = commaPos + 1;
			} while (commaPos != std::string::npos);

			// カンマがなくなったら結果を追加
			ret.push_back(comma);
		}

		return ret;
	}
};


//--------------------------------------------------------
// 関数
//--------------------------------------------------------

/**
 * @brief		度数法 -> 弧度法 に変換
 * @param[in]	double 角度
 * @return		double 変換したラジアン値
 * @author		Suzuki N
 * @date		24/09/23
 */
inline double Deg2Rad(const double _angle)
{
	return _angle * DX_PI / 180.f;
}

/**
 * @brief		弧度法 -> 度数法 に変換
 * @param[in]	double ラジアン値
 * @return		double 変換した角度
 * @author		Suzuki N
 * @date		24/09/23
 */
inline double Rad2Deg(const double _radian)
{
	return _radian * 180 / DX_PI;
}