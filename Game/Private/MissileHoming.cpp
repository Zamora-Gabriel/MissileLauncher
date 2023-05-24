//
// + MissileHoming.cpp
// missile to find enemy missile
//

#include "Game/Private/Game.h"
#include "Game/Private/MissileHoming.h"
#include "GameObjectHandle.h"

#include <math.h>
#include <iostream>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

//
// TODO - could a math library clean this file up a bit?
//

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const float gMissileHomingSpeed = 200.0f;
const float gMissileHomingRadius = 10.0f;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MissileHoming::MissileHoming( exEngineInterface* pEngine, const exVector2& v2Position, GameObject* pTarget )
	: GameObject( pEngine, v2Position, gMissileHomingRadius )
{
	mTarget = new GameObjectHandle(pTarget);
	// find our starting distance and cache it
	exVector2 v2MeToTarget;
	if (mTarget->isValid()) 
	{
		v2MeToTarget.x = mTarget->GetGameObject()->mPosition.x - mPosition.x;
		v2MeToTarget.y = mTarget->GetGameObject()->mPosition.y - mPosition.y;
	}
	
	mStartingDistance = sqrtf( v2MeToTarget.x * v2MeToTarget.x + v2MeToTarget.y * v2MeToTarget.y );
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MissileHoming::~MissileHoming()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MissileHoming::Update( float fDeltaT )
{
	// find our distance to the target
	exVector2 v2MeToTarget;

	if (!mTarget->isValid())
	{
		return;
	}

	v2MeToTarget.x = mTarget->GetGameObject()->mPosition.x - mPosition.x;
	v2MeToTarget.y = mTarget->GetGameObject()->mPosition.y - mPosition.y;

	float fMeToTargetLength = sqrtf(v2MeToTarget.x * v2MeToTarget.x + v2MeToTarget.y * v2MeToTarget.y);

	// colour in the target
	unsigned char cColor = (unsigned char)((fMeToTargetLength / mStartingDistance) * 255.0f);
		
	if (mTarget->GetGameObject()->mColor->isValid()) 
	{
		mTarget->GetGameObject()->mColor->GetColor()->mColor[0] = 255;
		mTarget->GetGameObject()->mColor->GetColor()->mColor[1] = cColor;
		mTarget->GetGameObject()->mColor->GetColor()->mColor[2] = cColor;
	}
		

	// are we colliding?
	if (fMeToTargetLength < gMissileHomingRadius + mTarget->GetGameObject()->mRadius)
	{
		extern MyGame gGame;
		gGame.CreateExplosion(mPosition);

		mExpiring = true;
		mTarget->GetGameObject()->mExpiring = true;

		return;
	}

	// go towards the target
	exVector2 v2Velocity;
	float inverseLength = 1.0f / fMeToTargetLength;
	v2Velocity.x = v2MeToTarget.x * inverseLength;
	v2Velocity.y = v2MeToTarget.y * inverseLength;

	v2Velocity.x *= gMissileHomingSpeed;
	v2Velocity.y *= gMissileHomingSpeed;

	mPosition.x += v2Velocity.x * fDeltaT;
	mPosition.y += v2Velocity.y * fDeltaT;
}
