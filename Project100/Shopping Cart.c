#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#pragma warning (disable : 4996)
#define _WIN32_WINNT 0x0500
#define COMMISSION 0.05

struct ShoppingCart {
	int cartID, custID;
	char sCartID[50];
};

typedef struct {
	char prodID[6];
	int qty;
	char prodName[50];
	double price;
	char status[50];
} Product;

typedef struct {
	char prodID[6];
	char prodName[50];
} BuyAgain;

typedef struct {
	WORD day, month, year, hour, min, sec;
	char prodID[6];
	int qty;
	char prodName[50];
	double price;
	char status[50];
} ViewHistory;

typedef struct {
	char prodID[50];
	int qty;
} ProductSelected;

//void red();
//void black();
//void whiteBackground();
//struct tm* curTime();
//char module();
//char displayShoppingCart();
//void shoppingCart(char prodID[6], char prodName[50], int qty, double price);
//int buyAgain();
//void rShopCart();
//int modify();
//int delete();
//void checkoutAll();
//void checkoutSelect();
//int selectBuy(char* back);
//void buyNow(char prodID[6], char prodName[50], int qty, double price);
//double totalPrice(FILE* order);
//void placeOrder(char shopCart[50], char buyAgain[50], char temp[50]);
//void monthlySales();
//void purchaseHistory(char buyCart[]);
//char viewHistory();
//int search(ViewHistory search[], FILE* view);

