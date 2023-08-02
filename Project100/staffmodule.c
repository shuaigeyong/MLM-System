#include "MLM.h"

//Author : Tan Chin Yong
//Module : Staff Module

//Account Testing:
//ID  Password
//O01 12345678@Abc
//I01 12345678@Abc

void staffModule() {
	system("mode con cols=120");         //define the window size and color
	sysColor();                  
	//initialization
	Staffaccount currentStaffAcc;
	Staffaccount staff = { 0 };
	int countStaff = 0;
	countStaff = countstaff(countStaff, staff);
	int verify;
	//
	char ch;
	currentStaffAcc = stafflogin(countStaff);
	if (currentStaffAcc.staffGender != '0') {
		verify = verify_robot();
		
		if (verify) {
			printf("\n\t\t\t\tlogin successful\n");
			system("pause");
			//record history to bin file
			FILE* fp;
			fp = fopen("history.bin", "ab");
			History h;
			getDateTime(&h.date.day, &h.date.month, &h.date.year, &h.htime.hour, &h.htime.minute, &h.htime.second);
			strcpy(h.staffName, currentStaffAcc.staffName);
			strcpy(h.staffId, currentStaffAcc.staffId);
			sprintf(h.event, "Login");
			fwrite(&h, sizeof(h), 1, fp);
			fclose(fp);
			//
			loading();
			do {
				int countStaff = 0;
				countStaff = countstaff(countStaff, staff);
				system("cls");
				printf("\n\n\t");
				display_currentAcc_info(currentStaffAcc);
				displayStaffHeader();
				printf("\t\t(N=Log out)\n");
				printf("\t\t1.Display All\n");
				printf("\t\t2.Register New Staff acc\n");
				printf("\t\t3.Delete Staff Account\n");
				printf("\t\t4.Modify Staff Account\n");
				printf("\t\t5.View Account History\n");
				printf("\t\t6.Stock Management\n");
				printf("\t\t7.Manage Notification\n");
				printf("\t\t8.Delete Member\n");
				printf("\t\t9.Reset Password\n");
				printf("\n\t\tEnter  > ");
				scanf("%c", &ch);
				rewind(stdin);
				switch (ch) {
				case '1':displayAllStaff();break;
				case '2':
					if (strcmp(currentStaffAcc.staffPosition, "Operations Manager") == 0 || strcmp(currentStaffAcc.staffPosition, "HR Manager") == 0) {
						registerNewStaff(countStaff,currentStaffAcc);
					}
					else {
						printf("Only Managers can Create New Account\n");
						Sleep(1000);
					}

					break;
				case '3':
					if (strcmp(currentStaffAcc.staffPosition, "Operations Manager") == 0 || strcmp(currentStaffAcc.staffPosition, "HR Manager") == 0) {
						deletestaff(countStaff, currentStaffAcc);
					}
					else {
						printf("Only Managers can Create New Account\n");
						Sleep(1000);
					}
					break;
				case '4':rewind(stdin); modifyStaffAcc(countStaff, currentStaffAcc); break;
				case '5':displayHistory(); break;
				case '6':stockModule(); break;
				case '7':manageNotice(currentStaffAcc); break;
				case '8':system("cls"); deleteMember(); break;
				case '9':resetPassword(currentStaffAcc); break;
				case 'n': break;
				default:
					printf("Invalid\a\n");
					Sleep(1000);
					break;
				}
				system("cls");
			} while (ch != 'n');
		}
	}

}




void displayHistory() {
	system("cls");
	printf("\t\t\t\t    --------------------------------\n");
	printf("          \t\t\t\t STAFF ACCOUNT HISTORY   \n");
	printf("\t\t\t\t    --------------------------------\n");
	printf("-----------------------------------------------------------------------------------------------------------------");
	char content[99];
	FILE* fp;
	fp = fopen("history.bin", "rb");
	History h;
	int day, month, year;
	printf("\nEnter Date (dd-mm-yyy) : ");
	rewind(stdin);
	scanf("%d-%d-%d", &day, &month, &year);
	rewind(stdin);
	int no=0;
	while (fread(&h, sizeof(h), 1, fp) != 0) {
		if (h.date.day == day && h.date.month == month && h.date.year == year) {
			no++;
			printf("%d.TIME:%d:%d:%d\n    ID:%s Name:%s : %s\n\n",no,h.htime.hour,h.htime.minute,h.htime.second, h.staffId,h.staffName, h.event);
		}
	}
	fclose(fp);
	system("pause");
}

int check_Position_Existing(char position[26]) {
	Staffaccount chck;
	FILE* fp;
	fp = fopen("staffAccount.bin", "rb");
	while (fread(&chck, sizeof(Staffaccount), 1, fp) != 0) {
		if (strcmp(chck.staffPosition, position) == 0) {
			return 1;
		}
	}
	fclose(fp);
	return 0;
}
void display_currentAcc_info(Staffaccount userInfo) {
	printf("User ID : %s\tUser Name : %s\tUser Position : %s\n", userInfo.staffId, userInfo.staffName, userInfo.staffPosition);
}

void countNotice() {
	char readList[999];
	int i = 0;
	FILE* fp;
	fp = fopen("notice.bin", "rb");
	while (fread(&readList, sizeof(readList), 1, fp) != 0) {
		i++;
	}
	printf("\t\tNotification x %d \n", i);
	fclose(fp);
}
void displayNotice() {
	char readList[999];
	int i = 0;

	FILE* fp;
	fp = fopen("notice.bin", "rb");
	system("cls");
	printf("\n                                        NOTIFICATION\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	while (fread(&readList, sizeof(readList), 1, fp) != 0) {
		printf("%d.%s\n\n", i + 1, readList);
		i++;
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	fclose(fp);
}
void manageNotice(Staffaccount currentAcc) {
	int op = 0;
	while (op != 3) {
		system("cls");
		displayNotice();
		printf("\t\t---------------------------------------\n");
		printf("\t\t  1.Add Noticfication\n");
		printf("\t\t  2.Delete Noticfication\n");
		printf("\t\t  3.Exit\n");
		printf("\t\t---------------------------------------\n");
		printf("Enter : ");
		scanf("%d", &op);
		rewind(stdin);
		switch (op) {
		case 1:
			addNotice(currentAcc);
			break;
		case 2:
			deleteNotice(currentAcc);
			break;
		default:
			break;
		}
	}

}
void addNotice(Staffaccount currentAcc) {
	char list[999];
	FILE* fp;
	fp = fopen("notice.bin", "ab");
	printf("Enter notice  : ");
	rewind(stdin);
	scanf("%[^\n]", list);
	rewind(stdin);
	fwrite(&list, sizeof(list), 1, fp);
	fclose(fp);
	printf("Successful Adding Notice\n");
	FILE* hfp;
	hfp = fopen("history.bin", "ab");
	History h;
	getDateTime(&h.date.day, &h.date.month, &h.date.year, &h.htime.hour, &h.htime.minute, &h.htime.second);
	strcpy(h.staffName, currentAcc.staffName);
	strcpy(h.staffId, currentAcc.staffId);
	sprintf(h.event, "Add Notification");
	fwrite(&h, sizeof(h), 1, hfp);
	fclose(hfp);
	system("pause");
}
void deleteNotice(Staffaccount currentAcc) {
	char list[99][999];
	int count = 0;
	int row;
	FILE* fp;
	fp = fopen("notice.bin", "rb");
	while (fread(&list[count], sizeof(list[count]), 1, fp) != 0) {
		count++;
	}
	printf("Row > ");
	scanf("%d", &row);
	rewind(stdin);
	if (row > 0 && row - 1 < count) {
		row = row - 1;
		fclose(fp);
		FILE* dfp;
		dfp = fopen("notice.bin", "wb");
		for (int i = row; i < count; i++) {
			strcpy(list[i], list[i + 1]);
		}
		for (int i = 0; i < count - 1; i++) {
			fwrite(&list[i], sizeof(list[i]), 1, dfp);
		}
		fclose(dfp);
		printf("Delete successful\n");
		system("pause");
	}
	else {
		printf("Invalid\n");
		system("pause");
	}
	FILE* hfp;
	hfp = fopen("history.bin", "ab");
	History h;
	getDateTime(&h.date.day, &h.date.month, &h.date.year, &h.htime.hour, &h.htime.minute, &h.htime.second);
	strcpy(h.staffName, currentAcc.staffName);
	strcpy(h.staffId, currentAcc.staffId);
	sprintf(h.event, "Delete Notification");
	fwrite(&h, sizeof(h), 1, hfp);
	fclose(hfp);
}

void ending() {
	//system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\tU _____ u _   _    ____    \n"
		"\t\t\t\t\t\t%c| ___%c|/| %c |%c|  |  _%c%c   \n"
		"\t\t\t\t\t\t |  _|%c <|  %c| |>/| | | |  \n"
		"\t\t\t\t\t\t | |___ U| |%c  |uU| |_| |%c \n"
		"\t\t\t\t\t\t |_____| |_| %c_|  |____/ u \n"
		"\t\t\t\t\t\t <<   >> ||   \\\\,-.|||_    \n"
		"\t\t\t\t\t\t(__) (__)(_%c)  (_/(__)_)   \n\n", 92, 34, 92, 34, 34, 92, 34, 92, 92, 92, 92, 34);
	printf("\t\t\t\t\t    %c THANKS FOR USING OUR  MLM SYSTEM %c \n\n\n\t\t\t\t\t\t", 1, 1);
	system("pause");
}

