#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"


#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s\n", p, player[p] ? "alive" : "DEAD");
	}
}

void dialog(char message[]) {
	// ���� ȭ�� ����
	char original_front_buf[ROW_MAX][COL_MAX];
	int original_sec = 0;

	memcpy(original_front_buf, front_buf, sizeof(front_buf));
	original_sec = DIALOG_DURATION_SEC;

	int start_row = 15 / 2;
	int start_col = 40 / 2;

	for (int sec = DIALOG_DURATION_SEC; sec >= 0; sec--) {
		// ���� ȭ�� ����� �޽��� ���
		for (int row = start_row; row <= start_row + 1; row++) {
			for (int col = start_col - strlen(message) / 2; col <= start_col + strlen(message) / 2; col++) {
				printxy(' ', row, col);  // ���� �޽����� ����� ���� ���� ���
			}
		}

		gotoxy(start_row, start_col - strlen(message) / 2);
		printf("%s", message);

		// ���� �ð� ���
		gotoxy(start_row + 1, start_col);
		printf("%d", sec);

		Sleep(1000);  // 1�� ���

	}

	// ���� ȭ�� ����
	for (int row = start_row; row <= start_row + 1; row++) {
		for (int col = start_col - strlen(message) / 2; col <= start_col + strlen(message) / 2; col++) {
			printxy(original_front_buf[row][col], row, col);
		}
	}
}
