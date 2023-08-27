#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

void CursorVisibleSize(bool Visible) {
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 100; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = (Visible) ? TRUE : FALSE;      //Ŀ�� Visible TRUE(����) FALSE(����)
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
    cout<<"�� �Է� ��: "<<count;
	CursorPos(0, 3);
    cout<<"�ƽ�Ű ���� | shift+q: ���α׶� ����";
	
    while(true) {
        if(kbhit()) {
            key = getch();
            if(key == 'Q') break;
            
            count++;
    		CursorPos(0, 2);
    		cout<<"�� �Է� ��: "<<count; 
    		
            CursorPos(0, 1);
            cout<<"�Էµ� Ű: "<<static_cast<char>(key)<<"       "<<endl;
            time_val = clock()+1000;
        }
        if(time_val <= clock() && time_val != -1){
        	CursorPos(0, 1);
    		cout<<"Ű�� �Է��ϼ���!         ";
    		time_val=-1;
		}
        CursorPos(0, 0);
        cout<<"clock: "<<clock();
    }

    return 0;
}

