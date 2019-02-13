/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:32:24 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/13 12:58:06 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	parce_champ(header_t *champ, int fd)
{
	unsigned int	read_n;
	unsigned int	head_len;
	unsigned int	i;

	i = 0;
	head_len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	read_n = read(fd, champ, head_len);
	if (read_n != head_len)
		error("BAD_HEADER");
	champ->magic = reverse(champ->magic);
	if (ft_strcmp(ft_itoa_base_x(COREWAR_EXEC_MAGIC, 16),
		ft_itoa_base_x(champ->magic, 16)))
		error("BAD_MAGIC");
	champ->prog_size = reverse(champ->prog_size);
	read_n = read(fd, champ->prog, CHAMP_MAX_SIZE + 1);
	if (read_n != champ->prog_size || champ->prog_size > CHAMP_MAX_SIZE)
		error("BAD_CHAMP_SIZE");
	while (i < champ->prog_size / 4)
	{
		champ->prog[i] = reverse(champ->prog[i]);
		i++;
	}
}
