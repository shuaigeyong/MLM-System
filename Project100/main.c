#include "MLM.h"

void main() {
	//displayAllStaff();
	//printf("\n");
	//system("pause");
	//loading();


	char select;
	do {
		sysColor();
		system("cls");
		displayHeader();
		printf("\t\t1.Login as member\n");
		printf("\t\t2.Login as staff\n");
		printf("\t\t3.Notification\n");
		printf("\t\t4.Setting:appearance\n");
		printf("\t\t5.Exit\n\n");
		printf("\t\tEnter > ");

		scanf("%c", &select);
		rewind(stdin);
		switch (select) {
		case '1':
			memberModule();
			break;
		case '2':
			staffModule();
			break;
		case '3':
			displayNotice();
			system("pause");
			break;
		case '4':
			appearance();
			break;
		case '5':
			system("cls");
			char text[50] = "thank for using our system !";
			char text2[100] = "We hope you have a great day and thank you again for choosing our company !";
			strupr(text);
			strupr(text2);
			printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
			for (int i = 0; i < strlen(text); i++) {
				printf("%c", text[i]);
				Sleep(70);
			}
			printf("\n\t\t\t\t\t\t");
			Sleep(700);
			for (int i = 0; i < strlen(text2); i++) {
				printf("%c", text2[i]);
				if (i == 27) {
					Sleep(500);
					printf("\n\t\t\t\t       ");
				}
				Sleep(70);
			}
			Sleep(1500);
			ending();
			break;
		
		default:
			rewind(stdin);
			printf("\nInvalid\a\n");
			Sleep(1000);
			break;
		}
	} while (select != '5');
}

void appearance() {
	FILE* fp;
	fp = fopen("appearance.bin", "wb");
	int op = '0';
	char key = '0';
	do {
		system("cls");
		printf("\n\t\t\t\t----------------------------------------------\n");
		printf("\t\t\t\t|                Appearance                  |\n");
		printf("\t\t\t\t----------------------------------------------\n");
		printf("\t\t\t\tSelect Then Press Enter...\n");
		printf("\t\t\t\t(Press 'N' to Exit)\n");
		
		switch (key) {
		case '1':
			printf("\n\n\n\t\t\t\t\t=============       -------------");
			printf("\n\t\t\t\t\t|1. Default |         2. Dark  ");
			printf("\n\t\t\t\t\t=============       -------------");
			op = 1;
			break;

		case '2':
		
			printf("\n\n\n\t\t\t\t\t-------------       =============");
			printf("\n\t\t\t\t\t 1. Default         | 2. Dark   |");
			printf("\n\t\t\t\t\t-------------       =============");
			op = 2;
			break;
		default:
			printf("\n\n\n\t\t\t\t\t-------------       -------------");
			printf("\n\t\t\t\t\t 1. Default           2. Dark  ");
			printf("\n\t\t\t\t\t-------------       -------------\n\n");
			op = 0;
			break;
		}
		rewind(stdin);
		key = getch();
		key = toupper(key);
		rewind(stdin);
	} while (key != 'N' && key!=13);
	if (op == 0) {
		fclose(fp);
		return 0;
	}
	else {
		fwrite(&op, sizeof(op), 1, fp);
		loading_animation();
		fclose(fp);
	}

}
void sysColor() {
	int color;
	FILE* fp;
	fp = fopen("appearance.bin", "rb");
	fread(&color, sizeof(color), 1, fp);
	if (color == 1) 
		system("color f0");
	else 
		system("color 0f");
	fclose(fp);
}


void loading() {
	//display loading image
	register int u, l, t;
	t = 0;
	for (int u = 0; u <= 50; u++) {
		system("cls");
		int l = 1;
		printf("\n\n\n\n");
		printf("\t\t                  U _____ u  _        ____   U  ___ u  __  __  U _____ u \n"
			"\t\t      __        __%c| ___%c|/ |%c|    U /%c___ | %c/ %c_ %c/U|' %c/ '|u%c| ___%c|/ \n"
			"\t\t      %c%c%c      /%c/ |  _| %cU | | u  %c| | u     | | | |%c| |%c/| |/ |  _|%c   \n"
			"\t\t      /%c %c /%c / /%c | |___  %c| |/__  | |/__.-,_| |_| | | |  | |  | |___   \n"
			"\t\t     U  %c V  V /  U|_____|  |_____|  %c____|%c_)-%c___/  |_|  |_|  |_____|  \n"
			"\t\t     .-,_%c /%c /_,-.<<   >>  //  %c%c  _// %c%c      %c%c   <<,-,,-.   <<   >>  \n"
			"\t\t      %c_)-'  '-(_/(__) (__)(_%c)(%c_)(__)(__)    (__)   (./  %c.) (__) (__) \n"
			, 92, 34, 34, 34, 92, 34, 92, 92, 92, 34, 92, 34, 92, 34, 34, 92, 92, 92, 34, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 34, 34, 92);
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t\tLoading...%d%c\n\t\t\t    ", t, 37);

		while (l <= u) {
			printf("%c", 22);
			l++;
		}
		printf("%c", 22);
		t += 2;
		Sleep(10);
	}
	printf("\n\n\t\t\t\t\t");

	system("pause");
	system("cls");

}