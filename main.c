#include <stdio.h>
#include <unistd.h>
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
 * @ret: return value
 * @pprogram: parent program name
 * Return: 0 as success
 */
int run(char *pargs,
	int *ret,
	char *pprogram)
{
	int status, i;
	char **args = NULL;
	pid_t pid;

	args = parsing(pargs);
	if (args)
	{
		for (i = 0; args[i] != NULL; i++)
			;
		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			gridfree(args, i);
			free(pargs);
			exit(127);
		}
		else if (pid == 0)
		{
			_strncpy(args[0], pargs, _strlen(pargs) - 1);
			if (execve(args[0], args, NULL) < 0)
				*ret = -1;
			else
				*ret = 0;
			free(pargs);
			gridfree(args, i);
			perror(pprogram);
			exit(127);
		}
		else
			wait(&status);

		gridfree(args, i);
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
	__attribute__((unused)) char *envp[])
{
	char *user_input = (char *)malloc(128 * sizeof(char));
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
			if (_strcmp(user_input, "exit\n") == 0)
				exit(0);
			run(user_input, &ret, argv[0]);
			_realloc(user_input, 128, 128);
			signal(SIGINT, prompt);
		}
		else
		{
			break;
		}
	}
	free(user_input);
	return (0);
}
