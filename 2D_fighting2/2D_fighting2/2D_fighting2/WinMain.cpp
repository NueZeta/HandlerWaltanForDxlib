#include"MyTransform.h"
#include"MyGameObject.h"



int main()
{
	unique_ptr<MyGameObject> obj = make_unique<MyGameObject>();

	obj->AddComponent(make_unique<MyTransform>());

	MyTransform* transform = obj->GetMyComponent<MyTransform>();

	cout << "X = " << transform->GetPosition().x << endl;
	cout << "Y = " << transform->GetPosition().y << endl;
	cout << "Z = " << transform->GetPosition().z << endl;

	transform->Position = { -1, -2, -3 };


	cout << "\n\n";

	MyGameObject* obj2 = transform->GetMyGameObject();

	auto gege = obj2->GetMyComponent<MyTransform>();

	cout << "X = " << gege->GetPosition().x << endl;
	cout << "Y = " << gege->GetPosition().y << endl;
	cout << "Z = " << gege->GetPosition().z << endl;


	obj->MyComponentsUpdate();


	return 0;
}