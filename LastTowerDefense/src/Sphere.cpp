#include "Sphere.h"
#include "Base/ResourceManager.h"

Sphere::Sphere()
{
	id = 102;
	model = (Graphic::Model*)ResourceManager::GetPtr()->GetElement("sphere");
	transform.SetTranslation(-2.5f, 210.0f, 0.0f);
	transform.SetScale(2.0f, 2.0f, 2.0f);
	rigidbody = new RigidBody(0.6, transform.GetTranslation(), transform.GetScale(),this);
}

Sphere::~Sphere()
{
	//TODO 
}

void Sphere::Draw()
{
	model->SetTransform(transform);
	model->Draw();
}

void Sphere::Update(unsigned int delta)
{
	transform.SetTranslation(rigidbody->GetObjectPosition());
	transform.SetRotation(rigidbody->GetObjectRotation());
}

void Sphere::OnTriggerEnter(void* ptr)
{
	std::cout << "hit Sphere";
}