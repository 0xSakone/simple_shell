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
 * @args: program environment
 * @ret: return value
 * @pprogram: parent program name
 * Return: 0 as success
 */
int run(char *pargs, char **args,
	int *ret,
	char *pprogram)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(127);
	}
	else if (pid == 0)
	{
		args[0] = (char *)malloc(128 * sizeof(char));
		args[1] = NULL;
		_strncpy(args[0], pargs, _strlen(pargs) - 1);
		if (execve(args[0], args, NULL) < 0)
			*ret = -1;
		else
			*ret = 0;
		free(args[0]);
		free(pargs);
		perror(pprogram);
		exit(127);
	}
	else
		wait(&status);

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
	char *args[2];
	size_t input_size = 128;
	int rivalue;
	int ret = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_printf("#cisfun$ ");

		_realloc(user_input, 128, 128);
		rivalue = getline(&user_input, &input_size, stdin);
		if (rivalue != -1)
		{
			run(user_input, args, &ret, argv[0]);
			free(user_input);
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
