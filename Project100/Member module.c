#include "MLM.h";

void memberModule() {
	system("mode con cols=120");
	sysColor();  // First letter set the background, second letter set the foreground

	struct Member read;
	int option2, product_status, stock_status = 0, exit_status = 0;
	int option_status = 1;
	char choice, back;
	char username[100], option[20], acc[50];
	double commission, total = 0;

	strcpy(username, "0");
	do {
		printf("Select the option:\n");
		printf("0. Exit program\n");
		printf("1. Sign up\n");
		printf("2. Login\n");
		printf("3. Forget password\n\n");
		printf("Enter your option: ");
		scanf("%[^\n]", &option);
		rewind(stdin);

		if (strcmp(option, "0") == 0) {
			break;
		}
		else if (strcmp(option, "1") == 0) {
			system("cls");
			exit_status = signup();
		}
		else if (strcmp(option, "2") == 0) {
			system("cls");
			strcpy(username, login());
			Sleep(1500);
			system("cls");
			if (strcmp(username, "1") != 0) {
				do {
					printf("Select the options:\n");
					printf("0. Log out\n");
					printf("1. View profile\n");
					printf("2. View product\n");
					printf("3. View cart");

					FILE* fptr;
					fptr = fopen("member.txt", "r");

					if (fptr == NULL) {
						printf("Error opening file.\n");
						exit(-1);
					}

					while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &read.member_ID, &read.username, &read.gender, &read.IC, &read.email, &read.add.houseNo, &read.add.streetNo, &read.add.postCode, &read.add.city, &read.add.state, &read.upline, &read.encrypted_password, &read.question, &read.answer, &read.account_available, &read.time.sec) != EOF) {
						if (strcmp(username, read.username) == 0) {
							if (strcmp(read.upline, "N/A") == 0) {
								printf("\n4. View stock");
								printf("\n5. View account balance");
								stock_status = 1;
							}
						}
					}

					fclose(fptr);

					printf("\n\nEnter your selection: ");
					scanf("%d", &option2);
					rewind(stdin);

					if (option2 == 0) {
						system("cls");
						exit_status = 1;
						break;
					}
					else if (option2 == 1) {
						system("cls");
						product_status = view_profile(username);
						system("cls");
					}
					else if (option2 == 2) {
						system("cls");
						product_status = view_product(username);
						system("cls");
					}
					else if (option2 == 3) {
						system("cls");
						FILE* fptr;

						fptr = fopen("member.txt", "r");
						if (fptr == NULL) {
							printf("Error opening file.\n");
							exit(-1);
						}

						while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &read.member_ID, &read.username, &read.gender, &read.IC, &read.email, &read.add.houseNo, &read.add.streetNo, &read.add.postCode, &read.add.city, &read.add.state, &read.upline, &read.encrypted_password, &read.question, &read.answer, &read.account_available, &read.time.sec) != EOF) {
							if (strcmp(username, read.username) == 0) {
								product_status = salesModule(read.member_ID);
							}
						}

						fclose(fptr);
						system("cls");
					}
					else if (option2 == 4) {
						if (stock_status == 1) {
							system("cls");
							product_status = view_stock(username);
							system("cls");
						}
						else {
							red();
							printf("\nError message: Invalid input.");
							Sleep(1500);
							system("cls");
							sysColor();
							product_status = 1;
						}
					}
					else if (option2 == 5) {
						if (stock_status == 1) {
							system("cls");

							sprintf(acc, "Account %s.txt", username);

							FILE* account;
							account = fopen(acc, "r");

							if (account == NULL) {
								printf("account can't open!\n");
								exit(-1);
							}

							while (fscanf(account, "%lf", &commission) != EOF) {
								total += commission;
							}

							printf("Account Balance\n");
							printf("=======================================================\n");
							printf("RM %.2f\n\n", total);
							printf("Press any key to back...");
							back = getch();
							if (back) {
								product_status = 1;
							}

							fclose(account);
							system("cls");
						}
						else {
							red();
							printf("\nError message: Invalid input.");
							Sleep(1500);
							system("cls");
							sysColor();
							product_status = 1;
						}
					}
					else {
						red();
						printf("\nError message: Invalid input.");
						Sleep(1500);
						system("cls");
						sysColor();
						product_status = 1;
					}
				} while (product_status == 1);
			}
		}
		else if (strcmp(option, "3") == 0) {
			system("cls");
			exit_status = forget_password();
			system("cls");
		}
		else {
			red();
			printf("\nError message: Invalid input.");
			Sleep(1500);
			system("cls");
			sysColor();
			option_status = 0;
		}
	} while (option_status == 0 || exit_status == 1 || strcmp(username, "1") == 0);
}

