/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:34:35 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/12 18:02:50 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	reverse(unsigned int b)
{
	b = (b >> 16 | b << 16);
	b = ((b & 0xFF00FF00) >> 8 | (b & 0x00FF00FF) << 8);
	return (b);
}

int		main(int argc, char **argv)
{
	int		fd;
	// char	*line;
	unsigned int		i;
	unsigned int		numb;
	header_t	*champ;
	
	i = 0;
	champ = (header_t *)malloc(sizeof(header_t));
	argc = 0;
	fd = open(argv[1], O_RDONLY);
	numb = read(fd, champ, 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4);
	champ->prog_size = reverse(champ->prog_size);
	ft_printf("magic = %x\n", champ->magic);
	ft_printf("magic = %s\n", champ->prog_name);
	ft_printf("magic = %i\n", champ->prog_size);
	ft_printf("magic = %s\n", champ->comment);
	if (numb < (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4))
		ft_printf("ERROR\n");
	ft_printf("%i\n", champ->prog_size);
	ft_printf("%u\n", (unsigned int)CHAMP_MAX_SIZE);
	if (champ->prog_size > (unsigned int)CHAMP_MAX_SIZE)
		ft_printf("ERROR\n");
	numb = read(fd, champ->prog, CHAMP_MAX_SIZE);
	ft_printf("%d\n", numb);
	if (numb != champ->prog_size)
		ft_printf("ERROR\n");
	while (i < champ->prog_size / 4)
	{
		champ->prog[i] = reverse(champ->prog[i]);
		ft_printf("magic = %.8x\n", champ->prog[i]);
		i++;
	}

	return (0);
}