void banana() {
	printf("\t\t\t\t _\n");
	printf("\t\t\t\t//\\\n");
	printf("\t\t\t\tV  \\\n");
	printf("\t\t\t\t \\  \\_\n");
	printf("\t\t\t\t  \\,'.`-.\n");
	printf("\t\t\t\t   |\\ `. `.\n");
	printf("\t\t\t\t   ( \\  `. `-.                        _,.-:\\\n");
	printf("\t\t\t\t    \\ \\   `.  `-._             __..--' ,-';/\n");
	printf("\t\t\t\t     \\ `.   `-.   `-..___..---'   _.--' ,'/\n");
	printf("\t\t\t\t      `. `.    `-._        __..--'    ,' /\n");
	printf("\t\t\t\t        `. `-_     ``--..''       _.-' ,'\n");
	printf("\t\t\t\t          `-_ `-.___        __,--'   ,'\n");
	printf("\t\t\t\t             `-.__  `----\"\"\"    __.-'\n");
	printf("\t\t\t\t                  `--..____..--'\n");

}
void alien() {
	printf("\t\t\t\t\t                   .-.\n");
	printf("\t\t\t\t\t    .-\"\"`\"\"-.    |(@ @)\n");
	printf("\t\t\t\t\t _/`oOoOoOoOo`\\_ \\ \\-/\n");
	printf("\t\t\t\t\t'.-=-=-=-=-=-=-.' \\/ \\\n");
	printf("\t\t\t\t\t  `-=.=-.-=.=-'    \\ /\\\n");
	printf("\t\t\t\t\t     ^  ^  ^       _H_ \n");

}
void dog() {
	printf("\t\t\t\t\t\t    ___\n");
	printf("\t\t\t\t\t\t __/o `.  .-\"\"\"-.\n");
	printf("\t\t\t\t\t\t \\_,` | \\-'  /   )`-')\n");
	printf("\t\t\t\t\t\t  \"\") `\"`    \\  ((`\"`\n");
	printf("\t\t\t\t\t\t ___Y  ,    .'7 /|\n");
	printf("\t\t\t\t\t\t(_,___/...-` (_/_/\n");
}
void cat() {
	printf("\t\t\t\t\t\t    /\\_____/\\\n");
	printf("\t\t\t\t\t\t   /  o   o  \\\n");
	printf("\t\t\t\t\t\t  ( ==  ^  == )\n");
	printf("\t\t\t\t\t\t   )         (\n");
	printf("\t\t\t\t\t\t  (           )\n");
	printf("\t\t\t\t\t\t ( (  )   (  ) )\n");
	printf("\t\t\t\t\t\t(__(__)___(__)__)\n");
}int i = 0;
int verify_robot() {
	int question;
	int key = 0;
	int answer;
	srand((unsigned)time(NULL));
	question = rand() % 4 + 1;
	int correct = 0;
	char confirmation;
	do {
		system("cls");
		printf("\t\t\t\t----------------------------------------------\n");
		printf("\t\t\t\t|           Verify You Not A Robot           |\n");
		printf("\t\t\t\t----------------------------------------------\n");
		printf("\t\t\t\tSelect Then Press Enter...\n");
		printf("\t\t\t\t(Press 'r' to Reset Question*)\n");
		switch (question) {
		case 1:
			cat();
			break;
		case 2:
			dog();
			break;
		case 3:
			alien();
			break;
		case 4:
			banana();
			break;
		default:
			printf("System Error\n");
			break;
		}
		printf("\n\n\t\t\t\tThe above IMAGE is...\n");
		switch (key) {
		case 1:
			printf("\n\t\t\t\t\t=============       -------------");
			printf("\n\t\t\t\t\t|1. CAT     |         2. DOG  ");
			printf("\n\t\t\t\t\t=============       -------------");
			printf("\n\t\t\t\t\t-------------       -------------");
			printf("\n\t\t\t\t\t 3. ALIEN             4. BANANA");
			printf("\n\t\t\t\t\t-------------       -------------\n\n");
			answer = 1;
			break;
		case 2:
			printf("\n\t\t\t\t\t-------------       =============");
			printf("\n\t\t\t\t\t 1. CAT             | 2. DOG    | ");
			printf("\n\t\t\t\t\t-------------       =============");
			printf("\n\t\t\t\t\t-------------       -------------");
			printf("\n\t\t\t\t\t 3. ALIEN             4. BANANA");
			printf("\n\t\t\t\t\t-------------       -------------\n\n");
			answer = 2;
			break;
		case 3:
			printf("\n\t\t\t\t\t-------------       --------------");
			printf("\n\t\t\t\t\t 1. CAT               2. DOG  ");
			printf("\n\t\t\t\t\t-------------       --------------");
			printf("\n\t\t\t\t\t=============       --------------");
			printf("\n\t\t\t\t\t|3. ALIEN   |         4. BANANA");
			printf("\n\t\t\t\t\t=============       --------------\n\n");
			answer = 3;
			break;
		case 4:
			printf("\n\t\t\t\t\t-------------       --------------");
			printf("\n\t\t\t\t\t 1. CAT               2. DOG  ");
			printf("\n\t\t\t\t\t-------------       --------------");
			printf("\n\t\t\t\t\t-------------       ==============");
			printf("\n\t\t\t\t\t 3. ALIEN           | 4. BANANA  |");
			printf("\n\t\t\t\t\t-------------       ==============\n\n");
			answer = 4;
			break;
		default:
			printf("\n\t\t\t\t\t-------------       --------------");
			printf("\n\t\t\t\t\t 1. CAT               2. DOG  ");
			printf("\n\t\t\t\t\t-------------       --------------");
			printf("\n\t\t\t\t\t-------------       --------------");
			printf("\n\t\t\t\t\t 3. ALIEN             4. BANANA");
			printf("\n\t\t\t\t\t-------------       --------------\n\n");
			answer = 0;
			break;
		}
		key = getch() - 48;
		rewind(stdin);
		if (key == 13 - 48) {
			printf("Are You Sure ? (Y=yes Otherkey=no) : ");
			confirmation = toupper(getchar());
			rewind(stdin);
			if (confirmation == 'Y') {
				if (answer == question) {
					correct = 1;
					printf("Correct !");
					return 1;
				}
				else {
					printf("Aiyoo Bodoh...\n");
					printf("Do you want to continue ? (Y=yes Otherkey=no) : ");
					confirmation = toupper(getchar());
					rewind(stdin);
					if (confirmation != 'Y') {
						return 0;
					}
				}
			}
		}
		else if (key == 114 - 48) {
			srand((unsigned)time(NULL));
			int t = rand() % 4 + 1;
			while (t == question) {
				srand((unsigned)time(NULL));
				t = rand() % 4 + 1;
			}
			question = t;
		}
	} while (correct == 0);
	return 1;
}


