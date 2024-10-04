#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

static const char HISTORY_FILE[] = "history.txt";

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
		printf("%s\n", command);
		free(command);
	}
	write_history(HISTORY_FILE);
	return 0;
}
