// 2023-2 고급프로그래밍 과제: 쭈꾸미 게임
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("플레이어 수: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}
int intro() {
	printf("  .／  ⌒   ＼ \n");
	printf("  ／　　  　＼		쭈 \n");
	printf("  /         |＼		꾸 \n");
	printf(" (/         | )		미 \n");
	printf(" /          |ㅣ		게 \n");
	printf(" f　　　　   ㅣ		임 \n");
	printf(" | ●　　●    ｜ \n");
	printf(" |    ▽   　 ｜ \n");
	printf(" ㄴ＿ ＿  　ノ \n");
	printf(" J丁丁丁丁￣l＼   \n");
	printf("く(_(_(＿L＿)ノ  \n");


	Sleep(5000);
}

int ending() {
		printf("         *the end*\n");
		printf("         *the end*\n");
		printf("         *the end*\n");
		printf("         *the end*\n");
		printf("	    ㅅ_ㅅ  \n");
		printf("	    ('ω')\n");
		printf("	／ Ｕ ∽ Ｕ＼\n");
		printf("	│＊　게　＊│\n");
		printf("	│＊　임　＊│\n");
		printf("	│＊　종　＊│\n");
		printf("	│＊　료　＊│\n");
		printf("	│＊　☆　＊ │\n");
		printf("	￣￣￣￣￣￣ \n");
		if (n_alive == 1) {
			// 우승자 출력
			printf(" 우승자: ");
			for (int i = 0; i < n_player; i++) {
				if (player[i]) {
					printf("플레이어 %d", i);
					break;
				}
			}
	}
}

int main(void) {
	jjuggumi_init();
	intro();
	//sample();
	mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	ending();
	return 0;
}
