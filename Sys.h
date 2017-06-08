#include <list>
#include <Windows.h>
#include "resource.h"

using namespace std;

// 背景音乐
#define MAIN_BACK_MUSIC    "sounds/main_back.wav"
#define ONEGAME_BACK_MUSIC "sounds/back_mydream.wav"
#define TWOGAME_BACK_MUSIC "sounds/back_cool.wav"

// 游戏音效
#define START_GAME_SOUND   "sounds/start.wav"
#define WIN_GAME_SOUND     "sounds/win.wav"
#define LOST_GAME_SOUND    "sounds/lost.wav"
#define DRAW_GAME_SOUND    "sounds/draw.wav"
#define BLAST_SOUND        "sounds/blast.wav"
#define APPEAR_TOOL_SOUND  "sounds/appear.wav"
#define GET_TOOL_SOUND     "sounds/get.wav"
#define PUT_BUEBLE_SOUND   "sounds/put.wav"
#define PLAYER_DIE_SOUND   "sounds/die.wav"

// 定时器
#define STOPSOUND_TIMER_ID       1
#define BubbleChange_TIMER_ID       2//改变泡泡大小变化的定时器