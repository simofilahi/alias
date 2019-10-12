/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 10:50:39 by mfilahi           #+#    #+#             */
/*   Updated: 2018/10/28 09:05:03 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		copy_in_line(char **text, char **line)
{
	char	*tmp;
	char	*p;
	int		i;

	p = *text;
	i = 0;
	while (p[i] && p[i] != '\n')
		i++;
	tmp = ft_strnew(i);
	i = 0;
	while (*p && *p != '\n')
		tmp[i++] = *p++;
	tmp[i] = '\0';
	*line = ft_strdup(tmp);
	free(tmp);
	*text = *text + i + 1;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*text[65536];
	char		buff[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || read(fd, buff, 0) < 0)
		return (-1);
	if (text[fd] == NULL)
		text[fd] = ft_strnew(1);
	*line = ft_strnew(1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		text[fd] = ft_strjoin(text[fd], buff);
		if (ft_strchr(text[fd], '\n'))
			break ;
	}
	if (*text[fd] != '\0')
		return (copy_in_line(&text[fd], line));
	return (0);
}
