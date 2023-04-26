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
 * @pargs: program argument
 * @envp: program environment
 * @pprogram: parent program name
 * Return: 0 as success
 */
int run(__attribute__((unused)) char *pargs,
	__attribute__((unused)) char **envp,
	char *pprogram)
{
	int status;
	char *cmd;
	char *args[] = {NULL, NULL};
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		cmd = (char *)malloc((_strlen(pargs) - 1) * sizeof(char));
		getCommand(cmd, pargs);
		args[0] = cmd;
		execve(cmd, args, NULL);
		free(cmd);
		free(pargs);
		perror(pprogram);
		exit(1);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			free(pargs);
			exit(1);
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
	char *user_input = NULL;
	size_t input_size = 128;
	int rivalue;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_printf("#cisfun$ ");

		rivalue = getline(&user_input, &input_size, stdin);

		if (rivalue != -1)
		{
			run(user_input, envp, argv[0]);
			signal(SIGINT, prompt);
		}
		else
		{
			free(user_input);
			break;
		}
	}
	return (0);
}
