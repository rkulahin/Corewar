/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:53:49 by yyakoven          #+#    #+#             */
/*   Updated: 2019/03/25 20:03:11 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void					error(char *message)
{
	ft_printf("%s %s \n", "ERROR:", message);
	exit(1);
}

void					e2(char *message, char *delay)
{
	int					a;

	a = OOPS;
	ft_printf("%s %s ", "ERROR:", message);
	while (a--)
		;
	ft_printf("%s\n", delay);
	exit(1);
}

char					*open_file(int argc, char **argv, int *fd_s)
{
	char				*name;
	char				*ptr;
	char				*line;

	name = NULL;
	if (argc != 2)
		e2("Wrong number of arguments...",
"don't hurry, noone's in a hurry, everyone's pleased to be in your presence.");
	else
	{
		*fd_s = open(argv[1], O_RDONLY);
		if (*fd_s == -1)
			e2("File doesn't exist...", "(╯°□°)╯︵ ┻━┻");
		ptr = ft_strrchr(argv[1], '/');
		line = ptr ? ptr + 1 : argv[1];
		if ((ptr = ft_strrchr(line, '.')) && *(ptr + 1) == 's' &&
		ptr != line && *(ptr + 2) == '\0')
			name = ft_strsub(line, 0, ptr - line);
		else
			e2("Invalid file name...", "ι(｀ロ´)ノ");
	}
	return (name);
}

void					create_file(int *fd_cor, char *name)
{
	char				*temp;

	temp = name;
	name = ft_strjoin(temp, ".cor");
	free(temp);
	*fd_cor = open(name, O_TRUNC | O_CREAT | O_RDWR, 0777);
	ft_printf("Writing output program to %s\n", name);
	free(name);
}
