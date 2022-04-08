#include "pch.h"

Component::Component(Actor* _owner, int _updateOrder)
	: mOwner(_owner)
	, mUpdateOrder(_updateOrder)
{
}

Component::~Component()
{
}