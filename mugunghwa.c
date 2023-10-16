#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct _point
{
	int x, y;
}point;
typedef enum _direction
{
	IDLE = 1, LEFT, UP, DOWN, RIGHT
}direction;
typedef enum _state { alive, dead, finished }state;		// 각 플레이어들의 상태를 나타내는 자료형
typedef struct _tickState
{
	double goalTick;	// 트리거틱
	double cntTick;		// 현재 틱
}tickState;		// 이벤트를 발생시키는 주기를 조절하기 위한 자료형

bool moveOn(point*, direction);	// 플레이어 이동
double getTick();		// Tick계산
int SayFlower();		// 무궁화꽃이피었습니다.  출력
void checkFinished();	// 플레이어가 골인지점에 도착하면 finised 처리
void killPlayer();		// 영희가 뒤돌아봤을 때 플레이어가 움직이면 dead 처리

bool running = true;	// 게임 반복문 실행 여부
point* pl;				// 플레이어 위치들
tickState* plTicks;		// 플레이어 이동 주기
state* states;			// 플레이어 상태 (alive, dead, finished)
int taggerY;			// 영희 세로 위치


void mugunghwa() {
	srand((unsigned int)time(NULL));

	////////////////////  게임 초기화  ////////////////////////////////////////////////////////////////////////////////
	system("cls");
	if (5 < n_player) {
		map_init(4 + n_player, 40);
	}
	else {
		map_init(9, 40);
	}

	// 영희 생성
	taggerY = N_ROW / 2;
	back_buf[taggerY-1] [1] = '#';
	back_buf[taggerY][1] = '#';
	back_buf[taggerY+1][1] = '#';
	tickState taggerSaying = { 100,0 };	// 영희가 말하고 있는 시간 설정
	tickState taggerWatching = { 3000,0 }; // 영희가 바라보고 있는 시간 설정
	bool isWatching = false;		// 영희는 처음에 앞을 보고 있다

	// 플레이어 위치 및 이동주기 및 상태 설정
	pl = (point*)malloc(sizeof(point) * n_player);
	plTicks = (tickState*)malloc(sizeof(tickState) * n_player);
	states = (state*)malloc(sizeof(state)*n_player);
	for (int i = 0; i < n_player; i++) 
	{
		// 플레이어들 위치 설정
		pl[i].x = 38;
		pl[i].y = 2+i;
		back_buf[pl[i].y][pl[i].x] = '0' + i;
		
		// 플레이어들 이동 주기 설정
		if (i == 0)
		{
			plTicks[0].goalTick = 0;
			plTicks[0].cntTick = 0;
		} 
		else
		{
			plTicks[i].goalTick = randint(100, 800); //ai 움직임 속도
			plTicks[i].cntTick = 0;
		}

		// 플레이어 상태 설정
		states[i] = alive;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// 게임 진행 루프문
	while (running) {
		display();
		//사용자 입력 처리
		{
			key_t key = get_key();
			if (key != K_UNDEFINED)
			{
				if (key == K_QUIT)
					running = false;
				else if (states[0] == alive && plTicks[0].goalTick <= plTicks[0].cntTick)
					switch (key)
					{
					case K_LEFT:
						moveOn(pl + 0, LEFT);
						break;
					case K_UP:
						moveOn(pl + 0, UP);
						break;
					case K_DOWN:
						moveOn(pl + 0, DOWN);
						break;
					case K_RIGHT:
						moveOn(pl + 0, RIGHT);
						break;
					}
			}

		}
		// AI 이동 처리
		for (int i = 1; i < n_player; i++)
		{
			// 캐릭터가 살아있는 상태고, 현재 틱이 이벤트 발생 틱을 넘어서면...
			if (states[i] == alive && plTicks[i].goalTick <= plTicks[i].cntTick)
			{
				plTicks[i].cntTick = 0;
				if (isWatching == false || (rand() % 10 == 0))	// 영희가 바라보면 10의 1확률로 움직인다. 현재 10%
				{
					int random = rand() % 10;	
					if (random == 0)
						moveOn(pl + i, IDLE);
					else if (random == 1)
						moveOn(pl + i, UP);
					else if (random == 2)
						moveOn(pl + i, DOWN);
					else
					{
						moveOn(pl + i, LEFT);
					}
				}
			}


		}
	

		// 영희 말하기&뒤돌아보기 구현
		if (isWatching)
		{
			if (taggerWatching.goalTick <= taggerWatching.cntTick)
			{
				isWatching = false;
				taggerWatching.cntTick = 0;
				back_buf[N_ROW / 2 - 1][1] = '#';
				back_buf[N_ROW / 2][1] = '#';
				back_buf[N_ROW / 2 + 1][1] = '#';
			}
			else
			{
				back_buf[N_ROW / 2 - 1][1] = '@';
				back_buf[N_ROW / 2][1] = '@';
				back_buf[N_ROW / 2 + 1][1] = '@';
				killPlayer();
			}
		}
		else
		{
			if (taggerSaying.goalTick <= taggerSaying.cntTick)
			{
				int cnt = SayFlower();
				if (cnt < 10) {
					if (cnt == 0)
						taggerSaying.goalTick = 1000;
					taggerSaying.goalTick += rand() % 200;
				}
				else
				{
					if (cnt == 10)
						taggerSaying.goalTick = 1000;
					taggerSaying.goalTick -= rand() % 300;
				}
				taggerSaying.cntTick = 0;
				if (20 <= cnt)
					isWatching = true;
			}

		}

		// 플레이어 도착 여부 확인
		checkFinished();

		// 각 플레이어들의 tick 증가
		double tick = getTick();
		for (int i = 0; i < n_player; i++) plTicks[i].cntTick += tick;
		taggerSaying.cntTick += tick;
		if (isWatching) taggerWatching.cntTick += tick;



		// 게임 종료 조건 여부 확인
		int finishedN = 0;
		for (int i = 0; i < n_player; i++)
			if (states[i] == finished)
				finishedN++;
		if (finishedN == n_alive)	// 클리어한 사람 수와 살아있는 플레이어 수가 같으면 게임 종료
			running = false;
		else if (n_alive <= 1 && finishedN == 0) // 아무도 클리어하지 못했고, 플레이어 수가 1명 이하면 게임 종료
			running = false;
		else if (finishedN == n_player)	// 다 도착했을 경우, 게임 종료
			running = false;

		
	}
	display();
	gotoxy(ROW_MAX+3, 0);
}




bool moveOn(point* pt, direction dir)
{
	switch (dir)
	{
	case LEFT:
		if (back_buf[pt->y][pt->x - 1] != ' ')
			return false;
		back_buf[pt->y][pt->x - 1] = back_buf[pt->y][pt->x];
		back_buf[pt->y][pt->x] = ' ';
		pt->x -= 1;
		break;

	case UP:
		if (back_buf[pt->y - 1][pt->x] != ' ')
			return false;
		back_buf[pt->y - 1][pt->x] = back_buf[pt->y][pt->x];
		back_buf[pt->y][pt->x] = ' ';
		pt->y -= 1;
		break;

	case DOWN:
		if (back_buf[pt->y + 1][pt->x] != ' ')
			return false;
		back_buf[pt->y + 1][pt->x] = back_buf[pt->y][pt->x];
		back_buf[pt->y][pt->x] = ' ';
		pt->y += 1;
		break;

	case RIGHT:
		if (back_buf[pt->y][pt->x + 1] != ' ')
			return false;
		back_buf[pt->y][pt->x + 1] = back_buf[pt->y][pt->x];
		back_buf[pt->y][pt->x] = ' ';
		pt->x += 1;
		break;
	}
	return true;
}


double getTick()
{
	static double beforeClock = 0;
	double temp = beforeClock;
	beforeClock = clock();
	return clock() - temp;

}

int SayFlower()
{
	static int cnt = 0;
	const char* sentence = "무궁화꽃이피었습니다";
	if (cnt == 0)	// 무궁화꽃이피었습니다 출력한 거 지우기
	{
		gotoxy(N_ROW + 1, 0);
		printf("                                                               ");
	}
	while (cnt < strlen(sentence))
	{
		gotoxy(N_ROW + 1, cnt);
		printf("%c%c", sentence[cnt], sentence[cnt + 1]);
		cnt += 2;
		return cnt;
	}
	cnt = 0;
	return cnt;
}

void checkFinished()
{
	for(int i =0;i<n_player;i++)
		if (states[i] == alive && ((pl[i].x == 1) || (pl[i].x == 2 && taggerY - 1 <= pl[i].y && pl[i].y <= taggerY + 1)))
		{
			back_buf[pl[i].y][pl[i].x] = ' ';
			states[i] = finished;
		}
}
void killPlayer()
{
	for (int i = 0; i < N_ROW; i++)
		for (int j = 0; j < N_COL; j++)
			if (front_buf[i][j] != back_buf[i][j] && back_buf[i][j] != '#' && back_buf[i][j] != '@')
			{
				if ('0' <= back_buf[i][j] && back_buf[i][j] <= '9')
				{
					// 위치가 바뀐 플레이어는 dead상태로 전환
					states[back_buf[i][j] - '0'] = dead;

					for (int k = j - 1; 1 < k; k--)
					{
						// 단, 앞에 사람이 있으면 alive상태로 다시 전환
						if ('0' <= back_buf[i][k] && back_buf[i][k] <= '9')
							states[back_buf[i][j] - '0'] = alive;
					}
					if (states[back_buf[i][j] - '0'] == dead)
					{
						player[back_buf[i][j] - '0'] = false;
						back_buf[i][j] = ' ';
						n_alive--;
					}
				}
			}
}