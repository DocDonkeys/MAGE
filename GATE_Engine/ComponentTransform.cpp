#include "Globals.h"
#include "ComponentTransform.h"

ComponentTransform::ComponentTransform() : Component()
{
	type = COMPONENT_TYPE::TRANSFORM;
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::Enable()
{
	active = true;
}

void ComponentTransform::Disable()
{
	active = false;
}

void ComponentTransform::PreUpdate()
{
	if (my_go->parent != nullptr)
	{
		if (needsMatUpdate) {
			UpdateGlobalMat();
			needsMatUpdate = false;
		}
	}
}

void ComponentTransform::UpdateGlobalMat()
{
	ComponentTransform* parentTrs = (ComponentTransform*)my_go->parent->GetComponent(COMPONENT_TYPE::TRANSFORM);
	globalTrs = parentTrs->globalTrs * localTrs;

	for (int i = 0; i < my_go->children.size(); i++) {
		ComponentTransform* childTrs = (ComponentTransform*)my_go->children[i]->GetComponent(COMPONENT_TYPE::TRANSFORM);
		childTrs->UpdateGlobalMat();
	}
}

void ComponentTransform::UpdateQuatByEuler(float3& newEuler)
{
	float3 rotAng = (newEuler - eulerRotation) * DEGTORAD;
	quatRotation = quatRotation * Quat::FromEulerXYZ(rotAng.x, rotAng.y, rotAng.z);
}

void ComponentTransform::DataToMat()
{
	localTrs = float4x4::FromTRS(position, quatRotation, scale);
	needsMatUpdate = true;
}

void ComponentTransform::MatToData()
{
	localTrs.Decompose(position, quatRotation, scale);
	eulerRotation = quatRotation.ToEulerXYZ() * RADTODEG;
}

bool ComponentTransform::UpdateValues(float3& pos, float3& rot, float3& scale)
{
	bool ret = false;

	if (pos.x != this->position.x
		|| pos.y != this->position.y
		|| pos.z != this->position.z)
	{
		position = pos;
		ret = true;
	}

	if (rot.x != this->eulerRotation.x
		|| rot.y != this->eulerRotation.y
		|| rot.z != this->eulerRotation.z)
	{
		eulerRotation = rot;
		UpdateQuatByEuler(eulerRotation);
		ret = true;
	}

	if (scale.x != this->scale.x
		|| scale.y != this->scale.y
		|| scale.z != this->scale.z)
	{
		this->scale = scale;
		ret = true;
	}

	if (ret) {
		DataToMat();
	}

	return ret;
}