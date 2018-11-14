#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passwd.h"

#define MAX_LENGTH 1024
#define fname "shadow"

static int is_registered(char *uname) {
	// Open your passwd storage file
	// Find if the User is present
	// return 1 if found
	// else return 0

	FILE *fd;
	char buffer[1540];
	ssize_t len;

	fd = fopen("shadowAS4", "r");
	if(fd == NULL) {
		return 0;
	}

	
	while(fgets(buffer, 1024, fd ) != NULL) {
		
		char *pass;
		char *username;
		pass = strtok(buffer, ":");
		username = strtok(NULL, ":");
		// printf("username %s", username);

		if (username !=NULL && strcmp(username, uname) == 0) //exists
			return 1;
	}

	return 0;
}

static int check_password(char *uname, char* passwd) {

	FILE *fd;
	char buffer[1281];
	ssize_t len;

	fd = fopen("shadowAS4", "r");
	if(fd == NULL)
		return 0;

	
	while(fgets(buffer, 1024, fd ) != NULL) {
		
		char *pass;
		char *username;
		pass = strtok(buffer, ":");
		username = strtok(NULL, ":");
		// printf("username %s", username);

		if (username !=NULL && strcmp(username, uname) == 0 && strcmp(pass, passwd) == 0) //exists
			return 1;
	}

	return 0;
}


int register_user(char *uname, char *passwd) {
	// Check if password store file is present
	// Create it if not present
	// Look for sane permission on file
	
	if (is_registered(uname)) {
		fprintf(stderr, "Choose another username\n");
		return 0;
	} else {
		// printf("\nUSERNAME : %s\n", uname);
		
		//Writing to file
		FILE *fd;
		char hash[SHA512_DIGEST_LENGTH+1];
		SHA512_CTX ctx;
		SHA512_Init(&ctx);
		SHA512_Update(&ctx, passwd, strlen(passwd));
		SHA512_Final(hash, &ctx);
		hash[SHA512_DIGEST_LENGTH] = '\0';
		fd = fopen("./shadowAS4", "a");
		if(fd == NULL) {
			printf("Could not open file\n");
			return 0;
		}
		// SHA1(passwd, sizeof(passwd) -1, hash);
		// int num = (int)strtol(hash, NULL, 16);
		// printf("PASSWORD   %s\n", hash);
		fprintf(fd, "%s:%s", hash, uname);
		fclose(fd);
		return 1;
	}
	// Open the password file and append the username and password
	// Dont append the password in plain text. Try something obscure.
	// If you are out of ideas look for how unix implements passwords.



	return 1;
}

int auth_user(char *uname, char *passwd) {
	// check if password store is present
	// if not return 0
	
	if (!is_registered(uname)) {
		fprintf(stderr, "User not registered\n");
		return 0;
	} else {
		char hash[SHA512_DIGEST_LENGTH+1];
		SHA512_CTX ctx;
		SHA512_Init(&ctx);
		SHA512_Update(&ctx, passwd, strlen(passwd));
		SHA512_Final(hash, &ctx);
		hash[SHA512_DIGEST_LENGTH] = '\0';
		if(check_password(uname, hash))
			return 1;
		return 0;
		// printf("username : %s\n", uname);
		// printf("password : %s\n", passwd);
	}

	// Parse the file and then compare username and password supplied.
	// If you recall password is not plain text...
	
	//return 0/1 depending on if the password was correct or not
}

/* Feel Free to add to functions to the already pathetic design.
 * You try creating these assignments sometime ... */