void modifyStaffAcc(int c, Staffaccount currentAcc) {

	Staffaccount modify[99];
	char id[40];
	int idExist = 0;
	int index;
	char ch = ' ';
	FILE* fp;
	fp = fopen("staffAccount.bin", "rb");
	fread(&modify, sizeof(Staffaccount), c, fp);
	fclose(fp);
	if (strcmp(currentAcc.staffPosition, "Operations Manager") == 0 || strcmp(currentAcc.staffPosition, "HR Manager") == 0) {
		do {
			system("cls");
			displayAllStaff();
			printf("Enter ID That want to Modify > ");
			scanf("%s", id);
			rewind(stdin);
			for (int i = 0; i < c; i++) {
				if (strcmp(modify[i].staffId, id) == 0) {
					idExist = 1;
					index = i;
					break;
				}
			}
			if (idExist == 0) {
				do {
					printf("\n\aStaff Id no existing (Y=continue N=exit)");
					rewind(stdin);
					ch = toupper(getchar());
					rewind(stdin);
					if (ch != 'Y' && ch != 'N') {
						printf("Invalid Input");
						Sleep(1000);
						system("cls");
						displayAllStaff();
						printf("Enter ID That want to Modify > ");
					}
				} while (ch != 'Y' && ch != 'N');
			}
			if (ch == 'N')
				break;
		} while (idExist == 0);
	}
	else {
		for (int i = 0; i < c; i++) {
			if (strcmp(modify[i].staffId, currentAcc.staffId) == 0) {
				idExist = 1;
				index = i;
				break;
			}
		}
	}

	char select = ' ';
	char name[40];
	int d, m, y;
	char gender;
	int format = 0;
	if (ch != 'N') {
		do {
			system("cls");
			printf("1.Staff ID       > %s\n", modify[index].staffId);
			printf("2.Staff Name     > %s\n", modify[index].staffName);
			printf("3.Staff IC       > %s\n", modify[index].staffIc);
			printf("4.Staff Position > %s\n", modify[index].staffPosition);
			printf("5.Staff Gender   > %c\n", modify[index].staffGender);
			printf("6.Staff Birth    > %02d/%02d/%02d\n", modify[index].birth.day, modify[index].birth.month, modify[index].birth.year);
			printf("7.Staff Address  > %s\n"
				"                 > %s\n"
				"                 > %s\n"
				"                 > %s\n"
				"                 > %s\n", modify[index].staffAddress.houseNo, modify[index].staffAddress.streetNo, modify[index].staffAddress.postCode, modify[index].staffAddress.city, modify[index].staffAddress.state);
			printf("Modify (1-7) X=Exit > ");
			select = toupper(getchar());
			rewind(stdin);
			switch (select) {
			case '1':
				printf("ID > ");
				scanf("%[^\n]", id);
				rewind(stdin);
				if (strlen(id) <= 3 && (int)id[0] >= 65 && (int)id[0] <= 90)
					strcpy(modify[index].staffId, id);
				else {
					printf("Invalid ID can not more than 3 words and the first character must be uppercase alpha\n");
					Sleep(1000);
				}
				break;
			case '2':
				printf("Name > ");
				scanf("%[^\n]", modify[index].staffName);
				rewind(stdin);
				for (int i = 0; i < strlen(modify[index].staffName); i++) {
					modify[index].staffName[i] = toupper(modify[index].staffName[i]);
				}
				break;
			case '3':
				format = 0;
				char tempic[20];
				do {
					system("cls");
					printf("1.Staff ID       > %s\n", modify[index].staffId);
					printf("2.Staff Name     > %s\n", modify[index].staffName);
					printf("3.Staff IC       > %s\n", modify[index].staffIc);
					printf("4.Staff Gender   > %c\n", modify[index].staffGender);
					printf("5.Staff Birth    > %02d/%02d/%02d\n", modify[index].birth.day, modify[index].birth.month, modify[index].birth.year);
					printf("6.Staff Address  > %s\n"
						"                 > %s\n"
						"                 > %d\n"
						"                 > %s\n"
						"                 > %s\n", modify[index].staffAddress.houseNo, modify[index].staffAddress.streetNo, modify[index].staffAddress.postCode, modify[index].staffAddress.city, modify[index].staffAddress.state);
					printf("Modify (1-5) X=Exit > ");
					printf("\nIC Numbers (030306-07-0229): ");
					gets(tempic);
					rewind(stdin);
					if (strlen(tempic) < 14) {
						printf("Invalid");
						Sleep(1000);
						continue;
					}
					if (tempic[6] != '-' && tempic[9] != '-') {
						printf("you forgot \'-\'");
						system("pause");

					}
					int year = (tempic[0] - 48) * 10 + (tempic[1] - 48);
					int month = (tempic[2] - 48) * 10 + (tempic[3] - 48);
					int day = (tempic[4] - 48) * 10 + (tempic[5] - 48);

					if (modify[index].staffGender == 'M' && (tempic[13] - 48) % 2 == 0) {
						printf("Invalid");
						Sleep(1000);

					}
					else if (day == 0 || month == 0 || year == 0) {
						printf("Invalid");
						Sleep(1000);
					}
					else if (modify[index].staffGender == 'F' && (tempic[13] - 48) % 2 != 0) {
						printf("Invalid");
						Sleep(1000);

					}
					else if (month > 12 || day > 31) {
						printf("Invalid");
						Sleep(1000);

					}
					else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
						printf("Invalid");
						Sleep(1000);

					}
					else if (month == 2 && year % 4 == 0 && day > 29) {
						printf("%d", year % 4);
						system("pause");
						printf("Invalid");
						Sleep(1000);

					}
					else if (month == 2 && year % 4 != 0 && day > 28) {
						printf("Invalid");
						Sleep(1000);

					}
					else {
						format = 1;
						modify[index].birth.day = day;
						modify[index].birth.month = month;
						modify[index].birth.year = year;
						strcpy(modify[index].staffIc, tempic);
					}
				} while (format == 0);

				break;
			case '4':
				printf("\t\tSelect Position \n"
					"\t\t  1. Operations Managers\n"
					"\t\t  2. HR Managers\n"
					"\t\t  3. Financial Analysts\n"
					"\t\t  4. IT Support Staff\n"
					"\t\t  5. Opearting Staff\n"
					"\t\t  : ");
				int u;
				scanf("%d", &u);
				rewind(stdin);
				switch (u) {
				case 1:
					strcpy(modify[index].staffPosition, "Operations Manager");
					break;
				case 2:
					strcpy(modify[index].staffPosition, "HR Manager");
					break;
				case 3:
					strcpy(modify[index].staffPosition, "Financial Analysts");
					break;
				case 4:
					strcpy(modify[index].staffPosition, "IT Support Staff");
					break;
				case 5:
					strcpy(modify[index].staffPosition, "Opearting Staff");
					break;
				default:
					printf("Invalid Position\a");
					continue;
				}
				break;
			case '5':

				printf("\nGender >");
				gender = toupper(getchar());
				rewind(stdin);
				if (gender != 'M' && gender != 'F') {
					gender = toupper(getchar());
					rewind(stdin);
					printf("\t\t\t\tInvalid input\a");
					Sleep(1000);
				}
				else
					modify[index].staffGender = gender;

				break;
			case '6':

				printf("\nBirth (DD-MM-YY) > ");
				scanf("%d-%d-%d", &d, &m, &y);
				rewind(stdin);
				if (m > 12 || d > 31) {
					printf("Invalid");
					Sleep(1000);

				}
				else if (d == 0 || m == 0 || y == 0) {
					printf("Invalid");
					Sleep(1000);
				}
				else if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) {
					printf("Invalid");
					Sleep(1000);

				}
				else if (m == 2 && y % 4 == 0 && d > 29) {


					printf("Invalid");
					Sleep(1000);

				}
				else if (m == 2 && y % 4 != 0 && d > 28) {
					printf("Invalid");
					Sleep(1000);

				}
				else {

					modify[index].birth.day = d;
					modify[index].birth.month = m;
					modify[index].birth.year = y;

				}
				break;

			case '7':
				printf("\t\tAddress\n"
					"\t\t  House No : ");
				gets(modify[index].staffAddress.houseNo);
				rewind(stdin);
				for (int i = 0; i < strlen(modify[index].staffAddress.houseNo); i++) {
					modify[index].staffAddress.houseNo[i] = toupper(modify[index].staffAddress.houseNo[i]);
				}
				printf("\t\t  Street : ");
				gets(modify[index].staffAddress.streetNo);
				rewind(stdin);
				for (int i = 0; i < strlen(modify[index].staffAddress.streetNo); i++) {
					modify[index].staffAddress.streetNo[i] = toupper(modify[index].staffAddress.streetNo[i]);
				}
				printf("\t\t  City :");
				gets(modify[index].staffAddress.city);
				rewind(stdin);
				for (int i = 0; i < strlen(modify[index].staffAddress.city); i++) {
					modify[index].staffAddress.city[i] = toupper(modify[index].staffAddress.city[i]);
				}
				printf("\t\t  Post Code : ");
				scanf("%[^\n]", &modify[index].staffAddress.postCode);
				rewind(stdin);
				printf("\t\t  State : ");
				gets(modify[index].staffAddress.state);
				rewind(stdin);
				for (int i = 0; i < strlen(modify[index].staffAddress.state); i++) {
					modify[index].staffAddress.state[i] = toupper(modify[index].staffAddress.state[i]);
				}
				break;
			case 'X':
				break;
			default:
				printf("Invaild");
				Sleep(1000);
				break;
			}
		} while (select != 'X');
		FILE* fp;
		fp = fopen("staffAccount.bin", "wb");
		fwrite(&modify, sizeof(Staffaccount), c, fp);
		fclose(fp);
		FILE* hfp;
		hfp = fopen("history.bin", "ab");
		History h;
		getDateTime(&h.date.day, &h.date.month, &h.date.year, &h.htime.hour, &h.htime.minute, &h.htime.second);
		strcpy(h.staffName, currentAcc.staffName);
		strcpy(h.staffId, currentAcc.staffId);
		sprintf(h.event, "Modify Account--> ID:%s NAME:%s\n",modify[index].staffId,modify[index].staffName);
		fwrite(&h, sizeof(h), 1, hfp);
		fclose(hfp);
	}

}