int salesModule() {
	system("mode con cols = 96 lines = 43");
	system("color f0");

	int back = 0, back2 = 0, invalid = 0;
	char option, choice, cartChoice, checkout, label = 0;
	char select[6], history[50];

	ViewHistory sHistory[1000];

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	sprintf(history, "Purchase History (Customer Id %d).txt", shop.cartID);

	FILE* view;
	view = fopen(history, "r");

	if (view == NULL) {
		printf("view can't open!\n");
		exit(-1);
	}

	do {
		label = 0;
		back = 0;
		option = module();
	
		do {
			if (option == '1') {
				cartChoice = displayShoppingCart();

				do {
					if (cartChoice == 1) {
						label = 1;
						back = 1;
						break;
					}

					else if (cartChoice == '1') {
						back = modify();
						if (back) {
							break;
						}
					}

					else if (cartChoice == '2') {
						back = modify();
						if (back) {
							break;
						}
					}

					else if (cartChoice == '3') {
						back = delete();
						if (back) {
							break;
						}
					}

					else if (cartChoice == '4') {
						back = selectBuy(&checkout);

						if (back) {
							break;
						}

						if (checkout == '2') {
							checkoutSelect();
						}

						break;

					}

					else if (cartChoice == '5') {
						checkoutAll();
						break;
					}
				} while (!back);
			}

			if (label) {
				break;
			} 

			else if (option == '2') {
				back = buyAgain();

				if (back) {
					break;
				}
			}
		
			else if (option == '3') {
				do {
					choice = viewHistory();

					if (GetAsyncKeyState(VK_LEFT) != 0) {
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

			else if (GetAsyncKeyState(VK_LEFT) != 0) {
				back = 1;
				return back;
			}

		} while (back);

	} while ((option != '1' && option != '2' && option != '3') || back == 0 || label == 1);

	return back;
}

char module() {
	int back = 0;
	char choice;

	do {
		system("cls");
		printf("WELCOME TO SALES MODULE\n");
		printf("1. Shopping Cart\n");
		printf("2. Buy Again\n");
		printf("3. History\n");
		printf("=======================\n\n");
		printf("Please Enter Your Choice : ");


		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		choice = getch();


		if (choice == '1' || choice == '2' || choice == '3') {
			break;			
		}

		else {
			if (GetAsyncKeyState(VK_LEFT) != 0) {
				red();
				printf("\n\nInvalid input! Please try again.\a\n");
				Sleep(1000);
				system("color f0");
			}		
		}

	} while (choice != '1' && choice != '2' && choice != '3');


	if (GetAsyncKeyState(VK_LEFT) != 0) {
		back = 1;
		return back;
	}

	else {
		return choice;
	}
}

void shoppingCart(char prodID[], char prodName[], int qty, double price) {
	int i = 0, count, label = 0;

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	Product read[1000];
	Product write;
	strcpy(write.prodID, prodID);
	write.qty = qty;
	strcpy(write.prodName, prodName);
	write.price = price;
	strcpy(write.status, "No Selected");

	sprintf(shop.sCartID, "Shopping Cart (Customer Id %d).dat", shop.cartID);

	FILE* rShopCart;
	FILE* wShopCart;

	rShopCart = fopen(shop.sCartID, "rb");
	

	if (rShopCart == NULL) {
		printf("rShopCart can't open!\n");
		exit(-1);
	}

	while (fread(&read[i], sizeof(Product), 1, rShopCart) != 0) {
		if (strcmp(read[i].prodID, write.prodID) == 0) {
			read[i].qty = write.qty;
		}
		label = 1;
		i++;
	}

	fclose(rShopCart);

	if (label) {
		wShopCart = fopen(shop.sCartID, "wb");
		if (wShopCart == NULL) {
			printf("wShopCart can't open!\n");
			exit(-1);
		}

		for (count = 0; count < i; count++) {
			fwrite(&read[count], sizeof(Product), 1, wShopCart);
		}
	}
	
	else {
		wShopCart = fopen(shop.sCartID, "ab");
		if (wShopCart == NULL) {
			printf("wShopCart can't open!\n");
			exit(-1);
		}

		fwrite(&write, sizeof(Product), 1, wShopCart);
	}

	fclose(wShopCart);
}

char displayShoppingCart() {
	system("cls");

	int back = 0;
	char choice;

	printf("SHOPPING CART\n");
	printf("======================================================================\n");
	printf("Product ID           Product Name            Quantity            Price\n");

	rShopCart();

	printf("======================================================================\n");
	printf("1. Add");
	printf("        2. Modify");
	printf("        3. Delete");
	printf("        4. Select");
	printf("        5. Checkout\n");
	printf("\nPlease select one : ");

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

void rShopCart() {
	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	Product read;

	sprintf(shop.sCartID, "Shopping Cart (Customer Id %d).dat", shop.cartID);

	FILE* rShopCart;

	rShopCart = fopen(shop.sCartID, "rb");

	if (rShopCart == NULL) {
		printf("rShopCart can't open!\n");
		exit(-1);
	}

	while (fread(&read, sizeof(Product), 1, rShopCart) != 0) {
		printf("%-20s %-23s %-19d %-6.2f\n", read.prodID, read.prodName, read.qty, read.price);
	}

	fclose(rShopCart);
}

int modify() {
	system("cls");

	printf("SHOPPING CART\n");
	printf("======================================================================\n");
	printf("Product ID           Product Name            Quantity            Price\n");
	rShopCart();
	printf("======================================================================\n\n");

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	Product org[1000];
	Product remain[1000];
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %d).dat", shop.cartID);

	int checkQty, found = 0, back = 0;
	int i, count = 0, modifyQty;
	char checkID, modifyProdID[50];

	FILE* modify;	

	do {
		modify = fopen(shop.sCartID, "rb");

		if (modify == NULL) {
			printf("rShopCart can't open!\n");
			exit(-1);
		}

		//fseek(modify, 0, SEEK_SET);
		if (fread(&org, sizeof(Product), 1, modify) == 0) {
			system("cls");
			printf("SHOPPING CART\n");
			printf("======================================================================\n");
			printf("Product ID           Product Name            Quantity            Price\n\n");
			printf("                             NO RECORD FOUND!\n\n");
			printf("======================================================================\n\n");
			printf("\n\n\n\n\n\n\n------------------------Press any key to back-------------------------\n");
			back = getch();
			if (back)
				break;
		}

		fseek(modify, 0, SEEK_SET);
		printf("Enter the product ID (B to back) : ");
		/*checkID = scanf("%s", modifyProdID);
		rewind(stdin);*/

		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);

		checkID = getch();
		if (GetAsyncKeyState(VK_LEFT) != 0) {
			back = 1;
			system("cls");
			break;
		}

		else {
			printf("%c", checkID);
			modifyProdID[0] = checkID;
			for (int i = 1; i < 6; i++) {
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					back = 1;
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
					printf("\nEnter the quantity : ");
					checkQty = scanf("%d", &modifyQty);
					rewind(stdin);

					if (modifyQty <= 0 || modifyQty >= 100 || checkQty != 1) {
						do {
							printf("Invalid Quantity!\n");
							Sleep(1000);
							system("cls");
							printf("SHOPPING CART\n");
							printf("======================================================================\n");
							printf("Product ID           Product Name            Quantity            Price\n");
							rShopCart();
							printf("======================================================================\n\n");
							printf("Enter the product ID (B to back) : %s\n", modifyProdID);
							printf("Enter the quantity : ");
							checkQty = scanf("%d", &modifyQty);
							rewind(stdin);					
							org[count].qty = modifyQty;
						} while (modifyQty <= 0 || modifyQty >= 100 || checkQty != 1);					
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
				printf("\n\nProduct ID not found in shopping cart!\a\n");
				Sleep(1000);
				system("color f0");
				system("cls");
				printf("SHOPPING CART\n");
				printf("======================================================================\n");
				printf("Product ID           Product Name            Quantity            Price\n");
				rShopCart();
				printf("======================================================================\n\n");
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
				printf("\nModify Successfully!\n");
				Sleep(1000);
				system("color f0");
				system("cls");
				printf("SHOPPING CART\n");
				printf("======================================================================\n");
				printf("Product ID           Product Name            Quantity            Price\n");

				while (fread(&remain[i], sizeof(Product), 1, newShopCart) != 0) {
					printf("%-20s %-23s %-19d %-6.2f\n", remain[i].prodID, remain[i].prodName, remain[i].qty, remain[i].price);
					i++;
				}

				printf("======================================================================\n\n");

				fclose(newShopCart);
			}
			
		}

	} while (!back);

	return back;
}

int delete() {
	system("cls");

	printf("SHOPPING CART\n");
	printf("======================================================================\n");
	printf("Product ID           Product Name            Quantity            Price\n");
	rShopCart();
	printf("======================================================================\n\n");

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;
	char temp[50];

	Product org;
	Product remain;
	
	sprintf(temp, "Temporary ShopCart (Customer Id %d).dat", shop.cartID);
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %d).dat", shop.cartID);

	int found = 0, back = 0;
	char check, del_prodID[6];

	FILE* readShopCart;
	FILE* tempShopCart;
	FILE* newShopCart;

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
			printf("SHOPPING CART\n");
			printf("======================================================================\n");
			printf("Product ID           Product Name            Quantity            Price\n\n");
			printf("                             NO RECORD FOUND!\n\n");
			printf("======================================================================\n\n");
			printf("\n\n\n\n\n\n\n------------------------Press any key to back-------------------------\n");
			back = getch();
			if (back)
				break;
		}

		printf("Enter the product ID : ");
		/*check = scanf("%s", del_prodID);
		rewind(stdin);*/

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
			fseek(readShopCart, 0, SEEK_SET);

			while (fread(&org, sizeof(Product), 1, readShopCart) != 0) {
				if (strcmp(del_prodID, org.prodID) != 0) {
					fwrite(&org, sizeof(Product), 1, tempShopCart);
				}

				else {
					found++;
				}
			}

			if (found == 0) {
				fclose(readShopCart);
				fclose(tempShopCart);

				red();
				printf("\n\nProduct ID not found in shopping cart!\a\n");
				Sleep(1000);
				system("color f0");
				system("cls");
				printf("SHOPPING CART\n");
				printf("======================================================================\n");
				printf("Product ID           Product Name            Quantity            Price\n");
				rShopCart();
				printf("======================================================================\n\n");
			}

			else {
				found = 0;
				fclose(readShopCart);
				fclose(tempShopCart);

				remove(shop.sCartID);
				rename(temp, shop.sCartID);

				newShopCart = fopen(shop.sCartID, "rb");

				red();
				printf("\n\nDelete Successfully!\n");
				Sleep(1000);
				system("color f0");
				system("cls");
				printf("SHOPPING CART\n");
				printf("======================================================================\n");
				printf("Product ID           Product Name            Quantity            Price\n");

				while (fread(&remain, sizeof(Product), 1, newShopCart) != 0) {
					printf("%-20s %-23s %-19d %-6.2f\n", remain.prodID, remain.prodName, remain.qty, remain.price);
				}

				printf("======================================================================\n\n");

				fclose(newShopCart);
			}		
		}

	} while (!back);

	return back;
}

