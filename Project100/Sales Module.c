#include "MLM.h";

int salesModule(char memberID[]) {
	system("mode con cols = 96 lines = 43");
	sysColor();

	int back = 0, back2 = 0, invalid = 0, found = 0;
	char option, choice, cartChoice, checkout, label = 0;
	char select[6], history[50];

	struct ShoppingCart shop;
	ViewHistory sHistory[1000];
	Product read;

	FILE* open;
	FILE* view;

	sprintf(history, "Purchase History (Customer Id %s).txt", memberID);
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %s).dat", memberID);

	open = fopen(history, "a");
	if (open == NULL) {
		printf("open can't open!\n");
		exit(-1);
	}

	fclose(open);

	view = fopen(history, "r");

	if (view == NULL) {
		printf("view can't open!\n");
		exit(-1);
	}

	do {
		label = 0;
		back = 0;
		option = module(memberID);

		do {
			if (option == '1') {
				cartChoice = displayShoppingCart(memberID);

				do {
					if (cartChoice == 1) {
						label = 1;
						back = 1;
						break;
					}

					else if (cartChoice == '1') {
						back = modify(memberID);
						if (back) {
							break;
						}
					}

					else if (cartChoice == '2') {
						back = delete(memberID);
						if (back) {
							break;
						}
					}

					else if (cartChoice == '3') {
						found = 0;

						FILE* open;
						FILE* rShopCart;

						open = fopen(shop.sCartID, "ab");
						if (open == NULL) {
							printf("rShopCart can't open!\n");
							exit(-1);
						}

						fclose(open);

						rShopCart = fopen(shop.sCartID, "rb");

						if (rShopCart == NULL) {
							printf("rShopCart can't open!\n");
							exit(-1);
						}

						while (fread(&read, sizeof(Product), 1, rShopCart) != 0) {
							found++;
						}

						fclose(rShopCart);

						if (found == 0) {
							back = 0;
							red();
							printf("\n\t\t\t\tPlease add at least 1 item to shopping cart!\a\n");
							Sleep(1000);
							sysColor();
						}

						else {
							do {
								back = selectBuy(&checkout, memberID);

								if (checkout == '2') {
									back = checkoutSelect(memberID);
								}

								if (back) {
									break;
								}

							} while (back);

							return 1;
						}

					}

					else if (cartChoice == '4') {
						found = 0;

						FILE* open;
						FILE* rShopCart;

						open = fopen(shop.sCartID, "ab");
						if (open == NULL) {
							printf("rShopCart can't open!\n");
							exit(-1);
						}

						fclose(open);

						rShopCart = fopen(shop.sCartID, "rb");

						if (rShopCart == NULL) {
							printf("rShopCart can't open!\n");
							exit(-1);
						}

						while (fread(&read, sizeof(Product), 1, rShopCart) != 0) {
							found++;
						}

						fclose(rShopCart);

						if (found == 0) {
							back = 0;
							red();
							printf("\n\t\t\t\tPlease add at least 1 item to shopping cart!\a\n");
							Sleep(1000);
							sysColor();
						}

						else {
							back = checkoutAll(memberID);

							if (back) {
								break;
							}

							else {
								//printf("Thank for purchase!\n");
								return 1;
							}
						}
					}
				} while (!back && found != 0);
			}

			if (label) {
				break;
			}

			else if (option == '2') {
				back = buyAgain(memberID);

				if (back) {
					break;
				}
			}

			else if (option == '3') {
				do {
					choice = viewHistory(memberID);

					if (GetAsyncKeyState(VK_LEFT) != 0) {
						keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
						back = 1;
						break;
					}

					else if (GetAsyncKeyState(VK_RIGHT) != 0) {
						keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
						back2 = search(sHistory, view);


					}

					else {
						invalid = 1;
					}

				} while (back2 || invalid);

				if (back) {
					break;
				}
			}

			else if (toupper(option) == 'X') {
				back = 1;
				return back;
			}

		} while (back || found == 0);

	} while ((option != '1' && option != '2' && option != '3') || back == 1 || label == 1);
}

char module(char memberID[]) {
	int back = 0;
	char choice;

	do {
		system("cls");
		printf("WELCOME TO SALES MODULE\n");
		printf("1. Shopping Cart\n");
		printf("2. Buy Again\n");
		printf("3. History\n");
		printf("=======================\n\n");
		printf("Please Enter Your Choice (X - Back) : ");

		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		choice = getch();


		if (choice == '1' || choice == '2' || choice == '3' || toupper(choice) == 'X') {
			break;
		}

		else {
			if (GetAsyncKeyState(VK_LEFT) != 0) {
				red();
				printf("\n\n\t\t\t\tInvalid input! Please try again.\a\n");
				Sleep(1000);
				sysColor();
			}
		}

	} while (choice != '1' && choice != '2' && choice != '3' && toupper(choice) != 'X');

	return choice;
}

void shoppingCart(char prodID[], char prodName[], int qty, double price, char memberID[]) {
	int i = 0, count, label = 0;

	struct ShoppingCart shop;

	Product read[1000];
	Product write;
	strcpy(write.prodID, prodID);
	write.qty = qty;
	strcpy(write.prodName, prodName);
	write.price = price;
	strcpy(write.status, "No Selected");

	sprintf(shop.sCartID, "Shopping Cart (Customer Id %s).dat", memberID);

	FILE* open;
	FILE* rShopCart;
	FILE* wShopCart;

	open = fopen(shop.sCartID, "ab");
	if (open == NULL) {
		printf("open can't open!\n");
		exit(-1);
	}

	fclose(open);

	rShopCart = fopen(shop.sCartID, "rb");

	if (rShopCart == NULL) {
		printf("rShopCart can't open!\n");
		exit(-1);
	}

	while (fread(&read[i], sizeof(Product), 1, rShopCart) != 0) {
		if (strcmp(read[i].prodID, prodID) == 0) {
			read[i].qty = qty;
			label++;
		}
		i++;
	}

	fclose(rShopCart);

	if (label > 0) {
		wShopCart = fopen(shop.sCartID, "wb");
		if (wShopCart == NULL) {
			printf("wShopCart can't open!\n");
			exit(-1);
		}

		for (count = 0; count < i; count++) {
			fwrite(&read[count], sizeof(Product), 1, wShopCart);
		}

		label = 0;
		fclose(wShopCart);
	}

	else {
		wShopCart = fopen(shop.sCartID, "ab");
		if (wShopCart == NULL) {
			printf("wShopCart can't open!\n");
			exit(-1);
		}

		fwrite(&write, sizeof(Product), 1, wShopCart);
		fclose(wShopCart);
	}
}

