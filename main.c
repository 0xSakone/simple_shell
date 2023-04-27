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
 * @ret: return value
 * @pprogram: parent program name
 * Return: 0 as success
 */
int run(__attribute__((unused)) char *pargs,
	__attribute__((unused)) char **envp,
	int *ret,
	char *pprogram)
{
	int status, rt = 0;
	/* char *cmd; */
	char *args[] = {NULL, NULL};
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(127);
	}
	else if (pid == 0)
	{
		cmd = (char *)malloc(128 * sizeof(char));
		_strncpy(cmd, pargs, _strlen(pargs) - 1);
		pargs[_strlen(pargs) - 1] = '\0';
		args[0] = pargs;
		rt = execve(pargs, args, NULL);
		if (rt == -1)
		{
			*ret = -1;
		}
		free(pargs);
		free(cmd);
		perror(pprogram);
		return (1);
	}
	else
	{
		wait(&status);
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
int main(__attribute__((unused))  int argc,
	char *argv[],
	__attribute__((unused)) char *envp[])
{
	char *user_input = NULL;
	size_t input_size = 128;
	int rivalue;
	int ret = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_printf("#cisfun$ ");

		rivalue = getline(&user_input, &input_size, stdin);

		if (rivalue != -1)
		{
			run(user_input, NULL, &ret, argv[0]);
			free(user_input);
			signal(SIGINT, prompt);
		}
		else
		{
			free(user_input);
			break;
		}
	}
	return (ret);
}
