#include "HandlerWaltan.h"



int main()
{
	unique_ptr<MyGameObject> obj = make_unique<MyGameObject>();

	obj->AddMyComponent(make_unique<MyTransform>());

	MyTransform* transform = obj->GetMyComponent<MyTransform>();

	transform->Position = { -1, -2, -3 };

	cout << "X = " << transform->GetPosition().x << endl;
	cout << "Y = " << transform->GetPosition().y << endl;
	cout << "Z = " << transform->GetPosition().z << endl;

	obj->AddMyComponent(make_unique<MyCollider>());

	cout << "\n\n";
	//obj->MyComponentsUpdate();


	return 0;
}