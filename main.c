#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
char flags[11][4];
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
		else if (hexcheck(0x563AD) == '\x90'){
			strcpy(flags[4], "ON");
		}
		
		//Check for REMOVE FREE PLAY TEXT
		if (hexcheck(0x14C3A) == '\x90' && hexcheck(0x14C3B) == '\x3f' && hexcheck(0x14C3C) == '\x12' && hexcheck(0x14C3D) == '\x10'){
			strcpy(flags[5], "OFF");
		}
		else if (hexcheck(0x14C3A) == '\x99' && hexcheck(0x14C3B) == '\x3f' && hexcheck(0x14C3C) == '\x12' && hexcheck(0x14C3D) == '\x10'){
			strcpy(flags[5], "ON");
		}
		
		//Check for Replace FREE PLAY Text with LED Ticker
		if (hexcheck(0x14C3A) == '\x90' && hexcheck(0x14C3B) == '\x3f' && hexcheck(0x14C3C) == '\x12' && hexcheck(0x14C3D) == '\x10') {
			strcpy(flags[6], "OFF");
		}
		else if (hexcheck(0x14C3A) == '\x24' && hexcheck(0x14C3B) == '\xAA' && hexcheck(0x14C3C) == '\x43' && hexcheck(0x14C3D) == '\x11'){
			strcpy(flags[6], "ON");
		}
		
		//Check for Leave System Volume Alone
		if (hexcheck(0xD5D09) == '\x00'){
			strcpy(flags[7], "OFF");
		}
		else if (hexcheck(0xD5D09) == '\x01'){
			strcpy(flags[7], "ON");
		}
		
		//Check for CS Style Song Select
		if (hexcheck(0x6BF3A) == '\x74' && hexcheck(0x6BF3B) == '\x23'){
			strcpy(flags[8], "OFF");
		}
		else if (hexcheck(0x6BF3A) == '\x90' && hexcheck(0x6BF3B) == '\x90'){
			strcpy(flags[8], "ON");
		}
		
		//Check for dark mode
		if (hexcheck(0x71182) == '\x74' && hexcheck(0x71183) == '\x32'){
			strcpy(flags[9], "OFF");
		}
		else if (hexcheck(0x71182) == '\x90' && hexcheck(0x71183) == '\x90'){
			strcpy(flags[9], "ON");
		}
		
	}

int main(){
	fp = fopen("bm2dx.dll", "r+b");
	if (fp == NULL){
		printf("Welcome to PENDUAL Enabler!\n");
		printf("By KcLKcL\n\n");
		printf("This tool will automagically patch your PENDUAL dll to enable\ncertain features and hacks!\n\n");
		printf("bm2dx.dll not found, put this on the same directory as bm2dx.dll, and make sure bm2dx.dll is not read-only."); getchar();
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
			printf("4. CS Style Song Select: %s\n", flags[8]);
			printf("5. Premium Free: %s\n", flags[3]);
			printf("6. Premium Free Timer Freeze: %s\n\n", flags[4]);
			printf("---Only one FREE PLAY hacks may be used at the same time---\n");
			printf("7. Remove FREE PLAY Text: %s\n", flags[5]);
			printf("8. Replace FREE Play Text With LED Ticker: %s\n", flags[6]);
			printf("-----------------------------------------------------------\n\n");
			//printf("9. Leave System Volume Alone: %s\n", flags[7]);
			//printf("10. Dark Mode: %s\n", flags[9]);

			printf("9. Exit\n\n");
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
						hexedit(0x58B3E, "\x75"); hexedit(0x58B3F, "\x0A");
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
			case 4: if (strcmp(flags[8], "OFF") == 0){
						hexedit(0x6BF3A, "\x90"); hexedit(0x6BF3B, "\x90");
						fclose(fp);
					}
					else{
						hexedit(0x6BF3A, "\x74"); hexedit(0x6BF3B, "\x23");
						fclose(fp);	
					}

			case 5: if (strcmp(flags[3], "OFF") == 0){
						hexedit(0x5D31B, "\xEB");
						fclose(fp);
					}
					 else{
						 hexedit(0x5D31B, "\x75");
						 fclose(fp);
					 }

			case 6: if (strcmp(flags[4], "OFF") == 0){
						hexedit(0x563AD, "\x90");
						fclose(fp);
					}
					else{
						hexedit(0x563AD, "\x48");
						fclose(fp);
					}
			case 7: if(strcmp(flags[6], "ON") == 0){
						break;
					}
					else if (strcmp(flags[5], "OFF") == 0){
						hexedit(0x14C3A, "\x99"); hexedit(0x14C3B, "\x3f"); hexedit(0x14C3C, "\x12"); hexedit(0x14C3D, "\x10");
						fclose(fp);
					}
					else{
						hexedit(0x14C3A, "\x90"); hexedit(0x14C3B, "\x3f"); hexedit(0x14C3C, "\x12"); hexedit(0x14C3D, "\x10");
						fclose(fp);
					}
			case 8: if(strcmp(flags[5], "ON") == 0){
						break;
					}
					if (strcmp(flags[6], "OFF") == 0){
						hexedit(0x14C3A, "\x24"); hexedit(0x14C3B, "\xAA"); hexedit(0x14C3C, "\x43"); hexedit(0x14C3D, "\x11");
						fclose(fp);
					}
					else{
						hexedit(0x14C3A, "\x90"); hexedit(0x14C3B, "\x3f"); hexedit(0x14C3C, "\x12"); hexedit(0x14C3D, "\x10");
						fclose(fp);
					}
			/*
			---
			This section is commented because:
			I have no idea on how to write NULL with fputs. It just won't write \x00 or \0.
			To turn off "Leave out system volume" and "Dark Mode", we need to write that address to \x00.
			But I can't seem to do it.
			Hopefully this can be added in later version.
			Feel free to contribute if you have a solution.
			---
			case 9: if (strcmp(flags[7], "OFF") == 0){
						hexedit(0xD5D09, "\x01");
						fclose(fp);
					}
					else{
						hexedit(0xD5D09, "\xEB");
						fclose(fp);
					}
			case 10:if (strcmp(flags[9], "OFF") == 0){
					hexedit(0xD5D09, "\x01");
					fclose(fp);
					}
					else{
					hexedit(0xD5D09, "\xEB");
					fclose(fp);
					}
			*/
		}
		} while (selection != 9);
	}
	return 0;
}