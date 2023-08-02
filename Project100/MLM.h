#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include<math.h>
# include <stdbool.h>
#include <windows.h>
#include <ctype.h>
#pragma warning (disable:4996)
#pragma warning (disable:6031)
void appearance();
void sysColor();

//               Structure
//1.stock module's structure
typedef struct {
	char item_code[10];
	char item_description[100];
	float item_price;
	int item_quantity, minimum_level, reorder_quantity;
}StockItem;

//2.staff module's structure
typedef struct {
	int day, month, year;
}Date;
typedef struct {
	int hour, minute, second;
}Htime;
typedef struct {
	char houseNo[26];
	char streetNo[26];
	char postCode[6];
	char city[26];
	char state[26];
} Address;
typedef struct {
	char staffId[4];
	char staffName[31];
	char staffGender;
	char staffIc[20];
	int staffPassword[99];
	char staffPosition[26];
	Address staffAddress;
	char joinDate[31];
	char lastLogin[31];
	Date birth;
}Staffaccount;
typedef struct {
	Date date;
	Htime htime;
	char staffId[4];
	char staffName[31];
	char event[99];
}History;

//3.member module's structure
typedef struct {
	long int sec;
} BlockingTime;
struct Member {
	char member_ID[6];
	char username[100];
	char gender[50];
	char IC[15];
	char email[100];
	char upline[100];
	char password[51];
	char password_confirm[51];
	int key;
	char encrypted_password[51];
	int question;
	char answer[100];
	char account_available[10];
	Address add;
	BlockingTime time;
};




//                 Functions
//-----------------------------------------------------------------------------------------------------------------------------
//1.stock module's function
StockItem stockItem[1000];
int numOfItem;
char cur_time[30];
void stockModule();
void add_item_to_stock_rand_generate();
void upline_purchase();
void display_asc_price();
void display_desc_price();
void display_asc_qty();
void display_desc_qty();
void import_file_to_add_stock();
void read_stock_from_file();
void delete_item_by_item_code();
int search_item_code(char item_code[]);
void search_item_by_price();
void get_lastest_time();
void write_stock_to_file();
void update_stock_item();
void add_item_to_stock();
void search_between_quantity();
void search_stock_item_code();
void display_stock();
void curTime(char timevalue[30]);
void minimum_stock_alert();
void loading_animation();
//-----------------------------------------------------------------------------------------------------------------------------
//2.staff module's function
void displayStaffHeader();
Staffaccount stafflogin(int c);
void banana();
void alien();
void dog();
void cat();
int  verify_robot();
void displayAllStaff();
void registerNewStaff(int staffCount, Staffaccount currentAcc);
void loading();
void displayHeader();
void getTime(char timevalue[30]);
int confirmPassword(int passwords[99], int count);
int countstaff(int countstaff, Staffaccount staff);
int check_Position_Existing(char position[26]);
void deletestaff(int c, Staffaccount currentAcc);
void modifyStaffAcc(int c, Staffaccount currentAcc);
void staffModule();
void display_currentAcc_info(Staffaccount userInfo);
void ending();
void displayHistory();
void countNotice();
void displayNotice();
void manageNotice(Staffaccount currentAcc);
void addNotice(Staffaccount currentAcc);
void deleteNotice(Staffaccount currentAcc);
void getDateTime(int* day, int* month, int* year, int* hour, int* min, int* second);
void resetPassword(Staffaccount currentAcc);


//3.member module
//-----------------------------------------------------------------------------------------------------------------------------
int view_memberlist();
int delete_member(struct Member read[1000], int count);
int view_bannedlist();
int restore_member(struct Member read[1000], int count);
void red();
void searching_animation();
void deleteMember();

//4.sale module
//-----------------------------------------------------------------------------------------------------------------------------
void memberModule();
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

// Member Module
int signup();
char* login();
bool username_validation(struct Member info);
int gender_validation(struct Member info);
int icnum_validation(struct Member info);
int email_validation(struct Member info);
int password_validation(struct Member info);
int confirm_password(struct Member info);
char* password_encryption(struct Member info);
char* password_decryption(struct Member input, char encrypted_password[51]);
int security_question();
void output(struct Member info);
int view_profile(char username[100]);
char* edit_profile(char name[100]);
int forget_password();
char* password_reset();
int view_product(char username[100]);
int search_product(StockItem prod[1000], StockItem prodSearched[1000], int count, int m, char username[100]);
int purchase_product(StockItem prod[1000], StockItem prodSearched[1000], int count, int m, char username[100]);
int view_stock(char username[100]);
void output2(struct Member info);
void red();
void searching_animation();
void purple();
void cyan();
void bear();
void congratulations();
void message1();
void message2();

// Sales Module
int salesModule(char memberID[]);
char module(char memberID[]);
char displayShoppingCart(char memberID[]);
void shoppingCart(char prodID[], char prodName[], int qty, double price, char memberID[]);
int buyAgain(char memberID[]);
void rShopCart(char memberID[]);
int modify(char memberID[]);
int delete(char memberID[]);
int checkoutAll(char memberID[]);
int checkoutSelect(char memberID[]);
int selectBuy(char* checkout, char memberID[]);
int buyNow(char prodID[], char prodName[], int qty, double price, char memberID[]);
double totalPrice(FILE* order);
void placeOrder(char shopCart[], char buyAgain[], char temp[], char memberID[]);
void reduceStock(char shopCart[], char memberID[]);
void commission(char shopCart[], char memberID[]);
void purchaseHistory(char buyCart[], char memberID[]);
char viewHistory(char memberID[]);
int search(ViewHistory search[], FILE* view);
