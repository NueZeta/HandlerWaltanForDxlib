#pragma once
#include "HWComponent.h"

/**
* @author   NZ
* @date     24/09/15
* @note		球体型のコライダーコンポーネントの定義
*/


/**
 * @class	HWSphereCollider
 * @brief	球体型のコライダーコンポーネント
 */
class HWQuaternion
{
public:

	/*     メンバ変数     */

    //! スカラー成分
    float w; 
    //! ベクトル成分
    float x, y, z;


public:
    // メソッド


    /**
     * @brief   コンストラクタ
     * @History 24/10/16 作成(NZ)
     */
    HWQuaternion();

    /**
     * @brief   コンストラクタ
     * @History 24/10/16 作成(NZ)
     */
    HWQuaternion(float w, float x, float y, float z);


    /**
     * @brief   クォータニオンの正規化
     * @History 24/10/16 作成(NZ)
     */
    HWQuaternion Normalize() const;

    /**
     * @brief   クォータニオンの逆元（共役）
     * @History 24/10/16 作成(NZ)
     */
    HWQuaternion Conjugate() const;

    /**
     * @brief   クォータニオンの積（2つのクォータニオンを合成する）
     * @History 24/10/16 作成(NZ)
     */
    HWQuaternion operator*(const HWQuaternion& q) const;

    /**
     * @brief   クォータニオンとベクトルの積（ベクトルにクォータニオンを適用）
     * @History 24/10/16 作成(NZ)
     */
    VECTOR RotateVector(const VECTOR& v) const;

    /**
     * @brief   クォータニオンを回転軸と角度から生成
     * @History 24/10/16 作成(NZ)
     */
    static HWQuaternion FromAxisAngle(const VECTOR& axis, float angle);

    /**
     * @brief   クォータニオンを回転行列に変換
     * @History 24/10/16 作成(NZ)
     */
    MATRIX ToMatrix() const;
};
