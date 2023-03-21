#include "main.h"
#include <string.h>
global_t LIST;
/**
 * free_List - frees the global variables
 *
 * Return: no return
 */
void free_List(void)
{
free_dlistint(List.head);
free(List.buffer);
fclose(List.fd);
}
/**
 * initialize_list - initializes list
 * @fd: file
 */
void initialize_list(FILE *fd)
{
LIST.type = 1;
LIST.current = 1;
LIST.arg = NULL;
LIST.head = NULL;
LIST.fd = fd;
LIST.buffer = NULL;
}
/**
 * check_input - checks if the file exists and if the file can
 * be opened
 *
 * @argc: argument count
 * @argv: argument vector
 * Return: file struct
 */
FILE *check_input(int argc, char *argv[])
{
FILE *fd;
if (argc == 1 || argc > 2)
{
dprintf(2, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
fd = fopen(argv[1], "r");
if (fd == NULL)
{
dprintf(2, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}
return (fd);
}
/**
 * main - ...
 * @argc: ..
 * @argv: ...
 * Return: ..
 */
int main(int argc, char *argv[])
{
void (*f)(stack_t **stack, unsigned int line_number);
FILE *fd;
ssize_t nlines = 0;
size_t size = 256;
char *lines[2] = {NULL, NULL};
fd = check_input(argc, argv);
initialize_list(fd);
nlines = getline(&LIST.buffer, &size, fd);
while (nlines != -1)
{
lines[0] = strtok(LIST.buffer, " \t\n");
if (lines[0] && lines[0][0] != '#')
{
f = get_opcodes(lines[0]);
if (!f)
{
dprintf(2, "L%u: ", LIST.current);
dprintf(2, "unknown instruction %s\n", lines[0]);
free_List();
exit(EXIT_FAILURE);
}
LIST.arg = strtok(NULL, " \t\n");
f(&LIST.head, LIST.current);
}
nlines = getline(&LIST.buffer, &size, fd);
LIST.current++;
}
free_List();
return (0);
}