int signup() {
	struct Member info;
	struct Member login[100];
	struct Member read;
	bool username_found = false;
	bool exit_signup = false;
	int exit_status = 0, gender_status, ic_status, email_status, address_status = 1, password_status, confirmPsd_status;
	int num_account = 0, x = 0, y = 1, z = 0, m = 1, upline_count[5], upline_selection;
	char temp_name[100];

	// Username Validation
	do {
		printf("Sign Up\n\n");
		printf("User Name (X - Back): ");
		scanf("%[^\n]", info.username);

		for (int i = 0; i < strlen(info.username); i++) {
			temp_name[i] = toupper(info.username[i]);
		}
		temp_name[strlen(info.username)] = '\0';

		if (strcmp(temp_name, "X") == 0) {
			exit_status = 1;
		}
		else {
			exit_status = 0;
			username_found = username_validation(info);
		}
		rewind(stdin);
	} while (username_found == true);

	system("cls");

	if (exit_status == 0) {
		// Gender Validation
		do {
			printf("Sign Up\n\n");
			printf("User Name (X - Back): %s\n\n", info.username);
			printf("Gender (M / F): ");
			scanf("%s", &info.gender);
			gender_status = gender_validation(info);
			rewind(stdin);
		} while (gender_status == 0);

		for (int i = 0; i < strlen(info.gender); i++) {
			info.gender[i] = toupper(info.gender[i]);
		}
		if (strcmp(info.gender, "MALE") == 0) {
			info.gender[0] = 'M';
			info.gender[1] = '\0';
		}
		else if (strcmp(info.gender, "FEMALE") == 0) {
			info.gender[0] = 'F';
			info.gender[1] = '\0';
		}

		system("cls");

		// IC Number Validation
		do {
			printf("Sign Up\n\n");
			printf("User Name (X - Back): %s\n\n", info.username);
			printf("Gender (M / F): %s\n\n", info.gender);
			printf("IC Number: ");
			scanf("%[^\n]", info.IC);
			ic_status = icnum_validation(info);
			rewind(stdin);
		} while (ic_status == 0);

		system("cls");

		// Email Validation
		do {
			printf("Sign Up\n\n");
			printf("User Name (X - Back): %s\n\n", info.username);
			printf("Gender (M / F): %s\n\n", info.gender);
			printf("IC Number: %s\n\n", info.IC);
			printf("Email: ");
			scanf("%[^\n]", info.email);
			email_status = email_validation(info);
			rewind(stdin);
		} while (email_status == 0);

		system("cls");

		// Address Validation
		do {
			printf("Sign Up\n\n");
			printf("User Name (X - Back): %s\n\n", info.username);
			printf("Gender (M / F): %s\n\n", info.gender);
			printf("IC Number: %s\n\n", info.IC);
			printf("Email: %s\n\n", info.email);
			printf("Current Address: ");
			if (scanf("%[^,\n], %[^,\n], %[^ \n] %[^,\n], %[^\n]", &info.add.houseNo, &info.add.streetNo, &info.add.postCode, &info.add.city, &info.add.state) != 5) {  // %[^,\n] -> 读取所有逗号和换行符之外的字符
				address_status = 0;
				red();
				printf("\nError message: The address format is invalid.");
				Sleep(1500);
				sysColor();
				system("cls");
			}
			else {
				// Postcode Validation
				if (strlen(info.add.postCode) != 5 || !isdigit(info.add.postCode[0]) || !isdigit(info.add.postCode[1]) || !isdigit(info.add.postCode[2]) || !isdigit(info.add.postCode[3]) || !isdigit(info.add.postCode[4])) {
					address_status = 0;
					red();
					printf("\nError message: The postcode in invalid.");
					Sleep(1500);
					sysColor();
					system("cls");
				}
				else {
					address_status = 1;
				}

				// State Validation
				if (address_status == 1) {
					// Change the address to uppercase
					for (int x = 0; x < strlen(info.add.houseNo); x++) {
						info.add.houseNo[x] = toupper(info.add.houseNo[x]);
					}
					for (int x = 0; x < strlen(info.add.streetNo); x++) {
						info.add.streetNo[x] = toupper(info.add.streetNo[x]);
					}
					for (int x = 0; x < strlen(info.add.city); x++) {
						info.add.city[x] = toupper(info.add.city[x]);
					}
					for (int x = 0; x < strlen(info.add.state); x++) {
						info.add.state[x] = toupper(info.add.state[x]);
					}

					if (strcmp(info.add.state, "PERLIS") != 0 && strcmp(info.add.state, "PULAU PINANG") != 0 && strcmp(info.add.state, "KEDAH") != 0 && strcmp(info.add.state, "KELANTAN") != 0 &&
						strcmp(info.add.state, "PERAK") != 0 && strcmp(info.add.state, "PAHANG") != 0 && strcmp(info.add.state, "TERENGGANU") != 0 && strcmp(info.add.state, "SELANGOR") != 0 &&
						strcmp(info.add.state, "NEGERI SEMBILAN") != 0 && strcmp(info.add.state, "MELAKA") != 0 && strcmp(info.add.state, "JOHOR") != 0 && strcmp(info.add.state, "SABAH") != 0 && strcmp(info.add.state, "SARAWAK") != 0) {

						address_status = 0;
						red();
						printf("\nError message: The state in invalid.");
						Sleep(1500);
						sysColor();
						system("cls");
					}
					else {
						address_status = 1;
					}
				}
			}
			rewind(stdin);
		} while (address_status == 0);

		system("cls");

		// Upline
		FILE* fptr;
		fptr = fopen("member.txt", "r");

		if (fptr == NULL) {
			printf("Error Opening File!\n");
			exit(-1);
		}

		while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login[x].member_ID, &login[x].username, &login[x].gender, &login[x].IC, &login[x].email, &login[x].add.houseNo, &login[x].add.streetNo, &login[x].add.postCode, &login[x].add.city, &login[x].add.state, &login[x].upline, &login[x].encrypted_password, &login[x].question, &login[x].answer, &login[x].account_available, &login[x].time.sec) != EOF) {
			if (strcmp(login[x].upline, "N/A") == 0) {
				num_account++;
				upline_count[z] = x;
				z++;
			}
			x++;
		}

		fclose(fptr);

		if (num_account < 5) {
			do {
				printf("Sign Up\n\n");
				printf("User Name (X - Back): %s\n\n", info.username);
				printf("Gender (M / F): %s\n\n", info.gender);
				printf("IC Number: %s\n\n", info.IC);
				printf("Email: %s\n\n", info.email);
				printf("Current Address: %s, %s, %s %s, %s\n\n", info.add.houseNo, info.add.streetNo, info.add.postCode, info.add.city, info.add.state);
				printf("Up-line (Please Select One): \n");
				printf("0. Become an upline\n");
				while (y <= num_account) {
					printf("%d. %s\n", y, login[upline_count[y - 1]].username);
					y++;
				}
				printf("\nEnter your selection: ");
				scanf("%d", &upline_selection);
				rewind(stdin);
				if (upline_selection >= y || upline_selection < 0) {
					y = 1;
					red();
					printf("\nError message: Invalid input!");
					Sleep(1500);
					system("cls");
					sysColor();
				}
			} while (upline_selection >= y || upline_selection < 0);
		}
		else {
			y = 1;
			do {
				printf("Sign Up\n\n");
				printf("User Name (X - Back): %s\n\n", info.username);
				printf("Gender (M / F): %s\n\n", info.gender);
				printf("IC Number: %s\n\n", info.IC);
				printf("Email: %s\n\n", info.email);
				printf("Current Address: %s, %s, %s %s, %s\n\n", info.add.houseNo, info.add.streetNo, info.add.postCode, info.add.city, info.add.state);
				printf("Up-line (Please Select One): \n");
				while (y <= num_account) {
					printf("%d. %s\n", y, login[upline_count[y - 1]].username);
					y++;
				}
				printf("\nEnter your selection: ");
				scanf("%d", &upline_selection);
				rewind(stdin);
				if (upline_selection >= y || upline_selection <= 0) {
					y = 1;
					red();
					printf("\nError message: Invalid input!");
					Sleep(1500);
					system("cls");
					sysColor();
				}
			} while (upline_selection >= y || upline_selection <= 0);
		}

		// Password Validation
		int i = 0, j, count1 = 0;
		char tempPsw;

		printf("\nPassword: ");
		do {
			do {
				tempPsw = getch();         // get the temporary password/input that user enter
				printf("%c", tempPsw);     // show the temp password/input that user enter
				Sleep(100);			       // but just diplay 0.1s
				system("cls");
				if (tempPsw == '\b') {     // '\b'= 'backspace' that user want to delete psw
					if (count1 > 0) {
						count1--;
					}                      // if count equal 0 then no need minus 
					else
						count1 = 0;
				}
				else if (tempPsw == '\r') {   // '13'and'\r' = enter key , user confirm psw then end the psw loop
					break;
				}
				else {
					info.password[i] = tempPsw;  // record the temp psw
					count1++;
				}

				output(info);
				y = 1;
				printf("Up-line (Please Select One): \n");

				if (num_account < 5) {
					printf("0. Become an upline\n");
				}

				while (y <= num_account) {
					printf("%d. %s\n", y, login[upline_count[y - 1]].username);
					y++;
				}

				printf("\nEnter your selection: %d\n\n", upline_selection);
				printf("Password: ");
				for (i = 0; i < count1; i++) {
					printf("*");
				}

			} while (tempPsw != 13);

			info.password[i] = '\0';

			output(info);
			y = 1;
			printf("Up-line (Please Select One): \n");

			if (num_account < 5) {
				printf("0. Become an upline\n");
			}

			while (y <= num_account) {
				printf("%d. %s\n", y, login[upline_count[y - 1]].username);
				y++;
			}

			printf("\nEnter your selection: %d\n\n", upline_selection);
			printf("Password: ");
			for (i = 0; i < count1; i++) {
				printf("*");
			}

			password_status = password_validation(info);

			output(info);
			y = 1;
			printf("Up-line (Please Select One): \n");

			if (num_account < 5) {
				printf("0. Become an upline\n");
			}

			while (y <= num_account) {
				printf("%d. %s\n", y, login[upline_count[y - 1]].username);
				y++;
			}

			printf("\nEnter your selection: %d\n\n", upline_selection);
			printf("Password: ");
			for (i = 0; i < count1; i++) {
				printf("*");
			}

		} while (password_status == 0);

		system("cls");
		output(info);
		y = 1;
		printf("Up-line (Please Select One): \n");

		if (num_account < 5) {
			printf("0. Become an upline\n");
		}

		while (y <= num_account) {
			printf("%d. %s\n", y, login[upline_count[y - 1]].username);
			y++;
		}

		printf("\nEnter your selection: %d\n\n", upline_selection);

		printf("Password: ");
		for (i = 0; i < count1; i++) {
			printf("*");
		}

		// Key Validation
		do {
			printf("\n\nEnter a key (Please remember it!!!): ");
			if (!scanf("%d", &info.key)) {
				red();
				printf("\nError message: Only digit is accepted.");
				Sleep(1500);
				sysColor();
				system("cls");
				output(info);
				y = 1;
				printf("Up-line (Please Select One): \n");

				if (num_account < 5) {
					printf("0. Become an upline\n");
				}

				while (y <= num_account) {
					printf("%d. %s\n", y, login[upline_count[y - 1]].username);
					y++;
				}

				printf("\nEnter your selection: %d\n\n", upline_selection);

				printf("Password: ");
				for (i = 0; i < count1; i++) {
					printf("*");
				}
			}
			else if (info.key < 0) {
				red();
				printf("\nError message: Encryption key cannot be negative value.");
				Sleep(1500);
				sysColor();
				system("cls");
				output(info);
				y = 1;
				printf("Up-line (Please Select One): \n");

				if (num_account < 5) {
					printf("0. Become an upline\n");
				}

				while (y <= num_account) {
					printf("%d. %s\n", y, login[upline_count[y - 1]].username);
					y++;
				}

				printf("\nEnter your selection: %d\n\n", upline_selection);

				printf("Password: ");
				for (i = 0; i < count1; i++) {
					printf("*");
				}
			}
			else {
				rewind(stdin);
				break;
			}
			rewind(stdin);
		} while (1);

		// Confirm Password Validation
		int k = 0, count2 = 0;
		char tempConPsw;

		printf("\nConfirm Password: ");
		do {
			do {
				tempConPsw = getch();
				printf("%c", tempConPsw);
				Sleep(100);
				system("cls");
				if (tempConPsw == '\b') {
					if (count2 > 0) {
						count2--;
					}
					else
						count2 = 0;
				}
				else if (tempConPsw == '\r') {
					break;
				}
				else {
					info.password_confirm[k] = tempConPsw;
					count2++;
				}

				output(info);
				y = 1;
				printf("Up-line (Please Select One): \n");

				if (num_account < 5) {
					printf("0. Become an upline\n");
				}

				while (y <= num_account) {
					printf("%d. %s\n", y, login[upline_count[y - 1]].username);
					y++;
				}

				printf("\nEnter your selection: %d\n\n", upline_selection);

				printf("Password: ");
				for (i = 0; i < count1; i++) {
					printf("*");
				}

				printf("\n\nEnter a key (Please remember it!!!): %d\n\n", info.key);

				printf("Confirm Password: ");
				for (k = 0; k < count2; k++) {
					printf("*");
				}

			} while (tempConPsw != 13);

			info.password_confirm[k] = '\0';

			output(info);
			y = 1;
			printf("Up-line (Please Select One): \n");

			if (num_account < 5) {
				printf("0. Become an upline\n");
			}

			while (y <= num_account) {
				printf("%d. %s\n", y, login[upline_count[y - 1]].username);
				y++;
			}

			printf("\nEnter your selection: %d\n\n", upline_selection);

			printf("Password: ");
			for (i = 0; i < count1; i++) {
				printf("*");
			}

			printf("\n\nEnter a key (Please remember it!!!): %d\n\n", info.key);

			printf("Confirm Password: ");
			for (k = 0; k < count2; k++) {
				printf("*");
			}
			printf("\n\n");

			confirmPsd_status = confirm_password(info);

			output(info);
			y = 1;
			printf("Up-line (Please Select One): \n");

			if (num_account < 5) {
				printf("0. Become an upline\n");
			}

			while (y <= num_account) {
				printf("%d. %s\n", y, login[upline_count[y - 1]].username);
				y++;
			}

			printf("\nEnter your selection: %d\n\n", upline_selection);

			printf("Password: ");
			for (i = 0; i < count1; i++) {
				printf("*");
			}

			printf("\n\nEnter a key (Please remember it!!!): %d\n\n", info.key);

			printf("Confirm Password: ");
			for (k = 0; k < count2; k++) {
				printf("*");
			}

		} while (confirmPsd_status == 0);

		// Password Encryption
		strcpy(info.encrypted_password, password_encryption(info));

		printf("\n\nWe will jump to the security question after a while");
		searching_animation();
		system("cls");

		// Security Question
		do {
			info.question = security_question();
			printf("\nEnter your answer: ");
			scanf("%[^\n]", info.answer);
			rewind(stdin);

			if (strlen(info.answer) <= 0 || strlen(info.answer) > 100) {
				red();
				printf("\nError message: The length of answer must between 1 - 100 character(s).");
				Sleep(1000);
				system("cls");
				sysColor();
			}

		} while (strlen(info.answer) <= 0 || strlen(info.answer) > 100);

		// Insert the record in the 'member.txt' file
		if (gender_status == 1 && ic_status == 1 && email_status == 1 && address_status == 1 && password_status == 1 && confirmPsd_status == 1) {
			strcpy(info.account_available, "Enable");
			info.time.sec = 0;
			if (upline_selection == 0) {
				strcpy(info.upline, "N/A");
			}
			else if (upline_selection == 1) {
				strcpy(info.upline, login[upline_count[0]].username);
			}
			else if (upline_selection == 2) {
				strcpy(info.upline, login[upline_count[1]].username);
			}
			else if (upline_selection == 3) {
				strcpy(info.upline, login[upline_count[2]].username);
			}
			else if (upline_selection == 4) {
				strcpy(info.upline, login[upline_count[3]].username);
			}
			else {
				strcpy(info.upline, login[upline_count[4]].username);
			}

			// Change the member_ID
			// Member ID in member.txt
			strcpy(info.member_ID, login[x - 1].member_ID);

			// Member ID in bannedlist.txt
			FILE* readfile;
			readfile = fopen("bannedlist.txt", "r");

			if (readfile == NULL) {
				printf("Error Opening File!\n");
				exit(-1);
			}

			while (fscanf(readfile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &read.member_ID, &read.username, &read.gender, &read.IC, &read.email, &read.add.houseNo, &read.add.streetNo, &read.add.postCode, &read.add.city, &read.add.state, &read.upline, &read.encrypted_password, &read.question, &read.answer, &read.account_available, &read.time.sec) != EOF) {
				if (strcmp(read.member_ID, info.member_ID) > 0) {
					strcpy(info.member_ID, read.member_ID);
				}
			}

			fclose(readfile);

			strncpy(info.member_ID, info.member_ID + 1, 4);
			info.member_ID[4] = "\0";
			int memberID = atoi(info.member_ID); // Turn the string to integer
			memberID++;
			sprintf(info.member_ID, "M%04d", memberID); // Combine the M with the sequence code

			FILE* log;
			log = fopen("member.txt", "a");

			if (log == NULL) {
				printf("Error Opening File!\n");
				exit(-1);
			}

			fprintf(log, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", info.member_ID, info.username, info.gender, info.IC, info.email, info.add.houseNo, info.add.streetNo, info.add.postCode, info.add.city, info.add.state, info.upline, info.encrypted_password, info.question, info.answer, info.account_available, info.time.sec);
			exit_status = 1;
			printf("\nProcessing");
			searching_animation();
			system("cls");
			bear();
			Sleep(2000);
			system("cls");
			sysColor();

			fclose(log);

			if (strcmp(info.upline, "N/A") == 0) {
				char filename[100];
				StockItem stock;

				FILE* createStock;
				FILE* readStock;

				sprintf(filename, "%s.txt", info.username);
				createStock = fopen(filename, "w");
				readStock = fopen("stock.txt", "r");

				if (createStock == NULL || readStock == NULL) {
					printf("Error opening file.\n");
					exit(-1);
				}

				while (fscanf(readStock, "%[^|]|%[^|]|%f|%d|%d|%d\n", &stock.item_code, &stock.item_description, &stock.item_price, &stock.item_quantity, &stock.minimum_level, &stock.reorder_quantity) != EOF) {
					stock.item_quantity = 0;
					stock.minimum_level = 0;
					stock.reorder_quantity = 0;
					fprintf(createStock, "%s|%s|%.2f|%d|%d|%d\n", stock.item_code, stock.item_description, stock.item_price, stock.item_quantity, stock.minimum_level, stock.reorder_quantity);
				}

				fclose(readStock);
				fclose(createStock);

				FILE* createAccount;
				sprintf(filename, "Account %s.txt", info.username);
				createAccount = fopen(filename, "a");

				if (createAccount == NULL) {
					printf("Error opening file.\n");
					exit(-1);
				}

				fclose(createAccount);
			}
		}
	}
	return exit_status;
}

