#pragma once

class GameObject;

class GameObjectHandle
{
public:
	GameObjectHandle(GameObject* gameObj);

	bool isValid() const;

	GameObject* GetGameObject() const;

private:
	GameObject* mGameObject;
};