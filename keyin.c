#include <conio.h>
#include <stdbool.h>
#include "keyin.h"

// 미리 정해두지 않은 키가 입력되면 무시하기 위한 함수
bool is_valid(key_t key) {
	// keyin.h에 있는 목록과 똑같이 맞춰야함(K_UNDEFINED 제외)
	static key_t key_list[] = {
		K_UP,
		K_DOWN,
		K_LEFT,
		K_RIGHT,		
		K_QUIT
	};

	for (int i = 0; i < N_KEY; i++) {
		if (key_list[i] == key) {
			return true;
		}
	}
	return false;
}

// 키보드에서 입력 받은 키가 무슨 키인지 구분해서 리턴
key_t get_key(void) {
	if (!_kbhit()) {
		return K_UNDEFINED;
	}

	int key = _getch();
	if (key == K_ARROW) {
		key = _getch();
	}

	if (is_valid(key)) {
		return key;
	} else {
		return K_UNDEFINED;
	}	
}
