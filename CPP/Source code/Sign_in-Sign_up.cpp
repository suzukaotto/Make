#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

#define MAX_LEN 10001

#define ID_LEN 10+1 // 문자열의 끝 표현하는 공간을 만들어 주기 위함 
#define PW_LEN 20+1
#define NIC_LEN 10+1

#define MAX_ACC 100

enum {N_ONE=49, N_TWO, N_THREE, N_FOUR, N_FIVE};

int accNum=0;

struct Account{
	char id[ID_LEN];
	char pw[PW_LEN];
	char nic[NIC_LEN];
};

struct Login_Whether{
	bool login_value=false;
	int login_account_num=-1;
};

Account Acc[MAX_ACC];
Login_Whether Login_Whet;

void Login();
void NewAcc();
void FindPw();
void ProgramExit();
//void WorkPlace();
void ModifyAcc();
void LogoutAcc();
void AccPrintSingle(int printAccNum);
void AccPrint();

int main()
{
	cout<<"%% 로그인/회원가입 구현 프로그램 %%"<<endl<<endl<<endl<<endl;
	cout<<"제목 그대로 입니다."<<endl;
	cout<<"로그인과 회원가입을 구현해본 프로그램 입니다."<<endl<<endl;
	cout<<"메뉴 창에서 Ctrl+C 키를 누르면 바로 종료하실 수 있습니다."<<endl;
	cout<<"종료 시 저장한 데이터가 모두 영구삭제 된다는 점 유의하십시오."<<endl<<endl;
	cout<<"5번 키를 눌르면 현재 저장되어있는 모든 계정들을 볼 수 있습니다."<<endl<<endl<<endl<<endl;
	cout<<"ⓒszukaotto 노마십가"<<endl<<endl;
	
	system("pause");
	
	int key;
	srand(time(NULL));

	
	while(1)
	{
		if(Login_Whet.login_value==true)
		{
			system("cls");
			cout<<"["<<Acc[Login_Whet.login_account_num].nic<<"]님, 어서와요!"<<endl;
			cout<<"로그인 된 ID: "<<Acc[Login_Whet.login_account_num].id<<endl<<endl; 
//			cout<<"1. 작업"<<endl;
			cout<<"1. 정보수정"<<endl;
			cout<<"2. 로그아웃"<<endl;
			cout<<"3. 종료"<<endl;
			cout<<"> "; key=getch();
			
			cout<<static_cast<char>(key)<<endl<<endl;
			
			// Ctrl+C 강제종료 
			if(key==3)
				return 0;
				
			switch(key)
			{
//				case N_ONE:
//					WorkPlace();
//					break;
					
				case N_ONE:
					ModifyAcc();
					break;
					
				case N_TWO:
					LogoutAcc();
					break;
					
				case N_THREE:
					ProgramExit();
					break;
					
				case N_FIVE:
					AccPrint();
					break;
					
				default:
					cout<<"[!] 잘못된 키를 눌렀습니다.";
					break;
					
			}
			
			cout<<endl<<endl<<endl<<"[>] 아무 키를 누르면 메인메뉴로 돌아갑니다 . . . ";
			getch();
		}
		else
		{
			system("cls");
			cout<<"환영합니다!"<<endl;
			cout<<"1. 로그인"<<endl; 
			cout<<"2. 회원가입"<<endl;
			cout<<"3. 비밀번호 찾기"<<endl;
			cout<<"4. 종료"<<endl;
			cout<<"> "; key=getch();
			
			cout<<static_cast<char>(key)<<endl<<endl;
			
			// Ctrl+C 강제종료 
			if(key==3)
				return 0;
			
			switch(key)
			{
				case N_ONE:
					Login();
					break;
					
				case N_TWO:
					NewAcc();
					break;
					
				case N_THREE:
					FindPw();
					break;
					
				case N_FOUR:
					ProgramExit();
					break;
					
				case N_FIVE:
					AccPrint();
					break;
					
				default:
					cout<<"[!] 잘못된 키를 눌렀습니다.";
					break;
					
			}
			
			cout<<endl<<endl<<endl<<"[>] 아무 키를 누르면 메인메뉴로 돌아갑니다 . . . ";
			getch();
		}
	}
}


void Login()
{
	system("cls");
	
	char id[MAX_LEN-1];
	char pw[MAX_LEN-1];
	
	cout<<"[ 로그인 ]"<<endl<<endl;
	
	cout<<"아이디: "; cin>>id;
	cout<<"비밀번호: "; cin>>pw;
	
	cout<<endl;
	
	for(int i=0; i<accNum; i++)
	{
		if(strcmp(Acc[i].id, id) == 0)
		{
			if(strcmp(Acc[i].pw, pw) == 0)
			{
				cout<<"[i] 로그인 성공";
				Login_Whet.login_value=true;
				Login_Whet.login_account_num=i;
				return;
			}
		}
	}
	
	cout<<"[!] 로그인 실패. 아이디 또는 비밀번호가 다릅니다.";
}