char* login() {
	struct Member input;
	struct Member login[100];
	struct Member read;
	char decrypted_password[51], encrypted_password[51], temp_name[100];
	bool account_found = false, account_available = true, account_banned = false;
	int password_status = 0, exit_status = 0;
	int life = 3, count = 0;
	int i, k;
	int min = 3, sec = 0, remain_min, remain_sec;

	FILE* log;
	log = fopen("member.txt", "r+");

	FILE* readfile;
	readfile = fopen("bannedlist.txt", "r");

	if (log == NULL || readfile == NULL) {
		printf("Error Opening File!\n");
		exit(-1);
	}

	printf("Login\n\n");
	printf("Your remaining opportunities for trying the password: %d\n\n", life - count);

	do {
		i = 0;
		do {
			account_banned = false;

			printf("User Name (X - Back): ");
			scanf("%[^\n]", input.username);
			rewind(stdin);

			for (int i = 0; i < strlen(input.username); i++) {
				temp_name[i] = toupper(input.username[i]);
			}
			temp_name[strlen(input.username)] = '\0';

			if (strcmp(temp_name, "X") == 0) {
				strcpy(input.username, "1");
				exit_status = 1;
			}
			else {
				exit_status = 0;
			}

			if (exit_status == 0) {
				while (fscanf(readfile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &read.member_ID, &read.username, &read.gender, &read.IC, &read.email, &read.add.houseNo, &read.add.streetNo, &read.add.postCode, &read.add.city, &read.add.state, &read.upline, &read.encrypted_password, &read.question, &read.answer, &read.account_available, &read.time.sec) != EOF) {
					if (strcmp(input.username, read.username) == 0) {
						account_banned = true;
						red();
						printf("\nError message: This account has been banned!");
						Sleep(1500);
						sysColor();
						system("cls");
						printf("Login\n\n");
						printf("Your remaining opportunities for trying the password: %d\n\n", life - count);
					}
				}
			}
		} while (account_banned == true);

		if (exit_status == 0) {
			time_t cur_time = time(NULL);
			rewind(log);  // 重置文件指针 (cursor)
			while (fscanf(log, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login[i].member_ID, &login[i].username, &login[i].gender, &login[i].IC, &login[i].email, &login[i].add.houseNo, &login[i].add.streetNo, &login[i].add.postCode, &login[i].add.city, &login[i].add.state, &login[i].upline, &login[i].encrypted_password, &login[i].question, &login[i].answer, &login[i].account_available, &login[i].time.sec) != EOF) {
				if (strcmp(input.username, login[i].username) == 0) {
					account_found = true;
					if (strcmp(login[i].account_available, "Disable") == 0) {
						if (cur_time - login[i].time.sec >= 180) {
							account_available = true;
							k = i;
						}
						else {
							account_available = false;
							remain_min = (180 - (cur_time - login[i].time.sec)) / 60;
							remain_sec = (180 - (cur_time - login[i].time.sec)) % 60;
							red();
							if (remain_min == 0) {
								printf("\nError message: The account still be blocked. You will be able to try to login to the account again after %d second(s).\n\n", remain_sec);
							}
							else {
								printf("\nError message: The account still be blocked. You will be able to try to login to the account again after %d min(s) %d second(s).\n\n", remain_min, remain_sec);
							}
							Sleep(1500);
							sysColor();
							system("cls");
							printf("Login\n\n");
							printf("Your remaining opportunities for trying the password: %d\n\n", life - count);
						}
					}
					else {
						account_available = true;
						k = i;
					}
					i++;
					continue;
				}
				i++;
			}

			if (account_found == false) {
				red();
				printf("\nError message: Cannot find the account!");
				Sleep(1500);
				sysColor();
				system("cls");
				printf("Login\n\n");
				printf("Your remaining opportunities for trying the password: %d\n\n", life - count);
			}
		}
	} while ((account_found == false || account_available == false) && exit_status == 0);

	fclose(log);
	fclose(readfile);

	if (exit_status == 0) {
		do {
			printf("\nPassword: ");
			scanf("%[^\n]", input.password);
			rewind(stdin);

			do {
				printf("\nEnter your decryption key: ");
				if (!scanf("%d", &input.key)) {
					red();
					printf("\nError message: Only digit is accepted.");
					Sleep(1500);
					system("cls");
					sysColor();
					printf("Login\n\n");
					printf("Your remaining opportunities for trying the password: %d\n\n", life - count);
					printf("User Name (X - Back): %s\n\n", input.username);
					printf("Password: %s\n", input.password);
				}
				else {
					rewind(stdin);
					break;
				}
				rewind(stdin);
			} while (1);

			strcpy(encrypted_password, login[k].encrypted_password);
			strcpy(decrypted_password, password_decryption(input, encrypted_password));

			if (strcmp(input.password, decrypted_password) == 0) {
				printf("\nLogin successfully!!!\n");
				password_status = 1;

				// Open file for writing
				FILE* fptw1;
				fptw1 = fopen("member.txt", "w");

				if (fptw1 == NULL) {
					printf("Error opening file!\n");
					exit(-1);
				}

				strcpy(login[k].account_available, "Enable");
				login[k].time.sec = 0;
				for (int x = 0; x < i; x++) {
					fprintf(fptw1, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", login[x].member_ID, login[x].username, login[x].gender, login[x].IC, login[x].email, login[x].add.houseNo, login[x].add.streetNo, login[x].add.postCode, login[x].add.city, login[x].add.state, login[x].upline, login[x].encrypted_password, login[x].question, login[x].answer, login[x].account_available, login[x].time.sec);
				}

				fclose(fptw1);

				break;
			}
			else {
				red();
				printf("\nError message: The password is incorrect!\n");
				count++;
				Sleep(1500);
				system("cls");
				sysColor();
				printf("Login\n\n");
				printf("Your remaining opportunities for trying the password: %d\n\n", life - count);
				printf("User Name (X - Back): %s\n", input.username);
			}

			if (count >= 3) {
				// Open file for writing
				FILE* fptw2;
				fptw2 = fopen("member.txt", "w");

				if (fptw2 == NULL) {
					printf("Error opening file!\n");
					exit(-1);
				}

				time_t lock_time = time(NULL);

				strcpy(login[k].account_available, "Disable");
				login[k].time.sec = lock_time;
				for (int x = 0; x < i; x++) {
					fprintf(fptw2, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", login[x].member_ID, login[x].username, login[x].gender, login[x].IC, login[x].email, login[x].add.houseNo, login[x].add.streetNo, login[x].add.postCode, login[x].add.city, login[x].add.state, login[x].upline, login[x].encrypted_password, login[x].question, login[x].answer, login[x].account_available, login[x].time.sec);
				}
				fclose(fptw2);

				system("cls");

				// Countdown for blocking time 
				time_t time_sec = 0;
				time_t old_sec = 0;

				time(&time_sec);  // 获取当前秒数 (从 1970-1-1 00:00:00 到现在)

				printf("\n\n\n\n\n\n\n\n\n\n\n\n                                    This account will be blocked for 3 minutes.\n");
				printf("                                  You will be able to continue trying after %d: %02d.\r", min, sec);

				old_sec = time_sec;  // 更新旧的秒数 -> 也是从 1970-1-1 00:00:00 到现在

				while (min > 0 || sec > 0) {
					time(&time_sec);  // 获取秒数保存到 time_t 变量

					if (time_sec != old_sec) {  // 如果秒数发生改变 (当时间过了一秒)
						old_sec = time_sec;  // 更新旧的秒数
						if (sec > 0) {
							sec--;  // 记时秒数减 1
						}
						else {
							sec = 59;  // 如果原秒数为 0, 则变为 59
							if (min > 0) {
								min--;  // 记时分钟减 1
							}
							else {
								min = 0;
							}
						}
						printf("                                  You will be able to continue trying after %d: %02d.\r", min, sec);
					}
				}

				if (min == 0 && sec == 0) {
					system("cls");
					count = 0, min = 3, sec = 0;

					printf("Login\n\n");
					printf("Your remaining opportunities for trying the password: %d\n\n", life - count);
					printf("User Name (X - Back): %s\n", input.username);

					// Open file for writing
					FILE* fptw3;
					fptw3 = fopen("member.txt", "w");

					strcpy(login[k].account_available, "Enable");
					login[k].time.sec = 0;
					for (int x = 0; x < i; x++) {
						fprintf(fptw3, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", login[x].member_ID, login[x].username, login[x].gender, login[x].IC, login[x].email, login[x].add.houseNo, login[x].add.streetNo, login[x].add.postCode, login[x].add.city, login[x].add.state, login[x].upline, login[x].encrypted_password, login[x].question, login[x].answer, login[x].account_available, login[x].time.sec);
					}

					fclose(fptw3);
				}
			}
		} while (password_status == 0);
	}

	return input.username;
}

bool username_validation(struct Member info) {
	struct Member login;
	char encrypted_password[51];
	bool username_found = false;

	FILE* log;
	log = fopen("member.txt", "r");

	FILE* log2;
	log2 = fopen("bannedlist.txt", "r");

	if (log == NULL || log2 == NULL) {
		printf("Error Opening File!\n");
		exit(-1);
	}

	while (fscanf(log, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login.member_ID, &login.username, &login.gender, &login.IC, &login.email, &login.add.houseNo, &login.add.streetNo, &login.add.postCode, &login.add.city, &login.add.state, &login.upline, &login.encrypted_password, &login.question, &login.answer, &login.account_available, &login.time.sec) != EOF) {
		if (strcmp(info.username, login.username) == 0) {
			username_found = true;
			red();
			printf("\nError message: The username is already existed!\n");
			Sleep(1500);
			system("cls");
			sysColor();
			return true;
		}
		else {
			username_found = false;
		}
	}

	fclose(log);

	if (username_found == false) {
		while (fscanf(log2, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login.member_ID, &login.username, &login.gender, &login.IC, &login.email, &login.add.houseNo, &login.add.streetNo, &login.add.postCode, &login.add.city, &login.add.state, &login.upline, &login.encrypted_password, &login.question, &login.answer, &login.account_available, &login.time.sec) != EOF) {
			if (strcmp(info.username, login.username) == 0) {
				username_found = true;
				red();
				printf("\nError message: The username is already existed!\n");
				Sleep(1500);
				system("cls");
				sysColor();
				return true;
			}
			else {
				username_found = false;
			}
		}
	}

	fclose(log2);

	return username_found;
}

int gender_validation(struct Member info) {
	int gender_status = 1;
	int gender_length = strlen(info.gender);

	for (int i = 0; i < gender_length; i++) {
		info.gender[i] = toupper(info.gender[i]);
	}

	if (gender_length > 1) {
		if (strcmp(info.gender, "MALE") == 0) {
			info.gender[0] = 'M';
			info.gender[1] = '\0';
		}
		else if (strcmp(info.gender, "FEMALE") == 0) {
			info.gender[0] = 'F';
			info.gender[1] = '\0';
		}
		else {
			gender_status = 0;
			red();
			printf("\nError message: Only 'M' and 'F' is accepted.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	}
	else if (gender_length == 1) {
		if (info.gender[0] == 'M') {
			info.gender[1] = '\0';
		}
		else if (info.gender[0] == 'F') {
			info.gender[1] = '\0';
		}
		else {
			gender_status = 0;
			red();
			printf("\nError message: Only 'M' and 'F' is accepted.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	}
	else {
		gender_status = 0;
		red();
		printf("\nError message: Only 'M' and 'F' is accepted.");
		Sleep(1500);
		system("cls");
		sysColor();
	}

	return gender_status;
}

int icnum_validation(struct Member info) {
	// must contains two '-' inside the IC number -> index 6 and 9   
	// 040910 - year / month / date
	// 0317 - the last number indicates the gender, odd -> male, even -> female
	struct Member login;
	int day[2], month[2], year[2];
	int result;
	int ic_length;
	int lstNum;
	int ic_status = 1;

	ic_length = strlen(info.IC);
	if (ic_length == 14) {
		for (int i = 0; i < 2; i++) {
			if (isdigit(info.IC[i])) {
				year[i] = info.IC[i] - '0';  // isdigit() 把 string 转去 ASCII, 所以要减去 0 的 ASCII value
			}
			else {
				ic_status = 0;
				red();
				printf("\nError message: Only digit is accepted.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
		for (int i = 2; i < 4; i++) {
			if (isdigit(info.IC[i])) {
				month[i - 2] = info.IC[i] - '0';
			}
			else {
				ic_status = 0;
				red();
				printf("\nError message: Only digit is accepted.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
		for (int i = 4; i < 6; i++) {
			if (isdigit(info.IC[i])) {
				day[i - 4] = info.IC[i] - '0';
			}
			else {
				ic_status = 0;
				red();
				printf("\nError message: Only digit is accepted.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
		for (int i = 6; i < 14; i++) {
			if (i == 6 || i == 9) {
				if (info.IC[i] != '-') {
					ic_status = 0;
					red();
					printf("\nError message: The IC format is wrong!");
					Sleep(1500);
					system("cls");
					sysColor();
					break;
				}
			}
			else {
				if (!isdigit(info.IC[i])) {
					ic_status = 0;
					red();
					printf("\nError message: Only digit is accepted.");
					Sleep(1500);
					system("cls");
					sysColor();
				}
				else {
					if (i == 13) {
						lstNum = info.IC[13] - '0';
						if (info.gender[0] == 'M' || info.gender[0] == 'm') {
							if (lstNum % 2 == 0) {
								ic_status = 0;
								red();
								printf("\nError message: The IC format is wrong!");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
						else if (info.gender[0] == 'F' || info.gender[0] == 'f') {
							if (lstNum % 2 != 0) {
								ic_status = 0;
								red();
								printf("\nError message: The IC format is wrong!");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
					}
				}
			}
		}
	}
	else if (ic_length < 14) {
		ic_status = 0;
		red();
		printf("\nError message: The number of length of IC is less than 14.");
		Sleep(1500);
		system("cls");
		sysColor();
	}
	else {
		ic_status = 0;
		red();
		printf("\nError message: The number of length of IC is less than 14.");
		Sleep(1500);
		system("cls");
		sysColor();
	}

	if (ic_status == 1) {
		// check if the month is between Jan to Sep
		if (month[0] == 0) {
			// make sure that no 00 happens in month
			if (month[1] >= 1 && month[1] <= 9) {
				// Jan, Mar, May, Jul, Aug -> has 31 days 
				if (month[1] == 1 || month[1] == 3 || month[1] == 5 || month[1] == 7 || month[1] == 8) {
					// check if the day is between 01 to 31
					if (day[0] >= 0 && day[0] <= 3) {
						// check if the day is 30 or 31
						if (day[0] == 3) {
							if (day[1] > 1) {
								ic_status = 0;
								red();
								printf("\nError message: The maximum number days is only up to 31 days.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
						// check if the day is between 01 to 09
						else if (day[0] == 0) {
							// make sure that no 00 in day
							if (day[1] == 0) {
								ic_status = 0;
								red();
								printf("\nError message: The day must start with 01.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
					}
					else {
						ic_status = 0;
						red();
						printf("\nError message: The maximum number days is only up to 31 days.");
						Sleep(1500);
						system("cls");
						sysColor();
					}
				}
				// Apr, Jun, Sep -> has 30 days
				else if (month[1] == 4 || month[1] == 6 || month[1] == 9) {
					if (day[0] >= 0 && day[0] <= 3) {
						if (day[0] == 3) {
							if (day[1] > 0) {
								ic_status = 0;
								red();
								printf("\nError message: The maximum number days is only up to 30 days.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
						else if (day[0] == 0) {
							if (day[1] == 0) {
								ic_status = 0;
								red();
								printf("\nError message: The day must start with 01.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
					}
					else {
						ic_status = 0;
						red();
						printf("\nError message: The maximum number days is only up to 30 days.");
						Sleep(1500);
						system("cls");
						sysColor();
					}
				}
				// handle Feb (special month) -> only has 28 or 29 days (4 years one times)
				else {
					result = year[0] % 4; // 5 remainder 1, 6 remainder 2, 7 remainder 3, 8 remainder 0... -> 5 stands for 195?, 6 stands for 196?, 7 stands for 197?, 8 stands for 198?...
					if (result == 1 || result == 3) {  // if remainder is 1 or 3 means in those 10 years, there will be two leap years
						if (year[1] == 2 || year[1] == 6) {  // the leap year is ends with 2 or 6 -> 1952, 1956, 1972, 1976
							if (day[0] >= 0 && day[0] <= 2) {  // leap year only has 29 days
								if (day[0] == 0) {
									// make sure that no 00 in day
									if (day[1] == 0) {
										ic_status = 0;
										red();
										printf("\nError message: The day must start with 01.");
										Sleep(1500);
										system("cls");
										sysColor();
									}
								}
							}
							else {
								ic_status = 0;
								red();
								printf("\nError message: The maximum number days is only up to 29 days.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
						else {  // handle normal year
							if (day[0] >= 0 && day[0] <= 2) {
								if (day[0] == 2) {
									if (day[1] == 9) {  // normal year only has 28 days
										ic_status = 0;
										red();
										printf("\nError message: The maximum number days is only up to 28 days.");
										Sleep(1500);
										system("cls");
										sysColor();
									}
								}
								else if (day[0] == 0) {
									if (day[1] == 0) {
										ic_status = 0;
										red();
										printf("\nError message: The day must start with 01.");
										Sleep(1500);
										system("cls");
										sysColor();
									}
								}
							}
							else {
								ic_status = 0;
								red();
								printf("\nError message: The day is only between 01 - 28/29.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
					}
					else {  // if remainder is 0 or 2 means in those 10 years, there will be three leap years
						if (year[1] == 0 || year[1] == 4 || year[1] == 8) {  // the leap year is ends with 0, 4 or 8 -> 1960, 1964, 1968, 1980, 1984, 1988
							if (day[0] >= 0 && day[0] <= 2) {  // leap year only has 29 days
								if (day[0] == 0) {
									// make sure that no 00 in day
									if (day[1] == 0) {
										ic_status = 0;
										red();
										printf("\nError message: The day must start with 01.");
										Sleep(1500);
										system("cls");
										sysColor();
									}
								}
							}
							else {
								ic_status = 0;
								red();
								printf("\nError message: The maximum number days is only up to 29 days.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
						else {  // handle normal year
							if (day[0] >= 0 && day[0] <= 2) {
								if (day[0] == 2) {
									if (day[1] == 9) {  // normal year only has 28 days
										ic_status = 0;
										red();
										printf("\nError message: The maximum number days is only up to 28 days.");
										Sleep(1500);
										system("cls");
										sysColor();
									}
								}
								else if (day[0] == 0) {
									if (day[1] == 0) {
										ic_status = 0;
										red();
										printf("\nError message: The day must start with 01.");
										Sleep(1500);
										system("cls");
										sysColor();
									}
								}
							}
							else {
								ic_status = 0;
								red();
								printf("\nError message: The day is only between 01 - 28/29.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
					}
				}
			}
		}
		else if (month[0] == 1) {
			if (month[1] >= 0 && month[1] <= 2) {
				// Oct, Dec -> has 31 days
				if (month[1] == 0 || month[1] == 2) {
					if (day[0] >= 0 && day[0] <= 3) {
						if (day[0] == 3) {
							if (day[1] > 1) {
								ic_status = 0;
								red();
								printf("\nError message: The maximum number days is only up to 31 days.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
						// check if the day is between 01 to 09
						else if (day[0] == 0) {
							// make sure that no 00 in day
							if (day[1] == 0) {
								ic_status = 0;
								red();
								printf("\nError message: The day must start with 01.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
					}
					else {
						ic_status = 0;
						red();
						printf("\nError message: The maximum number days is only up to 31 days.");
						Sleep(1500);
						system("cls");
						sysColor();
					}
				}
				// Nov -> has 30 days
				else {
					if (day[0] >= 0 && day[0] <= 3) {
						if (day[0] == 3) {
							if (day[1] > 0) {
								ic_status = 0;
								red();
								printf("\nError message: The maximum number days is only up to 30 days.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
						else if (day[0] == 0) {
							if (day[1] == 0) {
								ic_status = 0;
								red();
								printf("\nError message: The day must start with 01.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}
					}
					else {
						ic_status = 0;
						red();
						printf("\nError message: The maximum number days is only up to 30 days.");
						Sleep(1500);
						system("cls");
						sysColor();
					}
				}
			}
			else {
				ic_status = 0;
				red();
				printf("\nError message: There are only 12 months in a year.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
		else {
			ic_status = 0;
			red();
			printf("\nError message: The month is only between 01 - 12.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	}

	// Check whether the IC number is duplicate or not
	FILE* log;
	log = fopen("member.txt", "r");

	FILE* log2;
	log2 = fopen("bannedlist.txt", "r");

	if (log == NULL || log2 == NULL) {
		printf("Error Opening File!\n");
		exit(-1);
	}

	while (fscanf(log, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login.member_ID, &login.username, &login.gender, &login.IC, &login.email, &login.add.houseNo, &login.add.streetNo, &login.add.postCode, &login.add.city, &login.add.state, &login.upline, &login.encrypted_password, &login.question, &login.answer, &login.account_available, &login.time.sec) != EOF) {
		if (strcmp(info.IC, login.IC) == 0) {
			ic_status = 0;
			red();
			printf("\nError message: The IC number is already existed!");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	}

	fclose(log);

	if (ic_status == 1) {
		while (fscanf(log2, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login.member_ID, &login.username, &login.gender, &login.IC, &login.email, &login.add.houseNo, &login.add.streetNo, &login.add.postCode, &login.add.city, &login.add.state, &login.upline, &login.encrypted_password, &login.question, &login.answer, &login.account_available, &login.time.sec) != EOF) {
			if (strcmp(info.IC, login.IC) == 0) {
				ic_status = 0;
				red();
				printf("\nError message: The IC number is already existed!");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
	}

	fclose(log2);

	return ic_status;
}

int email_validation(struct Member info) {
	struct Member login;
	int email_length;
	int email_status = 1;
	int count = 0;
	char* position_1, position_2, position_3, position_4;
	char* valid_tld[] = { "com", "org", "net", "int", "edu", "gov", "mil", "my" };

	email_length = strlen(info.email);

	// Check whether '@' is in the correct position or not 
	position_1 = strchr(info.email, '@');
	// The email does not contains '@'
	if (position_1 == NULL) {
		email_status = 0;
		red();
		printf("\nError message: Please contains '@'.");
		Sleep(1500);
		system("cls");
		sysColor();
	}
	else {
		// The email contains more than one '@'
		while (position_1 != NULL) {
			count++;
			position_1 = strchr(position_1 + 1, '@'); // position_1 + 1 -> search '@' start from the following index 
		}
		if (count > 1) {
			email_status = 0;
			red();
			printf("\nError message: The email can only contain one @.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
		// The position of '@' is at the first index or last index
		else {
			position_1 = strchr(info.email, '@');
			if (position_1 == info.email || position_1 == info.email + email_length - 1) {  // info.email 的地址表示字符串的第一个字符的地址
				email_status = 0;
				red();
				printf("\nError message: The position of '@' cannot be at the first index or last index");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
	}

	if (email_status == 1) {
		position_2 = strchr(info.email, '.');
		// The email does not contains '.'
		if (position_2 == NULL) {
			email_status = 0;
			red();
			printf("\nError message: Please contains '.' after '@'.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
		else {
			position_3 = strstr(info.email, "..");
			if (position_3 != NULL) {
				email_status = 0;
				red();
				printf("\nError message: The email cannot contain consecutive dots.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
			else {
				position_1 = strchr(info.email, '@');
				position_2 = strrchr(position_1 + 1, '.'); // 从 @ 的地址后面开始查找

				if (position_2 == NULL) {
					email_status = 0;
					red();
					printf("\nError message: Please contains '.' after '@'.");
					Sleep(1500);
					system("cls");
					sysColor();
				}
				//else {
				//	for (int i = 0; i < sizeof(valid_tld) / sizeof(valid_tld[0]); i++) {  // sizeof(valid_tld) 的值等于该数组的长度乘以每个元素的大小(即 8 bits), 而 sizeof(valid_tld[0]) 指的是 valid_tld 里第一个字符串所占用的空间(即 8 bits)
				//		if (strcmp(position_2 + 1, valid_tld[i]) == 0) {
				//			printf("Invalid email. Please contains a Top-level Domain (TLD) after '.'.\n");
				//			email_status = 0;
				//		}
				//	}

				//	position_4 = strchr(info.email, '.');
				//	if (position_4 == info.email || position_4 == info.email + email_length - 1) {  // info.email 的地址表示字符串的第一个字符的地址
				//		printf("Invalid email.\n");
				//		email_status = 0;
				//	}
				//}
			}
		}
	}

	// Check whether the email is duplicate or not
	FILE* log;
	log = fopen("member.txt", "r");

	FILE* log2;
	log2 = fopen("bannedlist.txt", "r");

	if (log == NULL || log2 == NULL) {
		printf("Error Opening File!\n");
		exit(-1);
	}

	while (fscanf(log, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login.member_ID, &login.username, &login.gender, &login.IC, &login.email, &login.add.houseNo, &login.add.streetNo, &login.add.postCode, &login.add.city, &login.add.state, &login.upline, &login.encrypted_password, &login.question, &login.answer, &login.account_available, &login.time.sec) != EOF) {
		if (strcmp(info.email, login.email) == 0) {
			email_status = 0;
			red();
			printf("\nError message: The email is already existed!");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	}

	fclose(log);

	if (email_status == 1) {
		while (fscanf(log2, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login.member_ID, &login.username, &login.gender, &login.IC, &login.email, &login.add.houseNo, &login.add.streetNo, &login.add.postCode, &login.add.city, &login.add.state, &login.upline, &login.encrypted_password, &login.question, &login.answer, &login.account_available, &login.time.sec) != EOF) {
			if (strcmp(info.email, login.email) == 0) {
				email_status = 0;
				red();
				printf("\nError message: The email is already existed!");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
	}

	fclose(log2);

	return email_status;
}

int password_validation(struct Member info) {
	int password_length;
	int upper = 0, lower = 0, special = 0, number = 0;
	int password_status = 1;

	password_length = strlen(info.password);
	if (password_length >= 8 && password_length <= 50) {
		for (int i = 0; i < password_length; i++) {
			// [A - Z and a - z]
			if (isalpha(info.password[i])) {
				// [A - Z]
				if (isupper(info.password[i])) {
					upper++;
				}
				// [a - z]
				else {
					lower++;
				}
			}
			// number
			else if (isdigit(info.password[i])) {
				number++;
			}
			// special character
			else {
				special++;
			}
		}
		if (upper == 0 || lower == 0 || number == 0 || special == 0) {
			password_status = 0;
			red();
			printf("\n\nError message: The passowrd must contain at least one uppercase and lowercase letter, one number and one special character.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	}
	else {
		password_status = 0;
		red();
		printf("\n\nError message: The password's length must between 8 and 50.");
		Sleep(1500);
		system("cls");
		sysColor();
	}
	return password_status;
}

int confirm_password(struct Member info) {
	int confirmPsd_status = 1;

	printf("Matching");
	searching_animation();

	if (strcmp(info.password, info.password_confirm) == 1) {
		confirmPsd_status = 0;
		red();
		printf("Error message: The password does not matched.");
		Sleep(1500);
		system("cls");
		sysColor();
	}
	else {
		system("cls");
	}

	return confirmPsd_status;
}

char* password_encryption(struct Member info) {
	int password_length = strlen(info.password);
	char* encrypted_password = (char*)malloc(password_length + 1);

	// If memory cannot be allocated
	if (encrypted_password == NULL) {
		printf("Error! Memory not allocated.");
		exit(0);
	}

	for (int i = 0; i < password_length; i++) {
		// Encryption (number)
		if (info.password[i] == '0') {
			info.password[i] = '4';
		}
		else if (info.password[i] == '1') {
			info.password[i] = '7';
		}
		else if (info.password[i] == '2') {
			info.password[i] = '1';
		}
		else if (info.password[i] == '3') {
			info.password[i] = '5';
		}
		else if (info.password[i] == '4') {
			info.password[i] = '8';
		}
		else if (info.password[i] == '5') {
			info.password[i] = '9';
		}
		else if (info.password[i] == '6') {
			info.password[i] = '0';
		}
		else if (info.password[i] == '7') {
			info.password[i] = '3';
		}
		else if (info.password[i] == '8') {
			info.password[i] = '2';
		}
		else if (info.password[i] == '9') {
			info.password[i] = '6';
		}
		else {
			info.password[i] = info.password[i];
		}

		// Encryption (character)
		if (info.password[i] >= 'A' && info.password[i] <= 'Z') {
			encrypted_password[i] = ((info.password[i] - 'A') + info.key) % 26 + 'A';
		}
		else if (info.password[i] >= 'a' && info.password[i] <= 'z') {
			encrypted_password[i] = ((info.password[i] - 'a') + info.key) % 26 + 'a';
		}
		else {
			encrypted_password[i] = info.password[i];
		}
	}
	encrypted_password[password_length] = '\0';

	return encrypted_password;
}

char* password_decryption(struct Member input, char encrypted_password[51]) {
	int password_length = strlen(encrypted_password);
	char* decrypted_password = (char*)malloc(password_length + 1);

	// If memory cannot be allocated
	if (encrypted_password == NULL) {
		printf("Error! Memory not allocated.");
		exit(0);
	}

	for (int i = 0; i < password_length; i++) {
		// Decryption (number)
		if (encrypted_password[i] == '4') {
			encrypted_password[i] = '0';
		}
		else if (encrypted_password[i] == '7') {
			encrypted_password[i] = '1';
		}
		else if (encrypted_password[i] == '1') {
			encrypted_password[i] = '2';
		}
		else if (encrypted_password[i] == '5') {
			encrypted_password[i] = '3';
		}
		else if (encrypted_password[i] == '8') {
			encrypted_password[i] = '4';
		}
		else if (encrypted_password[i] == '9') {
			encrypted_password[i] = '5';
		}
		else if (encrypted_password[i] == '0') {
			encrypted_password[i] = '6';
		}
		else if (encrypted_password[i] == '3') {
			encrypted_password[i] = '7';
		}
		else if (encrypted_password[i] == '2') {
			encrypted_password[i] = '8';
		}
		else if (encrypted_password[i] == '6') {
			encrypted_password[i] = '9';
		}
		else {
			encrypted_password[i] = encrypted_password[i];
		}

		// Decryption (character)
		if (encrypted_password[i] >= 'A' && encrypted_password[i] <= 'Z') {
			decrypted_password[i] = ((encrypted_password[i] - 'A' + 26) - input.key) % 26 + 'A';
		}
		else if (encrypted_password[i] >= 'a' && encrypted_password[i] <= 'z') {
			decrypted_password[i] = ((encrypted_password[i] - 'a' + 26) - input.key) % 26 + 'a';
		}
		else {
			decrypted_password[i] = encrypted_password[i];
		}
	}
	decrypted_password[password_length] = '\0';

	return decrypted_password;
}

int security_question() {
	int option;

	do {
		printf("Security Question\n\n");
		printf("Please select a security question for password reset: \n");
		printf("1. What is your favorite color?\n");
		printf("2. What is your favorite food?\n");
		printf("3. What was your first pet's name?\n");
		printf("4. What is your mother's maiden name?\n");
		printf("5. What is the name of your favorite childhood teacher?\n\n");

		printf("Enter your selection: ");
		scanf("%d", &option);
		rewind(stdin);

		if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5) {
			red();
			printf("\nError message: Invalid input.");
			Sleep(1500);
			system("cls");
			sysColor();
		}

	} while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5);

	return option;
}

void output(struct Member info) {
	printf("Sign up\n\n");
	printf("User Name (X - Back): %s\n\n", info.username);
	printf("Gender (M / F): %s\n\n", info.gender);
	printf("IC Number: %s\n\n", info.IC);
	printf("Email: %s\n\n", info.email);
	printf("Current Address: %s, %s, %s %s, %s\n\n", info.add.houseNo, info.add.streetNo, info.add.postCode, info.add.city, info.add.state);
}

int view_profile(char username[100]) {
	struct Member info;
	char option[20];
	char name[100];
	int product_status = 0;

	FILE* fptr;
	fptr = fopen("member.txt", "r");

	if (fptr == NULL) {
		printf("Error Opening File!\n");
		exit(-1);
	}

	do {
		rewind(fptr);
		while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &info.member_ID, &info.username, &info.gender, &info.IC, &info.email, &info.add.houseNo, &info.add.streetNo, &info.add.postCode, &info.add.city, &info.add.state, &info.upline, &info.encrypted_password, &info.question, &info.answer, &info.account_available, &info.time.sec) != EOF) {
			if (strcmp(username, info.username) == 0) {
				printf("Name              :  %s\n", info.username);
				printf("Gender            :  %s\n", info.gender);
				printf("IC Number         :  %s\n", info.IC);
				printf("Email             :  %s\n", info.email);
				printf("Current Address   :  %s, %s, %s %s, %s\n", info.add.houseNo, info.add.streetNo, info.add.postCode, info.add.city, info.add.state);
				printf("Upline            :  %s\n", info.upline);
				printf("Password          :  ");
				for (int i = 0; i < strlen(info.encrypted_password); i++) {
					printf("*");
				}
				printf("\n\n");
				strcpy(name, info.username);
			}
		}
		printf("Select the option (X - Back): \n");
		printf("1. Modify your profile details\n\n");
		printf("Enter your selection: ");
		scanf("%[^\n]", option);
		rewind(stdin);

		for (int i = 0; i < strlen(option); i++) {
			option[i] = toupper(option[i]);
		}

		if (strcmp(option, "1") == 0) {
			// Modifying profile details
			strcpy(name, edit_profile(name));
			product_status = 1;
		}
		else if (strcmp(option, "X") == 0) {
			product_status = 1;
			break;
		}
		else {
			product_status = 0;
			red();
			printf("\nError message: Invalid input.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	} while (product_status == 0);

	fclose(fptr);

	return product_status;
}

char* edit_profile(char name[100]) {
	struct Member detail[100];
	struct Member login;
	struct Member storage;
	char option2, option3;
	int email_status, password_status, confirmPsd_status;
	bool username_found;
	char decrypted_password[51];
	int total_length, i = 0;

	FILE* fptr1;
	fptr1 = fopen("member.txt", "r");

	if (fptr1 == NULL) {
		printf("Error Opening File!\n");
		exit(-1);
	}

	rewind(fptr1);
	while (fscanf(fptr1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &detail[i].member_ID, &detail[i].username, &detail[i].gender, &detail[i].IC, &detail[i].email, &detail[i].add.houseNo, &detail[i].add.streetNo, &detail[i].add.postCode, &detail[i].add.city, &detail[i].add.state, &detail[i].upline, &detail[i].encrypted_password, &detail[i].question, &detail[i].answer, &detail[i].account_available, &detail[i].time.sec) != EOF) {
		if (strcmp(name, detail[i].username) == 0) {
			// For Save
			strcpy(login.username, detail[i].username);
			strcpy(login.gender, detail[i].gender);
			strcpy(login.IC, detail[i].IC);
			strcpy(login.email, detail[i].email);
			strcpy(login.add.houseNo, detail[i].add.houseNo);
			strcpy(login.add.streetNo, detail[i].add.streetNo);
			strcpy(login.add.postCode, detail[i].add.postCode);
			strcpy(login.add.city, detail[i].add.city);
			strcpy(login.add.state, detail[i].add.state);
			strcpy(login.upline, detail[i].upline);
			strcpy(login.encrypted_password, detail[i].encrypted_password);
			strcpy(login.account_available, detail[i].account_available);
			login.time.sec = detail[i].time.sec;

			// For Unsave
			strcpy(storage.username, detail[i].username);
			strcpy(storage.gender, detail[i].gender);
			strcpy(storage.IC, detail[i].IC);
			strcpy(storage.email, detail[i].email);
			strcpy(storage.add.houseNo, detail[i].add.houseNo);
			strcpy(storage.add.streetNo, detail[i].add.streetNo);
			strcpy(storage.add.postCode, detail[i].add.postCode);
			strcpy(storage.add.city, detail[i].add.city);
			strcpy(storage.add.state, detail[i].add.state);
			strcpy(storage.upline, detail[i].upline);
			strcpy(storage.encrypted_password, detail[i].encrypted_password);
			strcpy(storage.account_available, detail[i].account_available);
			storage.time.sec = detail[i].time.sec;

			output2(detail[i]);

			do {
				printf("Enter the detail that you want to edit (X - exit): ");
				scanf("%c", &option2);
				option2 = toupper(option2);
				rewind(stdin);

				if (option2 == '1') {
					printf("\nName: ");
					scanf("%[^\n]", login.username);
					rewind(stdin);
					username_found = username_validation(login);
					if (username_found == true) {
						strcpy(login.username, detail[i].username);
						output2(detail[i]);
					}
					else {
						strcpy(detail[i].username, login.username);
						output2(login);
					}
				}
				else if (option2 == '2') {
					red();
					printf("\nError message: Gender cannot be modified.");
					Sleep(1500);
					sysColor();
					output2(login);
				}
				else if (option2 == '3') {
					red();
					printf("\nError message: IC number cannot be modified.");
					Sleep(1500);
					sysColor();
					output2(login);
				}
				else if (option2 == '4') {
					printf("\nEmail: ");
					scanf("%s", login.email);
					rewind(stdin);
					email_status = email_validation(login);
					if (email_status == 0) {
						strcpy(login.email, detail[i].email);
						output2(detail[i]);
					}
					else {
						strcpy(detail[i].email, login.email);
						output2(login);
					}
				}
				else if (option2 == '5') {
					printf("\nCurrent Address: ");
					if (scanf("%[^,\n], %[^,\n], %[^ \n] %[^,\n], %[^\n]", &login.add.houseNo, &login.add.streetNo, &login.add.postCode, &login.add.city, &login.add.state) != 5) {
						red();
						printf("\nError message: The address format is invalid.");
						Sleep(1500);
						sysColor();
						output2(detail[i]);
					}
					else {
						if (strlen(login.add.postCode) != 5 || !isdigit(login.add.postCode[0]) || !isdigit(login.add.postCode[1]) || !isdigit(login.add.postCode[2]) || !isdigit(login.add.postCode[3]) || !isdigit(login.add.postCode[4])) {
							red();
							printf("\nError message: The postcode in invalid.");
							Sleep(1500);
							sysColor();
							output2(detail[i]);
						}
						else {
							// Change the address to uppercase
							for (int x = 0; x < strlen(login.add.houseNo); x++) {
								login.add.houseNo[x] = toupper(login.add.houseNo[x]);
							}
							for (int x = 0; x < strlen(login.add.streetNo); x++) {
								login.add.streetNo[x] = toupper(login.add.streetNo[x]);
							}
							for (int x = 0; x < strlen(login.add.city); x++) {
								login.add.city[x] = toupper(login.add.city[x]);
							}
							for (int x = 0; x < strlen(login.add.state); x++) {
								login.add.state[x] = toupper(login.add.state[x]);
							}

							if (strcmp(login.add.state, "PERLIS") != 0 && strcmp(login.add.state, "PULAU PINANG") != 0 && strcmp(login.add.state, "KEDAH") != 0 && strcmp(login.add.state, "KELANTAN") != 0 &&
								strcmp(login.add.state, "PERAK") != 0 && strcmp(login.add.state, "PAHANG") != 0 && strcmp(login.add.state, "TERENGGANU") != 0 && strcmp(login.add.state, "SELANGOR") != 0 &&
								strcmp(login.add.state, "NEGERI SEMBILAN") != 0 && strcmp(login.add.state, "MELAKA") != 0 && strcmp(login.add.state, "JOHOR") != 0 && strcmp(login.add.state, "SABAH") != 0 && strcmp(login.add.state, "SARAWAK") != 0) {

								red();
								printf("\nError message: The state in invalid.");
								Sleep(1500);
								sysColor();
								output2(detail[i]);
							}
							else {
								strcpy(detail[i].add.houseNo, login.add.houseNo);
								strcpy(detail[i].add.streetNo, login.add.streetNo);
								strcpy(detail[i].add.postCode, login.add.postCode);
								strcpy(detail[i].add.city, login.add.city);
								strcpy(detail[i].add.state, login.add.state);
								output2(login);
							}
						}
					}
					rewind(stdin);
				}
				else if (option2 == '6') {
					red();
					printf("\nError message: Upline cannot be modified.");
					Sleep(1500);
					sysColor();
					output2(login);
				}
				else if (option2 == '7') {
					//do {
					printf("\nPlease give the password to open the permission: ");
					scanf("%[^\n]", detail[i].password);
					rewind(stdin);

					do {
						printf("\nEnter your decryption key: ");
						if (!scanf("%d", &detail[i].key)) {
							rewind(stdin);
							red();
							printf("\nError message: Only digit is accepted.");
							Sleep(1500);
							sysColor();
							output2(login);
							printf("Enter the detail that you want to edit (X - exit): %c\n\n", option2);
							printf("Please give the password to open the permission: %s\n", detail[i].password);
						}
						else {
							rewind(stdin);
							break;
						}
					} while (1);

					if (strcmp(detail[i].encrypted_password, password_encryption(detail[i])) == 0) {
						strcpy(decrypted_password, password_decryption(detail[i], detail[i].encrypted_password));
						printf("\nPassword: %s\n\n", decrypted_password);

						do {
							printf("New password: ");
							scanf("%[^\n]", login.password);
							rewind(stdin);
							password_status = password_validation(login);
							if (password_status == 0) {
								output2(login);
								printf("Enter the detail that you want to edit (X - exit): %c\n\n", option2);
								printf("Please give the password to open the permission: %s\n\n", detail[i].password);
								printf("Enter your decryption key: %d\n\n", detail[i].key);
								printf("Password: %s\n\n", decrypted_password);
							}
						} while (password_status == 0);

						do {
							printf("\nEnter a new key (Please remember it!!!): ");
							if (!scanf("%d", &login.key)) {
								red();
								printf("\nError message: Only digit is accepted.");
								Sleep(1500);
								sysColor();
								output2(login);
								printf("Enter the detail that you want to edit (X - exit): %c\n\n", option2);
								printf("Please give the password to open the permission: %s\n\n", detail[i].password);
								printf("Enter your decryption key: %d\n\n", detail[i].key);
								printf("Password: %s\n\n", decrypted_password);
								printf("New password: %s\n", login.password);
							}
							else if (login.key < 0) {
								red();
								printf("\nError message: Encryption key cannot be nagative value.");
								Sleep(1500);
								sysColor();
								output2(login);
								printf("Enter the detail that you want to edit (X - exit): %c\n\n", option2);
								printf("Please give the password to open the permission: %s\n\n", detail[i].password);
								printf("Enter your decryption key: %d\n\n", detail[i].key);
								printf("Password: %s\n\n", decrypted_password);
								printf("New password: %s\n", login.password);
							}
							else {
								rewind(stdin);
								break;
							}
							rewind(stdin);
						} while (1);

						strcpy(login.encrypted_password, password_encryption(login));
						output2(login);
					}
					else {
						red();
						printf("\nError message: Unable to get permission! Please check your password and decryption key.");
						Sleep(1500);
						sysColor();
						output2(login);
					}
					//} while (password_status == 0);
				}
				else if (option2 == 'X') {
					do {
						printf("\nDo you want to save your changes? (Y - Yes, N - No): ");
						scanf("%c", &option3);
						option3 = toupper(option3);
						rewind(stdin);

						if (option3 == 'Y') {
							printf("\nSaving");
							searching_animation();
							strcpy(detail[i].username, login.username);
							strcpy(detail[i].gender, login.gender);
							strcpy(detail[i].IC, login.IC);
							strcpy(detail[i].email, login.email);
							strcpy(detail[i].add.houseNo, login.add.houseNo);
							strcpy(detail[i].add.streetNo, login.add.streetNo);
							strcpy(detail[i].add.postCode, login.add.postCode);
							strcpy(detail[i].add.city, login.add.city);
							strcpy(detail[i].add.state, login.add.state);
							strcpy(detail[i].upline, login.upline);
							strcpy(detail[i].encrypted_password, login.encrypted_password);
							strcpy(detail[i].account_available, login.account_available);
							detail[i].time.sec = login.time.sec;
							break;
						}
						else if (option3 == 'N') {
							strcpy(login.username, storage.username);
							strcpy(detail[i].username, storage.username);
							strcpy(detail[i].gender, storage.gender);
							strcpy(detail[i].IC, storage.IC);
							strcpy(detail[i].email, storage.email);
							strcpy(detail[i].add.houseNo, storage.add.houseNo);
							strcpy(detail[i].add.streetNo, storage.add.streetNo);
							strcpy(detail[i].add.postCode, storage.add.postCode);
							strcpy(detail[i].add.city, storage.add.city);
							strcpy(detail[i].add.state, storage.add.state);
							strcpy(detail[i].upline, storage.upline);
							strcpy(detail[i].encrypted_password, storage.encrypted_password);
							strcpy(detail[i].account_available, storage.account_available);
							detail[i].time.sec = storage.time.sec;
							break;
						}
						else {
							red();
							printf("\nError message: Invalid input.");
							Sleep(1500);
							sysColor();
							output2(login);
							printf("Enter the detail that you want to edit (X - exit): %c\n", option2);
						}

					} while (option3 != 'Y' && option3 != 'N');

					system("cls");
					break;
				}
				else {
					red();
					printf("\nError message: Invalid input.");
					Sleep(1500);
					sysColor();
					system("cls");
					output2(detail[i]);
				}

			} while (option2 != 'X');

			i++;
			continue;
		}
		i++;
	}

	fclose(fptr1);

	// Rewrite the file
	FILE* fptr2;
	fptr2 = fopen("member.txt", "w");

	if (fptr2 == NULL) {
		printf("Error Opening File!\n");
		exit(-1);
	}

	for (int k = 0; k < i; k++) {
		fprintf(fptr2, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", detail[k].member_ID, detail[k].username, detail[k].gender, detail[k].IC, detail[k].email, &detail[k].add.houseNo, &detail[k].add.streetNo, &detail[k].add.postCode, &detail[k].add.city, &detail[k].add.state, detail[k].upline, detail[k].encrypted_password, detail[k].question, detail[k].answer, detail[k].account_available, detail[k].time.sec);
	}

	fclose(fptr2);

	return login.username;
}

int forget_password() {
	struct Member login[100];
	char email[100], answer[100], temp_email[100];
	int option, i = 0, exit_status = 0;
	bool email_found, reset_status = false;

	FILE* fptr;
	fptr = fopen("member.txt", "r");

	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	do {
		printf("Forget Password\n\n");
		printf("Enter your email address (X - Back): ");
		scanf("%[^\n]", email);
		rewind(stdin);

		for (int i = 0; i < strlen(email); i++) {
			temp_email[i] = toupper(email[i]);
		}
		temp_email[strlen(email)] = '\0';

		if (strcmp(temp_email, "X") == 0) {
			exit_status = 1;
			email_found = true;
		}
		else {
			exit_status = 0;
			email_found = false;
		}

		if (exit_status == 0) {
			printf("\n");

			rewind(fptr);
			while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login[i].member_ID, &login[i].username, &login[i].gender, &login[i].IC, &login[i].email, &login[i].add.houseNo, &login[i].add.streetNo, &login[i].add.postCode, &login[i].add.city, &login[i].add.state, &login[i].upline, &login[i].encrypted_password, &login[i].question, &login[i].answer, &login[i].account_available, &login[i].time.sec) != EOF) {
				if (strcmp(email, login[i].email) == 0) {
					email_found = true;
					printf("Searching");
					searching_animation();
					system("cls");

					do {
						option = security_question();
						printf("\nEnter your answer: ");
						scanf("%[^\n]", answer);
						rewind(stdin);

						if (strlen(answer) <= 0 || strlen(answer) > 100) {
							red();
							printf("\nError message: The length of answer must between 1 - 100 character(s).");
							Sleep(1500);
							system("cls");
							sysColor();

						}
						else {
							if (strcmp(answer, login[i].answer) == 0 && option == login[i].question) {
								// password reset
								reset_status = true;
								printf("\nSearching");
								searching_animation();
								printf("We will jump to the reset password page after a while");
								searching_animation();
								system("cls");
								strcpy(login[i].encrypted_password, password_reset());
								printf("\n\nPassword reset successfully!!!.\n\n");
							}
							else {
								printf("\nSearching");
								searching_animation();
								red();
								printf("Error message: The security question or/and the answer is/are wrong!.");
								Sleep(1500);
								system("cls");
								sysColor();
							}
						}

					} while (strlen(answer) <= 0 || strlen(answer) > 100 || reset_status == false);

					i++;
					continue;
				}
				i++;
			}
			if (email_found == false) {
				printf("Searching");
				searching_animation();
				red();
				printf("Error message: Cannot find the email.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
	} while (email_found == false);

	fclose(fptr);

	if (exit_status == 0) {
		// Rewrite the file
		exit_status = 1;
		FILE* fptr2;
		fptr2 = fopen("member.txt", "w");

		if (fptr2 == NULL) {
			printf("Error Opening File!\n");
			exit(-1);
		}

		for (int k = 0; k < i; k++) {
			fprintf(fptr2, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", login[k].member_ID, login[k].username, login[k].gender, login[k].IC, login[k].email, &login[k].add.houseNo, &login[k].add.streetNo, &login[k].add.postCode, &login[k].add.city, &login[k].add.state, login[k].upline, login[k].encrypted_password, login[k].question, login[k].answer, login[k].account_available, login[k].time.sec);
		}

		fclose(fptr2);
	}
	return exit_status;
}

char* password_reset() {
	struct Member info;
	int password_status, confirmPsd_status;

	// Password Validation
	int i = 0, j, count = 0;
	char tempPsw;

	printf("Password Reset\n\n");
	printf("Enter the new password: ");
	do {
		do {
			tempPsw = getch();
			printf("%c", tempPsw);
			Sleep(100);
			system("cls");
			if (tempPsw == '\b') {
				if (count > 0) {
					count--;
				}
				else
					count = 0;
			}
			else if (tempPsw == '\r') {
				break;
			}
			else {
				info.password[i] = tempPsw;
				count++;
			}
			printf("Password Reset\n\n");
			printf("Enter the new password: ");
			for (i = 0; i < count; i++) {
				printf("*");
			}
		} while (tempPsw != 13);

		info.password[i] = '\0';
		printf("Password Reset\n\n");
		printf("Enter the new password: ");
		for (i = 0; i < count; i++) {
			printf("*");
		}

		password_status = password_validation(info);

		printf("Password Reset\n\n");
		printf("Enter the new password: ");
		for (i = 0; i < count; i++) {
			printf("*");
		}

	} while (password_status == 0);

	system("cls");
	printf("Password Reset\n\n");
	printf("Enter the new password: ");
	for (j = 0; j < count; j++) {
		printf("*");
	}

	do {
		printf("\n\nEnter a new key (Please remember it!!!): ");
		if (!scanf("%d", &info.key)) {
			red();
			printf("\nError message: Only digit is accepted.");
			Sleep(1500);
			sysColor();
			system("cls");
			printf("Password Reset\n\n");
			printf("Enter the new password: ");
			for (j = 0; j < count; j++) {
				printf("*");
			}
		}
		else if (info.key < 0) {
			red();
			printf("\nError message: Encryption key cannot be negative value.");
			Sleep(1500);
			sysColor();
			system("cls");
			printf("Password Reset\n\n");
			printf("Enter the new password: ");
			for (j = 0; j < count; j++) {
				printf("*");
			}
		}
		else {
			rewind(stdin);
			break;
		}
		rewind(stdin);
	} while (info.key != isdigit);

	// Confirm Password Validation
	count = 0;
	int k = 0;
	char tempConPsw;

	printf("\nConfirm password: ");

	do {
		do {
			tempConPsw = getch();
			printf("%c", tempConPsw);
			Sleep(100);
			system("cls");
			if (tempConPsw == '\b') {
				if (count > 0) {
					count--;
				}
				else
					count = 0;
			}
			else if (tempConPsw == '\r') {
				break;
			}
			else {
				info.password_confirm[k] = tempConPsw;
				count++;
			}

			printf("Password Reset\n\n");
			printf("Enter the new password: ");
			for (i = 0; i < strlen(info.password); i++) {
				printf("*");
			}
			printf("\n\nEnter a key (Please remember it!!!): %d\n\n", info.key);
			printf("Confirm password: ");
			for (k = 0; k < count; k++) {
				printf("*");
			}

		} while (tempConPsw != 13);

		info.password_confirm[k] = '\0';

		printf("Password Reset\n\n");
		printf("Enter the new password: ");
		for (i = 0; i < strlen(info.password); i++) {
			printf("*");
		}
		printf("\n\nEnter a key (Please remember it!!!): %d\n\n", info.key);
		printf("Confirm password: ");
		for (i = 0; i < strlen(info.password_confirm); i++) {
			printf("*");
		}
		printf("\n\n");

		confirmPsd_status = confirm_password(info);

		printf("Password Reset\n\n");
		printf("Enter the new password: ");
		for (i = 0; i < strlen(info.password); i++) {
			printf("*");
		}
		printf("\n\nEnter a key (Please remember it!!!): %d\n\n", info.key);
		printf("Confirm password: ");
		for (i = 0; i < strlen(info.password_confirm); i++) {
			printf("*");
		}

	} while (confirmPsd_status == 0);

	// Password Encryption
	strcpy(info.encrypted_password, password_encryption(info));

	return info.encrypted_password;
}

int view_product(char username[100]) {
	struct Member login;
	StockItem prod[1000];
	char opt[20], upline[100], filename[100];
	int i, product_status = 0;

	FILE* fptr1;
	fptr1 = fopen("member.txt", "r");

	if (fptr1 == NULL) {
		printf("Error opening file!\n");
		exit(-1);
	}

	while (fscanf(fptr1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &login.member_ID, &login.username, &login.gender, &login.IC, &login.email, &login.add.houseNo, &login.add.streetNo, &login.add.postCode, &login.add.city, &login.add.state, &login.upline, &login.encrypted_password, &login.question, &login.answer, &login.account_available, &login.time.sec) != EOF) {
		if (strcmp(username, login.username) == 0) {
			strcpy(upline, login.upline);
		}
	}

	fclose(fptr1);

	do {
		i = 0;

		FILE* fptr2;

		if (strcmp(upline, "N/A") == 0) {
			fptr2 = fopen("stock.txt", "r");
		}
		else {
			sprintf(filename, "%s.txt", upline);
			fptr2 = fopen(filename, "r");
		}

		if (fptr2 == NULL) {
			printf("Error opening file!\n");
			exit(-1);
		}

		printf("Product List\n\n");
		printf("----------------------------------------------------------------------------------------------\n");
		printf("| Code   | Description                         | Unit Price (RM)      | Available Quantity   |\n");
		printf("----------------------------------------------------------------------------------------------\n");

		while (fscanf(fptr2, "%[^|]|%[^|]|%f|%d|%d|%d\n", &prod[i].item_code, &prod[i].item_description, &prod[i].item_price, &prod[i].item_quantity, &prod[i].minimum_level, &prod[i].reorder_quantity) != EOF) {
			printf("| %-6s | %-35s | %-20.2f | %-20d |\n", prod[i].item_code, prod[i].item_description, prod[i].item_price, prod[i].item_quantity);
			printf("----------------------------------------------------------------------------------------------\n");
			i++;
		}

		fclose(fptr2);

		printf("Do you want to search product or purchase product? (X - Back)\n");
		printf("1. Search product\n");
		printf("2. Purchase product\n\n");
		printf("Enter your selection: ");
		scanf("%[^\n]", opt);
		rewind(stdin);

		for (int i = 0; i < strlen(opt); i++) {
			opt[i] = toupper(opt[i]);
		}

		if (strcmp(opt, "1") == 0) {
			system("cls");
			product_status = search_product(prod, prod, i, i, username);
		}
		else if (strcmp(opt, "2") == 0) {
			system("cls");
			product_status = purchase_product(prod, prod, i, i, username);
		}
		else if (strcmp(opt, "X") == 0) {
			product_status = 1;
			break;
		}
		else {
			red();
			printf("\nError message: Invalid input.");
			Sleep(1500);
			system("cls");
			sysColor();
		}

	} while (strcmp(opt, "1") != 0 && strcmp(opt, "2") != 0);

	return product_status;
}

int search_product(StockItem prod[1000], StockItem prodSearch[1000], int count, int m, char username[100]) {
	StockItem prodSearched[1000];
	char search[50], opt[20];
	int search_status = 0, product_status = 0, s = 0;

	printf("Product List\n\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("| Code   | Description                         | Unit Price (RM)      | Available Quantity   |\n");
	printf("----------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < m; i++) {
		printf("| %-6s | %-35s | %-20.2f | %-20d |\n", prodSearch[i].item_code, prodSearch[i].item_description, prodSearch[i].item_price, prodSearch[i].item_quantity);
		printf("----------------------------------------------------------------------------------------------\n");
	}

	if (m == 0) {
		printf("                                     Not product found!                                      |\n");
		printf("----------------------------------------------------------------------------------------------\n");
	}

	printf("\nEnter the product code or description that you want to search: ");
	scanf("%[^\n]", search);
	rewind(stdin);

	for (int k = 0; k < strlen(search); k++) {
		search[k] = toupper(search[k]);
	}
	system("cls");

	do {
		printf("Product List\n\n");
		printf("----------------------------------------------------------------------------------------------\n");
		printf("| Code   | Description                         | Unit Price (RM)      | Available Quantity   |\n");
		printf("----------------------------------------------------------------------------------------------\n");

		for (int q = 0; q < count; q++) {
			char temp_desc[100];

			strcpy(temp_desc, prod[q].item_description);

			for (int k = 0; k < strlen(temp_desc); k++) {
				temp_desc[k] = toupper(temp_desc[k]);
			}

			if (strstr(prod[q].item_code, search) != NULL || strstr(temp_desc, search) != NULL) {
				// Record the searched product
				strcpy(prodSearched[s].item_code, prod[q].item_code);
				strcpy(prodSearched[s].item_description, prod[q].item_description);
				prodSearched[s].item_price = prod[q].item_price;
				prodSearched[s].item_quantity = prod[q].item_quantity;
				s++;

				search_status = 1;
				printf("| %-6s | %-35s | %-20.2f | %-20d |\n", prod[q].item_code, prod[q].item_description, prod[q].item_price, prod[q].item_quantity);
				printf("----------------------------------------------------------------------------------------------\n");
			}
		}
		if (search_status == 0) {
			printf("                                     Not product found!                                      |\n");
			printf("----------------------------------------------------------------------------------------------\n");
		}

		printf("Do you want to search product or purchase product? (X - Back)\n");
		printf("1. Search product\n");
		printf("2. Purchase product\n\n");
		printf("Enter your selection: ");
		scanf("%[^\n]", opt);
		rewind(stdin);

		for (int i = 0; i < strlen(opt); i++) {
			opt[i] = toupper(opt[i]);
		}

		if (strcmp(opt, "1") == 0) {
			system("cls");
			product_status = search_product(prod, prodSearched, count, s, username);
		}
		else if (strcmp(opt, "2") == 0) {
			system("cls");
			product_status = purchase_product(prod, prodSearched, count, s, username);
		}
		else if (strcmp(opt, "X") == 0) {
			product_status = 1;
			break;
		}
		else {
			red();
			printf("\nError message: Invalid input.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	} while (strcmp(opt, "1") != 0 && strcmp(opt, "2") != 0);

	return product_status;
}

int purchase_product(StockItem prod[1000], StockItem prodSearched[1000], int count, int m, char username[100]) {
	char prodPurchase[5], opt;
	int qty = 1, prod_status = 0, record, qty_status = 1, back = 0;

	struct Member read;

	do {
		do {
			opt = '1';
			printf("Product List\n\n");
			printf("----------------------------------------------------------------------------------------------\n");
			printf("| Code   | Description                         | Unit Price (RM)      | Available Quantity   |\n");
			printf("----------------------------------------------------------------------------------------------");

			for (int i = 0; i < m; i++) {
				printf("\n| %-6s | %-35s | %-20.2f | %-20d |\n", prodSearched[i].item_code, prodSearched[i].item_description, prodSearched[i].item_price, prodSearched[i].item_quantity);
				printf("----------------------------------------------------------------------------------------------");
			}

			if (m == 0) {
				printf("\n                                     Not product found!                                      |\n");
				printf("----------------------------------------------------------------------------------------------");
			}

			printf("\n\nEnter the product code that you want to buy (X - Stop): ");
			scanf("%[^\n]", prodPurchase);
			rewind(stdin);
			printf("\n");

			for (int i = 0; i < strlen(prodPurchase); i++) {
				prodPurchase[i] = toupper(prodPurchase[i]);
			}

			for (int i = 0; i < count; i++) {
				if (strcmp(prodPurchase, prod[i].item_code) == 0) {
					prod_status = 2;
					record = i;
					break;
				}
				else if (strcmp(prodPurchase, "X") == 0) {
					prod_status = 1;
					break;
				}
				else {
					prod_status = 0;
				}
			}

			if (prod_status == 0) {
				red();
				printf("Error message: The product code you entered is invalid.\n");
				Sleep(1500);
				system("cls");
				sysColor();
			}

		} while (prod_status == 0);

		if (prod_status == 2) {
			do {
				if (qty != 1 || qty_status == 0) {
					printf("Product List\n\n");
					printf("----------------------------------------------------------------------------------------------\n");
					printf("| Code   | Description                         | Unit Price (RM)      | Available Quantity   |\n");
					printf("----------------------------------------------------------------------------------------------");

					for (int i = 0; i < m; i++) {
						printf("\n| %-6s | %-35s | %-20.2f | %-20d |\n", prodSearched[i].item_code, prodSearched[i].item_description, prodSearched[i].item_price, prodSearched[i].item_quantity);
						printf("----------------------------------------------------------------------------------------------\n");
					}

					if (m == 0) {
						printf("\n                                     Not product found!                                      |\n");
						printf("----------------------------------------------------------------------------------------------");
					}

					printf("\n\nEnter the product code that you want to buy (X - Stop): %s\n\n", prodPurchase);
				}
				printf("Enter the quantity of the product: ");
				if (!scanf("%d", &qty)) {
					qty_status = 0;
					red();
					printf("\nError message: Invalid input. Please enter an integer.");
					Sleep(1500);
					system("cls");
					sysColor();
				}
				else {
					rewind(stdin);
					if (qty > prod[record].item_quantity) {
						red();
						printf("\nError message: Insufficient stock quantity.");
						Sleep(1500);
						system("cls");
						sysColor();
					}
					else if (qty <= 0) {
						red();
						printf("\nError message: Invalid quantity entered. Quantity must be greater than 0.");
						Sleep(1500);
						system("cls");
						sysColor();
					}
					else {
						qty_status = 1;
						break;
					}
				}
				rewind(stdin);
			} while (1);

			printf("\n");

			do {
				if (opt != '1' || back == 1) {
					back = 0;
					printf("Product List\n\n");
					printf("----------------------------------------------------------------------------------------------\n");
					printf("| Code   | Description                         | Unit Price (RM)      | Available Quantity   |\n");
					printf("----------------------------------------------------------------------------------------------");

					for (int i = 0; i < m; i++) {
						printf("\n| %-6s | %-35s | %-20.2f | %-20d |\n", prodSearched[i].item_code, prodSearched[i].item_description, prodSearched[i].item_price, prodSearched[i].item_quantity);
						printf("----------------------------------------------------------------------------------------------\n");
					}

					if (m == 0) {
						printf("\n                                     Not product found!                                      |\n");
						printf("----------------------------------------------------------------------------------------------");
					}

					printf("\n\nEnter the product code that you want to buy (X - Stop): %s\n\n", prodPurchase);
					printf("Enter the quantity of the product: %d\n\n", qty);
				}
				printf("Do you want to buy now or add to cart?\n");
				printf("1. Buy Now\n");
				printf("2. Add to Cart\n\n");
				printf("Enter your selection: ");
				scanf("%c", &opt);
				rewind(stdin);

				if (opt == '1') {
					// Buy Now
					FILE* fptr;

					fptr = fopen("member.txt", "r");
					if (fptr == NULL) {
						printf("Error opening file.\n");
						exit(-1);
					}

					while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &read.member_ID, &read.username, &read.gender, &read.IC, &read.email, &read.add.houseNo, &read.add.streetNo, &read.add.postCode, &read.add.city, &read.add.state, &read.upline, &read.encrypted_password, &read.question, &read.answer, &read.account_available, &read.time.sec) != EOF) {
						if (strcmp(username, read.username) == 0) {
							back = buyNow(prod[record].item_code, prod[record].item_description, qty, prod[record].item_price, read.member_ID);
						}
					}

					fclose(fptr);

					if (back) {
						continue;
					}

					break;
				}
				else if (opt == '2') {
					// Add to cart
					FILE* fptr;

					fptr = fopen("member.txt", "r");
					if (fptr == NULL) {
						printf("Error opening file.\n");
						exit(-1);
					}

					while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &read.member_ID, &read.username, &read.gender, &read.IC, &read.email, &read.add.houseNo, &read.add.streetNo, &read.add.postCode, &read.add.city, &read.add.state, &read.upline, &read.encrypted_password, &read.question, &read.answer, &read.account_available, &read.time.sec) != EOF) {
						if (strcmp(username, read.username) == 0) {
							shoppingCart(prod[record].item_code, prod[record].item_description, qty, prod[record].item_price, read.member_ID);
						}
					}
					fclose(fptr);
					printf("\nThis product has been added to the cart.");
					searching_animation();
					system("cls");
					qty = 1, prod_status = 0, qty_status = 1;
				}
				else {
					red();
					printf("\nError message: Invalid input.");
					Sleep(1500);
					system("cls");
					sysColor();
				}
			} while ((opt != '1' && opt != '2') || back == 1);
		}
	} while (strcmp(prodPurchase, "X") != 0 && opt != '1');

	return prod_status;
}

int view_stock(char username[100]) {
	StockItem prod;
	char opt[20], filename[100];
	int product_status = 0;

	do {
		FILE* fptr;

		sprintf(filename, "%s.txt", username);
		fptr = fopen(filename, "r");

		if (fptr == NULL) {
			printf("Error opening file!\n");
			exit(-1);
		}

		printf("Stock List\n\n");
		printf("----------------------------------------------------------------------------------------------\n");
		printf("| Code   | Description                         | Unit Price (RM)      | Available Quantity   |\n");
		printf("----------------------------------------------------------------------------------------------\n");

		while (fscanf(fptr, "%[^|]|%[^|]|%f|%d|%d|%d\n", &prod.item_code, &prod.item_description, &prod.item_price, &prod.item_quantity, &prod.minimum_level, &prod.reorder_quantity) != EOF) {
			printf("| %-6s | %-35s | %-20.2f | %-20d |\n", prod.item_code, prod.item_description, prod.item_price, prod.item_quantity);
			printf("----------------------------------------------------------------------------------------------\n");
		}

		fclose(fptr);

		printf("\nPress X to back: ");
		scanf("%[^\n]", opt);
		rewind(stdin);

		for (int i = 0; i < strlen(opt); i++) {
			opt[i] = toupper(opt[i]);
		}

		if (strcmp(opt, "X") == 0) {
			product_status = 1;
			break;
		}
		else {
			red();
			printf("\nError message: Invalid input.");
			Sleep(1500);
			system("cls");
			sysColor();
			product_status = 0;
		}
	} while (product_status == 0);

	return product_status;
}

void output2(struct Member info) {
	system("cls");
	printf("Edit Profile:\n\n");
	printf("1. Name              :  %s\n", info.username);
	printf("2. Gender            :  %s\n", info.gender);
	printf("3. IC Number         :  %s\n", info.IC);
	printf("4. Email             :  %s\n", info.email);
	printf("5. Current Address   :  %s, %s, %s %s, %s\n", info.add.houseNo, info.add.streetNo, info.add.postCode, info.add.city, info.add.state);
	printf("6. Upline            :  %s\n", info.upline);
	printf("7. Password          :  ");
	for (int i = 0; i < strlen(info.encrypted_password); i++) {
		printf("*");
	}
	printf("\n\n");
}

void red() {
	printf("\033[1;31m");
}

void searching_animation() {
	for (int q = 0; q < 3; q++) {
		Sleep(500);
		printf(".");
	}
	printf("\n\n");
	Sleep(500);
}

void purple() {
	printf("\033[1;35m");
}

void cyan() {
	printf("\033[0;36m");
}

void bear() {
	sysColor();
	cyan();
	printf("			                     ,---.           ,---.\n");
	printf("			                    / /\"`\\.--\"\"\"--./,'\"\\ \\\n");
	printf("			                    \\ \\    _       _    / /\n");
	printf("			                     `./  / __   __ \\  \\,'\n");
	printf("			                      /    /_O)_(_O\\    \\\n");
	printf("			                      |  .-'  ___  `-.  |\n");
	printf("			                   .--|       \\_/       |--.\n");
	printf("			                 ,'    \\   \\   |   /   /    `.\n");
	printf("			                /       `.  `--^--'  ,'       \\\n");
	printf("			             .-\"\"\"\"\"\"-.    `--.___.--'     .-\"\"\"\"\"\"-.\n");
	printf("			.-----------/         \\------------------/         \\--------------.\n");
	printf("			| .---------\\         /----------------- \\         /------------. |\n");
	printf("			| |          `-`--`--'                    `--'--'-'             | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |");
	congratulations();
	cyan();
	printf("	                | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |");
	message1();
	cyan();
	printf("               | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |");
	message2();
	cyan();
	printf("		        | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |                                                             | |\n");
	printf("			| |_____________________________________________________________| |\n");
	printf("			|_________________________________________________________________|\n");
	printf("			                   )__________|__|__________(\n");
	printf("			                  |            ||            |\n");
	printf("			                  |____________||____________|\n");
	printf("			                    ),-----.(      ),-----.(\n");
	printf("			                  ,'   ==.   \\    /  .==    `.\n");
	printf("			                 /            )  (            \\\n");
	printf("			                 `===========\'    `===========\'\n");
}

void congratulations() {
	purple();
	printf("                     C"); Sleep(70);
	printf("O"); Sleep(70);
	printf("N"); Sleep(70);
	printf("G"); Sleep(70);
	printf("R"); Sleep(70);
	printf("A"); Sleep(70);
	printf("T"); Sleep(70);
	printf("U"); Sleep(70);
	printf("L"); Sleep(70);
	printf("A"); Sleep(70);
	printf("T"); Sleep(70);
	printf("I"); Sleep(70);
	printf("O"); Sleep(70);
	printf("N"); Sleep(70);
	printf("S"); Sleep(70);
	printf("!"); Sleep(70);
}

void message1() {
	purple();
	printf("              Y"); Sleep(70);
	printf("o"); Sleep(70);
	printf("u "); Sleep(70);
	printf("h"); Sleep(70);
	printf("a"); Sleep(70);
	printf("v"); Sleep(70);
	printf("e "); Sleep(70);
	printf("s"); Sleep(70);
	printf("u"); Sleep(70);
	printf("c"); Sleep(70);
	printf("c"); Sleep(70);
	printf("e"); Sleep(70);
	printf("s"); Sleep(70);
	printf("s"); Sleep(70);
	printf("f"); Sleep(70);
	printf("u"); Sleep(70);
	printf("l"); Sleep(70);
	printf("l"); Sleep(70);
	printf("y "); Sleep(70);
	printf("s"); Sleep(70);
	printf("i"); Sleep(70);
	printf("g"); Sleep(70);
	printf("n"); Sleep(70);
	printf("e"); Sleep(70);
	printf("d "); Sleep(70);
	printf("u"); Sleep(70);
	printf("p"); Sleep(70);
	printf("."); Sleep(70);
}

void message2() {
	purple();
	printf("                  W"); Sleep(70);
	printf("e"); Sleep(70);
	printf("l"); Sleep(70);
	printf("c"); Sleep(70);
	printf("o"); Sleep(70);
	printf("m"); Sleep(70);
	printf("e "); Sleep(70);
	printf("t"); Sleep(70);
	printf("o "); Sleep(70);
	printf("o"); Sleep(70);
	printf("u"); Sleep(70);
	printf("r "); Sleep(70);
	printf("c"); Sleep(70);
	printf("o"); Sleep(70);
	printf("m"); Sleep(70);
	printf("p"); Sleep(70);
	printf("a"); Sleep(70);
	printf("n"); Sleep(70);
	printf("y"); Sleep(70);
	printf("!"); Sleep(70);
}

void deleteMember() {

	sysColor();

	char opt[50];
	int ban_status = 0, restore_status = 0;

	do {
		printf("Do you want to view member list or banned list?\n");
		printf("1. Member List\n");
		printf("2. Banned List\n");
		printf("3. Exit\n\n");
		printf("Enter your selection: ");
		scanf("%[^\n]", &opt);
		rewind(stdin);


		if (strcmp(opt, "1") == 0) {
			system("cls");
			ban_status = view_memberlist();
		}
		else if (strcmp(opt, "2") == 0) {
			system("cls");
			restore_status = view_bannedlist();
		}
		else if (strcmp(opt, "3") == 0) {
			return 0;
		}
		else {
			red();
			printf("\n\aError message: Invalid input.");
			Sleep(1500);
			system("cls");
			sysColor();
		}
	} while ((strcmp(opt, "1") != 0 && strcmp(opt, "2") != 0) || (ban_status == 1 || restore_status == 1));
}

int view_memberlist() {
	struct Member read[1000];
	int i, ban_status = 0;

	do {
		i = 0;

		FILE* fptr;
		fptr = fopen("member.txt", "r");

		if (fptr == NULL) {
			printf("Error Opening File!\n");
			exit(-1);
		}

		printf("Member List\n\n");
		printf("---------------------------------------------------------------------------------------------------------------------------------\n");
		printf("| ID    | Username             | Gender | IC Number      | Email Address             | Upline               | Account Available |\n");
		printf("---------------------------------------------------------------------------------------------------------------------------------\n");

		while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &read[i].member_ID, &read[i].username, &read[i].gender, &read[i].IC, &read[i].email, &read[i].add.houseNo, &read[i].add.streetNo, &read[i].add.postCode, &read[i].add.city, &read[i].add.state, &read[i].upline, &read[i].encrypted_password, &read[i].question, &read[i].answer, &read[i].account_available, &read[i].time.sec) != EOF) {
			printf("| %-5s | %-20s |   %s    | %s | %-25s | %-20s | %-17s |\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].upline, read[i].account_available);
			printf("---------------------------------------------------------------------------------------------------------------------------------\n");
			i++;
		}

		fclose(fptr);

		ban_status = delete_member(read, i);

	} while (ban_status == 0);

	return ban_status;
}

int delete_member(struct Member read[1000], int count) {
	char memberID[6], sure[50];
	int member_status = 1, ban_status = 0, record = 0;

	do {
		if (member_status == 0 || member_status == 2) {
			printf("Member List\n\n");
			printf("---------------------------------------------------------------------------------------------------------------------------------\n");
			printf("| ID    | Username             | Gender | IC Number      | Email Address             | Upline               | Account Available |\n");
			printf("---------------------------------------------------------------------------------------------------------------------------------\n");

			for (int i = 0; i < count; i++) {
				printf("| %-5s | %-20s |   %s    | %s | %-25s | %-20s | %-17s |\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].upline, read[i].account_available);
				printf("---------------------------------------------------------------------------------------------------------------------------------\n");
			}
		}
		printf("\nEnter the member ID that you want to move to banned list (X - Back): ");
		scanf("%[^\n]", memberID);
		rewind(stdin);

		for (int i = 0; i < strlen(memberID); i++) {
			memberID[i] = toupper(memberID[i]);
		}

		if (strcmp(memberID, "X") == 0) {
			member_status = 3;
			ban_status = 1;
			system("cls");
			break;
		}
		else {
			for (int i = 0; i < count; i++) {
				if (strcmp(memberID, read[i].member_ID) == 0) {
					if (strcmp(read[i].upline, "N/A") != 0) {
						member_status = 1;
						record = i;
						break;
					}
					else {
						member_status = 2;
						break;
					}
				}
				else {
					member_status = 0;
				}
			}

			if (member_status == 0) {
				red();
				printf("\n\aError message: The member ID you entered is invalid.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
			else if (member_status == 2) {
				red();
				printf("\n\aError message: You do not have permission to move upline to the banned list.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
	} while (member_status == 0 || member_status == 2);

	if (member_status == 1) {
		do {
			if (member_status == 0) {
				printf("Member List\n\n");
				printf("---------------------------------------------------------------------------------------------------------------------------------\n");
				printf("| ID    | Username             | Gender | IC Number      | Email Address             | Upline               | Account Available |\n");
				printf("---------------------------------------------------------------------------------------------------------------------------------\n");

				for (int i = 0; i < count; i++) {
					printf("| %-5s | %-20s |   %s    | %s | %-25s | %-20s | %-17s |\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].upline, read[i].account_available);
					printf("---------------------------------------------------------------------------------------------------------------------------------\n");
				}
				printf("\nEnter the member ID that you want to move to banned list (X - Back): %s\n", memberID);
			}

			printf("\nAre you sure you want to move this member to the banned list? (Y - Sure, N - Not Sure): ");
			scanf("%[^\n]", &sure);
			rewind(stdin);

			sure[0] = toupper(sure[0]);

			if (strcmp(sure, "Y") == 0) {
				FILE* fptr;
				fptr = fopen("member.txt", "w");

				FILE* fptr2;
				fptr2 = fopen("bannedlist.txt", "a");

				if (fptr == NULL || fptr2 == NULL) {
					printf("Error opening file.\n");
					exit(-1);
				}

				for (int i = 0; i < count; i++) {
					if (strcmp(read[i].member_ID, read[record].member_ID) != 0) {
						fprintf(fptr, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].add.houseNo, read[i].add.streetNo, read[i].add.postCode, read[i].add.city, read[i].add.state, read[i].upline, read[i].encrypted_password, read[i].question, read[i].answer, read[i].account_available, read[i].time.sec);
					}
					else {
						fprintf(fptr2, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].add.houseNo, read[i].add.streetNo, read[i].add.postCode, read[i].add.city, read[i].add.state, read[i].upline, read[i].encrypted_password, read[i].question, read[i].answer, read[i].account_available, read[i].time.sec);
					}
				}

				fclose(fptr);
				fclose(fptr2);

				ban_status = 1;
				printf("\nBanning");
				searching_animation();
				printf("This member has been moved to the banned list.");
				Sleep(1500);
				system("cls");
				break;
			}
			else if (strcmp(sure, "N") == 0) {
				system("cls");
				ban_status = 0;
				break;
			}
			else {
				red();
				printf("\n\aError message: Invalid input. Only 'Y' and 'N' is accepted.");
				Sleep(1500);
				system("cls");
				sysColor();
				member_status = 0;
			}

		} while (strcmp(sure, "Y") != 0 && strcmp(sure, "N") != 0);
	}

	return ban_status;
}

int view_bannedlist() {
	struct Member read[1000];
	int i, restore_status = 0;

	do {
		i = 0;

		FILE* fptr;
		fptr = fopen("bannedlist.txt", "r");

		if (fptr == NULL) {
			printf("Error Opening File!\n");
			exit(-1);
		}

		printf("Banned List\n\n");
		printf("---------------------------------------------------------------------------------------------------------------------------------\n");
		printf("| ID    | Username             | Gender | IC Number      | Email Address             | Upline               | Account Available |\n");
		printf("---------------------------------------------------------------------------------------------------------------------------------\n");

		while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &read[i].member_ID, &read[i].username, &read[i].gender, &read[i].IC, &read[i].email, &read[i].add.houseNo, &read[i].add.streetNo, &read[i].add.postCode, &read[i].add.city, &read[i].add.state, &read[i].upline, &read[i].encrypted_password, &read[i].question, &read[i].answer, &read[i].account_available, &read[i].time.sec) != EOF) {
			printf("| %-5s | %-20s |   %s    | %s | %-25s | %-20s | %-17s |\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].upline, read[i].account_available);
			printf("---------------------------------------------------------------------------------------------------------------------------------\n");
			i++;
		}

		fclose(fptr);

		restore_status = restore_member(read, i);

	} while (restore_status == 0);

	return restore_status;
}

int restore_member(struct Member read[1000], int count) {
	char memberID[6], sure[50];
	int member_status = 1, restore_status = 0, record = 0;

	do {
		if (member_status == 0) {
			printf("Banned List\n\n");
			printf("---------------------------------------------------------------------------------------------------------------------------------\n");
			printf("| ID    | Username             | Gender | IC Number      | Email Address             | Upline               | Account Available |\n");
			printf("---------------------------------------------------------------------------------------------------------------------------------\n");

			for (int i = 0; i < count; i++) {
				printf("| %-5s | %-20s |   %s    | %s | %-25s | %-20s | %-17s |\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].upline, read[i].account_available);
				printf("---------------------------------------------------------------------------------------------------------------------------------\n");
			}
		}
		printf("\nEnter the member ID that you want to restore from banned list (X - Back): ");
		scanf("%[^\n]", memberID);
		rewind(stdin);

		for (int i = 0; i < strlen(memberID); i++) {
			memberID[i] = toupper(memberID[i]);
		}

		if (strcmp(memberID, "X") == 0) {
			member_status = 2;
			restore_status = 1;
			system("cls");
			break;
		}
		else {
			for (int i = 0; i < count; i++) {
				if (strcmp(memberID, read[i].member_ID) == 0) {
					member_status = 1;
					record = i;
					break;
				}
				else {
					member_status = 0;
				}
			}

			if (member_status == 0) {
				red();
				printf("\n\aError message: The member ID you entered is invalid.");
				Sleep(1500);
				system("cls");
				sysColor();
			}
		}
	} while (member_status == 0);

	if (member_status == 1) {
		do {
			if (member_status == 0) {
				printf("Banned List\n\n");
				printf("---------------------------------------------------------------------------------------------------------------------------------\n");
				printf("| ID    | Username             | Gender | IC Number      | Email Address             | Upline               | Account Available |\n");
				printf("---------------------------------------------------------------------------------------------------------------------------------\n");

				for (int i = 0; i < count; i++) {
					printf("| %-5s | %-20s |   %s    | %s | %-25s | %-20s | %-17s |\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].upline, read[i].account_available);
					printf("---------------------------------------------------------------------------------------------------------------------------------\n");
				}
				printf("\nEnter the member ID that you want to move to banned list (X - Back): %s\n", memberID);
			}

			printf("\nAre you sure you want to restore this member from the banned list? (Y - Sure, N - Not Sure): ");
			scanf("%s", &sure);
			rewind(stdin);
			sure[0] = toupper(sure[0]);

			if (strcmp(sure, "Y") == 0) {
				FILE* fptr;
				fptr = fopen("member.txt", "a");

				FILE* fptr2;
				fptr2 = fopen("bannedlist.txt", "w");

				if (fptr == NULL || fptr2 == NULL) {
					printf("Error opening file.\n");
					exit(-1);
				}

				for (int i = 0; i < count; i++) {
					if (strcmp(read[i].member_ID, read[record].member_ID) != 0) {
						fprintf(fptr2, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].add.houseNo, read[i].add.streetNo, read[i].add.postCode, read[i].add.city, read[i].add.state, read[i].upline, read[i].encrypted_password, read[i].question, read[i].answer, read[i].account_available, read[i].time.sec);
					}
					else {
						fprintf(fptr, "%s|%s|%s|%s|%s|%s, %s, %s %s, %s|%s|%s|%d|%s|%s|%ld\n", read[i].member_ID, read[i].username, read[i].gender, read[i].IC, read[i].email, read[i].add.houseNo, read[i].add.streetNo, read[i].add.postCode, read[i].add.city, read[i].add.state, read[i].upline, read[i].encrypted_password, read[i].question, read[i].answer, read[i].account_available, read[i].time.sec);
					}
				}

				fclose(fptr);
				fclose(fptr2);

				restore_status = 1;
				printf("\nRestore");
				searching_animation();
				printf("This member has been restore from the banned list.");
				Sleep(1500);
				system("cls");
				break;
			}
			else if (strcmp(sure, "N") == 0) {
				system("cls");
				restore_status = 0;
				break;
			}
			else {
				member_status = 0;
				red();
				printf("\n\aError message: Invalid input. Only 'Y' and 'N' is accepted.");
				Sleep(1500);
				system("cls");
				sysColor();
			}

		} while (strcmp(sure, "Y") != 0 && strcmp(sure, "N") != 0);
	}

	return restore_status;
}

