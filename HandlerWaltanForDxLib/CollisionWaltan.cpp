#include "h/CollisionWaltan.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		ColliderWaltanの実装ファイル
*/


#pragma region publucメソッド



#pragma endregion

#pragma region privateメソッド


CollisionWaltan::CollisionWaltan()
{

}


CollisionWaltan::~CollisionWaltan()
{

}

void CollisionWaltan::Update()
{
    for (auto& obj : HWGameObject::GetGameObjects())
    {
        obj->CallAllOnCollisionEnters();
        obj->CallAllOnCollisionStays();
        obj->CallAllOnCollisionExits();
    }
}


#pragma endregion

#pragma region staticメソッド


CollisionWaltan& CollisionWaltan::Instance()
{
    // シングルトンインスタンスを生成
    static CollisionWaltan instance;
    return instance;
}

int CollisionWaltan::Init()
{

    return 0;
}


#pragma endregion

