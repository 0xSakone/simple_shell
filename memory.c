#include "main.h"

/**
 * gridfree - free a matrix
 * @grid: it is the matrix
 * @height: height of the matrix
 * Return: nothing
 */
void gridfree(char **grid, int height)
{
	int i;

	for (i = 0; i < height; i++)
	{
		free(grid[i]);
	}
	free(grid);
}

/**
 * _calloc - concatenate tw strings specially
 * @nume: number of elements
 * @size: type of elements
 * Return: nothing
 */

void *_calloc(unsigned int nume, unsigned int size)
{
	void *p = NULL;
	unsigned int i;

	if (nume == 0 || size == 0)
	{
		return (NULL);
	}
	p = malloc(nume * size);
	if (p == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < (nume * size); i++)
	{
		*((char *)(p) + i) = 0;
	}
	return (p);
}

/**
 * _realloc - change the size and copy the content
 * @ptr: malloc pointer to reallocate
 * @old_size: old number of bytes
 * @new_size: new number of Bytes
 * Return: nothing
 */

void *_realloc(char *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p = NULL;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		p = _calloc(new_size + 1, sizeof(char));
		if (!p)
			return (NULL);
		return (p);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size > old_size)
	{
		p = _calloc(new_size + 1, sizeof(char));
		if (!p)
			return (NULL);
		for (i = 0; i < old_size; i++)
			p[i] = *((char *)ptr + i);
		free(ptr);
	}
	else
	{
		p = _calloc(new_size + 1, sizeof(char));
		if (!p)
			return (NULL);
		for (i = 0; i < new_size; i++)
			p[i] = *((char *)ptr + i);
		free(ptr);
	}
	return (p);
}

/**
 * Counter - counts the number of lim found in the input
 * @C: the input string;
 * @lim: character to find inside the C string
 * Return: number of characters found
 */
int Counter(char *C, char *lim)
{
	int i = 0, num = 0;

	if (lim != NULL)
	{
		while (C && C[i] != '\0')
		{
			if (C[i] != lim[0])
			{
				if (C[i + 1] == lim[0] || C[i + 1] == '\0')
					num++;
			}
			i++;
		}
	}
	return (num);
}

/**
 * parsing - create an array of pointers depending of the delimit characters
 * @line: input of the user
 * Return: an array of pointers of n size
 */
char **parsing(char *line)
{
	char *token = NULL, **p = NULL;
	int length = 0, j = 0, i = 0, buffsize = 0;

	if (line == NULL)
		return (NULL);
	buffsize = Counter(line, " ");
	p = _calloc((buffsize + 1), sizeof(char *));
	if (!p)
	{
		perror("No memory");
		return (NULL);
	}
	/*store the token partition inside **p */
	token = _strtok(line, " \t\n");
	if (!token)
	{
		free(p);
		return (NULL);
	}
	while (token)
	{
		while (token[length] != '\0')
			length++;
		p[j] = _calloc((length + 1), sizeof(char));
		if (p[j] == NULL)
		{
			gridfree(p, j);
			perror("No memory");
			return (NULL);
		}
		/*fill the pointer with the content of token*/
		for (i = 0; i < length; i++)
			p[j][i] = token[i];
		length = 0;
		j++;
		/*get the next element*/
		token = _strtok(NULL, " \t\n");
	}
	p[j] = NULL;
	return (p);
}

