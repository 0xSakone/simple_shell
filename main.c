#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "head.h"
#include "main.h"

/**
 * getCommand - function that get the command from string
 * @output: the cmd return
 * @input: the given string
 * Return: 0 as success
 */
int getCommand(char *output, char *input)
{
	char cmd[128];
	int i = 0;

	while (*input != '\0')
	{
		if (*input == ' ' || *input == '\n')
			break;
		cmd[i] = *input;
		input++;
		i++;
	}

	_strncpy(output, (char *)&cmd, i);
	return (1);
}

/**
 * main - entry function
 * @argc: number of argument passed to the programm
 * @argv: arguments passed
 * @envp: environnement variable
 * Return: 0 as success
 */
int main(__attribute__((unused)) int argc,
	char *argv[],
	__attribute__((unused)) char *envp[])
{
	char *user_input, *cmd;
	size_t input_size = 128;
	char *args[] = {NULL, NULL};
	char *const envps[] = {NULL};
	pid_t pid;
	int status;

	cmd = (char *)malloc(input_size * sizeof(char));
	user_input = (char *)malloc(input_size * sizeof(char));
	while (1)
	{
		_printf("$ ");
		if (getline(&user_input, &input_size, stdin) > 0)
		{
			pid = fork();
			if (pid == -1)
				perror("fork");
			else if (pid == 0)
			{
				cmd = (char *)malloc(128 * sizeof(char));
				args[0] = cmd;
				getCommand(cmd, user_input);
				if (execve(cmd, args, envps) < 1)
					perror(argv[0]);
				free(cmd);
			}
			else
			{
				if (wait(&status) == -1)
					perror("wait");
			}
		}
		else
		{
			free(user_input);
			fflush(STDIN_FILENO);
			break;
		}
	}
	return (0);
}
