// make day 21.9.2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS

void SelectionSort(int arr[], int n)
{
    int i, k, p, temp;
    for (i = 0; i < n - 1; i++) {
        p = i;
        for (k = i + 1; k < n; k++) {
            if (arr[k] < arr[p]) p = k;
        }
        temp = arr[i];
        arr[i] = arr[p];
        arr[p] = temp;
    }
}

int main()
{
    int  lotto[6] = { 0 };
    int i = 0, n = 0;
    int log = 0;
    
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    
    FILE *fp;
    
    fp = fopen("Log.txt", "w");
    
    printf("\tProgram RunTime: %dY-%dM-%dD %dh %dm %ds\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min , t->tm_sec);
    
    if(fp == NULL){
    	printf("\tFile Open Fail"); 
    	fprintf(fp, "[ %dY-%dM-%dD %dh %dm %ds ]: File Open Fail\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min , t->tm_sec);
  	} else {
   		printf("\tFile Open Complit");
   		fprintf(fp, "[ %dY-%dM-%dD %dh %dm %ds ]: File Open Complit\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min , t->tm_sec);
  	}
    
    printf("\n\t기준 - 나눔로또(동행복권, 평균 1등 당첨금액 기준 (dhlottery, 2022/9/2)), 독립시행");
    
    COORD pos;
		pos.X = 8;
		pos.Y = 14;
    
    srand((unsigned)time(NULL));

    while (n < 6)   
    {
        int r = rand() % 45 + 1;

        for (i = 0; i < n; i++){
            if (lotto[i] == r) break;
		}
        if (n == i) lotto[n++] = r;
    }

    SelectionSort(lotto, 6);

	fprintf(fp, "[ %dY-%dM-%dD %dh %dm %ds ]: Lotto Number\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min , t->tm_sec);
	printf("\n\n\n\tLotto Number\n");
    for (i = 1; i < 7; i++){
       	printf("\t%d. %d\n", i, lotto[i-1]);
       	fprintf(fp, "%d. %d   ", i, lotto[i-1]);
	}
	fprintf(fp, "\n");
	
	long long rotate = 0;
	
	while(1){
		int  lottoA[6] = { 0 };
    	int l = 0, nn = 0;
    	
    	time_t timer;
    	struct tm* t;
    	timer = time(NULL);
    	t = localtime(&timer);
    	
		rotate++;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		fprintf(fp, "[ %dY-%dM-%dD %dh %dm %ds ]: Calculation / Rotation: %d / Used Money: %d000\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min , t->tm_sec, rotate, rotate);
		printf("Lotto Calculation\n");
    	
    	while(nn < 6){
    	    int ra = rand() % 45 + 1;
	
	        for (l = 0; l < nn; l++){
	            if (lottoA[l] == ra) break;
			}
	        if (nn == l) lottoA[nn++] = ra;
	    }
	    
	    SelectionSort(lottoA, 6);
		
		for (l = 1; l < 7; l++){
        	printf("\t%d. %d\n", l, lottoA[l-1]);
        	fprintf(fp, "%d. %d   ", l, lottoA[l-1]);
		}
		fprintf(fp, "%\n");
		printf("\n\n\tRotation: %d\n\tUsed Money: %d000\n\n", rotate, rotate);
		
		if(lotto[0] == lottoA[0] && lotto[1] == lottoA[1] && lotto[2] == lottoA[2] && lotto[3] == lottoA[3] && lotto[4] == lottoA[4] && lotto[5] == lottoA[5]){
			fprintf(fp, "[ %dY-%dM-%dD %dh %dm %ds ]: Winning!", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min , t->tm_sec);
			printf("\n\tWinning!!                                                    	\n\tPercentage: 8145060 / '1'                          ");
			printf("\n\tPress any key to exit . . . ");
			getch();
			break;
		}
		
		printf("\n\tNow Time: [ %dY-%dM-%dD %dh %dm %ds ]       \n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min , t->tm_sec);
	}
	
	fclose(fp);
    return 0;
}