Staffaccount stafflogin(int c) {
	Staffaccount loginStaff[99];
	char id[40];
	int password[99];
	char tempPsw = ' ';
	int count = 0;
	char enterPsw = ' ';
	int idExist = 0;
	int pswWrong = 1;
	int pswlength1 = 0, pswlength2 = 0;
	int index;
	int ch = ' ';
	//check id if existing or no
	do {
		printf("\t\t\t\t----------------------------------------------\n");
		printf("\t\t\t\t               LOGIN AS STAFF\n");
		printf("\t\t\t\t----------------------------------------------\n");
		printf("\t\t\t\tEnter Staff ID > ");
		scanf("%s", id);
		rewind(stdin);
		FILE* fp;
		fp = fopen("staffAccount.bin", "rb");
		fread(&loginStaff, sizeof(Staffaccount), c, fp);
		fclose(fp);

		for (int i = 0; i < c; i++) {
			if (strcmp(loginStaff[i].staffId, id) == 0) {
				idExist = 1;
				index = i;
				fclose(fp);
			}
		}
		if (idExist == 0) {
			do {
				printf("\n\aStaff Id no existing (Y=continue N=exit)");
				ch = toupper(getchar());
				rewind(stdin);
				if (ch != 'Y' && ch != 'N') {
					printf("Invalid Input");
					Sleep(1000);
					system("cls");
					printf("\t\t\t\t----------------------------------------------\n");
					printf("\t\t\t\t               LOGIN AS STAFF\n");
					printf("\t\t\t\t----------------------------------------------\n");
					printf("\t\t\t\tEnter Staff ID > ");
				}
			} while (ch != 'Y' && ch != 'N');

			system("cls");
		}
		if (ch == 'N')
			break;
	} while (idExist == 0);


	if (ch != 'N') {
		system("cls");
		printf("\t\t\t\t----------------------------------------------\n");
		printf("\t\t\t\t               LOGIN AS STAFF\n");
		printf("\t\t\t\t----------------------------------------------\n");
		printf("\t\t\t\tEnter Staff ID > %s\n", loginStaff[index].staffId);
		printf("\t\t\t\tEnter Password > ");
		do {
			tempPsw = getch();         //get the temporary password/input that user enter
			printf("%c", tempPsw);     //show the temp password/input that user enter
			Sleep(100);			 //but just diplay 0.1s
			if (tempPsw == '\b') {     // '\b'= 'backspace' that user want to delete psw
				if (count > 0) {
					count--;
				}                 //if count equal 0 then no need minus 
				else
					count = 0;
			}
			else if (tempPsw == '\r') {   //'13'and'\r' = enter key , user confirm psw then end the psw loop
				rewind(stdin);
				pswWrong = 0;
				pswlength1 = 0;
				pswlength2 = 0;
				for (int i = 0; i < 99; i++) {
					if (loginStaff[index].staffPassword[i] >= 0 && loginStaff[index].staffPassword[i] <= 127)
						if (loginStaff[index].staffPassword[i] != password[i]) {
							pswWrong = 1;
						}
					if (loginStaff[index].staffPassword[i] != -858993460)
						pswlength1++;
					if (password[i] != -858993460)
						pswlength2++;
				}
				if (pswWrong == 0 && pswlength1 == count) {
					getTime(loginStaff[index].lastLogin);
					FILE* wfp;
					wfp = fopen("staffAccount.bin", "wb");
					fwrite(&loginStaff, sizeof(Staffaccount), c, wfp);
					fclose(wfp);
					//printf("\n\t\t\t\tlogin successful\n");
					//system("pause");

					return loginStaff[index];
				}


				do {
					printf("\n\t\t\t\tInvalid password if you enter again ? (Y=yes N=no)");
					enterPsw = toupper(getch());
					rewind(stdin);
					if (enterPsw != 'Y' && enterPsw != 'N') {
						printf("\nInvalid");
						Sleep(1000);
						system("cls");
						printf("\t\t\t\t----------------------------------------------\n");
						printf("\t\t\t\t               LOGIN AS STAFF\n");
						printf("\t\t\t\t----------------------------------------------\n");
						printf("\t\t\t\tEnter Staff ID > %s\n", id);

						printf("\t\t\t\tEnter Password > ");

						for (int i = 0; i < count; i++) {
							printf("*");
						}
					}

				} while (enterPsw != 'Y' && enterPsw != 'N');
			}
			else {
				password[count] = tempPsw; //record the temp psw
				count++;
			}
			system("cls");
			printf("\t\t\t\t----------------------------------------------\n");
			printf("\t\t\t\t               LOGIN AS STAFF\n");
			printf("\t\t\t\t----------------------------------------------\n");
			printf("\t\t\t\tEnter Staff ID > %s\n", id);

			printf("\t\t\t\tEnter Password > ");

			for (int i = 0; i < count; i++) {
				printf("*");
			}
		} while (enterPsw != 'N');
		//printf("%s", loginStaff[index].staffIc);
	}



	strcpy(id, "0");
	Staffaccount noacc;

	noacc.staffGender = '0';
	return noacc;


}


