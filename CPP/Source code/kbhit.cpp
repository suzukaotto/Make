#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

void CursorVisibleSize(bool Visible) {
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 100; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = (Visible) ? TRUE : FALSE;      //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


void CursorPos(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main() {
    int key;
    int time_val;
    int count = 0;
	CursorVisibleSize(false);
	
	// set
	CursorPos(0, 2);
    cout<<"총 입력 수: "<<count;
	CursorPos(0, 3);
    cout<<"아스키 값만 | shift+q: 프로그람 종료";
	
    while(true) {
        if(kbhit()) {
            key = getch();
            if(key == 'Q') break;
            
            count++;
    		CursorPos(0, 2);
    		cout<<"총 입력 수: "<<count; 
    		
            CursorPos(0, 1);
            cout<<"입력된 키: "<<static_cast<char>(key)<<"       "<<endl;
            time_val = clock()+1000;
        }
        if(time_val <= clock() && time_val != -1){
        	CursorPos(0, 1);
    		cout<<"키를 입력하세요!         ";
    		time_val=-1;
		}
        CursorPos(0, 0);
        cout<<"clock: "<<clock();
    }

    return 0;
}

