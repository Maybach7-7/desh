#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

static const char HISTORY_FILE[] = "history.txt";

void echo_command(char* command) {
	while(*command == ' ') {
		command++;
	}

	bool flag = true;
	char* token = strtok(command, "\\n");
	while(token != NULL) {
		flag = false;
		printf("%s\n", token);
		token = strtok(NULL, "\\n");
	}
	if(flag) {
		printf("\n");
	}
}

int main(){
	char* command;
	read_history(HISTORY_FILE);
	while(1){
		command = readline("desh> ");
		if(command==NULL) {
			break;
		}
	
		if(strcmp(command, "\0")==0 || strcmp(command, "exit")==0
				|| strcmp(command, "\\q")==0){
			break;
		}
		else {
			add_history(command);
		}

		if(strncmp(command, "echo", 4)==0) {
			echo_command(command + 5);
		}
		else printf("%s\n", command);
		free(command);
	}
	write_history(HISTORY_FILE);
	return 0;
}