void deletestaff(int c, Staffaccount currentAcc) {
	Staffaccount update[99];
	char id[4];
	int exist = 0;
	FILE* fp;
	fp = fopen("staffAccount.bin", "rb");
	fread(&update, sizeof(Staffaccount), c, fp);
	do {
		displayAllStaff();
		printf("\nEnter the ID That want to delete (X=exit) > ");
		scanf("%s", id);
		rewind(stdin);
		if (toupper(id[0]) == 'X') {
			return 0;
		}
		for (int i = 0; i < c; i++) {
			if (strcmp(update[i].staffId, id) == 0) {
				exist = 1;
				break;
			}
		}
		if (exist == 0)
			printf("\nNot Found This ID");

	} while (exist == 0);

	if (exist == 1) {
		int index = 0;
		for (int i = 0; i < c; i++) {
			if (strcmp(update[i].staffId, id) == 0) {
				break;
			}
			index++;
		}
		//record history to bin file
		FILE* fp;
		fp = fopen("history.bin", "ab");
		History h;
		getDateTime(&h.date.day, &h.date.month, &h.date.year, &h.htime.hour, &h.htime.minute, &h.htime.second);
		strcpy(h.staffName, currentAcc.staffName);
		strcpy(h.staffId, currentAcc.staffId);
		sprintf(h.event, "Delete Account--> ID:%s NAME:%s POSITION:%s", update[index].staffId, update[index].staffName,update[index].staffPosition);
		fwrite(&h, sizeof(h), 1, fp);
		fclose(fp);
		//


		for (int i = index; i < c - 1; i++) {
			update[i] = update[i + 1];
		}
		fclose(fp);
		FILE* wfp;
		wfp = fopen("staffAccount.bin", "wb");
		fwrite(&update, sizeof(Staffaccount), c - 1, wfp);
		fclose(wfp);
		printf("\n\tThe Staff Account Already Delete !\n");

		system("pause");
	}
}


int countstaff(int countstaff, Staffaccount staff) {
	FILE* rfp;
	rfp = fopen("staffAccount.bin", "rb");
	if (rfp == NULL) {
		printf("File no exist");
		exit(-1);
	}
	while (fread(&staff, sizeof(Staffaccount), 1, rfp) != 0) {

		countstaff++;

	}
	fclose(rfp);
	return countstaff;
}

/*old
void displayAllStaff() {
	system("cls");
	Staffaccount staff;
	FILE* rfp;
	rfp = fopen("staffAccount.bin", "rb");
	if (rfp == NULL) {
		printf("File no exist");
		exit(-1);
	}
	int i = 1;
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" NO STAFF ID         NAME        GENDER   POSITION                     IC          JOIN DATE & LAST LOGIN \n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	while (fread(&staff, sizeof(Staffaccount), 1, rfp) != 0) {

		printf(" %d. %5s \t %-19s%c \t  %-19s %-15s   %s\t\t\t\t\t\t\t\t\t\t/%s", i, staff.staffId, staff.staffName, staff.staffGender, staff.staffPosition, staff.staffIc, staff.joinDate, staff.lastLogin);

		//printf("\n%02d/%02d/%02d\n", staff.birth.day, staff.birth.month, staff.birth.year);
		printf("\n");
		i++;
	}
	fclose(rfp);

}*/
void displayAllStaff() {
	system("cls");
	Staffaccount staff[99];
	int count = 0;
	FILE* rfp;
	rfp = fopen("staffAccount.bin", "rb");
	if (rfp == NULL) {
		printf("File no exist");
		exit(-1);
	}
	while (fread(&staff[count], sizeof(Staffaccount), 1, rfp) != 0) {
		count++;
	}
	fclose(rfp);
	
	Staffaccount temp;
	strcmp(temp.staffId, " ");
	do {
		int idExist = 0;
		system("cls");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" NO STAFF ID         NAME        GENDER   POSITION                     IC          JOIN DATE & LAST LOGIN \n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < count; i++) {
			printf(" %d. %5s \t %-19s%c \t  %-19s %-15s   %s\t\t\t\t\t\t\t\t\t\t/%s\n", i + 1, staff[i].staffId, staff[i].staffName, staff[i].staffGender, staff[i].staffPosition, staff[i].staffIc, staff[i].joinDate, staff[i].lastLogin);
		}
		printf("\nEnter ID To View Detail (N to Exit/Continue) : ");
		scanf("%[^\n]", temp.staffId);
		rewind(stdin);
		temp.staffId[0] = toupper(temp.staffId[0]);
		for (int i = 0; i < count; i++) {
			if (strcmp(staff[i].staffId, temp.staffId) == 0) {
				idExist = 1;
				printf("1.Staff ID       > %s\n", staff[i].staffId);
				printf("2.Staff Name     > %s\n", staff[i].staffName);
				printf("3.Staff IC       > %s\n", staff[i].staffIc);
				printf("4.Staff Position > %s\n", staff[i].staffPosition);
				printf("5.Staff Gender   > %c\n", staff[i].staffGender);
				printf("6.Staff Birth    > %02d/%02d/%02d\n", staff[i].birth.day, staff[i].birth.month, staff[i].birth.year);
				printf("7.Staff Address  > %s\n"
					"                 > %s\n"
					"                 > %s\n"
					"                 > %s\n"
					"                 > %s\n", staff[i].staffAddress.houseNo, staff[i].staffAddress.streetNo, staff[i].staffAddress.postCode, staff[i].staffAddress.city, staff[i].staffAddress.state);
				system("pause");
				break;
			}
		}
		if (!idExist && temp.staffId[0]!='N') {
			printf("ID no Exist !\a\n");
			Sleep(1000);
		}
		
	} while (strcmp(temp.staffId, "N") != 0);
	rewind(stdin);

}





