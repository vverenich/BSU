/*
 * SPLPv1.c
 * The file is part of practical task for System programming course.
 * This file contains validation of SPLPv1 protocol.
 */



 /*
   Verenich Vladislav Nikolaevich
   13th gr
 */



 /*
 ---------------------------------------------------------------------------------------------------------------------------
 # |      STATE      |         DESCRIPTION       |           ALLOWED MESSAGES            | NEW STATE | EXAMPLE
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 1 | INIT            | initial state             | A->B     CONNECT                      |     2     |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 2 | CONNECTING      | client is waiting for con-| A<-B     CONNECT_OK                   |     3     |
   |                 | nection approval from srv |                                       |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 3 | CONNECTED       | Connection is established | A->B     GET_VER                      |     4     |
   |                 |                           |        -------------------------------+-----------+----------------------
   |                 |                           |          One of the following:        |     5     |
   |                 |                           |          - GET_DATA                   |           |
   |                 |                           |          - GET_FILE                   |           |
   |                 |                           |          - GET_COMMAND                |           |
   |                 |                           |        -------------------------------+-----------+----------------------
   |                 |                           |          GET_B64                      |     6     |
   |                 |                           |        ------------------------------------------------------------------
   |                 |                           |          DISCONNECT                   |     7     |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 4 | WAITING_VER     | Client is waiting for     | A<-B     VERSION ver                  |     3     | VERSION 2
   |                 | server to provide version |          Where ver is an integer (>0) |           |
   |                 | information               |          value. Only a single space   |           |
   |                 |                           |          is allowed in the message    |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 5 | WAITING_DATA    | Client is waiting for a   | A<-B     CMD data CMD                 |     3     | GET_DATA a GET_DATA
   |                 | response from server      |                                       |           |
   |                 |                           |          CMD - command sent by the    |           |
   |                 |                           |           client in previous message  |           |
   |                 |                           |          data - string which contains |           |
   |                 |                           |           the following allowed cha-  |           |
   |                 |                           |           racters: small latin letter,|           |
   |                 |                           |           digits and '.'              |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 6 | WAITING_B64_DATA| Client is waiting for a   | A<-B     B64: data                    |     3     | B64: SGVsbG8=
   |                 | response from server.     |          where data is a base64 string|           |
   |                 |                           |          only 1 space is allowed      |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 7 | DISCONNECTING   | Client is waiting for     | A<-B     DISCONNECT_OK                |     1     |
   |                 | server to close the       |                                       |           |
   |                 | connection                |                                       |           |
 ---------------------------------------------------------------------------------------------------------------------------

 IN CASE OF INVALID MESSAGE THE STATE SHOULD BE RESET TO 1 (INIT)

 */

#define _CRT_SECURE_NO_WARNINGS

#include "splpv1.h"
#include <string.h>





 /* FUNCTION:  validate_message
  *
  * PURPOSE:
  *    This function is called for each SPLPv1 message between client
  *    and server
  *
  * PARAMETERS:
  *    msg - pointer to a structure which stores information about
  *    message
  *
  * RETURN VALUE:
  *    MESSAGE_VALID if the message is correct
  *    MESSAGE_INVALID if the message is incorrect or out of protocol
  *    state
  */
enum test_status previousStatus = MESSAGE_VALID;
char previousState = 7;
char cmd  = 0;     // 1 - GET_DATA; 2 - GET_FILE; 3 - GET_COMMAND; 4 - GET_VER; 5 - GET_B64; 6 - DISCONNECT

