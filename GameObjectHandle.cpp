#include "GameObjectHandle.h"

GameObjectHandle::GameObjectHandle(GameObject* gameObj) 
	: mGameObject(gameObj)
{}

bool GameObjectHandle::isValid() const
{
	return mGameObject != nullptr;
}

GameObject* GameObjectHandle::GetGameObject() const
{
	return mGameObject;
}