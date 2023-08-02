# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdbool.h>
# include <conio.h>
# include <Windows.h>
# pragma warning (disable : 4996)
# pragma warning (disable : 6031)

void purple();
void cyan();
void bear();
void congratulations();
void message1();
void message2();

void purple() {
	printf("\033[1;35m");
}

void cyan() {
	printf("\033[0;36m");
}

void bear() {
	system("color 0f");
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