void registerNewStaff(int staffCount, Staffaccount currentAcc) {
	void exit(char);
	typedef struct {
		char id[4];
		char name[31];
		char gender;
		char ic[20];
		int password[99];
		char Position[26];
		Address address;
		char joinDate[31];
		char lastLogin[31];
		Date birth;
	}Newstaff;

	Newstaff nStaff;
	getTime(nStaff.joinDate);
	strcpy(nStaff.id, "A00");
	srand((unsigned)time(NULL));
	int random = rand() % 100;
	nStaff.id[1] = nStaff.id[1] + random / 10;
	nStaff.id[2] = nStaff.id[2] + random % 10;

	Staffaccount t[99];
	int exist = 0;
	FILE* fpt;
	fpt = fopen("staffAccount.bin", "rb");
	fread(&t, sizeof(Staffaccount), staffCount, fpt);

	rewind(stdin);
	strcpy(nStaff.Position, "");
	strcpy(nStaff.name, "");
	strcpy(nStaff.lastLogin, "-");
	nStaff.gender = " ";
	int icFormat = 0;
	int select = 0;
	int addressinfo = 0;
	int count = 0, count2 = 0;
	int pswinfo = 0, cpswinfo = 0;
	char tempPsw;
	char confirmInfo = " ";
	do {
		system("cls");
		printf("\t\t\t\t    --------------------------------\n");
		printf("        \t\t\t\tREGISTER NEW STAFF ACCOUNT   \n");
		printf("\t\t\t\t    --------------------------------\n");
		printf("-----------------------------------------------------------------------------------------------------------------\n");
		//printf("\n\n\t\tNew Staff ID            : %s", nStaff.id);
		printf("\n\n\t\tNew Staff Name             : ");
		(strlen(nStaff.name) == 0 ? scanf("%[^\n]", nStaff.name) : printf("%s\n", nStaff.name));
		rewind(stdin);
		for (int i = 0; i < strlen(nStaff.name); i++) {
			nStaff.name[i] = toupper(nStaff.name[i]);
		}
		printf("\t\tGender                     : ");
		if (nStaff.gender != 'M' && nStaff.gender != 'F') {
			nStaff.gender = toupper(getchar());
			rewind(stdin);
			if (nStaff.gender != 'M' && nStaff.gender != 'F') {
				printf("\t\t\t\tInvalid input\a");
				Sleep(1000);
				continue;
			}
		}
		else
			printf("%c\n", nStaff.gender);

		if (icFormat == 0) {
			printf("\t\tIC Numbers (030306-07-0229): ");
			gets(nStaff.ic);
			rewind(stdin);
			if (nStaff.ic[6] != '-' && nStaff.ic[9] != '-') {
				printf("you forgot/Invalid format \'-\'");
				system("pause");
				continue;
			}
			int year = (nStaff.ic[0] - 48) * 10 + (nStaff.ic[1] - 48);
			int month = (nStaff.ic[2] - 48) * 10 + (nStaff.ic[3] - 48);
			int day = (nStaff.ic[4] - 48) * 10 + (nStaff.ic[5] - 48);
			nStaff.birth.day = day;
			nStaff.birth.month = month;
			nStaff.birth.year = year;
			if (nStaff.gender == 'M' && (nStaff.ic[13] - 48) % 2 == 0) {
				printf("Invalid");
				Sleep(1000);
				continue;
			}
			else if (day == 0 || month == 0 || year == 0) {
				printf("Invalid");
				Sleep(1000);
				continue;
			}
			else if (nStaff.gender == 'F' && (nStaff.ic[13] - 48) % 2 != 0) {
				printf("Invalid");
				Sleep(1000);
				continue;
			}
			else if (month > 12 || day > 31) {
				printf("Invalid");
				Sleep(1000);
				continue;
			}
			else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
				printf("Invalid");
				Sleep(1000);
				continue;
			}
			else if (month == 2 && year % 4 == 0 && day > 29) {
				printf("%d", year % 4);
				system("pause");
				printf("Invalid");
				Sleep(1000);
				continue;;
			}
			else if (month == 2 && year % 4 != 0 && day > 28) {
				printf("Invalid");
				Sleep(1000);
				continue;
			}
		}
		else {
			printf("\t\tIC Numbers (030306-07-0229): %s\n", nStaff.ic);

		}
		icFormat = 1;

		printf("\t\tSelect Position \n"
			"\t\t  1. Operations Manager\n"
			"\t\t  2. HR Manager\n"
			"\t\t  3. Financial Analysts\n"
			"\t\t  4. IT Support Staff\n"
			"\t\t  5. Opearting Staff\n"
			"\t\t  : ");

		if (strlen(nStaff.Position) == 0) {
			scanf("%d", &select);
			rewind(stdin);
			switch (select) {
			case 1:

				if (check_Position_Existing("Operations Manager")) {
					printf("Operations Manager Already Existing");
					Sleep(1000);
					continue;
				}
				strcpy(nStaff.Position, "Operations Manager");
				nStaff.id[0] = 'O';
				break;
			case 2:
				if (check_Position_Existing("HR Manager")) {
					printf("HR Manager Already Existing");
					Sleep(1000);
					continue;
				}
				strcpy(nStaff.Position, "HR Manager");
				nStaff.id[0] = 'H';
				break;
			case 3:
				strcpy(nStaff.Position, "Financial Analysts");
				nStaff.id[0] = 'F';
				break;
			case 4:
				strcpy(nStaff.Position, "IT Support Staff");
				nStaff.id[0] = 'I';
				break;
			case 5:
				strcpy(nStaff.Position, "Opearting Staff");
				nStaff.id[0] = 'S';
				break;
			default:
				printf("Invalid Position\a");
				continue;
			}
		}
		else
			printf("%d\n", select);

		int indexP = 0;
		for (int i = 0; i < staffCount; i++) {
			if (strcmp(t[i].staffPosition, nStaff.Position) == 0) {
				indexP = i;
			}
		}



		if (t[indexP].staffId[2] == '9' && t[indexP].staffId[1] == '9') {
			nStaff.id[2] == '0';
			nStaff.id[1] == '0';
			nStaff.id[0] = t[indexP].staffId[0] + 1;
		}
		else if (t[staffCount - 1].staffId[2] != '9') {
			nStaff.id[1] = t[indexP].staffId[1];
			nStaff.id[2] = t[indexP].staffId[2] + 1;
		}
		else {
			nStaff.id[1] = t[indexP].staffId[1] + 1;
			nStaff.id[2] = '0';
		}
		if (indexP == 0) {
			nStaff.id[1] = '0';
			nStaff.id[2] = '1';
		}
		printf("\t\tStaff ID         : %s\n", nStaff.id);

		if (addressinfo == 0) {
			printf("\t\tAddress\n"
				"\t\t  House No : ");
			gets(nStaff.address.houseNo);
			rewind(stdin);
			for (int i = 0; i < strlen(nStaff.address.houseNo); i++) {
				nStaff.address.houseNo[i] = toupper(nStaff.address.houseNo[i]);
			}
			printf("\t\t  Street : ");
			gets(nStaff.address.streetNo);
			rewind(stdin);
			for (int i = 0; i < strlen(nStaff.address.streetNo); i++) {
				nStaff.address.streetNo[i] = toupper(nStaff.address.streetNo[i]);
			}
			printf("\t\t  City :");
			gets(nStaff.address.city);
			rewind(stdin);
			for (int i = 0; i < strlen(nStaff.address.city); i++) {
				nStaff.address.city[i] = toupper(nStaff.address.city[i]);
			}
			printf("\t\t  Post Code : ");
			scanf("%[^\n]", &nStaff.address.postCode);
			rewind(stdin);
			printf("\t\t  State : ");
			gets(nStaff.address.state);
			rewind(stdin);
			for (int i = 0; i < strlen(nStaff.address.state); i++) {
				nStaff.address.state[i] = toupper(nStaff.address.state[i]);
			}
			addressinfo = 1;
		}
		else {
			printf("\t\tAddress\n"
				"\t\t  House No : %s\n", nStaff.address.houseNo);
			printf("\t\t  Street : %s\n", nStaff.address.streetNo);
			printf("\t\t  City : %s\n", nStaff.address.city);
			printf("\t\t  Post Code : %s\n", nStaff.address.postCode);
			printf("\t\t  State : %s\n", nStaff.address.state);
		}

		printf("Do you confirm create a new staff acount ? (Y=Yes N=no) : ");
		confirmInfo = toupper(getchar());
		if (confirmInfo != 'Y' && confirmInfo != 'N') {
			printf("Invalid\a");
			Sleep(1000);
			continue;
		}

	} while (confirmInfo != 'Y' && confirmInfo != 'N');

	//set password
	if (confirmInfo == 'Y') {

		system("cls");
		do {
			char upper = 'X', lower = 'X', digit = 'X', special = 'X', minCha = 'X';
			char strength[9] = "Low";
			system("cls");
			for (int i = 0; i < count; i++) {
				if (nStaff.password[i] >= 48 && nStaff.password[i] <= 57) {
					digit = 'O';
				}
				else if (nStaff.password[i] >= 65 && nStaff.password[i] <= 90) {
					upper = 'O';
				}
				else if (nStaff.password[i] >= 97 && nStaff.password[i] <= 122) {
					lower = 'O';
				}
				else
					special = 'O';

			}
			if (count >= 12)
				minCha = 'O';

			if (digit == 'O' && upper == 'O' && lower == 'O' && special == 'O' && count >= 12)
				strcpy(strength, "Great");
			else if (digit == 'O' && upper == 'O' && lower == 'O' && minCha >= 8)
				strcpy(strength, "Normal");
			else if (special == 'O' && minCha >= 12 && minCha >= 8)
				strcpy(strength, "Normal");
			else
				strcpy(strength, "Low");
			printf("\n\n\t\t\t=====================================================================\n");
			printf("\t\t\tUpper Case : %c    Lower Case \t       : %c    Special Symbol : %c\n\t\t\tDigit      : %c    Minimum 12 character : %c    strength       : %s", upper, lower, special, digit, minCha, strength);
			printf("\n\n\t\t\t=====================================================================\n");
			printf("\t\t\t\tPassword          : ");
			for (int i = 0; i < count; i++) {
				printf("*");
			}


			tempPsw = getch();         //get the temporary password/input that user enter
			printf("%c", tempPsw);     //show the temp password/input that user enter
			Sleep(100);			 //but just diplay 0.1s

			if (tempPsw == '\b') {     // '\b'= 'backspace' that user want to delete psw
				if (count > 0) {
					count--;
				}                 //if count equal 0 then no need minus 
				else
					count = 0;
			}
			else if (tempPsw == '\r') {   //'13'and'\r' = enter key , user confirm psw then end the psw loop
				if (digit == 'O' && upper == 'O' && lower == 'O' && special == 'O' && count >= 12) {
					pswinfo = 1;
					rewind(stdin);
				}
				else {
					printf("\n\t\tYour Password Too Weak\a");
					Sleep(1000);
					continue;
				}
			}
			else {
				nStaff.password[count] = tempPsw; //record the temp psw
				count++;
			}



		} while (pswinfo != 1);
		int match = 0;
		char confirm = ' ';
		do {
			match = confirmPassword(nStaff.password, count);
			if (match) {
				printf("\nDo you ensure this password ? (Y=Yes N=No) : ");
				confirm = toupper(getchar());
				if (confirm == 'Y') {
					FILE* wfp;

					wfp = fopen("staffAccount.bin", "ab");
					if (wfp == NULL) {
						printf("File no exist");
						exit(-1);
					}
					fwrite(&nStaff, sizeof(Newstaff), 1, wfp);
					fclose(wfp);
					printf("New Account Already Recorded !\n");
					//record history to bin file
					FILE* hfp;
					hfp = fopen("history.bin", "ab");
					History h;
					getDateTime(&h.date.day, &h.date.month, &h.date.year, &h.htime.hour, &h.htime.minute, &h.htime.second);
					strcpy(h.staffName, currentAcc.staffName);
					strcpy(h.staffId, currentAcc.staffId);
					sprintf(h.event, "Register New Account--> ID:%s NAME:%s POSITION:%s",nStaff.id,nStaff.name,nStaff.Position);
					fwrite(&h, sizeof(h), 1, hfp);
					fclose(hfp);
				}
				if (confirm != 'Y' && confirm != 'N') {
					printf("\n\nInvalid");

				}
			}
		} while (confirm != 'Y' && confirm != 'N');
	}
	system("pause");
	rewind(stdin);
}

