#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#pragma waring(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define Player_X_init 1
#define Player_Y_init 1
#define Player_HP_init 100 

#define Board_Turn 3
#define Board_X 20
#define Board_Y 10

// 플레이어 및 게임 관련 
int Player_X=Player_X_init, Player_Y=Player_Y_init, Player_HP=Player_HP_init, Player_Score=0, Player_Damage, Player_Damage_Count = 0;
int Map_Score = 0, Map_Turn = 2, Map_Exit = 0;
int End = 0, Board_Message = 0;

// 0 빈공간 // 1 벽 // 2 점수 // 3 탈출구 // 4 플레이어 // 5 장애물 // 
int Board[Board_Turn][Board_Y][Board_X] = {
	{ // 1번째 판 
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 4, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 5, 3, 0, 0, 0, 0, 2, 1},
		{1, 0, 0, 0, 1, 0, 5, 1, 0, 1, 5, 0, 0, 1, 5, 5, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 5, 5, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 1, 2, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 5, 5, 5, 0, 1},
		{1, 0, 0, 0, 1, 5, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 0, 1, 5, 5, 5, 0, 1, 0, 1, 0, 5, 5, 5, 0, 1},
		{1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 5, 2, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	},
	{ // 2번째 판
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 1},
		{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1},
		{1, 5, 5, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 2, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1},
		{1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 2, 0, 0, 0, 1, 0, 1, 0, 0, 2, 1, 0, 0, 0, 1, 2, 1, 2, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	},
	{ // 3번째 판
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 4, 5, 0, 0, 0, 5, 0, 0, 0, 5, 2, 0, 0, 0, 0, 3, 0, 0, 1},
		{1, 0, 5, 0, 5, 0, 0, 0, 5, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 1},
		{1, 0, 5, 0, 5, 5, 5, 5, 5, 5, 0, 0, 5, 0, 0, 5, 5, 0, 0, 1},
		{1, 0, 5, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 5, 0, 0, 0, 0, 0, 1},
		{1, 0, 5, 5, 5, 5, 5, 5, 0, 5, 2, 5, 0, 0, 5, 0, 0, 5, 5, 1},
		{1, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, 0, 1},
		{1, 0, 5, 0, 5, 5, 0, 5, 0, 5, 0, 2, 0, 5, 0, 5, 0, 5, 0, 1},
		{1, 0, 0, 0, 0, 5, 0, 0, 0, 5, 2, 5, 0, 0, 0, 0, 0, 5, 2, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	}
};

void Game_Init();
void Cursor(int x, int y);
void game_end(int Value);
int Turn_Change();
void Board_Info_Get();
void print_board_message(int Value);
int judgment(int x, int y);
void play_key_input();
void print_board();
int game_play();

int main() {
	int end_value = game_play();
	game_end(end_value);
	
	return 0;
}

// 게임 끝 
void game_end(int Value) {
	int key;
	printf("\n\n");
	printf("          ---------- 게임 종료! ----------");
	printf("\n\n          ");
	
	// 종료 사유
	switch(Value) {
		case 0:
			printf("사용자가 게임을 종료하였습니다.");
			break;
			
		case 1:
			printf("플레이어가 사망하였습니다.");
			break;
			
		case 2:
			printf("게임 클리어!!");
			break;
			
		case 3:
			printf("");
			break;
			
		case 4:
			printf("");
			break;
			
		case 5:
			printf("");
			break;
			
		default :
			printf("! Wrong Value");
			break;

	}
	
	// 게임 기록 출력
	printf("\n\n          ---------- 게임 로그 -----------");
	printf("\n");
	
	printf("\n          ");
	printf("클리어 한 단계: %d", Map_Turn);
	
	if(Player_Damage_Count != 0) {
		printf("\n          ");
		printf("장애물 밟은 횟수: %d\n", Player_Damage_Count); 
		printf("\n          ");
		printf("장애물로 받은 데미지: %d\n", (Player_HP_init+((Player_HP_init/10) * (Map_Turn+1))) - Player_HP);
	} else if(Player_Damage_Count==0 && Map_Turn==Board_Turn){
		printf("\n          "); 
		printf("장애물을 하나도 안밟고 클리어 하였습니다. 대박!");
	}
	
//	printf("\n\n          ");
//	printf("플레이 시작한 시간: ", stime);
	
	 
	printf("\n\n");
	printf("          --------------------------------");
	printf("\n\n");
	
	printf("          엔터 또는 스페이스 키를 눌러 종료하세요. . . ");
	while(1) {
		key = getch();
		if(key == 13 || key == 32) {
			break;
		}
	}
}