char displayShoppingCart(char memberID[]) {
	system("cls");

	int back = 0;
	char choice;

	printf("\n    <--\n\n\n\n");
	printf("\t\t\t\t\t\t      SHOPPING CART\n");
	printf("\t\t\t\t=========================================================\n");
	printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
	printf("\t\t\t\t|-------------------------------------------------------|\n");

	rShopCart(memberID);

	printf("\t\t\t\t=========================================================\n\n");
	printf("\t\t\t\t1. Modify\t2. Delete\t3. Select\t4. Checkout\n\n");
	printf("\t\t\t\tPlease select one : ");

	do {
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		choice = getch();
	} while (GetAsyncKeyState(VK_LEFT) == 0 && choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5');

	if (GetAsyncKeyState(VK_LEFT) != 0) {
		back = 1;
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		return back;
	}

	else {
		return choice;
	}

}

void rShopCart(char memberID[]) {
	int found = 0;

	struct ShoppingCart shop;

	Product read;

	sprintf(shop.sCartID, "Shopping Cart (Customer Id %s).dat", memberID);

	FILE* open;
	FILE* rShopCart;

	open = fopen(shop.sCartID, "ab");
	if (open == NULL) {
		printf("open can't open!\n");
		exit(-1);
	}

	fclose(open);

	rShopCart = fopen(shop.sCartID, "rb");

	if (rShopCart == NULL) {
		printf("rShopCart can't open!\n");
		exit(-1);
	}

	while (fread(&read, sizeof(Product), 1, rShopCart) != 0) {
		printf("\t\t\t\t|     %-11s %-19s %-10d %.2f  |\n", read.prodID, read.prodName, read.qty, read.price);
		found++;
	}

	if (found == 0) {
		for (int i = 0; i < 7; i++) {
			if (i == 3) {
				printf("\t\t\t\t|\t\t\tNo Item!\t\t\t|\n");
				continue;
			}
			printf("\t\t\t\t|\t\t\t        \t\t\t|\n");
		}
	}

	fclose(rShopCart);
}

int modify(char memberID[]) {
	system("cls");

	printf("\n    <--\n\n\n\n");
	printf("\t\t\t\t\t\t      SHOPPING CART\n");
	printf("\t\t\t\t=========================================================\n");
	printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
	printf("\t\t\t\t|-------------------------------------------------------|\n");

	rShopCart(memberID);

	printf("\t\t\t\t=========================================================\n");

	struct ShoppingCart shop;

	Product org[1000];
	Product remain[1000];
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %s).dat", memberID);

	int checkQty, found = 0, back = 0;
	int i, count = 0, modifyQty;
	char checkID, modifyProdID[50];

	FILE* open;
	FILE* modify;

	open = fopen(shop.sCartID, "ab");
	if (open == NULL) {
		printf("open can't open!\n");
		exit(-1);
	}

	fclose(open);

	do {
		modify = fopen(shop.sCartID, "rb");

		if (modify == NULL) {
			printf("rShopCart can't open!\n");
			exit(-1);
		}

		//fseek(modify, 0, SEEK_SET);
		if (fread(&org, sizeof(Product), 1, modify) == 0) {
			system("cls");

			printf("\n    <--\n\n\n\n");
			printf("\t\t\t\t\t\t      SHOPPING CART\n");
			printf("\t\t\t\t=========================================================\n");
			printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
			printf("\t\t\t\t|-------------------------------------------------------|\n");

			for (int i = 0; i < 7; i++) {
				if (i == 3) {
					printf("\t\t\t\t|\t\t    No Record Found!    \t\t|\n");
					continue;
				}
				printf("\t\t\t\t|\t\t\t        \t\t\t|\n");
			}

			i = 0;
			printf("\t\t\t\t=========================================================\n");
			printf("\n\n\t\t\t\tPress any key to back...\n");

			back = getch();
			if (back)
				break;
		}

		fseek(modify, 0, SEEK_SET);
		printf("\n\t\t\t\tEnter the product ID : ");

		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);

		checkID = getch();
		if (GetAsyncKeyState(VK_LEFT) != 0) {
			back = 1;
			keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
			system("cls");
			break;
		}

		else {
			printf("%c", checkID);
			modifyProdID[0] = checkID;
			for (int i = 1; i < 6; i++) {
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					back = 1;
					keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
					system("cls");
					break;
				}

				checkID = getch();
				if (checkID == '\r' || checkID == '\n') {
					modifyProdID[i] = '\0';
					break;
				}

				else if (checkID == 8) {
					i -= 2;
					printf("\b \b");
					continue;
				}
				modifyProdID[i] = checkID;
				printf("%c", checkID);
			}
		}

		if (back) {
			break;
		}

		if (1) {
			count = 0;
			while (fread(&org[count], sizeof(Product), 1, modify) != 0) {
				if (strcmp(modifyProdID, org[count].prodID) == 0) {
					printf("\n\t\t\t\tEnter the quantity : ");
					checkQty = scanf("%d", &modifyQty);
					rewind(stdin);

					if (modifyQty <= 0 || checkQty != 1) {
						do {
							red();
							printf("\n\t\t\t\tQuantity must more than 0!\a\n");
							Sleep(1000);
							sysColor();
							system("cls");

							printf("\n    <--\n\n\n\n");
							printf("\t\t\t\t\t\t      SHOPPING CART\n");
							printf("\t\t\t\t=========================================================\n");
							printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
							printf("\t\t\t\t|-------------------------------------------------------|\n");

							rShopCart(memberID);

							printf("\t\t\t\t=========================================================\n");
							printf("\n\t\t\t\tEnter the product ID : %s\n", modifyProdID);
							printf("\t\t\t\tEnter the quantity : ");

							checkQty = scanf("%d", &modifyQty);
							rewind(stdin);

							org[count].qty = modifyQty;

						} while (modifyQty <= 0 || checkQty != 1);
					}

					else {
						org[count].qty = modifyQty;
					}
				}

				else {
					found++;
				}

				count++;
			}

			if (found == count) {
				found = 0;
				fclose(modify);

				red();
				printf("\n\n\t\t\t\tProduct ID not found in shopping cart!\a\n");
				Sleep(1000);
				sysColor();
				system("cls");

				printf("\n    <--\n\n\n\n");
				printf("\t\t\t\t\t\t      SHOPPING CART\n");
				printf("\t\t\t\t=========================================================\n");
				printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
				printf("\t\t\t\t|-------------------------------------------------------|\n");

				rShopCart(memberID);

				printf("\t\t\t\t=========================================================\n");
			}

			else {
				found = 0;
				fclose(modify);

				FILE* update;

				update = fopen(shop.sCartID, "wb");

				if (update == NULL) {
					printf("update can't open!\n");
					exit(-1);
				}

				for (i = 0; i < count; i++) {
					fwrite(&org[i], sizeof(Product), 1, update);
				}

				fclose(update);

				FILE* newShopCart;
				i = 0;

				newShopCart = fopen(shop.sCartID, "rb");

				if (newShopCart == NULL) {
					printf("newShopCart can't open!\n");
					exit(-1);
				}

				red();
				printf("\n\t\t\t\tModify Successfully!\n");
				Sleep(1000);
				sysColor();
				system("cls");

				printf("\n    <--\n\n\n\n");
				printf("\t\t\t\t\t\t      SHOPPING CART\n");
				printf("\t\t\t\t=========================================================\n");
				printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
				printf("\t\t\t\t|-------------------------------------------------------|\n");

				while (fread(&remain[i], sizeof(Product), 1, newShopCart) != 0) {
					printf("\t\t\t\t|     %-11s %-19s %-10d %.2f  |\n", remain[i].prodID, remain[i].prodName, remain[i].qty, remain[i].price);
					i++;
				}

				printf("\t\t\t\t=========================================================\n");

				fclose(newShopCart);
			}

		}

	} while (!back);

	return back;
}

int delete(char memberID[]) {
	system("cls");

	printf("\n    <--\n\n\n\n");
	printf("\t\t\t\t\t\t      SHOPPING CART\n");
	printf("\t\t\t\t=========================================================\n");
	printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
	printf("\t\t\t\t|-------------------------------------------------------|\n");

	rShopCart(memberID);

	printf("\t\t\t\t=========================================================\n");

	struct ShoppingCart shop;

	char temp[50];

	Product org[1000];
	Product remain;

	sprintf(temp, "Temporary ShopCart (Customer Id %s).dat", memberID);
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %s).dat", memberID);

	int found = 0, back = 0, i, count;
	char check, del_prodID[6];

	FILE* open;
	FILE* readShopCart;
	FILE* writeShopCart;
	FILE* tempShopCart;
	FILE* newShopCart;

	open = fopen(shop.sCartID, "ab");
	if (open == NULL) {
		printf("open can't open!\n");
		exit(-1);
	}

	fclose(open);

	do {
		readShopCart = fopen(shop.sCartID, "rb");
		tempShopCart = fopen(temp, "wb");

		if (readShopCart == NULL || tempShopCart == NULL) {
			printf("FILE can't open!\n");
			exit(-1);
		}

		fseek(readShopCart, 0, SEEK_SET);
		if (fread(&org, sizeof(Product), 1, readShopCart) == 0) {
			system("cls");

			printf("\n    <--\n\n\n\n");
			printf("\t\t\t\t\t\t      SHOPPING CART\n");
			printf("\t\t\t\t=========================================================\n");
			printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
			printf("\t\t\t\t|-------------------------------------------------------|\n");

			for (int i = 0; i < 7; i++) {
				if (i == 3) {
					printf("\t\t\t\t|\t\t    No Record Found!    \t\t|\n");
					continue;
				}
				printf("\t\t\t\t|\t\t\t        \t\t\t|\n");
			}

			i = 0;
			printf("\t\t\t\t=========================================================\n");
			printf("\n\n\t\t\t\tPress any key to back...\n");

			back = getch();
			if (back)
				break;
		}

		printf("\n\t\t\t\tEnter the product ID : ");

		check = getch();
		if (GetAsyncKeyState(VK_LEFT) != 0) {
			back = 1;
			system("cls");
			break;
		}

		else {
			printf("%c", check);
			del_prodID[0] = check;
			for (int i = 1; i < 6; i++) {
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					back = 1;
					system("cls");
					break;
				}

				check = getch();
				if (check == '\r' || check == '\n') {
					del_prodID[i] = '\0';
					break;
				}

				else if (check == 8) {
					i -= 2;
					printf("\b \b");
					continue;
				}
				del_prodID[i] = check;
				printf("%c", check);
			}
		}

		if (back) {
			break;
		}

		if (!back) {
			back = 0;
			i = 0;

			fseek(readShopCart, 0, SEEK_SET);
			while (fread(&org[i], sizeof(Product), 1, readShopCart) != 0) {
				i++;
			}

			fclose(readShopCart);

			writeShopCart = fopen(shop.sCartID, "wb");

			if (writeShopCart == NULL) {
				printf("writeShopCart can't open!\n");
				exit(-1);
			}

			for (count = 0; count < i; count++) {
				if (strcmp(del_prodID, org[count].prodID) == 0) {
					fwrite(&org[count], sizeof(Product), 1, tempShopCart);
					found++;
				}

				else {
					fwrite(&org[count], sizeof(Product), 1, writeShopCart);
				}
			}

			fclose(writeShopCart);
			fclose(tempShopCart);

			if (found == 0) {
				back = 0;

				red();
				printf("\n\n\t\t\t\tProduct ID not found in shopping cart!\a\n");
				Sleep(1000);
				sysColor();
				system("cls");

				printf("\n    <--\n\n\n\n");
				printf("\t\t\t\t\t\t      SHOPPING CART\n");
				printf("\t\t\t\t=========================================================\n");
				printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
				printf("\t\t\t\t|-------------------------------------------------------|\n");

				rShopCart(memberID);

				printf("\t\t\t\t=========================================================\n");
			}

			else {
				found = 0;
				back = 0;

				newShopCart = fopen(shop.sCartID, "rb");

				red();
				printf("\n\n\t\t\t\tDelete Successfully!\n");
				Sleep(1000);
				sysColor();
				system("cls");

				printf("\n    <--\n\n\n\n");
				printf("\t\t\t\t\t\t      SHOPPING CART\n");
				printf("\t\t\t\t=========================================================\n");
				printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
				printf("\t\t\t\t|-------------------------------------------------------|\n");

				while (fread(&remain, sizeof(Product), 1, newShopCart) != 0) {
					printf("\t\t\t\t|     %-11s %-19s %-10d %.2f  |\n", remain.prodID, remain.prodName, remain.qty, remain.price);
				}

				printf("\t\t\t\t=========================================================\n");

				fclose(newShopCart);
			}
		}

	} while (!back);

	return back;
}

