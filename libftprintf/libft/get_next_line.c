/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:44:23 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/10 11:27:41 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	custom(char buf[BUFF_SIZE + 1], int size, t_list *tmp)
{
	int		fd;
	char	*ptr;
	char	*str;

	str = "\0";
	size = 0;
	fd = tmp->content_size;
	while ((size = read(fd, buf, BUFF_SIZE)))
	{
		buf[size] = '\0';
		ptr = ft_strjoin(tmp->content, buf);
		free(tmp->content);
		tmp->content = ft_strjoin(ptr, str);
		free(ptr);
		if (ft_strchr(buf, '\n'))
			break ;
	}
}

char	*ft_jchar(char *line, char c)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	if (!line || !c)
		return (NULL);
	len = ft_strlen(line);
	str = ft_strnew(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = c;
	return (str);
}

int		ft_copy(char **line, t_list *list, char c)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	j = 0;
	str = list->content;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	*line = ft_strnew(i);
	*line = ft_strncpy(*line, str, i);
	return (i);
}

t_list	*find_list(t_list **start, int fd)
{
	t_list *tmp;

	tmp = *start;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_list));
	tmp->next = NULL;
	tmp->content = ft_strnew(1);
	tmp->content_size = fd;
	ft_lstadd(start, tmp);
	tmp = *start;
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	static	t_list	*node;
	t_list			*tmp;
	char			buf[BUFF_SIZE + 1];
	int				size;
	char			*s;

	size = 0;
	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0))
		return (-1);
	tmp = find_list(&node, fd);
	*line = NULL;
	custom(buf, size, tmp);
	if (size < BUFF_SIZE && !ft_strlen(tmp->content))
		return (0);
	size = ft_copy(line, tmp, '\n');
	if (size < (int)ft_strlen(tmp->content))
	{
		s = ft_strdup(tmp->content);
		free(tmp->content);
		tmp->content = ft_strsub(s, size + 1, ft_strlen(s) - size);
		free(s);
	}
	else
		ft_strclr(tmp->content);
	return (1);
}
