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
	char 	   **array;
	
	(void)data;
	(void)string;
	if (!(node = (t_alias *)malloc(sizeof(t_alias))))
		return ;
	if (!(array = ft_strsplit(string, '=')))
		return ;
	node->shortcut = ft_strdup(array[0]);
	node->cmd = ft_strdup(array[1]);
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
		if (!(access("42hrc", F_OK) == 0))
			data->fd = open("42hrc", O_WRONLY | O_CREAT, 0777);
		else
			data->fd = open("42hrc", O_WRONLY);
		flag = 1;
	}
}

void ImportAliasFileContent(t_aliaspkg *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(data->fd, &line))
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
		ft_putendl(curr->shortcut);
		curr = curr->next;
	}
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
		read(0, buff, sizeof(buff));
		ImportAliasFileContent(data);
		PushToList(buff, data);
		PrintList();
	}
	return (0);
}
