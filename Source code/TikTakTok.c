#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

enum {k1=49, k2, k3, k4, k5, k6, k7, k8, k9}; 

// 게임 종료 관련 키
enum {kQ=113, kCtrlC=3};

int turn = 1;
int end = 0;

char board[3][3] = { // 판
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

void print_board();
int check_win();
void pg_exit();

int main() {
    int player = 1; // 1 == O    1 != X 
    int y, x;
	
	printf(" [?] 수 놓기: 키패드 또는 숫자키(1~9)\n");
	printf(" [?] 나가기: Q 또는 Ctrl + C");
	
    while(1) {
        print_board();

        // 현재 차례인 플레이어 출력
        if(player == 1)
        	printf(" [i] 'O'의 차례입니다!\n", player);
		else
			printf(" [i] 'X'의 차례입니다!\n", player);
		
		// 키 입력 받고 위치 저장 
		printf(" [>] 키를 눌르세요 . . . ");
		
		switch(getch()) {
			case k1:
				y = 2, x = 0;
				break;
			
			case k2:
				y = 2, x = 1;
				break;
			
			case k3:
				y = 2, x = 2;
				break;
				
			case k4:
				y = 1, x = 0;
				break;
				
			case k5:
				y = 1, x = 1;
				break;
			
			case k6:
				y = 1, x = 2;
				break;
				
			case k7:
				y = 0, x = 0;
				break;
				
			case k8:
				y = 0, x = 1;
				break;
			
			case k9:
				y = 0, x = 2;
				break;
				
			case kQ:
				printf("\n\n [&] 게임이 종료되었습니다!");
				pg_exit();
				
			case kCtrlC:
				printf("\n\n [&] 게임이 종료되었습니다!");
				pg_exit();
				
			default :
				printf("\n\n [!] 잘못된 키를 눌렀습니다! 다시 입력하세요.\n ");
				
		}

        // 위치가 올바른가?
        if(y < 0 || y > 2 || x < 0 || x > 2) {
            printf(" [!] 잘못된 위치입니다. 다시 선택해주세요.\n ");
            continue;
        }
        
        if(board[y][x] == 'O' || board[y][x] == 'X') {
            printf("\n [!] 이미 선택된 위치입니다. 다시 선택해주세요.\n");
            continue;
        }

        // 수 놓기
        board[y][x] = player == 1 ? 'O' : 'X';

        // 승리 여부 체크 
        if(check_win()) {
            print_board();
            if(player == 1)
        		printf("\n [&] O의 승리입니다!", player);
			else
				printf("\n [&] X의 승리입니다!", player);
			
            pg_exit();
        }
        
        // 무승부일 시 
		if(turn == 9) {
			print_board();
			printf("\n [&] 무승부 입니다!");
			pg_exit();
		}
		
		// 턴 종료. 플레이어 변경 및 턴 증가 
        player = player == 1 ? 2 : 1;
        turn++;
    }
}

void print_board() {
    printf("\n\n");
    printf("         TURN %d\n", turn);
    printf("       %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("      ---+---+---\n");
    printf("       %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("      ---+---+---\n");
    printf("       %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int check_win() { // 승리 여부 체크
    int i, j;

    // 가로줄 체크
    for(i = 0; i < 3; i++) {
        if(board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return 1;
    	
    }

    // 세로줄 체크
    for(i = 0; i < 3; i++) {
        if(board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return 1;
        
    }

    // 대각선 체크
    if(board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return 1;
    
    if(board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return 1;
    

    return 0;
}

void pg_exit() {
	printf("\n\n");
	printf(" 프로그램을 종료합니다.\n");
	printf(" ⓒszukaotto 노마십가\n");
	printf(" 틱 택 톡\n\n ");
	
	system("pause");
	
	exit(0);
}
