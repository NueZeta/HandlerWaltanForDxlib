#include "HandlerWaltan.h"



int main()
{
	//当ライブラリで必須のオブジェクト
	HandlerWaltan& handlerWaltan = HandlerWaltan::Instance();

	//gameObjectの生成
	unique_ptr<MyGameObject> obj = make_unique<MyGameObject>();

	//MyTransformコンポーネントを新たにアタッチする
	obj->AddMyComponent(make_unique<MyTransform>());
	//MyTransformのコンポーネントを取得する
	MyTransform* transform = obj->GetMyComponent<MyTransform>();

	transform->Position = { -1, -2, -3 };

	cout << "\n\n";

	return 0;
}