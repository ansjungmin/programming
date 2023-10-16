#ifndef _KEYIN_H_
#define _KEYIN_H_

// 입력 받는 키 종류
// 키를 추가/수정할 경우 N_KEY와,
// keyin.c:is_valid():key_list[]도 함께 수정해야 함
#define N_KEY		6  // K_UNDEFINED 를 뺀 키 종류

// 참고: #define 대신 enum 구문으로도 구현 가능
#define K_ARROW		224
#define K_UP		72
#define K_DOWN		80
#define K_LEFT		75
#define K_RIGHT		77
#define K_QUIT		'q'
#define K_UNDEFINED	'\0'

typedef int key_t;

key_t get_key(void);

#endif
