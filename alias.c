#include "header.h"
#include <stdio.h>

t_aliaspkg *StoreAddrStruct(t_aliaspkg *addr)
{
	static t_aliaspkg *ret;

	if (addr == NULL)
		return (ret);
	else
		ret = addr;
	return (ret);
}

void PushToList(char *string, t_aliaspkg *data)
{
	t_alias *node;
	int	i;
	
	if (!(node = (t_alias *)malloc(sizeof(t_alias))))
		return ;
	i = -1;
	while (string[++i] && string[i] != '=')
		;
	node->shortcut = ft_strsub(string, 0, ++i);
	node->cmd = ft_strsub(string, i, ft_strlen(string) - 1);
	node->next = NULL;
	if (!data->head_ref && !data->tail_ref)
		data->head_ref = data->tail_ref = node;
	else 
	{
		data->tail_ref->next = node;
		data->tail_ref = node;
	}
}

void CreateAliasFile(t_aliaspkg *data)
{
	static int flag;

	if (!flag)
	{
		if (!(access("42shrc", F_OK) == 0))
			data->fd = open("42shrc", O_WRONLY | O_CREAT, 0777);
		else
			data->fd = open("42shrc", O_WRONLY);
		flag = 1;
	}
}

void ImportAliasFileContent()
{
	t_aliaspkg *data;
	char	*line;
	int	fd;

	line = NULL;
	data = StoreAddrStruct(NULL);
	fd = open("42shrc", O_RDONLY);
	while (get_next_line(fd, &line))
		PushToList(line, data);
}

void PrintList()
{
	t_aliaspkg *data;
	t_alias *curr;

	data = StoreAddrStruct(NULL);
	curr = data->head_ref;
	while (curr)
	{
		ft_putstr(curr->shortcut);
		ft_putendl(curr->cmd);
		curr = curr->next;
	}
}

void AliasMatched(char *shortcut, t_aliaspkg *data)
{
	t_alias *curr;

	// loop through cmdlist;
	//while ()
//	{
		curr = data->head_ref;
		while (curr)
		{
			if (ft_strcmp(curr->shortcut, shortcut) == 0) // change shortcut with cmd in the cmdlist;
			{
				ft_putendl("here assign cmd in the list to the new value stored int curr->cmd");
				break ; 
			}
			curr = curr->next;
		}
//	}
}

void RemoveAlias(char *shortcut)
{
	t_aliaspkg *data;
	t_alias *curr;
	t_alias *prev;

	data = StoreAddrStruct(NULL);
	curr = prev = data->head_ref;
	// this line for test
	shortcut[ft_strlen(shortcut) - 1] = '\0';
	shortcut = ft_strjoin(shortcut, "=");
//	printf("shortcut ==> %s\n curr->shortcut ==> %s\n", shortcut, curr->shortcut);
	while (curr && !(ft_strcmp(curr->shortcut, shortcut) == 0))
	{
		ft_putendl("inside");
		prev = curr;
		curr = curr->next;
	}
	if (curr == data->head_ref)
	{
		ft_putendl(" here head");
		data->head_ref = curr->next;
	}
	else if (curr == data->tail_ref)
	{
		ft_putendl("here tail");
		data->tail_ref = prev;
	}
	else
		prev->next = curr->next;
	ft_strdel(&curr->shortcut);
	ft_strdel(&curr->cmd);
	free(curr);
	printf("head->shortcut ==> %s\n tail->shortcut ==> %s\n", data->head_ref->shortcut, data->tail_ref->shortcut);
		PrintList();
	
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char buff[1024];
	t_aliaspkg *data;
	data = ft_memalloc(sizeof(data));
	StoreAddrStruct(data);
	CreateAliasFile(data);
	while (1)
	{
		ft_bzero(buff, 1024);
		read(0, buff, sizeof(buff));
		ImportAliasFileContent();
	//	PushToList(buff);
	//	AliasMatched(buff);
		RemoveAlias(buff);
		//PrintList();
	}
	return (0);
}