void NewAcc()
{
	char id[MAX_LEN-1];
	char pw[MAX_LEN-1];
	char repw[MAX_LEN-1];
	char nic[MAX_LEN-1];
	
	system("cls");
	
	cout<<"[ 회원가입 ]"<<endl<<endl;
	
	if(accNum==MAX_ACC)
	{
		cout<<"계정 생성 횟수 한도를 초과하였습니다.";
		return;
	}
	
	cout<<"사용할 아이디(4~"<<ID_LEN-1<<"): "; cin>>id;
	
	cout<<endl;
	
	if(strlen(id) < 4)
	{
		cout<<"[!] 사용할 아이디가 너무 짧습니다.";
		return;
	}
	
	if(strlen(id) > ID_LEN-1)
	{
		cout<<"[!] 사용할 아이디가 너무 깁니다.";
		return;
	}
	
	for(int i=0; i<accNum; i++)
	{
		if(strcmp(Acc[i].id, id) == 0)
		{
			cout<<"[!] 중복된 ID 입니다."<<endl;
			return;
		}
	}
	
	cout<<"비밀번호(8~"<<PW_LEN-1<<"): "; cin>>pw;
	
	if(strlen(pw) < 8)
	{
		cout<<"[!] 사용할 비밀번호가 너무 짧습니다.";
		return;
	}
	else if(strlen(pw) > PW_LEN-1)
	{
		cout<<"[!] 사용할 비밀번호가 너무 깁니다.";
		return;
	}
	
	cout<<"비밀번호 확인: "; cin>>repw;
	
	cout<<endl;
	
	if(strcmp(pw, repw) != 0)
	{
		cout<<"[!] 비밀번호가 일치하지 않습니다.";
		return;
	}
	
	cout<<"사용할 닉네임(2~"<<NIC_LEN-1<<"): "; cin>>nic;
	
	cout<<endl;
	
	if(strlen(nic) < 2)
	{
		cout<<"[!] 사용할 닉네임이 너무 짧습니다.";
		return;
	}
	
	if(strlen(nic) > NIC_LEN-1)
	{
		cout<<"[!] 사용할 닉네임이 너무 깁니다.";
		return;
	}
	
	cout<<"[?] 위 정보로 정말 계정을 생성하시겠습니까? (예: 1)"<<endl;
	cout<<"> ";
	
	if(getch()!=N_ONE)
	{
		cout<<"아니오"<<endl<<endl;
		cout<<"[i] 계정 생성이 취소되었습니다.";
		return; 
	}
	
	cout<<"예"<<endl<<endl;
	
	strcpy(Acc[accNum].id, id);
	strcpy(Acc[accNum].pw, pw);
	strcpy(Acc[accNum].nic, nic);
	
	cout<<"[i] 계정생성이 완료되었습니다."<<endl<<endl;
	
	AccPrintSingle(accNum);
	
	cout<<"[!] 아이디를 꼭 기억하시기 바랍니다.";
	
	accNum++;
}

void FindPw()
{
	int faccNum=-1;
	char id[MAX_LEN-1];
	char pw[MAX_LEN-1];
	char repw[MAX_LEN-1];
	
	system("cls");
	
	cout<<"[ 비밀번호 찾기 ]"<<endl<<endl;
	
	cout<<"아이디: "; cin>>id;
	
	for(int i=0; i<accNum; i++)
	{
		if(strcmp(Acc[i].id, id)==0)
		{
			faccNum=i;
		}
	}
	
	if(faccNum==-1)
	{
		cout<<endl<<"[!] 일치하는 계정을 찾을 수 없습니다.";
		return;
	}
	
	AccPrintSingle(faccNum);
	cout<<endl<<"[?] 비밀번호를 변경하시겠습니까? (예: 1)"<<endl;
	cout<<"> ";
	
	if(getch() != N_ONE)
	{
		cout<<"아니오"<<endl<<endl;
		cout<<"[i] 비밀번호를 변경하지 않았습니다."<<endl;
		cout<<"[i] [ 비밀번호 찾기 ]를 종료합니다.";
		return; 
	}
	
	cout<<"예"<<endl<<endl;
	
	cout<<"비밀번호(8~"<<PW_LEN<<"): "; cin>>pw;
	
	if(strlen(pw) < 8)
	{
		cout<<"[!] 비밀번호가 너무 짧습니다.";
		return;
	}
	else if(strlen(pw) > PW_LEN)
	{
		cout<<"[!] 비밀번호가 너무 깁니다.";
		return;
	}
	
	cout<<"비밀번호 확인: "; cin>>repw;
	
	cout<<endl;
	
	if(strcmp(pw, repw) != 0)
	{
		cout<<"[!] 비밀번호가 일치하지 않습니다.";
		return;
	}
	
	strcpy(Acc[faccNum].pw, pw);
	cout<<"[i] 비밀번호가 변경되었습니다."<<endl<<endl;
	
	AccPrintSingle(faccNum);
}

