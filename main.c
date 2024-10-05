#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

static const char HISTORY_FILE[] = "history.txt";

int is_executable(const char* path) {
    return access(path, X_OK) == 0;
}

void handle_sighup() {
	printf("The program interrupted\n");
	write_history(HISTORY_FILE);
	//exit(0);
}

char* find_in_path(char* command) {
	char* path = getenv("PATH");
	if(path == NULL) {
		return NULL;
	}

	char* path_copy = strdup(path);
	char* dir = strtok(path_copy, ":");
	static char full_path[1024];
	while(dir != NULL) {
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if(is_executable(full_path)) {
			free(path_copy);
			return full_path;
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return NULL;
}

void fork_exec(char* full_path) {
	pid_t pid = fork();
	if(pid==0) {
		execlp(full_path,full_path, NULL);
		perror("execv");
		exit(0);
	}
	else if (pid < 0) {
		perror("fork");
		exit(1);
	}
	else {
		int status;
		waitpid(pid, &status, 0);
	}
}

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
	signal(SIGINT, handle_sighup);
	signal(SIGHUP, handle_sighup);
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
		if(strncmp(command, "\\e", 2)==0){
			char* path = getenv("PATH");
			if(path != NULL){
				printf("%s\n", path);
			}
			else printf("Variable isn't set");
		}
		if(strncmp(command, "echo", 4)==0) {
			echo_command(command + 5);
		}
		if(find_in_path(command) != NULL) {
			fork_exec(find_in_path(command));
		}
		else printf("%s\n", command);
		free(command);
	}
	write_history(HISTORY_FILE);
	return 0;
}
