#pragma once
#include <Cube3D/Game/Game.h>
#include <Cube3D/Prerequisites.h>

class World : public Game
{
public:
	World();
	~World();

	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);

private:
	f32 m_elapsedSeconds = 0.0f;
};

