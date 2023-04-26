#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "head.h"
#include "main.h"

/**
 * prompt - show prompt
 * @signal: The signal.
 */
void prompt(int signal)
{
	char *new_prompt = "\n#cisfun$ ";

	(void)signal;
	write(STDIN_FILENO, new_prompt, 10);
}

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
 * run - execute program with args
 * @cmd: program to run
 * @pargs: program argument
 * @envp: program environment
 * @ret: return value pointer
 * @pprogram: parent program name
 * Return: 0 as success
 */
int run(char *cmd, char *pargs, char **envp, int *ret, char *pprogram)
{
	int rvalue = 0, status;
	char *args[] = {NULL, NULL};
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror(pprogram);
	else if (pid == 0)
	{
		args[0] = cmd;
		getCommand(cmd, pargs);
		rvalue = execve(cmd, args, envp);
		if (rvalue < 1)
		{
			perror(pprogram);
			*ret = rvalue;
			return (-1);
		}
		fflush(stdin);
		signal(SIGINT, prompt);
		return (0);
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror(pprogram);
			return (-1);
		}
	}
	return (0);
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
	char *envp[])
{
	char *user_input, *cmd;
	size_t input_size = 128;
	int ret;

	user_input = (char *)malloc(input_size * sizeof(char));
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		if (getline(&user_input, &input_size, stdin) != -1)
		{
			cmd = (char *)malloc(128 * sizeof(char));
			if (run(cmd, user_input, envp, &ret, argv[0]) == -1)
			{
				free(user_input);
				free(cmd);
				exit(ret);
			}
		}
		else
		{
			free(user_input);
			break;
		}
	}
	return (0);
}
