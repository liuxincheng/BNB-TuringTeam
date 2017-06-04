#pragma once

#include "Sys.h"
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

class CPlayMusic
{
public:
	CPlayMusic();
	~CPlayMusic();
public:
	void PlayBackMusic(char* music_name);
	void SotpBackMusic();

	bool isStop;
};