int selectBuy(char* checkout, char memberID[]) {
	system("cls");

	struct ShoppingCart shop;

	char sel[100];

	Product read;
	Product org[1000];
	Product select[1000];

	sprintf(sel, "Selected ShopCart (Customer Id %s).dat", memberID);
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %s).dat", memberID);

	int i, j, k, error = 0, character, count, found = 0, back = 0, selected = 0;
	char a, check, selProdID[6];

	FILE* open;
	FILE* readShopCart;
	FILE* selShopCart;
	FILE* readSelect;

	open = fopen(sel, "ab");
	if (open == NULL) {
		printf("open can't open!\n");
		exit(-1);
	}

	fclose(open);

	readShopCart = fopen(shop.sCartID, "rb");

	if (readShopCart == NULL) {
		printf("readShopCart can't open!\n");
		exit(-1);
	}

	if (fread(&read, sizeof(Product), 1, readShopCart) == 0) {
		printf("SHOPPING CART\n");
		printf("======================================================================\n");
		printf("Product ID           Product Name            Quantity            Price\n\n");
		printf("                             NO RECORD FOUND!\n\n");
		printf("======================================================================\n\n");
		printf("\n\n\n\n\n\n\n------------------------Press any key to back-------------------------\n");
		a = getch();
		if (a)
			back = 1;
		return back;
	}

	fclose(readShopCart);

	do {
		system("cls");
		readShopCart = fopen(shop.sCartID, "rb");
		selShopCart = fopen(sel, "wb");

		if (readShopCart == NULL || selShopCart == NULL) {
			printf("File can't open!\n");
			exit(-1);
		}

		printf("\n    <--\n\n\n\n");
		printf("\t\t\t\t\t      SHOPPING CART\n");
		printf("\t\t\t=================================================================\n");
		printf("\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price \t Status  |\n");
		printf("\t\t\t|---------------------------------------------------------------|\n");

		j = 0;
		while (fread(&org[j], sizeof(Product), 1, readShopCart) != 0) {
			fwrite(&org[j], sizeof(Product), 1, selShopCart);
			printf("\t\t\t|     %-11s %-19s %-10d %-10.2f %s\n", org[j].prodID, org[j].prodName, org[j].qty, org[j].price, org[j].status);
			j++;
		}

		fclose(readShopCart);
		fclose(selShopCart);
		printf("\t\t\t=================================================================\n");
		printf("\t\t\t1. CheckOut\n\n");

		do {
			printf("\n\t\t\tEnter the product ID : ");

			check = getch();
			if (GetAsyncKeyState(VK_LEFT) != 0) {
				back = 1;
				return back;
			}

			else {
				printf("%c", check);
				selProdID[0] = check;
				for (int k = 1; k < 6; k++) {
					if (GetAsyncKeyState(VK_LEFT) != 0) {
						back = 1;
						return back;
					}

					check = getch();
					if (check == '\r' || check == '\n') {
						selProdID[k] = '\0';
						break;
					}

					else if (check == 8) {
						k -= 2;
						printf("\b \b");
						continue;
					}
					selProdID[k] = check;
					printf("%c", check);
				}
			}

			character = strlen(selProdID);

			if (strcmp(selProdID, "1") == 0) {
				selected = 0;
				selShopCart = fopen(sel, "rb");

				if (selShopCart == NULL) {
					printf("selShopCart can't open!\n");
					exit(-1);
				}

				while (fread(&read, sizeof(Product), 1, selShopCart) != 0) {
					if (strcmp(read.status, "Selected") == 0) {
						selected++;
					}
				}

				fclose(selShopCart);

				if (selected == 0) {
					red();
					printf("\n\n\t\t\tPlease select at least 1 product!\a\n");
					Sleep(1000);
					sysColor();
					system("cls");
					continue;
				}

				else {
					back = 0;
					*checkout = '2';
					return;
				}
			}

			if (character == 4) {

				for (i = 0; i < j; i++) {

					// Search product ID in Shopping Cart
					if (strcmp(selProdID, org[i].prodID) == 0) {
						if (strcmp(org[i].status, "No Selected") == 0) {
							strcpy(org[i].status, "Selected");
						}
						else if (strcmp(org[i].status, "Selected") == 0) {
							strcpy(org[i].status, "No Selected");
						}
						else
							break;
						error++;
					}

					else {
						found++;
					}
				}

				if (found == i) {
					found = 0;

					red();
					printf("\n\n\t\t\tProduct ID not found in shopping cart!\a\n");
					Sleep(1000);
					sysColor();
					system("cls");

					printf("\n    <--\n\n\n\n");
					printf("\t\t\t\t\t      SHOPPING CART\n");
					printf("\t\t\t===============================================================\n");
					printf("\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price \t Status  |\n");
					printf("\t\t\t|-------------------------------------------------------------|\n");

					readShopCart = fopen(shop.sCartID, "rb");
					selShopCart = fopen(sel, "rb");

					if (readShopCart == NULL || selShopCart == NULL) {
						printf("File can't open!\n");
						exit(-1);
					}

					if (error == 0) {
						while (fread(&read, sizeof(Product), 1, readShopCart) != 0) {
							printf("\t\t\t%-20s %-23s %-19d %-17.2f %-15s\n", read.prodID, read.prodName, read.qty, read.price, read.status);
						}
					}

					else {
						while (fread(&read, sizeof(Product), 1, selShopCart) != 0) {
							printf("\t\t\t|     %-11s %-19s %-10d %-10.2f %s\n", read.prodID, read.prodName, read.qty, read.price, read.status);
						}
					}

					printf("\t\t\t===============================================================\n");
					printf("\t\t\t1. CheckOut\n\n");

					fclose(readShopCart);
					fclose(selShopCart);
				}

				else {
					found = 0;

					selShopCart = fopen(sel, "wb");

					if (selShopCart == NULL) {
						printf("selShopCart can't open!\n");
						exit(-1);
					}

					for (count = 0; count < i; count++) {
						fwrite(&org[count], sizeof(Product), 1, selShopCart);
					}

					fclose(selShopCart);

					selShopCart = fopen(sel, "rb");

					if (selShopCart == NULL) {
						printf("selShopCart can't open!\n");
						exit(-1);
					}

					system("cls");
					printf("\n    <--\n\n\n\n");
					printf("\t\t\t\t\t      SHOPPING CART\n");
					printf("\t\t\t===============================================================\n");
					printf("\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price \t Status  |\n");
					printf("\t\t\t|-------------------------------------------------------------|\n");

					i = 0;
					while (fread(&select[i], sizeof(Product), 1, selShopCart) != 0) {
						printf("\t\t\t|     %-11s %-19s %-10d %-10.2f %s\n", select[i].prodID, select[i].prodName, select[i].qty, select[i].price, select[i].status);
						i++;
					}

					printf("\t\t\t===============================================================\n");
					printf("\t\t\t1. CheckOut\n\n");

					fclose(selShopCart);
				}
			}

			else {
				found = 0;
				selected = 0;

				if (character < 4) {
					red();
					printf("\n\n\t\t\tProduct ID must have 4 character!\a\n");
					Sleep(1000);
					sysColor();
					system("cls");
				}
				else if (character > 4) {
					red();
					printf("\n\n\t\t\tProduct ID have only 4 character!\a\n");
					Sleep(1000);
					sysColor();
					system("cls");
				}

				printf("\n    <--\n\n\n\n");
				printf("\t\t\t\t\t      SHOPPING CART\n");
				printf("\t\t\t===============================================================\n");
				printf("\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price \t Status  |\n");
				printf("\t\t\t|-------------------------------------------------------------|\n");

				readShopCart = fopen(shop.sCartID, "rb");
				selShopCart = fopen(sel, "rb");

				if (readShopCart == NULL || selShopCart == NULL) {
					printf("File can't open!\n");
					exit(-1);
				}

				if (error == 0) {
					while (fread(&read, sizeof(Product), 1, readShopCart) != 0) {
						printf("\t\t\t|     %-11s %-19s %-10d %-10.2f %s\n", read.prodID, read.prodName, read.qty, read.price, read.status);
					}
				}

				else {
					while (fread(&read, sizeof(Product), 1, selShopCart) != 0) {
						printf("\t\t\t|     %-11s %-19s %-10d %-10.2f %s\n", read.prodID, read.prodName, read.qty, read.price, read.status);
					}
				}

				printf("\t\t\t===============================================================\n");
				printf("\t\t\t1. CheckOut\n\n");

				fclose(readShopCart);
				fclose(selShopCart);
			}

		} while ((strcmp(selProdID, "1") != 0 && !back) || selected != 0);

	} while ((strcmp(selProdID, "1") != 0 && !back) || selected == 0);

	return back;
}