int visitbility = 0;
int confirmPassword(int passwords[99], int count) {
	int i = 0;
	int confirmPsw[99];
	char tempPsw;
	int count2 = 0;
	system("cls");
	int match[99];
	int correct = 0;

	do {
		printf("\n\n\t\t\t=====================================================================\n");
		printf("\t\t\tUpper Case : %c    Lower Case \t       : %c    Special Symbol : %c\n\t\t\tDigit      : %c    Minimum 12 character : %c    strength       : %s", 'O', 'O', 'O', 'O', 'O', "Great");
		printf("\n\n\t\t\t=====================================================================\n");
		printf("\t\t\t\tPassword          : ");
		if (visitbility == 0) {
			for (i = 0; i < count; i++) {
				printf("*");
			}
		}
		else {
			for (i = 0; i < count; i++) {
				printf("%c", passwords[i]);
			}
		}
		printf("\n\t\t\t\tConfirm Passwords : ");
		for (i = 0; i < count2; i++) {
			printf("*");
		}
		tempPsw = getch();         //get the temporary password/input that user enter
		printf("%c", tempPsw);     //show the temp password/input that user enter
		Sleep(100);			 //but just diplay 0.1s

		if (tempPsw == '\b') {     // '\b'= 'backspace' that user want to delete psw
			if (count2 > 0) {
				count2--;
			}                 //if count equal 0 then no need minus 
			else
				count2 = 0;
		}
		else if (tempPsw == '\r') {   //'13'and'\r' = enter key , user confirm psw then end the psw loop
			visitbility = 0;
			for (int i = 0; i < count; i++) {
				if (confirmPsw[i] != passwords[i]) {
					printf("\n\t\t\t\t\a    Password Not Match !\n\t\t\t\t      Do you want to exit?(Y=Continue F=See Passwords X=Exit)");
					char ch;
					rewind(stdin);
					ch = toupper(getchar());
					rewind(stdin);
					if (ch == 'Y') {
						correct = 0;
						break;
					}
					else if (ch == 'F') {
						correct = 0;
						visitbility = 1;
						break;
					}
					
					visitbility = 0;
					Sleep(1000);
					return 0;
				}
				correct = 1;
			}
			//correct = 1;
		}
		else {
			confirmPsw[count2] = tempPsw; //record the temp psw
			count2++;
		}
		if (correct == 0)
			system("cls");
	} while (correct != 1);
	return 1;
}

void getTime(char timevalue[30]) {
	time_t t;
	time(&t);
	strcpy(timevalue, ctime(&t));
}
void getDateTime(int *day,int *month,int *year,int *hour,int *min,int *second) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	*day = t.wDay;
	*month = t.wMonth;
	*year = t.wYear;
	*hour = t.wHour;
	*min = t.wMinute;
	*second = t.wSecond;
}

