/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:46:53 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/13 13:03:22 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_map(int nb, unsigned int plr[CHAMP_MAX_SIZE + 1], unsigned int size)
{
	unsigned char	map[MEM_SIZE];
	int				i;
	unsigned int	j;
	long			bytes;

	ft_bzero(map, MEM_SIZE);
	//print
	i = -1;
	while (++i < MEM_SIZE)
		ft_printf("%c", map[i]);
	//print
	bytes = MEM_SIZE / nb;
	i = 0;
	while (map[i] != '0' && i != MEM_SIZE)
		i += bytes;
	j = 0;
	if (map[i] == '0')
		while (j < size / 4)
		{
			map[i] = plr[j];
			i++;
			j++;
		}
	//print
	i = -1;
	while (++i < MEM_SIZE)
		ft_printf("%c", map[i]);
	//print
}