static const int answer[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
base64[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

char getStateFromMessage(struct Message *msg) {
	enum Direction dir = msg->direction;
	char *str = msg->text_message;

	if (dir == B_TO_A) {
		if (strcmp(str, "CONNECT_OK") == 0) {
			return 2;
		}
		else if (strncmp("VERSION", str, 7) == 0) {
			if (isVersionValid(str)) {
				return 4;
			}
			return 0;
		}
		else if (strncmp(str, "GET_DATA ", 9) == 0 || strncmp(str, "GET_COMMAND ", 12) == 0 || strncmp(str, "GET_FILE ", 9) == 0) {
			if (isCommandValid(str)) {
				return 5;
			}
			return 0;
		}
		else if (strncmp("B64: ", str, 5) == 0) {
			if (isB64Valid(str)) {
				return 6;
			}
			return 0;
		}
		else if (strcmp(str, "DISCONNECT_OK") == 0 && cmd == 6) {
			return 7;
		}
	}
	else if (dir == A_TO_B) {
		if (strcmp(str, "CONNECT") == 0) {
			return 1;
		}
		else if (strcmp(str, "GET_DATA") == 0) {
			cmd = 1;
			return 3;
		}
		else if (strcmp(str, "GET_FILE") == 0) {
			cmd = 2;
			return 3;
		}
		else if (strcmp(str, "GET_COMMAND") == 0) {
			cmd = 3;
			return 3;
		}
		else if (strcmp(str, "GET_VER") == 0) {
			cmd = 4;
			return 3;
		}
		else if (strcmp(str, "GET_B64") == 0) {
			cmd = 5;
			return 3;
		}
		else if (strcmp(str, "DISCONNECT") == 0) {
			cmd = 6;
			return 3;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

enum test_status validate_message(struct Message *msg)
{
	int currentState = getStateFromMessage(msg);

	if (currentState == 0) {
		previousState = currentState;
		previousStatus = MESSAGE_INVALID;
		return previousStatus;
	}

	if (previousStatus) {
		if (previousState == 1) {
			if (currentState == 2) {
				previousState = currentState;
				return MESSAGE_VALID;
			}
		} 
		else if (previousState == 3) {
			if (currentState == 4 || currentState == 5 || currentState == 6 || currentState == 7) {
				previousState = currentState;
				return MESSAGE_VALID;
			}
		}
		else if (previousState == 2 || previousState == 4 || previousState == 5 || previousState == 6) {
			if (currentState == 3) {
				previousState = currentState;
				return MESSAGE_VALID;
			}
		}
		else if (previousState == 7) {
			if (currentState == 1) {
				previousState = currentState;
				return MESSAGE_VALID;
			}
		}
	} 
	else if (previousState == 0) {
		if (currentState == 1) {
			previousState = currentState;
			previousStatus = MESSAGE_VALID;
			return previousStatus;
		}
	}

	previousState = 0;
	previousStatus = MESSAGE_INVALID;
	return MESSAGE_INVALID;
}

int isVersionValid(char* str) {

	if (cmd != 4) {
		return 0;
	}

	if (strncmp("VERSION ", str, 8) == 0) {
		if (str[8] <= 48 || str[8] > 57) {
			return 0;
		}
		str += 8;
		for (; *str!='\0'; ++str) {
			if (*str < 48 || *str > 57) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

int isCommandValid(char* str) {
	char command[15];
	char lastSymbols[15];

	if (cmd == 1) {
		strcpy(command, "GET_DATA ");
		strcpy(lastSymbols, " GET_DATA");
	}
	else if (cmd == 2) {
		strcpy(command, "GET_FILE ");
		strcpy(lastSymbols, " GET_FILE");
	}
	else if (cmd == 3) {
		strcpy(command, "GET_COMMAND ");
		strcpy(lastSymbols, " GET_COMMAND");
	}

	int lengthOfCommand = strlen(command);

	if (strncmp(command, str, lengthOfCommand) != 0  ) {
		return 0;
	}

	str += lengthOfCommand;
	for (; *str!=' '; ++str) {
		if (!answer[*str]) {
			return 0;
		}
	}

	if (strncmp(lastSymbols, str, lengthOfCommand) != 0) {
		return 0;
	}

	return 1;
}

int isB64Valid(char* str) {	
	if (cmd != 5) {
		return 0;
	}

	if (strncmp("B64: ", str, 5) != 0) {
		return 0;
	}

	int length = 5;
	str += length;

	for (; *str!='='&& *str!='\0'; ++str) {
		if (!base64[*str]) {
			return 0;
		}
		++length;
	}
	
	int i = 0;

	for (; *str != '\0'; ++str) {
		++i;
		if (*str != '='||i>2) {
			return 0;
		}
		++length;
	}

	if ((length - 5) % 4 != 0) {
		return 0;
	}

	return 1;
}