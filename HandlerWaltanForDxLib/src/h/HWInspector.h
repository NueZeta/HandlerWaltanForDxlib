#pragma once
#include "HWComponent.h"


/**
* @author   NZ
* @date     25/09/19
* @note		GUIインスペクターの定義
*/


/**
 * @class	InspectorItem
 * @brief	インスペクターに登録されるパラメータ群
 */
struct InspectorItem 
{
	std::string name;
	void* data;
	enum Type { INT, FLOAT } type;
};


/**
 * @class	HWInspector
 * @brief	GUIインスペクター
 */
class HWInspector
{
public:

	/*     メンバ変数     */

	//! 登録されているパラメータ
	std::vector<InspectorItem> items;

	
	/*     メソッド     */

	/**
	 * @brief		インスペクターの描画
	 * @author		NZ
	 * @date		24/09/24
	 */
	void Draw();

};