int Turn_Change() { // 맵 변경 
	Map_Turn++; // 맵 턴 증가 및 끝단계까지 왔는지 검토 
	if(Map_Turn == Board_Turn) {
		return 1;
	}
	
	Map_Exit = 0; // 맵 탈출 비활성화 
	Player_Score = 0; // 플레이어 스코어 초기화 
	Board_Info_Get(); // 보드 정보 새로고침
	 
	Player_X = Player_X_init, Player_Y = Player_Y_init; // 플레이어 위치 초기화
	 
	Board_Message = 3;
	Sleep(2000);
	print_board();
	
	
	Sleep(2000);
	Board_Message = 6;
	print_board();
	Sleep(2000);
	Board_Message = 8;
	print_board();
	
	return 0;
}

void Cursor(int x, int y) { // 커서 원하는 곳으로 
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Game_Init() {
	// 초기 시간 관련
	//stime = time(NULL);

	srand(time(NULL));
}

void Board_Info_Get() {
	int i, l;
	Map_Score = 0; 
	
	for(i=0; i<Board_Y; i++) {
		for(l=0; l<Board_X; l++) { // x
			if(Board[Map_Turn][i][l] == 2) {
				Map_Score++;
			}
		}
	}
}

void print_board_message(int Value) { // 판 아래 메세지 출력 
	int Player_HP_Plus = 0;
	
	if(Value == 0) { // 0이면 아무 메세지 출력 ㄴㄴ 
		printf("");
	} else { 
		if(Value == 1) {
			printf("앞이 막혔습니다!");
		} else if(Value == 2) {
			printf("잘못된 키를 눌렀습니다!");
		} else if(Value == 3) {
			printf("%d단계로 진입합니다!", Map_Turn+1);
		} else if(Value == 4) {
			if(Player_Score == Map_Score) {
				printf("%d단계 탈출 성공!", Map_Turn+1);
			} else {
				
				printf("열쇠가 부족합니다!");
			}
		} else if(Value == 5) {
			if(Player_Score == Map_Score)
				printf("열쇠를 모두 모았습니다. 탈출구(E)에 들어갈 수 있습니다!!\t\t");
			else
				printf("열쇠 획득! (%d => %d)\t\t\t\t\t\t\t\t", Player_Score-1, Player_Score);
		} else if(Value == 6) {
			// 체력 회복
			// 10% 채우는데 초기 값보다 크면 그냥 초기값으로 할려던 코드 
			//Player_HP_Plus = (Player_HP+(Player_HP_init/10) > Player_HP_init) ? (Player_HP+(Player_HP_init)-Player_HP_init) : Player_HP_init/10;
			
			Player_HP_Plus = Player_HP_init/10;
			Player_HP += Player_HP_Plus;
			 
			printf("( 체력 회복 +10%% // %d => %d )", Player_HP - Player_HP_Plus, Player_HP);
		} else if(Value == 7) {
			int Rand_Message = 1; 
			//int Rand_Message = rand()%5+1;
			if(Player_Damage==0) {
				printf("운수 좋은날! - ");
				
				if(Rand_Message == 1)
					printf("");
				if(Rand_Message == 2)
					printf("");
				if(Rand_Message == 3)
					printf("");
				if(Rand_Message == 4)
					printf("");
				if(Rand_Message == 5)
					printf("");
				
			} else if(Player_Damage<=5) {       // 약한 데미지 문구 ( <5 )
				printf("약한 데미지 - ");
				
				if(Rand_Message == 1)
					printf("");
				if(Rand_Message == 2)
					printf("");
				if(Rand_Message == 3)
					printf("");
				if(Rand_Message == 4)
					printf("");
				if(Rand_Message == 5)
					printf("");
					 
			} else if(Player_Damage<=10) { // 좀 강한 데미지 문구 ( <10 )
				printf("좀 강한 데미지 - ");
				 
				if(Rand_Message == 1)
					printf("");
				if(Rand_Message == 2)
					printf("");
				if(Rand_Message == 3)
					printf("");
				if(Rand_Message == 4)
					printf("");
				if(Rand_Message == 5)
					printf("");
				
			} else if(Player_Damage<=15) { // 강한 데미지 문구 ( <15 )
				printf("강한 데미지 - ");
				
				if(Rand_Message == 1)
					printf("");
				if(Rand_Message == 2)
					printf("");
				if(Rand_Message == 3)
					printf("");
				if(Rand_Message == 4)
					printf("");
				if(Rand_Message == 5)
					printf("");
				
			} else if(Player_Damage<=20) { // 아주 강한 데미지 문구 ( <20 ) 
				printf("아주 강한 데미지 - ");
				
				if(Rand_Message == 1)
					printf("");
				if(Rand_Message == 2)
					printf("");
				if(Rand_Message == 3)
					printf("");
				if(Rand_Message == 4)
					printf("");
				if(Rand_Message == 5)
					printf("");
				
			}
			printf("..! (체력 감소 -%d // %d => %d)", Player_Damage, Player_HP+Player_Damage, (Player_HP < 0) ? 0 : Player_HP);
			Player_Damage_Count++;
			
		} else if(Value == 8) {
			printf("                                                                                  ");
		} else if(Value == 9) {
			printf("");
		} else if(Value == 10) {
			printf("");
		} else {
			printf("! Wrong Value");
		}
		printf("                                                                    "); // 뒤에 남는 메세지 모두 삭제하기
		
	}
	Board_Message = 0;
}

// 0 빈공간 // 1 벽 // 2 점수 // 3 탈출구 // 4 플레이어 // 5 장애물 // 
int judgment(int x, int y) {
	Board[Map_Turn][Player_Y][Player_X] = 0;
	if(Board[Map_Turn][Player_Y+y][Player_X+x] == 0) {
		Player_X+=x, Player_Y+=y;
		
	} else if(Board[Map_Turn][Player_Y+y][Player_X+x] == 1) {
		Board_Message=1;
		Board[Map_Turn][Player_Y][Player_X] = 4;
		
	} else if(Board[Map_Turn][Player_Y+y][Player_X+x] == 2) {
		Player_Score++;
		Player_X+=x, Player_Y+=y;
		
		Board_Message = 5;
				
	} else if(Board[Map_Turn][Player_Y+y][Player_X+x] == 3) {
		if(Player_Score == Map_Score) {
			Map_Exit = 1;
			Board_Message=4;
			Player_X+=x, Player_Y+=y;
			
		} else {
			Board_Message=4;
			
		}
		
	} else if(Board[Map_Turn][Player_Y+y][Player_X+x] == 5) {
		Player_Damage = rand()%20+1;
		Player_HP -= Player_Damage;
		
		Board_Message = 7;
		Player_X+=x, Player_Y+=y;
		
	}
	
}

// 0 빈공간 // 1 벽 // 2 점수 // 3 탈출구 // 4 플레이어 //
void play_key_input() {
	int key = 0;
	
	while(1) {
		key = getch();
		
		/* 
		'w, W' 119 87
		'a, A' 97 65
		's, S' 115 83
		'd, D' 100 68
		
		'q, Q' 113 81
		*/
		
		if(key == 119 || key == 87) { // W
			judgment(0, -1);
			break;
			
		} else if(key == 115 || key == 83) { // S
			judgment(0, 1);
			break;
			
		} else if(key == 97 || key == 65) { // A
			judgment(-1, 0);
			break;
			
		} else if(key == 100 || key == 68) { // D
			judgment(1, 0);
			break;
			
		} else if(key == 113 || key == 81 || key == 3) { // Q 또는 Ctrl + C 
			End = 1;
			break;
			
		} else {
			Board_Message = 2;
			break;
			
		}
	}
}

void print_board() { // 판 출력
	int x, y;
	
	// 플레이어 위치 저장
	Board[Map_Turn][Player_Y][Player_X] = 4; 
	
	// 상단 문구 
	Cursor(10, 3);
	printf("조작: WASD   나가기: Q");
	
	// 0 빈공간 // 1 벽 // 2 점수 // 3 탈출구 // 4 플레이어 // 5 장애물 // 
	for(y=0; y<Board_Y; y++) {
		Cursor(10, y+5);
		for(x=0; x<Board_X; x++) { // x
			if(Board[Map_Turn][y][x] == 0) { 
				printf(" ");
			} else if(Board[Map_Turn][y][x] == 1) {
				printf("0");
			} else if(Board[Map_Turn][y][x] == 2) {
				printf("K");
			} else if(Board[Map_Turn][y][x] == 3) {
				printf("E");
			} else if(Board[Map_Turn][y][x] == 4) {
				if(y == Player_Y || x == Player_X) {
					printf((Player_HP < 0) ? "X" : "P");
				} else {
					Board[Map_Turn][y][x] = 0;
					printf(" ");
				}
			} else if(Board[Map_Turn][y][x] == 5) {
				printf("#");
			} else {
				printf("!");
			}
		}
		printf("\n");
	}
	Cursor(10, y+5+1+1);
	print_board_message(Board_Message);
	Cursor(10, y+5+1);
	printf("[ 체력: %d ]  [ 단계: %d ]  [ 열쇠: %d/%d ]                   ", (Player_HP < 0) ? 0 : Player_HP, Map_Turn+1, Map_Score, Player_Score);
	printf("\n");
}

// 게임 시작 
int game_play() {
	Game_Init();
	Board_Info_Get();
	print_board();

	while(1) {
		play_key_input();
		
		print_board();
		
		if(End == 1) { // 게임 끝 
			return 0;
			break;
		}
		if(Player_HP <= 0) {
			return 1;
			break;
		}
		if(Map_Exit == 1) {
			if(Turn_Change()) {
				return 2;
				break;
			}
		}
	}
}
