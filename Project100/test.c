#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>   //for getch() function
#include<math.h>
#include <time.h>
#include <Windows.h>  //for Sleep() function
#pragma warning(disable:4996)
typedef struct {
	char staffId[7];
	char staffName[31];
	//int staffIc
	int staffPassword[99];
	char staffPosition[26];
}Test;

void maidfwefwef() {
	int r[3];
	printf("%d", r[3]);


	/*Test test[4] = {
		{"abc","def",{57,57,57},"ceo"},
		{"dad","der",{57,57,57},"cio"},
		{"bc","df",{57,57,57},"eo"},
		{"ac","ef",{57,57,57},"co"}
	};
	Test t2[999];
	FILE* fp;
	fp = fopen("t.bin", "rb");
	//fwrite(&test, sizeof(test), 1, fp);
	fread(&t2, sizeof(t2), 1, fp);
	printf("%s", t2[2].staffName);


	fclose(fp);*/
	char c = getch();
	printf("%d", c);
	
}