void resetPassword(Staffaccount currentAcc) {
	Staffaccount readAcc[99];
	FILE* rfp;
	rfp = fopen("staffAccount.bin", "rb");
	int index = 0;
	int staffcount = 0;
	while (fread(&readAcc[staffcount], sizeof(Staffaccount), 1, rfp)!=0) {
		if (strcmp(readAcc[staffcount].staffId, currentAcc.staffId) == 0) {
			index = staffcount;
		}
		staffcount++;
	}
	
	
	int count = 0, count2 = 0;
	int pswinfo = 0, cpswinfo = 0;
	char tempPsw;
	Staffaccount tempAcc;
	do {
		char upper = 'X', lower = 'X', digit = 'X', special = 'X', minCha = 'X';
		char strength[9] = "Low";
		system("cls");
		for (int i = 0; i < count; i++) {
			if (tempAcc.staffPassword[i] >= 48 && tempAcc.staffPassword[i] <= 57) {
				digit = 'O';
			}
			else if (tempAcc.staffPassword[i] >= 65 && tempAcc.staffPassword[i] <= 90) {
				upper = 'O';
			}
			else if (tempAcc.staffPassword[i] >= 97 && tempAcc.staffPassword[i] <= 122) {
				lower = 'O';
			}
			else
				special = 'O';

		}
		if (count >= 12)
			minCha = 'O';

		if (digit == 'O' && upper == 'O' && lower == 'O' && special == 'O' && count >= 12)
			strcpy(strength, "Great");
		else if (digit == 'O' && upper == 'O' && lower == 'O' && minCha >= 8)
			strcpy(strength, "Normal");
		else if (special == 'O' && minCha >= 12 && minCha >= 8)
			strcpy(strength, "Normal");
		else
			strcpy(strength, "Low");
		printf("\n\n\t\t\t=====================================================================\n");
		printf("\t\t\tUpper Case : %c    Lower Case \t       : %c    Special Symbol : %c\n\t\t\tDigit      : %c    Minimum 12 character : %c    strength       : %s", upper, lower, special, digit, minCha, strength);
		printf("\n\n\t\t\t=====================================================================\n");
		printf("\t\t\t\tPassword          : ");
		for (int i = 0; i < count; i++) {
			printf("*");
		}


		tempPsw = getch();         //get the temporary password/input that user enter
		printf("%c", tempPsw);     //show the temp password/input that user enter
		Sleep(100);			 //but just diplay 0.1s

		if (tempPsw == '\b') {     // '\b'= 'backspace' that user want to delete psw
			if (count > 0) {
				count--;
			}                 //if count equal 0 then no need minus 
			else
				count = 0;
		}
		else if (tempPsw == '\r') {   //'13'and'\r' = enter key , user confirm psw then end the psw loop
			if (digit == 'O' && upper == 'O' && lower == 'O' && special == 'O' && count >= 12) {
				
				pswinfo = 1;
				rewind(stdin);
			}
			else {
				printf("\n\t\tYour Password Too Weak\a");
				Sleep(1000);
				continue;
			}
		}
		else {
			tempAcc.staffPassword[count] = tempPsw; //record the temp psw
			count++;
		}



	} while (pswinfo != 1);
	int match = 0;
	char confirm = ' ';
	do {
		match = confirmPassword(tempAcc.staffPassword, count);
		if (match) {
			printf("\nDo you ensure this password ? (Y=Yes N=No) : ");
			confirm = toupper(getchar());
			if (confirm == 'Y') {
				FILE* wfp;
				for (int i = 0; i < count; i++) {
					readAcc[index].staffPassword[i] = tempAcc.staffPassword[i];
				}
				wfp = fopen("staffAccount.bin", "wb");
				if (wfp == NULL) {
					printf("File no exist");
					exit(-1);
				}
				fwrite(&readAcc, sizeof(Staffaccount), staffcount, wfp);
				fclose(wfp);
				printf("New Password Already Recorded !\n");
				//record history to bin file
				FILE* hfp;
				hfp = fopen("history.bin", "ab");
				History h;
				getDateTime(&h.date.day, &h.date.month, &h.date.year, &h.htime.hour, &h.htime.minute, &h.htime.second);
				strcpy(h.staffName, currentAcc.staffName);
				strcpy(h.staffId, currentAcc.staffId);
				sprintf(h.event, "Reset Password");
				fwrite(&h, sizeof(h), 1, hfp);
				fclose(hfp);
			}
			if (confirm != 'Y' && confirm != 'N') {
				printf("\n\nInvalid");

			}
		}
	} while (confirm != 'Y' && confirm != 'N');
	system("pause");
    rewind(stdin);
	
}

void displayHeader() {
	printf("\t\t\t\t\t _______   ________      ___    __ \n");
	printf("\t\t\t\t\t|\\  ___ \\ |\\_____  \\    |\\  \\  / /|\n");
	printf("\t\t\t\t\t\\ \\   __/\\|\\|___/  /|   \\ \\  \\/ / /\n");
	printf("\t\t\t\t\t \\ \\  \\_|/__   /  / /    \\ \\   / / \n");
	printf("\t\t\t\t\t  \\ \\  \\_|\\ \\ /  /_/__    \\/  / /  \n");
	printf("\t\t\t\t\t   \\ \\_______\\\\________\\__/  / /   \n");
	printf("\t\t\t\t\t    \\|_______|\\|_______|\\___/ /    \n");
	printf("\t\t\t\t\t                       \\|___|/     \n");


	printf("\t\t      =================================================================\n");
	printf("\t\t                         WELCOME TO EasyBuy MLM SYSTEM                    \n");
	printf("\t\t                                                                       \n");
	printf("\t\t                                                                       \n");
	printf("\t\t      ========================  MLM  SYSTEM  ==========================\n");
	printf("\t\t      |                                                               |\n");
	printf("\t\t      |                          HOME PAGE                            |\n");
	printf("\t\t      |                                                               |\n");
	printf("\t\t      =================================================================\n\t");
	countNotice();
	printf("\t===============================================================================================\n");
	printf("  \n");
	
}
void displayStaffHeader() {
	printf("\t\t\t\t\t _______   ________      ___    __ \n");
	printf("\t\t\t\t\t|\\  ___ \\ |\\_____  \\    |\\  \\  / /|\n");
	printf("\t\t\t\t\t\\ \\   __/\\|\\|___/  /|   \\ \\  \\/ / /\n");
	printf("\t\t\t\t\t \\ \\  \\_|/__   /  / /    \\ \\   / / \n");
	printf("\t\t\t\t\t  \\ \\  \\_|\\ \\ /  /_/__    \\/  / /  \n");
	printf("\t\t\t\t\t   \\ \\_______\\\\________\\__/  / /   \n");
	printf("\t\t\t\t\t    \\|_______|\\|_______|\\___/ /    \n");
	printf("\t\t\t\t\t                       \\|___|/     \n");


	printf("\t\t      =================================================================\n");
	printf("\t\t                         WELCOME TO EasyBuy MLM SYSTEM                    \n");
	printf("\t\t                                                                       \n");
	printf("\t\t                                                                       \n");
	printf("\t\t      ========================  MLM  SYSTEM  ==========================\n");
	printf("\t\t      |                                                               |\n");
	printf("\t\t      |                          ADMIN PAGE                           |\n");
	printf("\t\t      |                                                               |\n");
	printf("\t\t      =================================================================\n\t");
	countNotice();
	printf("\t===============================================================================================\n");
	printf("  \n");

}