int selectBuy(char *checkout) {
	system("cls");

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;
	char sel[100];

	Product read;
	Product org[1000];
	Product select[1000];

	sprintf(sel, "Selected ShopCart (Customer Id %d).dat", shop.cartID);
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %d).dat", shop.cartID);

	int i, j, k, error = 0, character, count, found = 0, back = 0, selected = 0;
	char a, check, selProdID[6];

	FILE* readShopCart;
	FILE* selShopCart;
	FILE* readSelect;

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

	fseek(readShopCart, 0, SEEK_SET);
	printf("SHOPPING CART\n");
	printf("==============================================================================================\n");
	printf("Product ID           Product Name            Quantity            Price             Status\n");

	j = 0;
	while (fread(&org[j], sizeof(Product), 1, readShopCart) != 0) {
		printf("%-20s %-23s %-19d %-17.2f %-15s\n", org[j].prodID, org[j].prodName, org[j].qty, org[j].price, org[j].status);
		j++;
	}

	fclose(readShopCart);
	printf("==============================================================================================\n");
	printf("1. Back \t\t\t\t\t\t\t 2. CheckOut\n\n");

	do {
		printf("Enter the product ID : ");
		//check = scanf("%s", selProdID);  // Selected Product ID
		//character = strlen(selProdID);
		//rewind(stdin);

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

		if (strcmp(selProdID, "2") == 0) {
			readShopCart = fopen(shop.sCartID, "rb");
			while (fread(&read, sizeof(Product), 1, readShopCart) != 0) {
				if (strcmp(read.status, "Selected") == 0) {	
					selected++;
				}
			}

			fclose(readShopCart);

			if (selected > 0) {
				*checkout = '2';
				break;
			}	

			else {
				red();
				printf("\nPlease select at least 1 product!\a\n");
				Sleep(1000);
				system("color f0");
				system("cls");
			}
		}

		else if (character == 5) {
			i = 0;

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
				printf("\nProduct ID not found in shopping cart!\a\n");
				Sleep(1000);
				system("color f0");
				system("cls");
				printf("SHOPPING CART\n");
				printf("==============================================================================================\n");
				printf("Product ID           Product Name            Quantity            Price             Status\n");

				readShopCart = fopen(shop.sCartID, "rb");
				selShopCart = fopen(sel, "rb");

				if (readShopCart == NULL || selShopCart == NULL) {
					printf("File can't open!\n");
					exit(-1);
				}

				if (error == 0) {
					while (fread(&read, sizeof(Product), 1, readShopCart) != 0) {
						printf("%-20s %-23s %-19d %-17.2f %-15s\n", read.prodID, read.prodName, read.qty, read.price, read.status);
					}
				}

				else {
					while (fread(&read, sizeof(Product), 1, selShopCart) != 0) {
						printf("%-20s %-23s %-19d %-17.2f %-15s\n", read.prodID, read.prodName, read.qty, read.price, read.status);
					}
				}

				printf("==============================================================================================\n");
				printf("1. Back \t\t\t\t\t\t\t 2. CheckOut\n\n");

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
				printf("SHOPPING CART\n");
				printf("==============================================================================================\n");
				printf("Product ID           Product Name            Quantity            Price             Status\n");

				i = 0;
				while (fread(&select[i], sizeof(Product), 1, selShopCart) != 0) {
					printf("%-20s %-23s %-19d %-17.2f %-20s\n", select[i].prodID, select[i].prodName, select[i].qty, select[i].price, select[i].status);
					i++;
				}

				printf("==============================================================================================\n");
				printf("1. Back \t\t\t\t\t\t\t 2. CheckOut\n\n");

				fclose(selShopCart);
			}
		}

		else {
			found = 0;

			if (character < 5) {
				red();
				printf("\n\nProduct ID must have 5 character!\a\n");
				Sleep(1000);
				system("color f0");
				system("cls");
			}
			else {
				red();
				printf("\n\nProduct ID have only 5 character!\a\n");
				Sleep(1000);
				system("color f0");
				system("cls");
			}

		
			printf("SHOPPING CART\n");
			printf("==============================================================================================\n");
			printf("Product ID           Product Name            Quantity            Price             Status\n");

			readShopCart = fopen(shop.sCartID, "rb");
			selShopCart = fopen(sel, "rb");

			if (readShopCart == NULL || selShopCart == NULL) {
				printf("File can't open!\n");
				exit(-1);
			}

			if (error == 0) {
				while (fread(&read, sizeof(Product), 1, readShopCart) != 0) {
					printf("%-20s %-23s %-19d %-17.2f %-15s\n", read.prodID, read.prodName, read.qty, read.price, read.status);
				}
			}

			else {
				while (fread(&read, sizeof(Product), 1, selShopCart) != 0) {
					printf("%-20s %-23s %-19d %-17.2f %-15s\n", read.prodID, read.prodName, read.qty, read.price, read.status);
				}
			}

			printf("==============================================================================================\n");
			printf("1. Back \t\t\t\t\t\t\t 2. CheckOut\n\n");

			fclose(readShopCart);
			fclose(selShopCart);
		}

	} while (strcmp(selProdID, "2") != 0 && !back);

	return back;
}