int buyNow(char prodID[], char prodName[], int qty, double price, char memberID[]) {
	system("cls");

	SYSTEMTIME t;
	GetLocalTime(&t);

	int choice, orderID = 1, i = 0, j = 0, back = 0;
	double subTotal = qty * price;
	double total = subTotal + (subTotal * COMMISSION);
	char ctn = 'Y';
	char buyAgainFile[50], temporary[50], history[50], acc[50], upline[100];;

	struct Member compare;
	struct ShoppingCart shop;
	BuyAgain bAgain[1000];
	BuyAgain rewrite;
	Product read;

	sprintf(buyAgainFile, "Buy Again (Customer Id %s).dat", memberID);
	sprintf(temporary, "Temporary ShopCart (Customer Id %s).dat", memberID);
	sprintf(history, "Purchase History (Customer Id %s).txt", memberID);

	FILE* rAgain;
	FILE* wAgain;
	FILE* temp;
	FILE* wHistory;
	FILE* clear;

	rAgain = fopen(buyAgainFile, "rb");
	temp = fopen(temporary, "wb");
	wHistory = fopen(history, "a");

	if (rAgain == NULL || temp == NULL || wHistory == NULL) {
		printf("File can't open!\n");
		exit(-1);
	}

	do {
		back = 0;
		system("cls");

		printf("\t\t\t\tCheckout\n");
		printf("======================================================================\n");
		printf("Product ID \t\t Product Name \t\t Quantity \t\t Price\n");
		printf("----------------------------------------------------------------------\n");
		printf("%s \t\t %s \t\t %d \t\t %.2f\n\n", prodID, prodName, qty, price);
		printf("======================================================================\n");
		printf("Sub Total  \t\t\t\t\t\t %.2f\n", subTotal);
		printf("Commission \t\t\t\t\t\t %.0f%%\n", COMMISSION * 100);
		printf("----------------------------------------------------------------------\n");
		printf("Total \t\t\t\t\t\t %.2f\n", total);
		printf("======================================================================\n");
		printf("1. Back \t\t\t\t\t\t 2. Place Order\n\n");
		printf("Please select one : ");
		scanf("%d", &choice);
		rewind(stdin);

		if (choice == 1) {
			back = 1;
			return back;
		}

		if (choice == 2) {
			printf("Do you want to continue ? (Y - Yes  N - No) : ");
			scanf("%c", &ctn);
			rewind(stdin);

			if (toupper(ctn) == 'Y') {

				FILE* fptr;

				fptr = fopen("member.txt", "r");
				if (fptr == NULL) {
					printf("Error opening file.\n");
					exit(-1);
				}

				while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &compare.member_ID, &compare.username, &compare.gender, &compare.IC, &compare.email, &compare.add.houseNo, &compare.add.streetNo, &compare.add.postCode, &compare.add.city, &compare.add.state, &compare.upline, &compare.encrypted_password, &compare.question, &compare.answer, &compare.account_available, &compare.time.sec) != EOF) {
					if (strcmp(memberID, compare.member_ID) == 0) {
						strcpy(upline, compare.upline);
						sprintf(acc, "Account %s.txt", upline);
					}
				}

				fclose(fptr);

				FILE* account;
				account = fopen(acc, "a");

				if (account == NULL) {
					printf("account can't open!\n");
					exit(-1);
				}

				fprintf(account, "%f", subTotal * COMMISSION);

				fclose(account);

				fwrite(&prodID, sizeof(prodID), 1, temp);
				fwrite(&prodName, sizeof(prodName), 1, temp);

				i = 0;

				while (fread(&bAgain[i], sizeof(BuyAgain), 1, rAgain) != 0) {
					i++;
				}

				for (j = 0; j < i; j++) {
					if (strcmp(prodID, bAgain[j].prodID) != 0) {
						fwrite(&bAgain[j].prodID, sizeof(bAgain[j].prodID), 1, temp);
						fwrite(&bAgain[j].prodName, sizeof(bAgain[j].prodName), 1, temp);
					}
				}

				fprintf(wHistory, "%02d/%02d/%d %02d:%02d:%02d %s %d %s| %lf\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond, prodID, qty, prodName, price);

				fclose(rAgain);
				fclose(temp);
				fclose(wHistory);

				temp = fopen(temporary, "rb");
				wAgain = fopen(buyAgainFile, "wb");

				while (fread(&rewrite, sizeof(BuyAgain), 1, temp) != 0) {
					fwrite(&rewrite, sizeof(BuyAgain), 1, wAgain);
				}

				fclose(temp);
				fclose(wAgain);

				clear = fopen(temporary, "wb");
				fclose(clear);
			}

			else if (toupper(ctn) == 'N') {
				continue;
			}

			else {
				red();
				printf("Invalid Input! Please Try Again.\n");
				Sleep(1000);
				sysColor();
			}
		}

		else {
			red();
			printf("Invalid Input! Please Try Again.\n");
			Sleep(1000);
			sysColor();
		}

	} while (toupper(ctn) != 'Y' || (choice != 1 && choice != 2));

}

int checkoutAll(char memberID[]) {
	struct ShoppingCart shop;

	int choice, orderID = 1, back = 0;
	double total;
	char ctn = 'Y';
	char buyAgain[50], temp[50];

	sprintf(shop.sCartID, "Shopping Cart (Customer Id %s).dat", memberID);
	sprintf(buyAgain, "Buy Again (Customer Id %s).dat", memberID);
	sprintf(temp, "Temporary ShopCart (Customer Id %s).dat", memberID);

	do {
		back = 0;
		FILE* shopCart;
		shopCart = fopen(shop.sCartID, "rb");

		system("cls");

		printf("\n\n\n\n\n\t\t\t\t\t\t\t CheckOut\n");
		printf("\t\t\t\t=========================================================\n");
		printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
		printf("\t\t\t\t|-------------------------------------------------------|\n");

		rShopCart(memberID);

		printf("\t\t\t\t=========================================================\n");
		printf("\t\t\t\t|SubTotal \t\t\t\t\t");

		total = totalPrice(shopCart);

		printf("\t\t\t\t=========================================================\n");
		printf("\t\t\t\t1. Back \t\t\t\t   2. Place Order\n\n");
		printf("\t\t\t\t\Please select one : ");
		scanf("%d", &choice);
		rewind(stdin);

		fclose(shopCart);

		if (choice == 1) {
			back = 1;
			return back;
		}

		else if (choice == 2) {
			printf("\t\t\t\tDo you want to continue ? (Y - Yes  N - No) : ");
			scanf("%c", &ctn);
			rewind(stdin);

			if (toupper(ctn) == 'Y') {
				system("cls");

				FILE* totalSales;
				FILE* clear;

				placeOrder(shop.sCartID, buyAgain, temp, memberID);

				commission(shop.sCartID, memberID);

				reduceStock(shop.sCartID, memberID);

				purchaseHistory(shop.sCartID, memberID);

				clear = fopen(shop.sCartID, "wb");
				fclose(clear);

				return 0;
			}

			else if (toupper(ctn) == 'N') {
				continue;
			}

			else {
				red();
				printf("\n\t\t\t\tInvalid Input! Please Try Again.\a\n");
				Sleep(1000);
				sysColor();
			}
		}

		else {
			red();
			printf("\n\t\t\t\tInvalid Input! Please Try Again.\a\n");
			Sleep(1000);
			sysColor();
		}
	} while (toupper(ctn) != 'Y' || (choice != 1 && choice != 2));
}

int checkoutSelect(char memberID[]) {
	struct ShoppingCart shop;

	int choice, orderID = 1, back = 0;
	char ctn = 'Y';
	char selectedShopCart[50], buyAgain[50], temp[50];
	double total;

	sprintf(selectedShopCart, "Selected ShopCart (Customer Id %s).dat", memberID);
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %s).dat", memberID);
	sprintf(buyAgain, "Buy Again (Customer Id %s).dat", memberID);
	sprintf(temp, "Temporary ShopCart (Customer Id %s).dat", memberID);

	Product read;

	do {
		FILE* shopCart;
		shopCart = fopen(selectedShopCart, "rb");

		if (shopCart == NULL) {
			printf("shopCart can't open!\n");
			exit(-1);
		}

		system("cls");

		printf("\n\n\n\n\n\t\t\t\t\t\t\t CheckOut\n");
		printf("\t\t\t\t=========================================================\n");
		printf("\t\t\t\t|  Product ID \t  Product Name \t   Quantity \t Price  |\n");
		printf("\t\t\t\t|-------------------------------------------------------|\n");

		while (fread(&read, sizeof(Product), 1, shopCart) != 0) {
			if (strcmp(read.status, "Selected") == 0) {
				printf("%-20s %-23s %-19d %-6.2f\n", read.prodID, read.prodName, read.qty, read.price);
			}
		}

		printf("\t\t\t\t=========================================================\n");
		printf("\t\t\t\t|SubTotal \t\t\t\t\t");

		total = totalPrice(shopCart);

		printf("\t\t\t\t=========================================================\n");
		printf("\t\t\t\t1. Back \t\t\t\t   2. Place Order\n\n");
		printf("\t\t\t\tPlease select one : ");
		scanf("%d", &choice);
		rewind(stdin);

		fclose(shopCart);

		if (choice == 1) {
			back = 1;
			return back;
		}

		else if (choice == 2) {
			printf("\t\t\t\tDo you want to continue ? (Y - Yes  N - No) : ");
			scanf("%c", &ctn);
			rewind(stdin);

			if (toupper(ctn) == 'Y') {
				system("cls");

				FILE* totalSales;
				FILE* filter;
				FILE* reset;

				printf("%.2lf\n", total);

				placeOrder(selectedShopCart, buyAgain, temp, memberID);

				reduceStock(selectedShopCart, memberID);

				commission(selectedShopCart, memberID);

				totalSales = fopen("totalSales.dat", "ab");

				if (totalSales == NULL) {
					printf("totalSales can't open!\n");
					exit(-1);
				}

				fwrite(&total, sizeof(total), 1, totalSales);
				fclose(totalSales);

				purchaseHistory(selectedShopCart, memberID);

				filter = fopen(selectedShopCart, "rb");
				reset = fopen(shop.sCartID, "wb");

				while (fread(&read, sizeof(Product), 1, filter) != 0) {
					if (strcmp(read.status, "No Selected") == 0) {
						fwrite(&read, sizeof(Product), 1, reset);
					}
				}

				fclose(filter);
				fclose(reset);

				return 0;
			}

			else if (toupper(ctn) == 'N') {
				continue;
			}

			else {
				red();
				printf("\n\t\t\t\tInvalid Input! Please Try Again.\a\n");
				Sleep(1000);
				sysColor();
			}
		}

		else {
			red();
			printf("\n\t\t\t\tInvalid Input! Please Try Again.\a\n");
			Sleep(1000);
			sysColor();
		}
	} while (toupper(ctn) != 'Y' || (choice != 1 && choice != 2));
}

