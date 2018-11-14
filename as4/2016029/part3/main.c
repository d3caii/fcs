// #include <stdio.h>
#include <termios.h>
#include <getopt.h>
#include <stdlib.h>

#include "passwd.h"

#define MAX_LENGTH 1024


int getch(); // To take input without echoing on terminal(Used in conio.h from MS-DOS)
void backspace();
void printstar(int );
void getPassword(char *, int);
void help(char *);

int main(int argc, char *argv[])
{
	int option;
	int printPass = 0; //Do not print by default
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];
	if(argc == 1)
		help(argv[0]);
	while((option = getopt(argc, argv, "parh")) != -1){
		switch(option) {
			case 'p':
				printPass = 1; //Print * when entering password
				break;
			case 'a':
				// printf("AUTH\n");
				printf("ENTER USERNAME : ");
				fgets(username, 1024, stdin);
				printf("ENTER PASSWORD : ");
				getPassword(password, printPass);
				// printf("password : %s\n", password);
				if (auth_user(username, password))
					printf("SUCCESS\n");
				else
					printf("FAIL\n");
				return(0);
			case 'r':
				// printf("REGISTER\n");
				printf("ENTER USERNAME : ");
				fgets(username, 1024, stdin);
				printf("ENTER PASSWORD : ");
				getPassword(password, printPass);
				// printf("password : %s\n", password);
				if(register_user(username, password)) 
					printf("SUCCESS\n");
				else
					printf("FAIL\n");
				return(0);
			case 'h':
			default:
				help(argv[0]);
				return(1);
		}
	}		
	// exit cleanly if all was well
	// else exit with a non-0 return val
	return 0;
}



void getPassword(char *p, int printPass) {
	// fgets(p, 1024, stdin);
	int i;
	for(i=0; i<1023;) {
		int ch = getch();
		if(ch != 10 && ch != 8 && ch != 13 && ch !=127){ //Enter and backspace
			p[i] = ch;
			 i++;
			 printstar(printPass);
		} else if(ch == 8 || ch == 127) {
			if(i > 0) { 
				i--;
				backspace();
			}
		} else{
			p[i] = '\0';
			break;
		}
	}
	p[i+1]='\0';
	putchar('\n');
	// printf("password : %s\n", p);
}


int getch() { //Get one character form stdin but without it appearing in stdin

    int ch;
    struct termios old, new;
    
    tcgetattr(0, &old);
    tcgetattr(0, &new);
    
    new.c_lflag &= ~ICANON;
    new.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new);

    ch = getchar();

    tcsetattr(0, TCSANOW, &old);

    return ch;

}

void printstar(int yes) { //print a star
	if(yes) {
		putchar('*');
	}
}

void backspace() { //remove the last printed char
	putchar('\b');
	putchar(' ');
	putchar('\b');
	
}

void help(char *binary) {
	printf("Usage: %s [OPTION]\n", binary);
	printf("	-p 		Print Stars instead of blank for password\n");
	printf("	-r 		Register user\n");
	printf("	-a 		Authorise user\n");
	printf("	-h 		Prints this help text\n");
}