void WorkPlace()
{
	system("cls");
	
	cout<<"[ 작업 ]";
}

void ModifyAcc()
{
	char id[MAX_LEN];
	char pw[MAX_LEN];
	char repw[MAX_LEN];
	char nic[MAX_LEN];
	
	system("cls");
	
	cout<<"[ 정보수정 ]"<<endl<<endl;
	
	cout<<"비밀번호 확인: "; cin>>pw;
	
	if(strcmp(Acc[Login_Whet.login_account_num].pw, pw) != 0)
	{
		cout<<"[!] 비밀번호가 일치하지 않습니다.";
		return;
	}
	
	system("cls");
	
	cout<<"[ 정보수정 ]"<<endl;
	cout<<"로그인 된 ID: "<<Acc[Login_Whet.login_account_num].id<<endl<<endl; 
	
	cout<<"[ 변경할 정보 ]"<<endl;
	cout<<"1. 아이디"<<endl; 
	cout<<"2. 비밀번호"<<endl;
	cout<<"3. 닉네임"<<endl;
	cout<<"4. 나가기"<<endl;
	cout<<"> ";
	
	switch(getch())
	{
		case N_ONE:
			cout<<"1"<<endl<<endl;
			
			cout<<"변경할 아이디(4~"<<ID_LEN-1<<"): "; cin>>id;
	
			cout<<endl;
			
			if(strlen(id) < 4)
			{
				cout<<"[!] 변경할 아이디가 너무 짧습니다.";
				return;
			}
			
			if(strlen(id) > ID_LEN-1)
			{
				cout<<"[!] 변경할 아이디가 너무 깁니다.";
				return;
			}
			
			for(int i=0; i<accNum; i++)
			{
				if(strcmp(Acc[i].id, id) == 0)
				{
					cout<<"[!] 중복된 아이디 입니다.";
					return; 
				}
			}
			
			cout<<"[?] 정말 아이디를 변경하시곘습니까? (예: 1)"<<endl;
			cout<<"> ";
			
			if(getch()!=N_ONE)
			{
				cout<<"아니오"<<endl<<endl;
				cout<<"[i] 아이디 변경이 취소되었습니다.";
				return;
			}
			
			cout<<"예"<<endl<<endl;
			
			strcpy(Acc[Login_Whet.login_account_num].id, id);
			
			cout<<"[i] 아이디 변경이 완료되었습니다."<<endl<<endl;
			
			AccPrintSingle(Login_Whet.login_account_num);
			
			return;
		
		case N_TWO:
			cout<<"2"<<endl<<endl;
			 
			cout<<"비밀번호 확인: "; cin>>pw;
	
			if(strcmp(Acc[Login_Whet.login_account_num].pw, pw) != 0)
			{
				cout<<"[!] 비밀번호가 일치하지 않습니다.";
				return;
			}
			
			cout<<endl;
			
			cout<<"변경할 비밀번호(8~"<<PW_LEN-1<<"): "; cin>>pw;
	
			if(strlen(pw) < 8)
			{
				cout<<"[!] 변경할 비밀번호가 너무 짧습니다.";
				return;
			}
			else if(strlen(pw) > PW_LEN-1)
			{
				cout<<"[!] 변경할 비밀번호가 너무 깁니다.";
				return;
			}
			
			cout<<"비밀번호 확인: "; cin>>repw;
			
			cout<<endl;
			
			if(strcmp(pw, repw) != 0)
			{
				cout<<"[!] 비밀번호가 일치하지 않습니다.";
				return;
			}
			
			cout<<"[?] 정말 비밀번호를 변경하시곘습니까? (예: 1)"<<endl;
			cout<<"> ";
			
			if(getch()!=N_ONE)
			{
				cout<<"아니오"<<endl<<endl;
				cout<<"[i] 비밀번호 변경이 취소되었습니다.";
				return;
			}
			
			cout<<"예"<<endl<<endl;
			
			strcpy(Acc[Login_Whet.login_account_num].pw, pw);
			
			cout<<"[i] 비밀번호 변경이 완료되었습니다."<<endl<<endl;
			
			AccPrintSingle(Login_Whet.login_account_num);
			
			return;
			
		case N_THREE:
			cout<<"3"<<endl<<endl;
			
			cout<<"변경할 닉네임(2~"<<NIC_LEN-1<<"): "; cin>>nic;
	
			cout<<endl;
			
			if(strlen(nic) < 2)
			{
				cout<<"[!] 사용할 닉네임이 너무 짧습니다.";
				return;
			}
			
			if(strlen(nic) > NIC_LEN-1)
			{
				cout<<"[!] 사용할 닉네임이 너무 깁니다.";
				return;
			}
			
			cout<<"[?] 정말 닉네임을 변경하시겠습니까? (예: 1)"<<endl;
			cout<<"> ";
			
			if(getch()!=N_ONE)
			{
				cout<<"아니오"<<endl<<endl;
				cout<<"[i] 닉네임 변경이 취소되었습니다.";
				return;
			}
			
			cout<<"예"<<endl<<endl;
			
			strcpy(Acc[Login_Whet.login_account_num].nic, nic);
			
			cout<<"[i] 닉네임 변경이 완료되었습니다."<<endl<<endl;
			
			AccPrintSingle(Login_Whet.login_account_num);
			
			return;
			
		case N_FOUR:
			cout<<"3"<<endl<<endl;
			
			return;
			
		default:
			cout<<"?"<<endl<<endl;
			cout<<"[!] 잘못된 키를 눌렀습니다.";
			
			return;
			
	}
	
}