double totalPrice(FILE* order) {
	int filter = 0;
	double subTotal, total = 0;

	Product read;

	fseek(order, 0, SEEK_SET);
	while (fread(&read, sizeof(Product), 1, order) != 0) {
		if (strcmp(read.status, "Selected") == 0) {
			subTotal = read.qty * read.price;
			total += subTotal;
			filter++;
		}
	}

	if (filter == 0) {
		fseek(order, 0, SEEK_SET);
		while (fread(&read, sizeof(Product), 1, order) != 0) {
			subTotal = read.qty * read.price;
			total += subTotal;
		}
	}

	printf(" %.2f|\n", total);
	printf("\t\t\t\t|Comission (%.0f%%)\t\t\t\t\t   %.2f|\n", COMMISSION * 100, total * COMMISSION);
	total += total * COMMISSION;
	printf("\t\t\t\t|Total \t\t\t\t\t");
	printf("RM %.2f|\n", total);

	fclose(order);

	return total;
}

void placeOrder(char shopCart[], char buyAgain[], char temporary[], char memberID[]) {
	FILE* order;
	FILE* rAgain;
	FILE* wAgain;
	FILE* temp;

	order = fopen(shopCart, "rb");
	rAgain = fopen(buyAgain, "rb");

	if (order == NULL || rAgain == NULL) {
		printf("File can't open!\n");
		exit(-1);
	}

	Product read[1000];
	BuyAgain bAgain[1000];
	BuyAgain rewrite;

	int filter = 0, check = 0, chk = 0;
	int i = 0, j = 0, k, l = 0, a = 0;
	int repeat[1000], rpt;

	while (fread(&bAgain[i], sizeof(BuyAgain), 1, rAgain) != 0) {
		i++;
	}

	while (fread(&read[j], sizeof(Product), 1, order) != 0) {
		j++;
	}

	fclose(order);
	fclose(rAgain);

	wAgain = fopen(buyAgain, "wb");
	temp = fopen(temporary, "wb");

	if (wAgain == NULL) {
		printf("wAgain can't open!\n");
		exit(-1);
	}

	while (1) {
		for (k = 0; k < j; k++) {
			if (strcmp(read[k].status, "Selected") == 0) {
				fwrite(&read[k].prodID, sizeof(read[k].prodID), 1, temp);
				fwrite(&read[k].prodName, sizeof(read[k].prodName), 1, temp);
				repeat[chk] = k;
				chk++;
				filter++;
			}
		}

		if (filter == 0)
			break;

		for (l = 0; l < i; l++) {
			for (k = 0; k < chk; k++) {
				if (strcmp(read[repeat[k]].prodID, bAgain[l].prodID) == 0) {
					rpt = 1;
					break;
				}
				else {
					rpt = 0;
				}
			}

			if (i > 0) {
				if (!rpt) {
					fwrite(&bAgain[l].prodID, sizeof(bAgain[l].prodID), 1, temp);
					fwrite(&bAgain[l].prodName, sizeof(bAgain[l].prodName), 1, temp);
				}
			}
		}

		break;
	}

	if (filter == 0) {
		for (k = 0; k < j; k++) {
			fwrite(&read[k].prodID, sizeof(read[k].prodID), 1, temp);
			fwrite(&read[k].prodName, sizeof(read[k].prodName), 1, temp);
		}

		for (l = 0; l < i; l++) {
			for (k = 0; k < j; k++) {
				if (strcmp(read[k].prodID, bAgain[l].prodID) == 0) {
					rpt = 1;
					break;
				}
				else {
					rpt = 0;
				}
			}

			if (i > 0) {
				if (!rpt) {
					fwrite(&bAgain[l].prodID, sizeof(bAgain[l].prodID), 1, temp);
					fwrite(&bAgain[l].prodName, sizeof(bAgain[l].prodName), 1, temp);
				}
			}
		}
	}

	filter = 0;

	fclose(wAgain);
	fclose(temp);

	temp = fopen(temporary, "rb");
	wAgain = fopen(buyAgain, "wb");

	while (fread(&rewrite, sizeof(BuyAgain), 1, temp) != 0) {
		fwrite(&rewrite, sizeof(BuyAgain), 1, wAgain);
	}

	fclose(temp);
	fclose(wAgain);
}

