#include "MLM.h"

//read stock from file
void read_stock_from_file() {
	FILE* file = fopen("stock.txt", "r");
	if (file != NULL) {
		char item_code[20];
		char item_description[100];
		float item_price;
		int item_quantity, minimum_level, reorder_quantity;
		int i = 0;

		while (fscanf(file, "%[^|]|%[^|]|%f|%d|%d|%d", &item_code, &item_description, &item_price, &item_quantity, &minimum_level, &reorder_quantity) == 6) {

			StockItem item;//temp array
			strcpy(item.item_code, item_code);
			strcpy(item.item_description, item_description);
			item.item_price = item_price;
			item.item_quantity = item_quantity;
			item.minimum_level = minimum_level;
			item.reorder_quantity = reorder_quantity;
			stockItem[i++] = item;//temp array info add to stockitem array
			fscanf(file, "\n");
		}
		fclose(file);
		numOfItem = i;
	}
}


//search item quantity
int search_item_quantity(int item_quantity[]) {
	for (int i = 0; i < numOfItem; i++) {
		if (strcmp(stockItem[i].item_quantity, item_quantity) == 0) {
			return i;
		}
	}
	return -1;
}
//alert when less than stock minimum level
void minimum_stock_alert() {
	read_stock_from_file();
	int j = 0;
	for (int i = 0; i < numOfItem; i++) {
		if (stockItem[i].item_quantity <= stockItem[i].minimum_level) {
			j = 1;
			break;
		}
	}

	if (j == 1) {
		printf("\t\t\t\t\t\tStock Level ALERT!!!\a\n");
		Sleep(20);
		printf("\t\t\t     ---------------------------------------------------------\n");
		Sleep(20);
		printf("\t\t\t     |  Item Code |    Description    | Quantity | Min Level | \n");
		Sleep(20);
		printf("\t\t\t     ---------------------------------------------------------\n");

		for (int i = 0; i < numOfItem; i++) {

			if (stockItem[i].item_quantity <= stockItem[i].minimum_level) {
				printf("\t\t\t     |    %-10s%-20s% -5d%12d    |\n", stockItem[i].item_code, stockItem[i].item_description, stockItem[i].item_quantity, stockItem[i].minimum_level);
				Sleep(20);

			}

		}
		Sleep(20);
		printf("\t\t\t     ---------------------------------------------------------\n");
		Sleep(20);
		printf("\t\t\tQuantity of the following items has been LOWER than minimum level!\n");
		system("pause");
		system("cls");
	}


}
//write stock to file
void write_stock_to_file() {
	FILE* file = fopen("stock.txt", "w");
	FILE* file2 = fopen("time.txt", "w");

	if (file != NULL) {
		for (int i = 0; i < numOfItem; i++) {
			StockItem item = stockItem[i];
			fprintf(file, "%s|%s|%.2f|%d|%d|%d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
		}
		fclose(file);
	}

	if (file2 != NULL) {
		char lastest_time[30];
		curTime(lastest_time);
		strcpy(cur_time, lastest_time);
		fprintf(file2, "%s\n", cur_time);
	}
	fclose(file2);
}

//search item by item code
void search_stock_item_code() {
	int o = 0;
	do
	{
		int num = 0;
		system("cls");
		char item_code[10];
		printf("Enter item code to search (or exit to quit):");
		scanf("%[^\n]", item_code);
		rewind(stdin);
		if (strcmp("exit", item_code) == 0) {
			return 0;
		}
		num = search_item_code(item_code);
		if (num != -1) {
			StockItem item = stockItem[num];
			printf("\t\t\t-----------------------------------------------------------------------------\n");
			printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
			printf("\t\t\t-----------------------------------------------------------------------------\n");
			printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
			printf("\t\t\t------------------------------------------------------------------------------\n");
			system("pause");
		}
		else {
			printf("Item Not Found!\n\a");
			Sleep(1500);
			o = -1;
		}
	} while (o == -1);



}
//modify item information
void update_stock_item() {
	char item_code[10];
	printf("Enter item code to modify (or exit to quit):");
	scanf("%[^\n]", item_code);
	if (strcmp("exit", item_code) == 0) {
		return 0;
	}
	rewind(stdin);
	int num = search_item_code(item_code);
	if (num != -1) {
		StockItem item = stockItem[num];

		printf("\t\t\t-----------------------------------------------------------------------------\n");
		printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
		printf("\t\t\t-----------------------------------------------------------------------------\n");

		int er = 1;
		while (er == 1) {

			printf("Enter new item description (Enter / to keep current value):");
			char new_item_description[100];
			scanf("%[^\n]", new_item_description);
			rewind(stdin);
			if (strcmp(new_item_description, "/") == 0) {
				printf("Current Value Saved!\n\n");
				er = 0;
			}
			else if (strlen(new_item_description) > 0 && strlen(new_item_description) <= 18) {
				strcpy(item.item_description, new_item_description);
				er = 0;
			}
			else {
				printf("\t\t\tItem descriptions should not exceed 18 characters\n\n\a");
				Sleep(2000);
				system("cls");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				er = 1;
			}
		}
		er = 1;
		while (er == 1) {

			printf("Enter new item price (Enter 0 to keep current value): ");
			float new_item_price;
			scanf("%f", &new_item_price);
			rewind(stdin);
			if (new_item_price > 0) {
				item.item_price = new_item_price;
				er = 0;
			}
			else if (new_item_price == 0) {
				printf("Current Value Saved!\n\n");
				er = 0;
			}
			else {
				printf("\t\t\tOnly numbers are allowed!\n\n\a");
				Sleep(2000);
				system("cls");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				er = 1;
			}
		}
		er = 1;
		while (er == 1) {
			printf("Enter new quantity in stock (Enter 0 to keep current value): ");
			int new_item_quantity;
			scanf("%d", &new_item_quantity);
			rewind(stdin);
			if (new_item_quantity > 0) {
				item.item_quantity = new_item_quantity;
				er = 0;
			}
			else if (new_item_quantity == 0) {
				printf("Current Value Saved!\n\n");
				er = 0;
			}
			else {
				printf("\t\t\tOnly numbers are allowed!\n\n\a");
				Sleep(2000);
				system("cls");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				er = 1;
			}
		}
		er = 1;
		while (er == 1) {
			printf("Enter new minimum level (Enter 0 to keep current value): ");
			int new_minimum_level;
			scanf("%d", &new_minimum_level);
			rewind(stdin);
			if (new_minimum_level > 0) {
				item.minimum_level = new_minimum_level;
				er = 0;
			}
			else if (new_minimum_level == 0) {
				printf("Current Value Saved!\n\n");
				er = 0;
			}
			else {
				printf("\t\t\tOnly numbers are allowed!\n\n\a");
				Sleep(2000);
				system("cls");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				er = 1;
			}
		}
		er = 1;
		while (er == 1) {
			printf("Enter new reorder quantity (Enter 0 to keep current value): ");
			int new_reorder_quantity;
			scanf("%d", &new_reorder_quantity);
			rewind(stdin);
			if (new_reorder_quantity > 0) {
				item.reorder_quantity = new_reorder_quantity;
				er = 0;
			}
			else if (new_reorder_quantity == 0) {
				printf("Current Value Saved!\n\n");
				er = 0;
			}
			else {
				printf("\t\t\tOnly numbers are allowed!\n\n\a");
				Sleep(2000);
				system("cls");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
				printf("\t\t\t-----------------------------------------------------------------------------\n");
				er = 1;
			}
		}
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		system("pause");
		stockItem[num] = item;
		write_stock_to_file();
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tStock Updated Successfully!\n");
		Sleep(1300);
	}
	else {
		system("cls");
		printf("Item Not Found!\n\a");
		Sleep(1300);
	}

	system("cls");
}
//import file to add stock
void import_file_to_add_stock() {
	char file_location[50];
	FILE* fptr = fopen("stock.txt", "a");
	system("cls");
	printf("Enter your files location or drag and drop your files here (or exit to quit) \n>>");
	scanf("%[^\n]", file_location);
	if (strcmp("exit", file_location) == 0) {
		return 0;
	}
	rewind(stdin);
	FILE* fptr2 = fopen(file_location, "r");
	if (fptr == NULL || fptr2 == NULL) {
		system("cls");
		printf("Can't find Your file!\a");
		Sleep(1800);
		return 0;
	}
	char item_code[20];
	char item_description[100];
	float item_price;
	int item_quantity, minimum_level, reorder_quantity;
	char new_item_code[20];
	char new_item_description[100];
	char valid[1000];
	int i = 0;

	while (fscanf(fptr2, "%[^\|]|\n", &valid) == 1) {
		i++;
	}
	if (i % 5 == 0) {
		i = -1;
	}
	else {
		i = 1;
	}
	fclose(fptr2);

	FILE* fptr3 = fopen(file_location, "r");
	if (i == 1) {

		while (fscanf(fptr3, "%[^|]|%[^|]|%f|%d|%d|%d\n", &item_code, &item_description, &item_price, &item_quantity, &minimum_level, &reorder_quantity) == 6) {

			StockItem item;
			strcpy(item.item_code, item_code);
			strcpy(item.item_description, item_description);
			item.item_price = item_price;
			item.item_quantity = item_quantity;
			item.minimum_level = minimum_level;
			item.reorder_quantity = reorder_quantity;
			stockItem[i++] = item;
			fprintf(fptr, "%s|%s|%.2f|%d|%d|%d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
		}

		system("cls");
		printf("Data has been successfully imported and saved!\n");
		Sleep(2000);
		system("cls");
	}
	else if (i == -1) {
		system("cls");
		printf("Data import failed, please check if the data FORMAT is correct.\n\a");
		Sleep(2000);
		system("cls");
		return 0;
	}

	fclose(fptr3);
	fclose(fptr);
}
//add new item to stock with random generate code
void add_item_to_stock_rand_generate() {
	StockItem item;
	char letter;
	int number[4];
	char itemCode[6];
	char choice;
	int j = 0, i;
	system("cls");

	do
	{
		system("cls");
		srand(time(NULL));
		for (i = 0; i < 4; i++) {
			number[i] = rand() % 10;
		}

		sprintf(itemCode, "%d%d%d%d", number[0], number[1], number[2], number[3]);
		strcpy(item.item_code, itemCode);
		printf("Item Code: %s\n", item.item_code);
		printf("Press R to regenerate or ENTER to continue");
		choice = getche();
		rewind(stdin);
	} while (choice == 'r' || choice == 'R');

	for (int i = 0; i < numOfItem; i++) {

		if (strcmp(item.item_code, stockItem[i].item_code) == 0) {
			system("cls");
			printf("Item Code already exits\n");
			Sleep(1200);
			system("cls");
			j = -1;
			break;
		}
	}
	if (j != -1) {
		system("cls");
		printf("\t\t\t\t\t================================\n");
		printf("\t\t\t\t\t            ADD ITEM            \n");
		printf("\t\t\t\t\t================================\n\n\n");

		printf("\t\t\tItem Code: %s\n", item.item_code);
		strcpy(item.item_description, "");
		printf("\t\t\tEnter item description : ");
		scanf("%[^\n]", item.item_description);
		rewind(stdin);
		while (strlen(item.item_description) == 0 || strlen(item.item_description) > 18) {

			if (strlen(item.item_description) == 0) {
				printf("\t\t\tItem description must NOT be empty\a\n");
				Sleep(2000);
			}
			else {
				printf("\t\t\tItem descriptions should NOT exceed 18 characters\a\n");
				Sleep(2000);

			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tEnter item description : ");
			scanf("%[^\n]", item.item_description);
			rewind(stdin);
		}



		int er = 1;
		while (er == 1) {
			printf("\t\t\tEnter item price : ");
			scanf("%f", &item.item_price);
			rewind(stdin);
			if (item.item_price == 0) {
				printf("\t\t\titem price must NOT be 0 !\a\n");
				Sleep(2000);

			}
			else if (item.item_price >= 9999) {
				printf("\t\t\tItem price must NOT exceed 9999 !\a\n");
				Sleep(2000);

			}
			else if (item.item_price > 0 && item.item_price <= 9999) {
				break;
			}
			else {
				printf("\t\t\tInput error\a\n");
				Sleep(2000);
			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tItem Code        : %s\n", item.item_code);
			printf("\t\t\tItem Description : %s\n", item.item_description);
		}


		while (er == 1) {
			printf("\t\t\tEnter quantity in stock: ");
			scanf("%d", &item.item_quantity);
			rewind(stdin);
			if (item.item_quantity == 0) {
				printf("\t\t\titem quantity must NOT be 0 !\a\n");
				Sleep(2000);

			}
			else if (item.item_quantity >= 99999) {
				printf("\t\t\tItem quantity must NOT exceed 99999 !\a\n");
				Sleep(2000);

			}
			else if (item.item_quantity > 0 && item.item_quantity <= 99999) {
				break;
			}
			else {
				printf("\t\t\tInput error\a\n");
				Sleep(2000);
			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tItem Code        : %s\n", item.item_code);
			printf("\t\t\tItem Description : %s\n", item.item_description);
			printf("\t\t\tItem Price       : %.2f\n", item.item_price);
		}

		while (er == 1) {
			printf("\t\t\tEnter minimum level : ");
			scanf("%d", &item.minimum_level);
			rewind(stdin);
			if (item.minimum_level == 0) {
				printf("\t\t\tMinimum level must NOT be 0 !\a\n");
				Sleep(2000);

			}
			else if (item.minimum_level >= 99999) {
				printf("\t\t\tMinimum level must NOT exceed 99999 !\a\n");
				Sleep(2000);

			}
			else if (item.minimum_level > 0 && item.minimum_level <= 99999) {
				break;
			}
			else {
				printf("\t\t\tInput error\a\n");
				Sleep(2000);
			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tItem Code        : %s\n", item.item_code);
			printf("\t\t\tItem Description : %s\n", item.item_description);
			printf("\t\t\tItem Price       : %.2f\n", item.item_price);
			printf("\t\t\tItem Quantity    : %d\n", item.item_quantity);

		}

		while (er == 1) {
			printf("\t\t\tEnter reorder quantity : ");
			scanf("%d", &item.reorder_quantity);
			rewind(stdin);
			if (item.reorder_quantity == 0) {
				printf("\t\t\tReorder quantity must NOT be 0 !\a\n");
				Sleep(2000);

			}
			else if (item.reorder_quantity >= 99999) {
				printf("\t\t\tReorder quantity must NOT exceed 99999 !\a\n");
				Sleep(2000);

			}
			else if (item.reorder_quantity > 0 && item.reorder_quantity <= 99999) {
				break;
			}
			else {
				printf("\t\t\tInput error\a\n");
				Sleep(2000);
			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tItem Code        : %s\n", item.item_code);
			printf("\t\t\tItem Description : %s\n", item.item_description);
			printf("\t\t\tItem Price       : %.2f\n", item.item_price);
			printf("\t\t\tItem Quantity    : %d\n", item.item_quantity);
			printf("\t\t\tMinimum Level    : %d\n", item.minimum_level);
		}

		stockItem[numOfItem++] = item;
		write_stock_to_file();
		printf("\t\t\tStock item added successfully!\n");
		Sleep(2000);
	}
	system("cls");
}

//add new item to stock
void add_item_to_stock() {

	StockItem item;
	char itemCode[10];
	int j = 0, i;
	system("cls");


	do
	{
		read_stock_from_file();
		printf("\t\t\t\t\t================================\n");
		printf("\t\t\t\t\t            ADD ITEM            \n");
		printf("\t\t\t\t\t================================\n\n\n");
		printf("\t\t\tLast Item Code: %s\n", stockItem[numOfItem - 1].item_code);

		j = 0;
		printf("\t\t\tEnter Item Code (or exit to quit): ");
		scanf("%[^\n]", &item.item_code);
		if (strcmp("exit", &item.item_code) == 0) {
			return 0;
		}
		rewind(stdin);


		if (strlen(item.item_code) != 4) {
			system("cls");
			printf("\t\t\tThe ITEM CODE must be 4 CHARACTERS \n\a");
			Sleep(2000);
			system("cls");
			j = -1;
		}
		if (j != -1) {
			for (int i = 0; i < numOfItem; i++) {

				if (strcmp(item.item_code, stockItem[i].item_code) == 0) {
					system("cls");
					printf("\t\t\tItem Code already exits\n");
					Sleep(1200);
					system("cls");
					j = -1;

				}
			}
		}

	} while (j == -1);



	system("cls");
	printf("\t\t\t\t\t================================\n");
	printf("\t\t\t\t\t            ADD ITEM            \n");
	printf("\t\t\t\t\t================================\n\n\n");
	printf("\t\t\tItem Code :%s\n", item.item_code);

	if (j != -1) {
		strcpy(item.item_description, "");
		printf("\t\t\tEnter item description : ");
		scanf("%[^\n]", item.item_description);
		rewind(stdin);
		while (strlen(item.item_description) == 0 || strlen(item.item_description) > 18) {

			if (strlen(item.item_description) == 0) {
				printf("\t\t\tItem description must NOT be empty\a\n");
				Sleep(2000);
			}
			else {
				printf("\t\t\tItem descriptions should NOT exceed 18 characters\a\n");
				Sleep(2000);

			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tEnter item description : ");
			scanf("%[^\n]", item.item_description);
			rewind(stdin);
		}



		int er = 1;
		while (er == 1) {
			printf("\t\t\tEnter item price : ");
			scanf("%f", &item.item_price);
			rewind(stdin);
			if (item.item_price == 0) {
				printf("\t\t\tItem price must NOT be 0 !\a\n");
				Sleep(2000);

			}
			else if (item.item_price >= 9999) {
				printf("\t\t\tItem price must NOT exceed 9999 !\a\n");
				Sleep(2000);

			}
			else if (item.item_price > 0 && item.item_price <= 9999) {
				break;
			}
			else {
				printf("\t\t\tInput error\a\n");
				Sleep(2000);
			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tItem Code        : %s\n", item.item_code);
			printf("\t\t\tItem Description : %s\n", item.item_description);
		}


		while (er == 1) {
			printf("\t\t\tEnter quantity in stock : ");
			scanf("%d", &item.item_quantity);
			rewind(stdin);
			if (item.item_quantity == 0) {
				printf("\t\t\tItem quantity must NOT be 0 !\a\n");
				Sleep(2000);

			}
			else if (item.item_quantity >= 99999) {
				printf("\t\t\tItem quantity must NOT exceed 99999 !\a\n");
				Sleep(2000);

			}
			else if (item.item_quantity > 0 && item.item_quantity <= 99999) {
				break;
			}
			else {
				printf("\t\t\tInput error\a\n");
				Sleep(2000);
			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tItem Code        : %s\n", item.item_code);
			printf("\t\t\tItem Description : %s\n", item.item_description);
			printf("\t\t\tItem Price       : %.2f\n", item.item_price);
		}

		while (er == 1) {
			printf("\t\t\tEnter minimum level : ");
			scanf("%d", &item.minimum_level);
			rewind(stdin);
			if (item.minimum_level == 0) {
				printf("\t\t\tMinimum level must NOT be 0 !\a\n");
				Sleep(2000);

			}
			else if (item.minimum_level >= 99999) {
				printf("\t\t\tMinimum level must NOT exceed 99999 !\a\n");
				Sleep(2000);

			}
			else if (item.minimum_level > 0 && item.minimum_level <= 99999) {
				break;
			}
			else {
				printf("\t\t\tInput error\a\n");
				Sleep(2000);
			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tItem Code        : %s\n", item.item_code);
			printf("\t\t\tItem Description : %s\n", item.item_description);
			printf("\t\t\tItem Price       : %.2f\n", item.item_price);
			printf("\t\t\tItem Quantity    : %d\n", item.item_quantity);

		}

		while (er == 1) {
			printf("\t\t\tEnter reorder quantity : ");
			scanf("%d", &item.reorder_quantity);
			rewind(stdin);
			if (item.reorder_quantity == 0) {
				printf("\t\t\tReorder quantity must NOT be 0 !\a\n");
				Sleep(2000);

			}
			else if (item.reorder_quantity >= 99999) {
				printf("\t\t\tReorder quantity must NOT exceed 99999 !\a\n");
				Sleep(2000);

			}
			else if (item.reorder_quantity > 0 && item.reorder_quantity <= 99999) {
				break;
			}
			else {
				printf("\t\t\tInput error\a\n");
				Sleep(2000);
			}
			system("cls");
			printf("\t\t\t\t\t================================\n");
			printf("\t\t\t\t\t            ADD ITEM            \n");
			printf("\t\t\t\t\t================================\n\n\n");
			printf("\t\t\tItem Code        : %s\n", item.item_code);
			printf("\t\t\tItem Description : %s\n", item.item_description);
			printf("\t\t\tItem Price       : %.2f\n", item.item_price);
			printf("\t\t\tItem Quantity    : %d\n", item.item_quantity);
			printf("\t\t\tMinimum Level    : %d\n", item.minimum_level);
		}

		stockItem[numOfItem++] = item;
		write_stock_to_file();
		printf("\t\t\tStock item added successfully!\n");
		Sleep(2000);
	}
	system("cls");
}

void get_lastest_time() {
	FILE* file2 = fopen("time.txt", "r");
	if (file2 != NULL) {
		fscanf(file2, "%[^\n]\n", cur_time);
	}
	fclose(file2);
}
void curTime(char timevalue[30]) {
	time_t t;
	time(&t);
	strcpy(timevalue, ctime(&t));
}

int search_item_code(char item_code[]) {
	for (int i = 0; i < numOfItem; i++) {
		if (strcmp(stockItem[i].item_code, item_code) == 0) {
			return i;
		}
	}
	return -1;
}
//display all item in stock
void display_stock() {
	get_lastest_time();
	minimum_stock_alert();

	printf("\t\t\t\t\t\t\t     Last Updated: %s\n", cur_time);
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	Sleep(20);
	printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	Sleep(20);
	int j = 0, o = 1;
	for (int i = 0; i < numOfItem; i++) {
		StockItem item = stockItem[i];
		printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item.item_code, item.item_description, item.item_price, item.item_quantity, item.minimum_level, item.reorder_quantity);
		Sleep(20);
		j++;
		if (j == 10) {
			printf("\n");
			printf("\t\t      %d------------------------------------------------------------------------------\n", o);
			o++;
			j -= 10;
		}
	}
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	Sleep(20);
	printf("\t\t\t\t\tTotal of %d items were found!\n", numOfItem);

	system("pause");
	system("cls");
}

//search item with range of quantity
void search_between_quantity() {
	FILE* fptr = fopen("stock.txt", "r");
	if (fptr != NULL) {
		char item_code[20];
		char item_description[100];
		float item_price;
		int item_quantity, minimum_level, reorder_quantity;
		int min, max;
		printf("Enter MINIMUM value and MAXIMUM value (or -1 to quit)\n");
		printf("Minimum Quantity :");
		scanf("%d", &min);
		if (min == -1) {
			return 0;
		}

		rewind(stdin);
		printf("Maximum Quantity:");
		scanf("%d", &max);
		rewind(stdin);
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		Sleep(20);
		printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
		Sleep(20);
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		int j = 0, o = 1, a = 0;
		while (fscanf(fptr, "%[^|]|%[^|]|%f|%d|%d|%d ", &item_code, &item_description, &item_price, &item_quantity, &minimum_level, &reorder_quantity) == 6) {

			if (item_quantity >= min && item_quantity <= max) {
				printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item_code, item_description, item_price, item_quantity, minimum_level, reorder_quantity);
				Sleep(20);
				j++; a = 1;
				if (j == 10) {
					printf("\n");
					printf("\t\t      %d------------------------------------------------------------------------------\n", o);
					o++;
					j -= 10;

				}
			}
		}
		Sleep(20);
		printf("\t\t\t------------------------------------------------------------------------------\n");

		if (a == 0) {
			system("cls");
			printf("Item Not Found!\n\a");
			Sleep(2000);

		}
		system("pause");
	}

	fclose(fptr);
}

//search item with range of price
void search_item_by_price() {
	FILE* fptr = fopen("stock.txt", "r");
	if (fptr != NULL) {
		char item_code[20];
		char item_description[100];
		float item_price;
		int item_quantity, minimum_level, reorder_quantity;
		int min, max;
		printf("Enter MINIMUM value and MAXIMUM value (or -1 to exit)\n");
		printf("Minimum price:");
		scanf("%d", &min);
		if (min == -1) {
			return 0;
		}
		rewind(stdin);
		printf("Maximum price :");
		scanf("%d", &max);
		rewind(stdin);
		Sleep(20);
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		Sleep(20);
		printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
		Sleep(20);
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		int j = 0, o = 1, a = 0;
		while (fscanf(fptr, "%[^|]|%[^|]|%f|%d|%d|%d ", &item_code, &item_description, &item_price, &item_quantity, &minimum_level, &reorder_quantity) == 6) {

			if (item_price >= min && item_price <= max) {
				printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", item_code, item_description, item_price, item_quantity, minimum_level, reorder_quantity);
				Sleep(20);
				j++; a = 1;
				if (j == 10) {
					printf("\n");
					Sleep(20);
					printf("\t\t      %d------------------------------------------------------------------------------\n", o);
					o++;
					j -= 10;
				}
			}
		}
		Sleep(20);
		printf("\t\t\t------------------------------------------------------------------------------\n");
		if (a == 0) {
			system("cls");
			printf("Item Not Found!\n\a");
			Sleep(2000);

		}
		system("pause");
	}

	fclose(fptr);
}
//display stock ascending by quantity

void display_asc_price() {
	read_stock_from_file();
	for (int i = 0; i < numOfItem - 1; i++) {
		for (int j = 0; j < numOfItem - 1 - i; j++) {
			if (stockItem[j].item_price > stockItem[j + 1].item_price) {
				StockItem temp = stockItem[j];
				stockItem[j] = stockItem[j + 1];
				stockItem[j + 1] = temp;
			}
		}
	}
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	Sleep(20);
	printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	int j = 0, o = 1;
	for (int i = 0; i < numOfItem; i++) {
		printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", stockItem[i].item_code, stockItem[i].item_description, stockItem[i].item_price, stockItem[i].item_quantity, stockItem[i].minimum_level, stockItem[i].reorder_quantity);
		Sleep(20);
		j++;
		if (j == 10) {
			printf("\n");
			Sleep(20);
			printf("\t\t      %d------------------------------------------------------------------------------\n", o);
			o++;
			j -= 10;
		}
	}
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	system("pause");
}

//display stock descending by price
void display_desc_price() {
	read_stock_from_file();
	for (int i = 0; i < numOfItem - 1; i++) {
		for (int j = 0; j < numOfItem - 1 - i; j++) {
			if (stockItem[j].item_price > stockItem[j + 1].item_price) {
				StockItem temp = stockItem[j];
				stockItem[j] = stockItem[j + 1];
				stockItem[j + 1] = temp;
			}
		}
	}
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	Sleep(20);
	printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	int j = 0, o = 1;
	for (int i = numOfItem - 1; i >= 0; i--) {
		printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", stockItem[i].item_code, stockItem[i].item_description, stockItem[i].item_price, stockItem[i].item_quantity, stockItem[i].minimum_level, stockItem[i].reorder_quantity);
		Sleep(20);
		j++;
		if (j == 10) {
			printf("\n");
			Sleep(20);
			printf("\t\t      %d------------------------------------------------------------------------------\n", o);
			o++;
			j -= 10;
		}
	}
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	system("pause");
}
//display stock ascending by quantity

void display_asc_qty() {
	read_stock_from_file();
	for (int i = 0; i < numOfItem - 1; i++) {
		for (int j = 0; j < numOfItem - 1 - i; j++) {
			if (stockItem[j].item_quantity > stockItem[j + 1].item_quantity) {
				StockItem temp = stockItem[j];
				stockItem[j] = stockItem[j + 1];
				stockItem[j + 1] = temp;
			}
		}
	}
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	Sleep(20);
	printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	int a = 0, o = 1;
	for (int i = 0; i < numOfItem; i++) {
		printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", stockItem[i].item_code, stockItem[i].item_description, stockItem[i].item_price, stockItem[i].item_quantity, stockItem[i].minimum_level, stockItem[i].reorder_quantity);
		Sleep(20);
		a++;
		if (a == 10) {
			printf("\n");
			Sleep(20);
			printf("\t\t      %d------------------------------------------------------------------------------\n", o);
			o++;
			a -= 10;
		}
	}
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	system("pause");
}
//display stock descending by quantity
void display_desc_qty() {
	read_stock_from_file();
	for (int i = 0; i < numOfItem - 1; i++) {
		for (int j = 0; j < numOfItem - 1 - i; j++) {
			if (stockItem[j].item_quantity > stockItem[j + 1].item_quantity) {
				StockItem temp = stockItem[j];
				stockItem[j] = stockItem[j + 1];
				stockItem[j + 1] = temp;
			}
		}
	}
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	Sleep(20);
	printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
	Sleep(20);
	printf("\t\t\t-----------------------------------------------------------------------------\n");
	int a = 0, o = 1;
	for (int i = numOfItem - 1; i >= 0; i--) {
		printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", stockItem[i].item_code, stockItem[i].item_description, stockItem[i].item_price, stockItem[i].item_quantity, stockItem[i].minimum_level, stockItem[i].reorder_quantity);
		Sleep(20);
		a++;
		if (a == 10) {
			printf("\n");
			Sleep(20);
			printf("\t\t      %d------------------------------------------------------------------------------\n", o);
			o++;
			a -= 10;
		}
	}
	printf("\t\t\t----------------------------------------------------------------------------------\n");
	system("pause");
}

void loading_animation() {

	int u, l, t;
	t = 0;

	for (u = 0; u <= 50; u++) {
		system("cls");
		l = 1;
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t\t\tLoading...%d%%\n\t\t\t\t     ", t);

		while (l <= u) {

			printf("%c", 22);
			l++;
		}
		if (l == 26) {
			printf("\n\n\n\t\t\t\t\t\t\tPlease Wait");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);
		}
		if (l == 46) {
			printf("\n\n\n\t\t\t\t\t\t\tPlease Wait");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);

		}
		printf("\n\n\n\t\t\t\t\t\t\tPlease Wait...\n");
		t += 2;
		Sleep(10);
	}
	Sleep(1000);
	system("cls");
}

//delete item from stock
void delete_item_by_item_code() {
	read_stock_from_file();
	FILE* fptr = fopen("stock.txt", "r");
	char item_to_del[10];
	int a = 0, b, z = 0, i;
	char choice = 'N';

	do
	{

		while (toupper(choice) == 'N') {
			if (fptr != NULL) {
				z = 0;
				system("cls");
				printf("Enter item code to delete (or exit to quit):");
				scanf("%[^\n]", item_to_del);
				rewind(stdin);
				if (strcmp("exit", item_to_del) == 0) {
					return 0;
				}

				if (strlen(item_to_del) != 4) {
					system("cls");
					printf("The ITEM CODE must be 4 CHARACTERS \n\a");
					Sleep(2000);
					return 0;
					system("cls");
				}


				printf("Item Code: %s\n", item_to_del);
				b = search_item_code(item_to_del);
				if (b == -1) {
					z = -1;
					system("cls");
					printf("Item Not Found!\n\a");
					Sleep(1500);
				}
				else {

					Sleep(20);
					printf("\t\t\t-----------------------------------------------------------------------------\n");
					Sleep(20);
					printf("\t\t\t  Item Code |    Description    | Price | Quantity | Min Level | Reorder Qty  \n");
					Sleep(20);
					printf("\t\t\t-----------------------------------------------------------------------------\n");
					printf("\t\t\t    %-10s%-20s%-10.2f%-5d%10d%13d\n", stockItem[b].item_code, stockItem[b].item_description, stockItem[b].item_price, stockItem[b].item_quantity, stockItem[b].minimum_level, stockItem[b].reorder_quantity);
					Sleep(20);
					printf("\t\t\t-----------------------------------------------------------------------------\n");
					Sleep(20);
					printf("Confirm deletion of this item ?(Y or N)\n");
					scanf("%c", &choice);
					rewind(stdin);
				}

			}
			else {
				printf("Error to open file");
				exit(-1);
			}
		}


		for (i = 0; i < numOfItem; i++) {
			if (strcmp(stockItem[i].item_code, item_to_del) == 0) {

				for (int j = i; j < numOfItem - 1; j++) {
					stockItem[j] = stockItem[j + 1];
				}
				numOfItem--;
				i--;
				a = 1;
			}


		}

		fclose(fptr);
	} while (z == -1);

	if (a != 1) {
		system("cls");
		printf("Item Not Found!\n\a");
		Sleep(1500);
	}
	if (a == 1) {
		FILE* fptr2 = fopen("stock.txt", "w");
		if (fptr2 != NULL) {

			for (int i = 0; i < numOfItem; i++) {
				fprintf(fptr2, "%s|%s|%.2f|%d|%d|%d\n", stockItem[i].item_code, stockItem[i].item_description, stockItem[i].item_price, stockItem[i].item_quantity, stockItem[i].minimum_level, stockItem[i].reorder_quantity);
			}
		}
		else {
			printf("Error to open file");
			exit(-1);
		}

		system("cls");
		printf("The item with item code %s has been successfully removed from stock.\n", item_to_del);
		Sleep(2500);
		fclose(fptr2);
	}


}



void stockModule() {
	printf("\033[?25l");
	sysColor();
	read_stock_from_file();
	int choice, p = 0, p1 = 0;
	do {
		choice = 0;
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t\t+----------------------+\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|      STOCK MODULE    |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t+----------------------+\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|    1. Add Item       |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|                      |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|    2. Search Item    |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|                      |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|    3. Modify Item    |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|                      |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|    4. View Item      |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|                      |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t|    5. Exit           |\n");
		Sleep(20);
		printf("\t\t\t\t\t\t+----------------------+\n");
		Sleep(20);
		printf("\t\t\t\t\t\tChoice > ");
		scanf("%d", &choice);
		rewind(stdin);

		switch (choice) {
		case 1:
			p = 0;
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|       ADD  ITEM      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|  1. Manually Input   |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|  2. Import File      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|  3. Exit             |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\tChoice > ");
			scanf("%d", &p);
			rewind(stdin);

			if (p == 1) {
				p = 0;
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|    MANUALLY INPUT    |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  1. Custom Item Code |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|                      |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  2. Random Item Code |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|                      |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  3. Exit             |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\tChoice : ");
				scanf("%d", &p);
				rewind(stdin);
				if (p == 1) {
					add_item_to_stock();
				}
				else if (p == 2) {
					add_item_to_stock_rand_generate();
				}
				else if (p == 3) {
					system("cls");
					break;
				}
				else {
					system("cls");
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tInvalid Input!\n\a");
					Sleep(1300);
					system("cls");
				}

			}
			else if (p == 2) {
				import_file_to_add_stock();
				read_stock_from_file();
			}
			else if (p == 3) {
				system("cls");
			}
			else {
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tInvalid Input!\n\a");
				Sleep(1300);
				system("cls");
			}
			break;
		case 2:
			p = 0;
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|      SEARCH ITEM     |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|   1. Item Code       |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|   2. Item Quantity   |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|   3. Item Price      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|   4. Exit            |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\tChoice > ");
			scanf("%d", &p);
			rewind(stdin);

			if (p == 1) {
				system("cls");
				search_stock_item_code();

			}
			else if (p == 2) {
				system("cls");
				search_between_quantity();

			}
			else if (p == 3) {
				system("cls");
				search_item_by_price();

			}
			else if (p == 4) {
				system("cls");
				break;
			}
			else {
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tInvalid Input!\a");
				Sleep(1300);
			}
			system("cls");
			break;

		case 3:
			p = 0;
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|      MODIFY ITEM     |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|    1. Item Detail    |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|    2. Delete Item    |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|    3. Exit           |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\tChoice > ");
			scanf("%d", &p);
			rewind(stdin);

			if (p == 1) {
				system("cls");
				update_stock_item();
			}
			else if (p == 2) {
				system("cls");
				delete_item_by_item_code();
			}
			else if (p == 3) {
				system("cls");
				break;
			}
			else {
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tInvalid Input!\a");
				Sleep(1300);
			}

			break;

		case 4:
			p = 0;
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|       VIEW ITEM      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|  1. Item Price       |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|  2. Item Quantity    |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|  3. Display All Item |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|                      |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t|  4. Exit             |\n");
			Sleep(20);
			printf("\t\t\t\t\t\t+----------------------+\n");
			Sleep(20);
			printf("\t\t\t\t\t\tChoice > ");
			scanf("%d", &p);
			rewind(stdin);

			if (p == 1) {
			b:
				p = 0;
				system("cls");

				printf("\n\n\n\n\n\n\n\n\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|    VIEW ITEM PRICE   |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  1. Ascending order  |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|                      |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  2. Descending order |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|                      |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  3. Range            |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|                      |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  4. Exit             |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\tChoice > ");
				scanf("%d", &p);
				rewind(stdin);

				if (p == 1) {
					system("cls");
					display_asc_price();
					goto b;
				}
				else if (p == 2) {
					system("cls");
					display_desc_price();
					goto b;
				}
				else if (p == 3) {
					system("cls");
					search_item_by_price();
					goto b;
				}
				else if (p == 4) {
					system("cls");
					break;
				}
				else {
					system("cls");
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tInvalid Input!\a");
					Sleep(1300);
					goto b;
				}
			}
			else if (p == 2) {
			a:
				p = 0;
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  VIEW ITEM QUANTITY  |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  1. Ascending order  |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|                      |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  2. Descending order |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|                      |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  3. Range            |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|                      |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t|  4. Exit             |\n");
				Sleep(20);
				printf("\t\t\t\t\t\t+----------------------+\n");
				Sleep(20);
				printf("\t\t\t\t\t\tChoice > ");
				scanf("%d", &p);
				rewind(stdin);

				if (p == 1) {
					system("cls");
					display_asc_qty();
					goto a;
				}
				else if (p == 2) {
					system("cls");
					display_desc_qty();
					goto a;

				}
				else if (p == 3) {
					system("cls");
					search_between_quantity();
					goto a;

				}
				else if (p == 4) {
					system("cls");
					break;
				}
				else {
					system("cls");
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tInvalid Input!\a");
					Sleep(1300);
					goto a;

				}
			}
			else if (p == 3) {
				if (p1 == 0) {
					loading_animation();
					p1++;
				}
				system("cls");
				display_stock();
				break;
			}
			else if (p == 4) {
				system("cls");
				break;
			}
			else {
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tInvalid Input!\a");
				Sleep(1300);
				break;
			}

			/*case 5:
				system("cls");
				upline_purchase();
				break;*/
		case 5:
			return 0;
			break;


		default:
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n          \t\t\t\t\tInvalid choice! Please try again.\n\a");
			Sleep(1300);
			system("cls");
			p = 0;

		}
	} while (choice != 5);
}