void ProgramExit()
{
	system("cls");
	
	// 0~9 ASCII
	int exit_code = rand()%9;
	exit_code += 48;
	
	cout<<"[ 종료 ]"<<endl<<endl;
	
	cout<<"[!] 정말로 종료하시겠습니까? [모든 정보]가 사라집니다. 종료하실려면 '"<<static_cast<char>(exit_code)<<"'번 키를 누르세요."<<endl;
	cout<<"[?] 다른키를 누르면 종료가 취소됩니다."<<endl<<"> ";
	
	if(getch() == exit_code)
	{
		cout<<static_cast<char>(exit_code)<<endl<<endl; 
		
		exit_code = rand()%9;
		exit_code += 48;
		
		cout<<"[!] 정말? 정말로 종료하시겠습니까? [모든 정보]가 사라집니다. 종료하실려면 '"<<static_cast<char>(exit_code)<<"'번 키를 누르세요."<<endl;
		cout<<"[?] 다른키를 누르면 종료가 취소됩니다."<<endl<<"> ";
		
		if (getch() == exit_code)
		{
			for(int i=3; i>0;)
			{
				system("cls");
				
				cout<<"&& 프로그램을 종료합니다. &&"<<endl<<endl;
				cout<<"ⓒszukaotto 노마십가"<<endl;
				cout<<"회원가입/로그인 구현 프로그램"<<endl<<endl;
				
				cout<<i<<"초 후 자동 종료됩니다 . . . ";
				Sleep(1000);
				cout<<endl;
				i--;
			}
			
			exit(0);
		}
	}
	cout<<"취소"<<endl<<endl;
	cout<<"[i] 다른 키를 눌러 종료가 취소되었습니다."<<endl;
}

void LogoutAcc()
{
	system("cls");
	
	cout<<"[ 로그아웃 ]"<<endl<<endl;
	
	cout<<"[?] 정말 로그아웃 하시겠습니까? (예: 1)"<<endl;
	cout<<"> ";
	
	if(getch() != N_ONE)
	{
		cout<<"아니오"<<endl<<endl;
		cout<<"로그아웃이 취소되었습니다.";
		return;
	}
	
	cout<<"예"<<endl<<endl;
	
	Login_Whet.login_value=false;
	
	cout<<"로그아웃이 완료되었습니다.";
}

void AccPrintSingle(int printAccNum)
{
	cout<<"[ 계정 정보 ]"<<endl;
	cout<<"아이디: "<<Acc[printAccNum].id<<endl;
	cout<<"비밀번호: "<<Acc[printAccNum].pw<<endl;
	cout<<"닉네임: "<<Acc[printAccNum].nic<<endl<<endl;
}

void AccPrint()
{
	system("cls");
	
	cout<<"[ 전체 계정 정보 ]"<<endl<<endl;
	for(int i=0; i<accNum; i++)
	{
		cout<<"No."<<i+1<<endl;
		AccPrintSingle(i);
	}
}
