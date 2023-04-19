/*
	* Bangking System ( 열혈 C++ 51p ) 	* Made by szukaotto 노마십가
*/ 
/*
	230413 | 기본적인 뼈대와 프로그램 종료 구현 완료. 함수 '계좌개설, 입금, 출금, 잔액조회'만 만들면 완성
	230414 | 모든 기능 구현 완료! 최종 완성.
	230415 | 최최종 완성. ui 더 깔끔하게
*/

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

#define NAME_LEN 20
#define MAX_ACCOUNT 1

void MakeAccount(void);      // 계좌개설 
void DepositMoney(void);     // 입    금 
void WithdrawalMoney(void);  // 출    금
void AccountInfo(void);      // 잔액조회 
void ProgramExit(void);      // 종    료 

enum {MAKE=1, DEPOSIT, WITHDRAWAL, INFO, EXIT};

typedef struct
{
	unsigned long accID;        // 계좌번호
	unsigned long accMoney;     // 잔    액
	char accName[NAME_LEN];     // 고객이름 
} acc;

acc accArr[MAX_ACCOUNT];      // 계정 저장

int accNum=0;                 // 현재 계정 갯수

int main(void) {
	srand(time(NULL));
  
	while(1) {
		// 메뉴 출력 
		system("cls");
		cout<<"----- 메뉴 -----"<<endl;
		cout<<"1. 계좌개설"<<endl;
		cout<<"2. 입    금"<<endl;
		cout<<"3. 출    금"<<endl;
		cout<<"4. 계정정보"<<endl;
		cout<<"5. 종    료"<<endl;
		cout<<"= ";

		int type=0;
		// cin 오류 방지. 버퍼 제거 
		if(!(cin>>type))
		{
			cout<<endl<<"숫자만 입력하세요 . . . ";
			cin.clear();
			cin.ignore(10000, '\n');
			getch();
			continue;
		}
   
		cout<<endl;

		switch(type)
		{
      case MAKE: // 계좌개설 
        MakeAccount();
        break;
      
      case DEPOSIT: // 입금
        DepositMoney();
        break;
      
      case WITHDRAWAL: // 출금 
        WithdrawalMoney();
        break;
      
      case INFO: // 계좌정보 
        AccountInfo();
        break;
      
      case EXIT: // 프로그램 종료
        ProgramExit();
        break;
      
      default : // 잘못된 값 입력
        cout<<"1~5 중으로 다시 입력해주세요 . . . ";
        type=0;
    }
    cout<<endl<<"아무 키를 누르면 메뉴로 돌아갑니다 . . . ";
		getch();

	}
}

void MakeAccount(void)
{
	unsigned long id;
	char name[NAME_LEN];
	unsigned long money;

	cout<<"[계좌개설]"<<endl;

	if(MAX_ACCOUNT == accNum)
	{
		cout<<endl<<"계좌생성 개수를 초과하였습니다. "<<MAX_ACCOUNT<<"개 이상을 넘을 순 없습니다."<<endl;
		return; 

	}

	cout<<"계좌번호: "; cin>>id;
	cout<<"성    함: "; cin>>name;
	cout<<"입 금 액: "; cin>>money;
	cout<<endl;	

	for(int i=0; i<accNum; i++)
	{
		if(accArr[i].accID == id)
		{
			cout<<"중복된 계좌번호 입니다. 계좌생성이 불가합니다."<<endl;
			return;

		}
	}

	cout<<"위 정보로 정말 계좌를 개설하시겠습니까? 계좌를 개설하시려면 1번 키를 누르세요."<<endl;
	cout<<"다른 키를 누르면 계좌개설이 취소됩니다."<<endl<<"> ";

	if(getch() != 49)
	{
		cout<<"Cancel"<<endl<<endl;
		cout<<"계좌개설이 취소되었습니다.";
		return; 

	} 

	cout<<"1"<<endl<<endl;

	accArr[accNum].accID=id;
	accArr[accNum].accMoney=money;
	strncpy(accArr[accNum].accName, name, NAME_LEN);

	cout<<"계좌개설이 완료되었습니다."<<endl<<endl;
	cout<<"[개설정보]"<<endl;
	cout<<"계좌번호: "<<accArr[accNum].accID<<endl;
	cout<<"성    함: "<<accArr[accNum].accName<<endl;
	cout<<"자    금: "<<accArr[accNum].accMoney<<endl;
  
	accNum++;
}

void DepositMoney(void)
{

	unsigned long id;
	unsigned long money;

	cout<<"[입    금]"<<endl;
	cout<<"계좌번호: "; cin>>id;

	for (int i=0; i<accNum; i++)
	{
		if(accArr[i].accID == id)
		{
			cout<<"입 금 액: "; cin>>money;

			if(money <= 0)
			{
				cout<<endl<<"1원 이하는 입금이 불가합니다."<<endl;
				return;
			}

			cout<<endl<<accArr[i].accName<<"님에게 정 "<<money<<"원을 보내시겠습니까? 보내시려면 1번 키를 누르세요."<<endl;
			cout<<"다른 키를 누르면 입금이 취소됩니다."<<endl<<"> ";

			if(getch() == 49)
			{
				cout<<"1"<<endl<<endl;
				accArr[i].accMoney += money;
        
				cout<<"입금이 완료되었습니다."<<endl<<endl;
				cout<<"["<<accArr[i].accID<<"] 계좌 잔액: "<<accArr[i].accMoney;
				return;
			}

			cout<<"Cancel"<<endl<<endl;
			cout<<"입금이 취소되었습니다.";
			return; 
		}
	}
	cout<<endl<<"입력하신 계좌번호를 찾을 수 없습니다."<<endl;
}

