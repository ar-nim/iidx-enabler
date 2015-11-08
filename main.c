#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
char flags[3][15];
int selection;

void hexedit(int address, char const* value){ //Function to do the hex edit itself
	fseek(fp, address, SEEK_SET);
	fputs(value, fp);
}

char hexcheck(int address){
	char value;
	fseek(fp, address, SEEK_SET);
	fscanf(fp, "%c", &value);
	return value;
}

void toggles(){
	//Check for Timer Freeze
		if (hexcheck(0x9C55E) == '\x74'){
			strcpy(flags[0], "OFF");
		}
		else if (hexcheck(0x9C55E) == '\xEB'){
			strcpy(flags[0], "ON");
		}

		//Check for All Song Unlock
		if (hexcheck(0x58B3E) == '\x75' && hexcheck(0x58B3F) == '\x0A'){
			strcpy(flags[1], "OFF");
		}
		else if (hexcheck(0x58B3E) == '\x90' && hexcheck(0x58B3F) == '\x90'){
			strcpy(flags[1], "ON");
		}

		//Check for CS Style Song Delay
		if (hexcheck(0x77CF6) == '\x7C'){
			strcpy(flags[2], "OFF");
		}
		else if (hexcheck(0x77CF6) == '\xEB'){
			strcpy(flags[2], "ON");
		}

		//Check for Premium Free
		if (hexcheck(0x5D31B) == '\x75'){
			strcpy(flags[3], "OFF");
		}
		else if (hexcheck(0x5D31B) == '\xEB'){
			strcpy(flags[3], "ON");
		}

		//Check for Premium Free Timer Freeze
		if (hexcheck(0x563AD) == '\x48'){
			strcpy(flags[4], "OFF");
		}
		else if (hexcheck(0x563AD), '\x90'){
			strcpy(flags[4], "ON");
		}
	}

int main(){
	fp = fopen("bm2dx.dll", "r+b");
	if (fp == NULL){
		printf("bm2dx.dll not found, put this on the same directory as bm2dx.dll");
	}
	else{
		do{
			fp = fopen("bm2dx.dll", "r+b");
			system("cls");
			printf("Welcome to PENDUAL Enabler!\n");
			printf("By KcLKcL\n\n");
			printf("This tool will automagically patch your PENDUAL dll to enable\ncertain features and hacks!\n\n");
			toggles();
			printf("Available Hacks:\n");
			printf("1. Timer Freeze: %s\n", flags[0]);
			printf("2. Unlock All Songs: %s\n", flags[1]);
			printf("3. CS Style Song Delay: %s\n", flags[2]);
			printf("4. Premium Free: %s\n", flags[3]);
			printf("5. Premium Free Timer Freeze: %s\n", flags[4]);
			//printf("6. Remove FREE PLAY Text: %s\n", flags[5]);
			//printf("7. Replace FREE Play Text With LED Ticker: %s\n\n", flags[6]);
			
			printf("8. Exit\n");
			printf("Enter Selection to toggle: ");
			scanf("%d", &selection); fflush(stdin);
			switch (selection){
			case 1: if (strcmp(flags[0], "OFF") == 0){
					hexedit(0x9C55E, "\xEB");
					fclose(fp);
					}
					else{
						hexedit(0x9C55E, "\x74");
						fclose(fp);
					}

			case 2: if (strcmp(flags[1], "OFF") == 0){
					hexedit(0x58B3E, "\x90"); hexedit(0x58B3F, "\x90");
					fclose(fp);
					}
					else{
						hexedit(0x58B3E, "\x75"); hexedit(0x58B3F, "\x09");
						fclose(fp);
					}

			case 3: if (strcmp(flags[2], "OFF") == 0){
				hexedit(0x77CF6, "\xEB");
				fclose(fp);
			}
					else{
						hexedit(0x77CF6, "\x7C");
						fclose(fp);
					}

			case 4: if (hexcheck(0x5D31B) == '\x75'){
				hexedit(0x5D31B, "\xEB");
				fclose(fp);
			}
					 else{
						 hexedit(0x5D31B, "\x75");
						 fclose(fp);
					 }

			case 5: if (strcmp(flags[4], "OFF") == 0){
				hexedit(0x563AD, "\x90");
				fclose(fp);
			}
					else{
						hexedit(0x563AD, "\x48");
						fclose(fp);
					}
		}
		} while (selection != 8);
	}
	return 0;
}