void reduceStock(char shopCart[], char memberID[]) {
	Product read;
	struct Member compare;
	StockItem recordStock[1000];
	StockItem recordUpline[1000];
	char filename[100];
	int i = 0, n = 0, file_open_status, filter = 0;

	FILE* fptr;

	fptr = fopen("member.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	FILE* readStock = NULL;
	FILE* readCart;

	readCart = fopen(shopCart, "rb");

	if (readCart == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &compare.member_ID, &compare.username, &compare.gender, &compare.IC, &compare.email, &compare.add.houseNo, &compare.add.streetNo, &compare.add.postCode, &compare.add.city, &compare.add.state, &compare.upline, &compare.encrypted_password, &compare.question, &compare.answer, &compare.account_available, &compare.time.sec) != EOF) {
		if (strcmp(memberID, compare.member_ID) == 0) {
			if (strcmp(compare.upline, "N/A") == 0) {
				readStock = fopen("stock.txt", "r");

				FILE* readUpline;
				sprintf(filename, "%s.txt", compare.username);
				readUpline = fopen(filename, "r");

				if (readUpline == NULL) {
					printf("Error opening file.\n");
					exit(-1);
				}

				while (fscanf(readUpline, "%[^|]|%[^|]|%f|%d|%d|%d\n", &recordUpline[n].item_code, &recordUpline[n].item_description, &recordUpline[n].item_price, &recordUpline[n].item_quantity, &recordUpline[n].minimum_level, &recordUpline[n].reorder_quantity) != EOF) {
					n++;
				}

				fclose(readUpline);

				file_open_status = 0;
			}
			else {
				sprintf(filename, "%s.txt", compare.upline);
				readStock = fopen(filename, "r");
				file_open_status = 1;
			}
		}
	}

	fclose(fptr);

	if (readStock == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	while (fread(&read, sizeof(Product), 1, readCart) != 0) {
		if (strcmp(read.status, "Selected") == 0) {
			while (fscanf(readStock, "%[^|]|%[^|]|%f|%d|%d|%d\n", &recordStock[i].item_code, &recordStock[i].item_description, &recordStock[i].item_price, &recordStock[i].item_quantity, &recordStock[i].minimum_level, &recordStock[i].reorder_quantity) != EOF) {
				if (strcmp(read.prodID, recordStock[i].item_code) == 0) {
					recordStock[i].item_quantity = recordStock[i].item_quantity - read.qty;
					recordUpline[i].item_quantity += read.qty;
				}
				i++;
			}
			filter++;
		}
	}

	fseek(readStock, 0, SEEK_SET);
	if (filter == 0) {
		while (fscanf(readStock, "%[^|]|%[^|]|%f|%d|%d|%d\n", &recordStock[i].item_code, &recordStock[i].item_description, &recordStock[i].item_price, &recordStock[i].item_quantity, &recordStock[i].minimum_level, &recordStock[i].reorder_quantity) != EOF) {
			fseek(readCart, 0, SEEK_SET);
			while (fread(&read, sizeof(Product), 1, readCart) != 0) {
				if (strcmp(read.prodID, recordStock[i].item_code) == 0) {
					recordStock[i].item_quantity = recordStock[i].item_quantity - read.qty;
					recordUpline[i].item_quantity = recordUpline[i].item_quantity + read.qty;
				}
			}
			i++;
		}
	}

	fclose(readCart);
	fclose(readStock);

	FILE* reduceStock;

	if (file_open_status == 0) {
		// Reduce company stock
		reduceStock = fopen("stock.txt", "w");
		// Add upline stock
		FILE* addStock;
		addStock = fopen(filename, "w");

		for (int h = 0; h < n; h++) {
			fprintf(addStock, "%s|%s|%.2f|%d|%d|%d\n", recordUpline[h].item_code, recordUpline[h].item_description, recordUpline[h].item_price, recordUpline[h].item_quantity, recordUpline[h].minimum_level, recordUpline[h].reorder_quantity);
		}

		fclose(addStock);
	}
	else {
		reduceStock = fopen(filename, "w");
	}

	if (reduceStock == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	for (int k = 0; k < i; k++) {
		fprintf(reduceStock, "%s|%s|%.2f|%d|%d|%d\n", recordStock[k].item_code, recordStock[k].item_description, recordStock[k].item_price, recordStock[k].item_quantity, recordStock[k].minimum_level, recordStock[k].reorder_quantity);
	}

	fclose(reduceStock);
}

void commission(char shopCart[], char memberID[]) {
	int filter = 0, status = 0;
	double subTotal, total = 0, commission;
	char acc[50], upline[100];

	struct Member compare;
	Product read;

	FILE* fptr;
	FILE* order;

	order = fopen(shopCart, "rb");
	fptr = fopen("member.txt", "r");

	if (fptr == NULL || order == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &compare.member_ID, &compare.username, &compare.gender, &compare.IC, &compare.email, &compare.add.houseNo, &compare.add.streetNo, &compare.add.postCode, &compare.add.city, &compare.add.state, &compare.upline, &compare.encrypted_password, &compare.question, &compare.answer, &compare.account_available, &compare.time.sec) != EOF) {
		if (strcmp(memberID, compare.member_ID) == 0) {
			if (strcmp(compare.upline, "N/A") != 0) {
				strcpy(upline, compare.upline);
				sprintf(acc, "Account %s.txt", upline);
				status = 1;
			}
		}
	}

	if (status == 0) {
		sprintf(acc, "Account %s.txt", "company");
	}

	fclose(fptr);

	FILE* account;
	account = fopen(acc, "a");
	printf("%s\n", acc);

	if (account == NULL) {
		printf("account can't open!\n");
		exit(-1);
	}

	fseek(order, 0, SEEK_SET);
	while (fread(&read, sizeof(Product), 1, order) != 0) {
		if (strcmp(read.status, "Selected") == 0) {
			subTotal = read.qty * read.price;
			total += subTotal;
			filter++;
		}
	}

	if (filter == 0) {
		fseek(order, 0, SEEK_SET);
		while (fread(&read, sizeof(Product), 1, order) != 0) {
			subTotal = read.qty * read.price;
			total += subTotal;
		}
	}

	commission = total * COMMISSION;

	fprintf(account, "%f\t", commission);

	fclose(account);
	fclose(order);
}

int buyAgain(char memberID[]) {
	system("cls");

	Product read;
	struct Member compare;
	StockItem recordStock[1000];
	StockItem recordUpline[1000];
	struct ShoppingCart shop;

	char choice, selection;
	char bAgain[50], prodID[6];
	int j = 0, qty, label, back = 0, found = 0;
	char filename[100];
	int i = 0, n = 0, file_open_status, filter = 0;

	FILE* fptr;

	fptr = fopen("member.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	FILE* readStock = NULL;

	while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^,], %[^,], %[^ ] %[^,], %[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%ld\n", &compare.member_ID, &compare.username, &compare.gender, &compare.IC, &compare.email, &compare.add.houseNo, &compare.add.streetNo, &compare.add.postCode, &compare.add.city, &compare.add.state, &compare.upline, &compare.encrypted_password, &compare.question, &compare.answer, &compare.account_available, &compare.time.sec) != EOF) {
		if (strcmp(memberID, compare.member_ID) == 0) {
			if (strcmp(compare.upline, "N/A") == 0) {
				readStock = fopen("stock.txt", "r");

				FILE* readUpline;
				sprintf(filename, "%s.txt", compare.username);
				readUpline = fopen(filename, "r");

				if (readUpline == NULL) {
					printf("Error opening file.\n");
					exit(-1);
				}

				while (fscanf(readUpline, "%[^|]|%[^|]|%f|%d|%d|%d\n", &recordUpline[n].item_code, &recordUpline[n].item_description, &recordUpline[n].item_price, &recordUpline[n].item_quantity, &recordUpline[n].minimum_level, &recordUpline[n].reorder_quantity) != EOF) {
					n++;
				}

				fclose(readUpline);

				file_open_status = 0;
			}
			else {
				sprintf(filename, "%s.txt", compare.upline);
				readStock = fopen(filename, "r");
				file_open_status = 1;
			}
		}
	}

	fclose(fptr);

	if (readStock == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}


	BuyAgain buyAgain;

	sprintf(bAgain, "Buy Again (Customer Id %s).dat", memberID);

	FILE* open;
	FILE* rAgain;

	open = fopen(bAgain, "ab");
	if (open == NULL) {
		printf("rAgain can't open!\n");
		exit(-1);
	}

	fclose(open);

	rAgain = fopen(bAgain, "rb");

	if (rAgain == NULL) {
		printf("rAgain can't open!\n");
		exit(-1);
	}

	label = 0;
first_loop:
	do {
		system("cls");

		printf("\n  <--");
		printf("\n\n\t\t\t\t\t\t\t Buy Again\n");
		printf("\t\t======================================================================================\n");
		printf("\t\t    Product ID \t\t Product Name \t\t Quantity \t\t   Price\n");
		printf("\t\t--------------------------------------------------------------------------------------\n");

		fseek(rAgain, 0, SEEK_SET);
		j = 0;
		while (fread(&buyAgain, sizeof(BuyAgain), 1, rAgain) != 0) {
			fseek(readStock, 0, SEEK_SET);
			while (fscanf(readStock, "%[^|]|%[^|]|%f|%d|%d|%d\n", &recordStock[j].item_code, &recordStock[j].item_description, &recordStock[j].item_price, &recordStock[j].item_quantity, &recordStock[j].minimum_level, &recordStock[j].reorder_quantity) != EOF) {
				if (strcmp(buyAgain.prodID, recordStock[j].item_code) == 0) {
					printf("\t\t    %-10s \t\t %-10s \t\t %-10d \t\t   %-10.2f\n", buyAgain.prodID, buyAgain.prodName, recordStock[j].item_quantity, recordStock[j].item_price);
				}
				j++;
			}
		}

		printf("\t\t======================================================================================\n\n");
		printf("\t\t 1. Add to Cart\n");

		selection = getch();

		if (GetAsyncKeyState(VK_LEFT) != 0) {
			back = 1;
			return back;
		}

		if (selection == '1') {
			// Buy Now or Add to Cart
			do {
				system("cls");

				printf("\n  <--");
				printf("\n\n\t\t\t\t\t\t\t Buy Again\n");
				printf("\t\t======================================================================================\n");
				printf("\t\t    Product ID \t\t Product Name \t\t Quantity \t\t   Price\n");
				printf("\t\t--------------------------------------------------------------------------------------\n");

				fseek(rAgain, 0, SEEK_SET);
				j = 0;
				while (fread(&buyAgain, sizeof(BuyAgain), 1, rAgain) != 0) {
					fseek(readStock, 0, SEEK_SET);
					while (fscanf(readStock, "%[^|]|%[^|]|%f|%d|%d|%d\n", &recordStock[j].item_code, &recordStock[j].item_description, &recordStock[j].item_price, &recordStock[j].item_quantity, &recordStock[j].minimum_level, &recordStock[j].reorder_quantity) != EOF) {
						if (strcmp(buyAgain.prodID, recordStock[j].item_code) == 0) {
							printf("\t\t    %-10s \t\t %-10s \t\t %-10d \t\t   %-10.2f\n", buyAgain.prodID, buyAgain.prodName, recordStock[j].item_quantity, recordStock[j].item_price);
						}
						j++;
					}
				}

				printf("\t\t======================================================================================\n\n");
				printf("\t\t Enter Product ID : ");

				choice = getch();

				if (GetAsyncKeyState(VK_LEFT) != 0) {
					label = 1;
					keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
					system("cls");
					goto first_loop;
				}

				else {
					printf("%c", choice);
					prodID[0] = choice;
					for (int i = 1; i < 6; i++) {
						if (GetAsyncKeyState(VK_LEFT) != 0) {
							label = 1;
							keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
							system("cls");
							goto first_loop;
						}

						choice = getch();
						if (choice == '\r' || choice == '\n') {
							prodID[i] = '\0';
							break;
						}

						else if (choice == 8) {
							i -= 2;
							printf("\b \b");
							continue;
						}
						prodID[i] = choice;
						printf("%c", choice);
					}
				}

				found = 0;
				fseek(rAgain, 0, SEEK_SET);
				while (fread(&buyAgain, sizeof(BuyAgain), 1, rAgain) != 0) {
					if (strcmp(prodID, buyAgain.prodID) == 0) {

						// Product ID found in Buy Again, Enter quantity
						printf("\n\t\t Quantity : ");
						scanf("%d", &qty);

						/*
							Stock Quantity Validation
						*/

						// Add to Cart
						j = 0;
						fseek(readStock, 0, SEEK_SET);

						while (fscanf(readStock, "%[^|]|%[^|]|%f|%d|%d|%d\n", &recordStock[j].item_code, &recordStock[j].item_description, &recordStock[j].item_price, &recordStock[j].item_quantity, &recordStock[j].minimum_level, &recordStock[j].reorder_quantity) != EOF) {
							if (strcmp(prodID, recordStock[j].item_code) == 0) {
								shoppingCart(prodID, buyAgain.prodName, qty, recordStock[j].item_price, memberID);
							}
							j++;
						}

						red();
						printf("\n\t\t Add Successfully!\n");
						Sleep(1000);
						sysColor();
						system("cls");

						found++;
					}
				}

				if (found == 0) {
					// Product ID not found in Buy Again
					red();
					printf("\n\t\t Product ID not found! Please try again.\a\n");
					Sleep(1000);
					sysColor();
				}
			} while (strcmp(prodID, buyAgain.prodID) != 0);
		}

		else if (!label) {
			red();
			printf("\n\t\t Invalid input! Please try again.\a\n");
			Sleep(1000);
			sysColor();
			system("cls");
		}

		label = 0;
	} while (selection != '1');

	fclose(rAgain);
}

void purchaseHistory(char buyCart[], char memberID[]) {
	SYSTEMTIME t;
	GetLocalTime(&t);

	char history[50];
	int filter = 0;

	struct ShoppingCart shop;

	Product read;

	sprintf(history, "Purchase History (Customer Id %s).txt", memberID);

	FILE* wHistory;
	FILE* rShopCart;

	wHistory = fopen(history, "a");
	rShopCart = fopen(buyCart, "rb");

	if (wHistory == NULL || rShopCart == NULL) {
		printf("File can't open!\n");
		exit(-1);
	}

	while (fread(&read, sizeof(Product), 1, rShopCart) != 0) {
		if (strcmp(read.prodID, "Selected") == 0) {
			fprintf(wHistory, "%02d/%02d/%d %02d:%02d:%02d %s %d %s| %lf\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond, read.prodID, read.qty, read.prodName, read.price);

			filter++;
		}
	}

	fseek(rShopCart, 0, SEEK_SET);

	if (filter == 0) {
		while (fread(&read, sizeof(Product), 1, rShopCart) != 0) {
			fprintf(wHistory, "%02d/%02d/%d %02d:%02d:%02d %s %d %s| %lf\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond, read.prodID, read.qty, read.prodName, read.price);
		}
	}

	fclose(wHistory);
	fclose(rShopCart);
}

char viewHistory(char memberID[]) {
	system("cls");

	struct ShoppingCart shop;

	ViewHistory vHistory[1000];
	ViewHistory sHistory[1000];

	char history[50];
	char choice;
	int i = 0, j = 0, back = 0;
	double subTotal = 0, total = 0;

	sprintf(history, "Purchase History (Customer Id %s).txt", memberID);

	FILE* view;
	view = fopen(history, "r");

	if (view == NULL) {
		printf("view can't open!\n");
		exit(-1);
	}

	printf("\n\n \t\t ==============================================================================\n");
	printf("\t\t |\t\t\t\t Purchase History \t\t\t      |\n");
	printf("\t\t ==============================================================================\n");

	while (fscanf(view, "%02d/%02d/%d %02d:%02d:%02d %s %d %[^|]| %lf", &vHistory[i].day, &vHistory[i].month, &vHistory[i].year, &vHistory[i].hour, &vHistory[i].min, &vHistory[i].sec, vHistory[i].prodID, &vHistory[i].qty, vHistory[i].prodName, &vHistory[i].price) != EOF) {
		if (i == 0) {
			printf("\t\t |\t     Date Purchased : ");
			printf("%02d/%02d/%02d    Time Purchased : %02d:%02d:%02d \t      |\n", vHistory[i].day, vHistory[i].month, vHistory[i].year, vHistory[i].hour, vHistory[i].min, vHistory[i].sec);
			printf("\t\t |----------------------------------------------------------------------------|\n");
			printf("\t\t |Product ID \t\t Product Name \t\t Quantity \t     Price    |\n");
			printf("\t\t |----------------------------------------------------------------------------|\n");
			printf("\t\t |%-22s %-23s x %-17d %-9.2f|\n", vHistory[i].prodID, vHistory[i].prodName, vHistory[i].qty, vHistory[i].price);
			subTotal += vHistory[i].qty * vHistory[i].price;
		}

		if (i > 0) {
			if ((vHistory[i].year == vHistory[i - 1].year) && (vHistory[i].month == vHistory[i - 1].month) && (vHistory[i].day == vHistory[i - 1].day) && (vHistory[i].hour == vHistory[i - 1].hour) && (vHistory[i].min == vHistory[i - 1].min) && (vHistory[i].sec == vHistory[i - 1].sec)) {
				printf("\t\t |%-22s %-23s x %-17d %-9.2f|\n", vHistory[i].prodID, vHistory[i].prodName, vHistory[i].qty, vHistory[i].price);
				subTotal += vHistory[i].qty * vHistory[i].price;
			}
			else {
				printf("\t\t |----------------------------------------------------------------------------|\n");
				printf("\t\t |SUBTOTAL         RM %.2f \t\t\t\t\t\t      |\n", subTotal);
				printf("\t\t |COMMISSION       %.0f %% \t\t\t\t\t\t\t      |\n", COMMISSION * 100);
				printf("\t\t |----------------------------------------------------------------------------|\n");
				printf("\t\t |ORDER TOTAL      RM %.2f \t\t\t\t\t\t      |\n", subTotal += subTotal * COMMISSION);
				subTotal = 0;
				printf("\t\t ==============================================================================\n");
				printf("\t\t |\t     Date Purchased : ");
				printf("%02d/%02d/%02d    Time Purchased : %02d:%02d:%02d \t      |\n", vHistory[i].day, vHistory[i].month, vHistory[i].year, vHistory[i].hour, vHistory[i].min, vHistory[i].sec);
				printf("\t\t |----------------------------------------------------------------------------|\n");
				printf("\t\t |Product ID \t\t Product Name \t\t Quantity \t     Price    |\n");
				printf("\t\t |----------------------------------------------------------------------------|\n");
				printf("\t\t |%-22s %-23s x %-17d %-9.2f|\n", vHistory[i].prodID, vHistory[i].prodName, vHistory[i].qty, vHistory[i].price);
				subTotal += vHistory[i].qty * vHistory[i].price;
			}
		}
		i++;
	}

	printf("\t\t |----------------------------------------------------------------------------|\n");
	printf("\t\t |SUBTOTAL         RM %.2f \t\t\t\t\t\t      |\n", subTotal);
	printf("\t\t |COMMISSION       %.0f %% \t\t\t\t\t\t\t      |\n", COMMISSION * 100);
	printf("\t\t |----------------------------------------------------------------------------|\n");
	printf("\t\t |ORDER TOTAL      RM %.2f \t\t\t\t\t\t      |\n", subTotal += subTotal * COMMISSION);
	printf("\t\t ==============================================================================\n\n");
	printf("\t\t <-- Back \t\t\t\t\t\t\t     Search -->\n");

	fclose(view);

	choice = getch();

	return choice;
}

int search(ViewHistory search[], FILE* view) {
	int back = 0, found = 0, searchTime = 0;
	char selection, ctn = 'Y';
	char searchName[100], searchProdID[6];
	int searchMonth, searchYear;
	int i = 0, j = 0, k = 0, count = 0, time = 0, oneTime = 0, invalid = 0;
	int totalQty = 0;
	double orderTotal = 0, total = 0;
	bool t = true;

	do {
		system("cls");
		printf("1. ID         2. Name         3. Date\n\n");
		printf("Enter your selection : ");

		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);

		selection = getch();

		if (GetAsyncKeyState(VK_LEFT) != 0) {
			back = 1;
			keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
			system("cls");
			return back;
		}

		if (selection == '1') {
			do {
				found = 0;
				system("cls");

				printf("Enter the product ID (-1 to Back) : ");
				scanf("%s", searchProdID);
				rewind(stdin);
				printf("\n");

				if (strcmp(searchProdID, "-1") == 0) {
					back = 1;
					return back;
				}

				do {
					fseek(view, 0, SEEK_SET);
					while (fscanf(view, "%02d/%02d/%d %02d:%02d:%02d %s %d %[^|]| %lf", &search[i].day, &search[i].month, &search[i].year, &search[i].hour, &search[i].min, &search[i].sec, search[i].prodID, &search[i].qty, search[i].prodName, &search[i].price) != EOF) {
						if (strcmp(searchProdID, search[i].prodID) == 0) {
							k = j;
							j = i;
							searchTime++;

							if (t) {
								printf("\n\t\t\t\t\t\tDate Purchased : ");
								printf("%02d/%02d/%02d\n\n", search[i].day, search[i].month, search[i].year);
								printf("\t\t\t\t --------------------------------------------------------\n");
								printf("\t\t\t\t\t\t      Time : ");
								printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
								printf("\t\t\t\t --------------------------------------------------------\n");
								printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
								orderTotal += search[i].qty * search[i].price;
								totalQty += search[i].qty;
								total = orderTotal;
								t = false;
							}

							else if (true) {
								if ((search[i].year == search[k].year) && (search[i].month == search[k].month) && (search[i].day == search[k].day) && (search[i].hour == search[k].hour) && (search[i].min == search[k].min) && (search[i].sec == search[k].sec)) {
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}

								else if ((search[i].year == search[k].year) && (search[i].month == search[k].month) && (search[i].day == search[k].day) && ((search[i].hour != search[k].hour) || (search[i].min != search[k].min) || (search[i].sec != search[k].sec))) {
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t\t\t      Time : ");
									printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal = 0;
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}

								else if ((search[i].year != search[k].year) || (search[i].month != search[k].month) || (search[i].day != search[k].day)) {
									if (toupper(ctn) == 'Y' && searchTime == 1) {
										printf("\t\t\t\t --------------------------------------------------------\n");
										printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
									}

									else if (toupper(ctn) == 'Y' && searchTime > 1) {
										if (invalid > 0) {
											printf("\t\t\t\t --------------------------------------------------------\n");
											printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
										}

										invalid++;
									}

									else if (toupper(ctn) != 'Y' || searchTime > 1) {
										if (invalid > 0) {
											printf("\t\t\t\t --------------------------------------------------------\n");
											printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
										}

										invalid++;
									}

									printf("\n\t\t\t\t\t\tDate Purchased : ");
									printf("%02d/%02d/%02d\n\n", search[i].day, search[i].month, search[i].year);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t\t\t      Time : ");
									printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal = 0;
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}
							}

							found++;
						}
						i++;
					}

					if (found == 0) {
						red();
						printf("No Record Found! Please Try Again.\a\n");
						Sleep(1000);
						sysColor();
						continue;
					}

					printf("\t\t\t\t --------------------------------------------------------\n");
					printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
					printf("\t\t\t\t ========================================================\n");
					printf("\t\t\t\t |\t\t\t  Summary  \t\t\t|\n");
					printf("\t\t\t\t |------------------------------------------------------|\n");
					printf("\t\t\t\t |QUANTITY      x %-7d\t\t\t\t|\n", totalQty);
					printf("\t\t\t\t |SUBTOTAL      RM %-7.2f\t\t\t\t|\n", total);
					printf("\t\t\t\t |COMMISSION    %.0f%%\t\t\t\t\t|\n", COMMISSION * 100);
					printf("\t\t\t\t |------------------------------------------------------|\n");
					printf("\t\t\t\t |TOTAL         RM %-7.2f\t\t\t\t|\n", total + (total * COMMISSION));
					printf("\t\t\t\t ========================================================\n\n");
					printf("\t\t\t\t Do you want to continue ? (Y - Yes   N - No) : ");
					scanf("%c", &ctn);
					rewind(stdin);

					if (toupper(ctn) == 'Y') {
						invalid = 0;
						totalQty = 0;
						total = 0;
						break;
					}

					else if (toupper(ctn) == 'N') {
						back = 1;
						return back;
					}

					else {
						totalQty = 0;
						total = 0;
						invalid = 0;
						red();
						printf("\n\t\t\t\t Invalid Input! Please Try Again.\a\n");
						Sleep(1000);
						sysColor();
						system("cls");
						printf("Enter the product ID (-1 to Back) : %s\n\n\n", searchProdID);
					}

				} while (toupper(ctn) != 'Y' && toupper(ctn) != 'N');

			} while (found == 0 || toupper(ctn) == 'Y');
		}

		else if (selection == '2') {    // Search Keyword (Name)
			do {
				found = 0;
				system("cls");

				printf("Enter keyword (-1 to Back) : ");
				scanf("%[^\n]", searchName);
				rewind(stdin);
				printf("\n");

				if (strcmp(searchName, "-1") == 0) {
					back = 1;
					return back;
				}

				count = strlen(searchName);

				do {
					fseek(view, 0, SEEK_SET);
					while (fscanf(view, "%02d/%02d/%d %02d:%02d:%02d %s %d %[^|]| %lf", &search[i].day, &search[i].month, &search[i].year, &search[i].hour, &search[i].min, &search[i].sec, search[i].prodID, &search[i].qty, search[i].prodName, &search[i].price) != EOF) {
						if (strncmp(searchName, search[i].prodName, count) == 0) {
							k = j;
							j = i;
							searchTime++;

							if (t) {
								printf("\n\t\t\t\t\t\tDate Purchased : ");
								printf("%02d/%02d/%02d\n\n", search[i].day, search[i].month, search[i].year);
								printf("\t\t\t\t --------------------------------------------------------\n");
								printf("\t\t\t\t\t\t      Time : ");
								printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
								printf("\t\t\t\t --------------------------------------------------------\n");
								printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
								orderTotal += search[i].qty * search[i].price;
								totalQty += search[i].qty;
								total = orderTotal;
								t = false;
							}

							else if (true) {
								if ((search[i].year == search[k].year) && (search[i].month == search[k].month) && (search[i].day == search[k].day) && (search[i].hour == search[k].hour) && (search[i].min == search[k].min) && (search[i].sec == search[k].sec)) {
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}

								else if ((search[i].year == search[k].year) && (search[i].month == search[k].month) && (search[i].day == search[k].day) && ((search[i].hour != search[k].hour) || (search[i].min != search[k].min) || (search[i].sec != search[k].sec))) {
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t\t\t      Time : ");
									printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal = 0;
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}

								else if ((search[i].year != search[k].year) || (search[i].month != search[k].month) || (search[i].day != search[k].day)) {
									if (toupper(ctn) == 'Y' && searchTime == 1) {
										printf("\t\t\t\t --------------------------------------------------------\n");
										printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
									}

									else if (toupper(ctn) == 'Y' && searchTime > 1) {
										if (invalid > 0) {
											printf("\t\t\t\t --------------------------------------------------------\n");
											printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
										}

										invalid++;
									}

									else if (toupper(ctn) != 'Y' || searchTime > 1) {
										if (invalid > 0) {
											printf("\t\t\t\t --------------------------------------------------------\n");
											printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
										}

										invalid++;
									}

									printf("\n\t\t\t\t\t\tDate Purchased : ");
									printf("%02d/%02d/%02d\n\n", search[i].day, search[i].month, search[i].year);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t\t\t      Time : ");
									printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal = 0;
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}
							}
							found++;
						}
						i++;
					}

					if (found == 0) {
						red();
						printf("No Record Found! Please Try Again.\a\n");
						Sleep(1000);
						sysColor();
						continue;
					}

					printf("\t\t\t\t --------------------------------------------------------\n");
					printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
					printf("\t\t\t\t ========================================================\n");
					printf("\t\t\t\t |\t\t\t  Summary  \t\t\t|\n");
					printf("\t\t\t\t |------------------------------------------------------|\n");
					printf("\t\t\t\t |QUANTITY      x %-7d\t\t\t\t|\n", totalQty);
					printf("\t\t\t\t |SUBTOTAL      RM %-7.2f\t\t\t\t|\n", total);
					printf("\t\t\t\t |COMMISSION    %.0f%%\t\t\t\t\t|\n", COMMISSION * 100);
					printf("\t\t\t\t |------------------------------------------------------|\n");
					printf("\t\t\t\t |TOTAL         RM %-7.2f\t\t\t\t|\n", total + (total * COMMISSION));
					printf("\t\t\t\t ========================================================\n\n");
					printf("\t\t\t\t Do you want to continue ? (Y - Yes   N - No) : ");
					scanf("%c", &ctn);
					rewind(stdin);

					if (toupper(ctn) == 'Y') {
						invalid = 0;
						totalQty = 0;
						total = 0;
						break;
					}

					else if (toupper(ctn) == 'N') {
						back = 1;
						return back;
					}

					else {
						totalQty = 0;
						total = 0;
						invalid = 0;
						red();
						printf("\n\t\t\t\t Invalid Input! Please Try Again.\a\n");
						Sleep(1000);
						sysColor();
						system("cls");
						printf("Enter keyword (-1 to Back) : %s\n\n\n", searchName);
					}

				} while (toupper(ctn) != 'Y' && toupper(ctn) != 'N');

			} while (found == 0 || toupper(ctn) == 'Y');
		}

		else if (selection == '3') {
			do {
				found = 0;
				system("cls");

				printf("Enter month and year (1/2023) (-1 to Back) : ");
				scanf("%02d/%d", &searchMonth, &searchYear);
				rewind(stdin);
				printf("\n");

				if (strcmp(searchProdID, "-1") == 0) {
					back = 1;
					return back;
				}

				do {
					fseek(view, 0, SEEK_SET);
					while (fscanf(view, "%02d/%02d/%d %02d:%02d:%02d %s %d %[^|]| %lf", &search[i].day, &search[i].month, &search[i].year, &search[i].hour, &search[i].min, &search[i].sec, search[i].prodID, &search[i].qty, search[i].prodName, &search[i].price) != EOF) {
						if ((searchMonth == search[i].month) && (searchYear == search[i].year)) {
							k = j;
							j = i;
							searchTime++;

							if (t) {
								printf("\n\t\t\t\t\t\tDate Purchased : ");
								printf("%02d/%02d/%02d\n\n", search[i].day, search[i].month, search[i].year);
								printf("\t\t\t\t --------------------------------------------------------\n");
								printf("\t\t\t\t\t\t      Time : ");
								printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
								printf("\t\t\t\t --------------------------------------------------------\n");
								printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
								orderTotal += search[i].qty * search[i].price;
								totalQty += search[i].qty;
								total = orderTotal;
								t = false;
							}

							else if (true) {
								if ((search[i].year == search[k].year) && (search[i].month == search[k].month) && (search[i].day == search[k].day) && (search[i].hour == search[k].hour) && (search[i].min == search[k].min) && (search[i].sec == search[k].sec)) {
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}

								else if ((search[i].year == search[k].year) && (search[i].month == search[k].month) && (search[i].day == search[k].day) && ((search[i].hour != search[k].hour) || (search[i].min != search[k].min) || (search[i].sec != search[k].sec))) {
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t\t\t      Time : ");
									printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal = 0;
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}

								else if ((search[i].year != search[k].year) || (search[i].month != search[k].month) || (search[i].day != search[k].day)) {
									if (toupper(ctn) == 'Y' && searchTime == 1) {
										printf("\t\t\t\t --------------------------------------------------------\n");
										printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
									}

									else if (toupper(ctn) == 'Y' && searchTime > 1) {
										if (invalid > 0) {
											printf("\t\t\t\t --------------------------------------------------------\n");
											printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
										}

										invalid++;
									}

									else if (toupper(ctn) != 'Y' || searchTime > 1) {
										if (invalid > 0) {
											printf("\t\t\t\t --------------------------------------------------------\n");
											printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
										}

										invalid++;
									}

									printf("\n\t\t\t\t\t\tDate Purchased : ");
									printf("%02d/%02d/%02d\n\n", search[i].day, search[i].month, search[i].year);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t\t\t      Time : ");
									printf("%02d:%02d:%02d\n", search[i].hour, search[i].min, search[i].sec);
									printf("\t\t\t\t --------------------------------------------------------\n");
									printf("\t\t\t\t ID %-13s %-16s  x%-12d RM %-11.2f\n", search[i].prodID, search[i].prodName, search[i].qty, search[i].price);
									orderTotal = 0;
									orderTotal += search[i].qty * search[i].price;
									totalQty += search[i].qty;
									total += search[i].qty * search[i].price;
								}

							}
							found++;
						}
						i++;
					}

					if (found == 0) {
						red();
						printf("No Record Found! Please Try Again.\a\n");
						Sleep(1000);
						sysColor();
						continue;
					}

					printf("\t\t\t\t --------------------------------------------------------\n");
					printf("\t\t\t\t ORDER TOTAL RM %.2f\n\n", orderTotal);
					printf("\t\t\t\t ========================================================\n");
					printf("\t\t\t\t |\t\t\t  Summary  \t\t\t|\n");
					printf("\t\t\t\t |------------------------------------------------------|\n");
					printf("\t\t\t\t |QUANTITY      x %-7d\t\t\t\t|\n", totalQty);
					printf("\t\t\t\t |SUBTOTAL      RM %-7.2f\t\t\t\t|\n", total);
					printf("\t\t\t\t |COMMISSION    %.0f%%\t\t\t\t\t|\n", COMMISSION * 100);
					printf("\t\t\t\t |------------------------------------------------------|\n");
					printf("\t\t\t\t |TOTAL         RM %-7.2f\t\t\t\t|\n", total + (total * COMMISSION));
					printf("\t\t\t\t ========================================================\n\n");
					printf("\t\t\t\t Do you want to continue ? (Y - Yes   N - No) : ");
					scanf("%c", &ctn);
					rewind(stdin);

					if (toupper(ctn) == 'Y') {
						invalid = 0;
						totalQty = 0;
						total = 0;
						break;
					}

					else if (toupper(ctn) == 'N') {
						back = 1;
						return back;
					}

					else {
						totalQty = 0;
						total = 0;
						invalid = 0;
						red();
						printf("\n\t\t\t\t Invalid Input! Please Try Again.\a\n");
						Sleep(1000);
						sysColor();
						system("cls");
						printf("Enter month and year (1/2023) (-1 to Back) : %02d/%d\n\n\n", searchMonth, searchYear);
					}

				} while (toupper(ctn) != 'Y' && toupper(ctn) != 'N');

			} while (found == 0 || toupper(ctn) == 'Y');
		}

		else {
			if (oneTime > 0) {
				red();
				printf("\n\nInvalid Input! Please Try Again.\a\n");
				Sleep(1000);
				sysColor();
			}

			oneTime++;
		}

	} while (selection != '1' && selection != '2' && selection != '3');

	return back;
}