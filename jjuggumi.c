// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("�÷��̾� ��: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}
int intro() {
	printf("  .��  ��   �� \n");
	printf("  ������  ����		�� \n");
	printf("  /         |��		�� \n");
	printf(" (/         | )		�� \n");
	printf(" /          |��		�� \n");
	printf(" f��������   ��		�� \n");
	printf(" | �ܡ�����    �� \n");
	printf(" |    ��   �� �� \n");
	printf(" ���� ��  ���� \n");
	printf(" J�������ˣ�l��   \n");
	printf("��(_(_(��L��)��  \n");


	Sleep(5000);
}

int ending() {
	if (n_player == 1) {
		printf("         *the end*\n");
		printf("         *the end*\n");
		printf("         *the end*\n");
		printf("         *the end*\n");
		printf("	    ��_��  \n");
		printf("	    ('��')\n");
		printf("	�� �� �� �ա�\n");
		printf("	�������ࡡ����\n");
		printf("	�������ϡ�����\n");
		printf("	�������ء�����\n");
		printf("	�������䡡����\n");
		printf("	�������١��� ��\n");
		printf("	������������ \n");

	}
}

int main(void) {
	jjuggumi_init();
	intro();
	sample();
	//mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	ending();
	return 0;
}