void WithdrawalMoney(void)
{
	unsigned long id;
	unsigned long money;

	cout<<"[출    금]"<<endl;
	cout<<"계좌번호: "; cin>>id;

	for(int i=0; i<accNum; i++)
	{
		if(accArr[i].accID == id)
		{
			cout<<endl<<"["<<accArr[i].accID<<"] 계좌 잔액: "<<accArr[i].accMoney<<endl<<endl;
			cout<<"출금액수: "; cin>>money;
			cout<<endl;

			if(money<=0)
			{
				cout<<"0원 이하의 금액은 출금할 수 없습니다."<<endl;
				return;
			}

			if(accArr[i].accMoney >= money)
			{
				accArr[i].accMoney -= money;
				cout<<"출금이 완료되었습니다."<<endl<<endl;
				cout<<"["<<accArr[i].accID<<"] 계좌 잔액: "<<accArr[i].accMoney;
				return; 
			}
      else
			{
				cout<<"잔액이 부족합니다.";
				return;
			}
  }
	cout<<"입력하신 계좌번호에 해당하는 정보를 찾을 수 없습니다."<<endl;
}

void AccountInfo(void)

{

	while(1)

	{

		cout<<"[계정정보]"<<endl;

		

		cout<<"1. 계좌번호로 검색하기"<<endl;

		cout<<"2. 모든 계정 검색하기"<<endl;

		cout<<"3. 메뉴로 돌아가기"<<endl<<"> ";

		

		int key = getch();

		

		if(key == 49)

		{

			int id;

			

			cout<<static_cast<char>(key)<<endl<<endl;

			

			cout<<"계좌번호: "; cin>>id; cout<<endl;

			

			cout<<"[조회결과]"<<endl;

			

			for(int l=0; l<accNum;l++)

			{

				if(accArr[l].accID == id)

				{

					cout<<"계좌번호  "<<accArr[l].accID<<endl;

					cout<<"성    함  "<<accArr[l].accName<<endl;

					cout<<"잔    액  "<<accArr[l].accMoney<<endl;

					return;

				}

			}

			cout<<"입력하신 계좌번호에 해당하는 정보를 찾을 수 없습니다."<<endl;

			return;

		}

		else if(key == 50)

		{

			cout<<static_cast<char>(key)<<endl<<endl;

				

			for(int i=0; i<accNum; i++) {

				cout<<"No. "<<i+1<<endl;

				cout<<"계좌번호  "<<accArr[i].accID<<endl;

				cout<<"성    함  "<<accArr[i].accName<<endl;

				cout<<"잔    액  "<<accArr[i].accMoney<<endl;

				cout<<endl;

			}

			

			return;

			

		}

		else if(key == 51)

		{

			cout<<static_cast<char>(key)<<endl<<endl;

			return;

		}

		else

		{

 			cout<<"?"<<endl<<endl;

			cout<<"잘못된 키를 눌렀습니다."<<endl;

			return; 

		}

	}

}

void ProgramExit(void)

{

	// 0~9 ASCII

	int exit_code = rand()%9;

	exit_code += 48;

	

	cout<<"[종    료]"<<endl;

	

	cout<<"! 정말로 종료하시겠습니까? [모든 정보]가 사라집니다. 종료하실려면 '"<<static_cast<char>(exit_code)<<"'번 키를 누르세요."<<endl;

	cout<<"다른키를 누르면 종료가 취소됩니다."<<endl<<"> ";

	

	if(getch() == exit_code)

	{

		cout<<static_cast<char>(exit_code)<<endl<<endl; 

		

		exit_code = rand()%9;

		exit_code += 48;

		

		cout<<"!! 정말? 정말로 종료하시겠습니까? [모든 정보]가 사라집니다. 종료하실려면 '"<<static_cast<char>(exit_code)<<"'번 키를 누르세요."<<endl;

		cout<<"다른키를 누르면 종료가 취소됩니다."<<endl<<"> ";

		

		if (getch() == exit_code)

		{

			cout<<static_cast<char>(exit_code)<<endl<<endl; 

			

			cout<<"프로그램을 종료합니다."<<endl<<endl;

			cout<<"ⓒszukaotto 노마십가"<<endl;

			cout<<"열혈 C++ 51p '은행계좌 관리 프로그램'"<<endl;

			

			for(int i=3; i>0;)

			{

				cout<<endl<<i<<"초 후 자동 종료됩니다 . . . ";

				Sleep(1000);

				i--;

			}

			

			exit(0);

		}

	}

	cout<<"Cancel"<<endl<<endl;

	cout<<"다른 키를 눌러 종료가 취소되었습니다."<<endl;

}
