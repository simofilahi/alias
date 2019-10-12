#ifndef HEADER_H
#define HEADER_H
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

typedef struct s_alias t_alias;
typedef struct s_aliaspkg t_aliaspkg;

struct s_alias
{
	char *shortcut;
	char *cmd;
	t_alias *next;
};

struct s_aliaspkg 
{
	int fd;
	t_alias *head_ref;
	t_alias *tail_ref;
};

#endif

/*
[] -> [] -> [] -> [] -> []

CreateFile();
Pushtolist();
storeStruct();
first time run shell . CreateAliasFile();
while runing time of shell AliaseFileContent();

PushToList();

PrintLisT();
*/
