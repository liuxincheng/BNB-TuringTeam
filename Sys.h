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
#define STOPSOUND_TIMER_ID          1 // 音效播完自动停止
#define BUBBLE_CHANGE_TIMER_ID      2 // 改变泡泡大小变化
#define GAME_TIME_TIMER_ID          3 // 游戏倒计时
#define STATUS_INFO_TIMER_ID        4 // 游戏状态文字移动
#define PLAYERSTART_TIMER_ID	    5 // 玩家开场动画
#define WIND_TIMER_ID               6 // 风车转动
#define KEY_STATE_TIMER_ID          7 // 监测按键
#define PLAYER_MOVE_TIMER_ID        8 // 玩家移动
#define PLAYER_MOVE_SHOW_TIMER_ID   9 // 玩家移动