void buyNow(char prodID[], char prodName[], int qty, double price) {
	SYSTEMTIME t;
	GetLocalTime(&t);

	int choice, orderID = 1, i = 0, j = 0;
	double subTotal = qty * price;
	double total = subTotal + (subTotal * COMMISSION);
	char buyAgainFile[50], temporary[50], history[50];

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	BuyAgain bAgain[1000];

	sprintf(buyAgainFile, "Buy Again (Customer Id %d).dat", shop.cartID);
	sprintf(temporary, "Temporary ShopCart (Customer Id %d).dat", shop.cartID);
	sprintf(history, "Purchase History (Customer Id %d).txt", shop.cartID);

	FILE* rAgain;
	FILE* temp;
	FILE* wHistory;

	rAgain = fopen(buyAgainFile, "rb");
	temp = fopen(temporary, "wb");
	wHistory = fopen(history, "a");

	if (rAgain == NULL || temp == NULL || wHistory == NULL) {
		printf("File can't open!\n");
		exit(-1);
	}

	printf("\t\t\t\tCheckout\n");
	printf("======================================================================\n");
	printf("Booking ID : B%04d\n", orderID);
	printf("======================================================================\n");
	printf("Product ID \t\t Product Name \t\t Quantity \t\t Price\n");
	printf("----------------------------------------------------------------------\n");
	printf("%s \t\t %s \t\t %d \t\t %.2f\n\n", prodID, prodName, qty, price);
	printf("======================================================================\n");
	printf("Sub Total  \t\t\t\t\t\t %.2f\n", subTotal);
	printf("Commission \t\t\t\t\t\t %.0f%%\n", COMMISSION * 100);
	printf("----------------------------------------------------------------------\n");
	printf("Total \t\t\t\t\t\t %.2f", total);
	printf("======================================================================\n");
	printf("1. Back \t\t\t\t\t\t 2. Place Order\n\n");
	printf("Please select one : ");
	scanf("%d", &choice);
	rewind(stdin);

	if (choice == 2) {
		while (fread(&bAgain[i], sizeof(BuyAgain), 1, rAgain) != 0) {
			i++;
		}

		fwrite(&prodID, sizeof(prodID), 1, temp);
		fwrite(&prodName, sizeof(prodName), 1, temp);

		for (j = 0; j < i; j++) {
			if (strcmp(prodID, bAgain[j].prodID) != 0) {
				fwrite(&bAgain[j].prodID, sizeof(bAgain[j].prodID), 1, temp);
				fwrite(&bAgain[j].prodName, sizeof(bAgain[j].prodName), 1, temp);
			}
		}

		fprintf(wHistory, "%02d/%02d/%d %02d:%02d:%02d %s %d %s %lf\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond, prodID, qty, prodName, price);
	}

	fclose(rAgain);
	fclose(temp);
	fclose(wHistory);
}

void checkoutAll() {
	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	int choice, orderID = 1;
	double total;
	char buyAgain[50], temp[50];

	sprintf(shop.sCartID, "Shopping Cart (Customer Id %d).dat", shop.cartID);
	sprintf(buyAgain, "Buy Again (Customer Id %d).dat", shop.cartID);
	sprintf(temp, "Temporary ShopCart (Customer Id %d).dat", shop.cartID);

	FILE* shopCart;
	shopCart = fopen(shop.sCartID, "rb");
	
	system("cls");

	printf("\t\t\t\t\t\tCheckout\n");
	printf("======================================================================\n");
	printf("Order ID : O%04d\n", orderID);
	printf("======================================================================\n");
	printf("Product ID           Product Name            Quantity            Price\n\n");

	rShopCart();

	printf("======================================================================\n");
	printf("Total                                                          ");

	total = totalPrice(shopCart);

	printf("======================================================================\n");

	printf("\n1. Back");
	printf("                                      2. Place Order\n");
	printf("\nPlease select one : ");
	scanf("%d", &choice);
	rewind(stdin);

	fclose(shopCart);

	if (choice == 2) {
		system("cls");

		FILE* totalSales;
		FILE* clear;

		printf("%.2lf\n", total);

		placeOrder(shop.sCartID, buyAgain, temp);

		totalSales = fopen("totalSales.dat", "ab");	
		
		if (totalSales == NULL) {
			printf("totalSales can't open!\n");
			exit(-1);
		}

		fwrite(&total, sizeof(total), 1, totalSales);
		fclose(totalSales);
		
		purchaseHistory(shop.sCartID);

		clear = fopen(shop.sCartID, "wb");
		fclose(clear);
	}	
}

void checkoutSelect() {
	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	int choice, orderID = 1;
	char selectedShopCart[50], buyAgain[50], temp[50];
	double total;

	sprintf(selectedShopCart, "Selected ShopCart (Customer Id %d).dat", shop.cartID);
	sprintf(shop.sCartID, "Shopping Cart (Customer Id %d).dat", shop.cartID);
	sprintf(buyAgain, "Buy Again (Customer Id %d).dat", shop.cartID);
	sprintf(temp, "Temporary ShopCart (Customer Id %d).dat", shop.cartID);

	Product read;

	FILE* shopCart;
	shopCart = fopen(selectedShopCart, "rb");

	if (shopCart == NULL) {
		printf("shopCart can't open!\n");
		exit(-1);
	}

	system("cls");

	printf("Checkout\n");
	printf("======================================================================\n");
	printf("Order ID : O%-04d\n", orderID);
	printf("======================================================================\n");
	printf("Product ID           Product Name            Quantity            Price\n\n");

	while (fread(&read, sizeof(Product), 1, shopCart) != 0) {
		if (strcmp(read.status, "Selected") == 0) {
			printf("%-20s %-23s %-19d %-6.2f\n", read.prodID, read.prodName, read.qty, read.price);
		}		
	}

	printf("======================================================================\n");
	printf("Total                                                          ");

	total = totalPrice(shopCart);

	printf("======================================================================\n");

	printf("\n1. Back");
	printf("                                      2. Place Order\n");
	printf("\nPlease select one : ");
	scanf("%d", &choice);
	rewind(stdin);

	fclose(shopCart);

	if (choice == 2) {
		system("cls");

		FILE* totalSales;
		FILE* filter;
		FILE* reset;

		printf("%.2lf\n", total);

		placeOrder(selectedShopCart, buyAgain, temp);

		totalSales = fopen("totalSales.dat", "ab");

		if (totalSales == NULL) {
			printf("totalSales can't open!\n");
			exit(-1);
		}

		fwrite(&total, sizeof(total), 1, totalSales);
		fclose(totalSales);

		purchaseHistory(selectedShopCart);

		filter = fopen(selectedShopCart, "rb");
		reset = fopen(shop.sCartID, "wb");

		while (fread(&read, sizeof(Product), 1, filter) != 0) {
			if (strcmp(read.status, "No Selected") == 0) {
				fwrite(&read, sizeof(Product), 1, reset);
			}
		}

		fclose(filter);
		fclose(reset);
	}
}

double totalPrice(FILE* order) {
	Product read;

	int filter = 0;
	double subTotal, total = 0;

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

	printf("%.2f\n", total);
	printf("Comission: %.2lf\n", COMMISSION);
	total += total * COMMISSION;
	printf("%.2f\n", total);

	fclose(order);

	return total;
}

void placeOrder(char shopCart[], char buyAgain[], char temporary[]) {
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

	while(1) {
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

	remove(buyAgain);
	rename(temporary, buyAgain);
}

int buyAgain() {
	system("cls");

	char choice, selection;
	char bAgain[50], prodID[6];
	int i = 0, qty, label, back = 0;

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	BuyAgain buyAgain;

	sprintf(bAgain, "Buy Again (Customer Id %d).dat", shop.cartID);

	FILE* rAgain;
	rAgain = fopen(bAgain, "rb");

	label = 0;
	first_loop:
	do {
		system("cls");

		printf("\n  <--");
		printf("\n\n\t\t\t\t\t\t\t Buy Again\n");
		printf("\t\t======================================================================================\n");
		printf("\t\t\t\tProduct ID \t\t\t\t Product Name\n");
		printf("\t\t--------------------------------------------------------------------------------------\n");

		fseek(rAgain, 0, SEEK_SET);
		while (fread(&buyAgain, sizeof(BuyAgain), 1, rAgain) != 0) {
			printf("\t\t\t\t   %s \t\t\t\t    %s\n", buyAgain.prodID, buyAgain.prodName);
		}

		printf("\t\t======================================================================================\n\n");
		printf("\t\t 1. Buy Now \t\t\t\t\t\t\t\t2. Add to Cart\n");

		selection = getch();
		
		if (GetAsyncKeyState(VK_LEFT) != 0) {
			back = 1;
			return back;		
		}

		if (selection == '1' || selection == '2') {
			// Buy Now or Add to Cart
			do {
				system("cls");

				printf("\n  <--");
				printf("\n\n\t\t\t\t\t\t\t Buy Again\n");
				printf("\t\t======================================================================================\n");
				printf("\t\t\t\tProduct ID \t\t\t\t Product Name\n");
				printf("\t\t--------------------------------------------------------------------------------------\n");

				fseek(rAgain, 0, SEEK_SET);
				while (fread(&buyAgain, sizeof(BuyAgain), 1, rAgain) != 0) {
					printf("\t\t\t\t   %s \t\t\t\t    %s\n", buyAgain.prodID, buyAgain.prodName);
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

				fseek(rAgain, 0, SEEK_SET);
				while (fread(&buyAgain, sizeof(BuyAgain), 1, rAgain) != 0) {
					if (strcmp(prodID, buyAgain.prodID) == 0) {
						// Product ID found in Buy Again, Enter quantity
						printf("\n\t\t Quantity : ");
						scanf("%d", &qty);

						/*
							Stock Quantity Validation
						*/

						if (selection == '1') {
							// Buy Now
							system("cls");
							buyNow(buyAgain.prodID, buyAgain.prodName, qty, 7.00);
						}
							
						else {
							// Add to Cart
							shoppingCart(buyAgain.prodID, buyAgain.prodName, qty, 7.00);
							red();
							printf("\n\t\t Add Successfully!\n");
							Sleep(1000);
							system("color f0");
							system("cls");
						}
					}

					else {
						// Product ID not found in Buy Again
						red();
						printf("\n\t\t Product ID not found! Please try again.\a\n");
						Sleep(1000);
						system("color f0");
					}
				}
			} while (strcmp(prodID, buyAgain.prodID) != 0);
		}
		
		else if (!label) {
			red();
			printf("\n\t\t Invalid input! Please try again.\a\n");
			Sleep(1000);
			system("color f0");
			system("cls");
		}

		label = 0;
	} while (selection != '1' && selection != '2');

	fclose(rAgain);
}

void purchaseHistory(char buyCart[]) {
	SYSTEMTIME t;
	GetLocalTime(&t);

	char history[50];
	int filter = 0;

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	Product read;

	sprintf(history, "Purchase History (Customer Id %d).txt", shop.cartID);

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

char viewHistory() {
	system("cls");

	struct ShoppingCart shop;
	shop.custID = 1;
	shop.cartID = shop.custID;

	ViewHistory vHistory[1000];
	ViewHistory sHistory[1000];

	char history[50];
	char choice;
	int i = 0, j = 0, back = 0;
	double subTotal = 0, total = 0;

	sprintf(history, "Purchase History (Customer Id %d).txt", shop.cartID);

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
						system("color f0");
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
						system("color f0");
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
						system("color f0");
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
						system("color f0");
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
						system("color f0");
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
						system("color f0");
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
				system("color f0");
			}

			oneTime++;
		}

	} while (selection != '1' && selection != '2' && selection != '3');

	return back;
}

void monthlySales() {
	double price, total, charge;

	system("cls");
	//curTime();
	printf("\n\nTotal Sales Record\n");
	printf("====================================================\n\n");

	FILE* commission;
	commission = fopen("totalSales.dat", "rb");

	if (commission == NULL) {
		printf("commission can't open!\n");
		exit(-1);
	}

	printf("Sales Order ID        Customer ID        Total Sales\n");

	while (fread(&total, sizeof(total), 1, commission) != 0) {		
		printf("1                     1                   %.2f\n", total);
		total += total;
	}   

	printf("====================================================\n");
	printf("TOTAL %42.2f\n", total);
}

double commission(monthlySales) {
	double charge;

	charge = monthlySales * 0.05;
	printf("\nCharge of commission to up line > %.2f\n", charge);
}