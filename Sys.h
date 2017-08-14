#include <list>
#include <Windows.h>
#include "resource.h"

using namespace std;

// ��������
#define MAIN_BACK_MUSIC    "sounds/main_back.wav"
#define ONEGAME_BACK_MUSIC "sounds/back_mydream.wav"
#define TWOGAME_BACK_MUSIC "sounds/back_cool.wav"

// ��Ϸ��Ч
#define START_GAME_SOUND   "sounds/start.wav"
#define WIN_GAME_SOUND     "sounds/win.wav"
#define LOST_GAME_SOUND    "sounds/lost.wav"
#define DRAW_GAME_SOUND    "sounds/draw.wav"
#define BLAST_SOUND        "sounds/blast.wav"
#define APPEAR_TOOL_SOUND  "sounds/appear.wav"
#define GET_TOOL_SOUND     "sounds/get.wav"
#define PUT_BUEBLE_SOUND   "sounds/put.wav"
#define PLAYER_DIE_SOUND   "sounds/die.wav"

// ��ʱ��
#define STOPSOUND_TIMER_ID          1 // ��Ч�����Զ�ֹͣ
#define BUBBLE_CHANGE_TIMER_ID      2 // �ı����ݴ�С�仯
#define GAME_TIME_TIMER_ID          3 // ��Ϸ����ʱ
#define STATUS_INFO_TIMER_ID        4 // ��Ϸ״̬�����ƶ�
#define PLAYERSTART_TIMER_ID	    5 // ��ҿ�������
#define WIND_TIMER_ID               6 // �糵ת��
#define KEY_STATE_TIMER_ID          7 // ��ⰴ��
#define PLAYER_MOVE_TIMER_ID        8 // ����ƶ�
#define PLAYER_MOVE_SHOW_TIMER_ID   9 // ����ƶ