#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "GameBase.h"
#include "LoadTexture.h"
struct GameManager {
	bool Init();
	bool LoadMedia();
	void Close();
	void Run();
};
#endif
