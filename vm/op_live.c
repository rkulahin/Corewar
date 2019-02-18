/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:21:23 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/18 19:20:38 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char			*valid_str(t_vm *vm, t_carriage *carriage, int	nb)
{
	char		*s1;
	char		*s2;
	int			delta;

	if (carriage->position == 8191)
		return (ft_strncpy(ft_strnew(nb), (char *)&vm->map[1], nb));
	else if (carriage->position + 2 + nb - 1 > 8191)
	{
		delta = carriage->position + 2 + nb - 8192;
		s1 = ft_strncpy(ft_strnew(nb - delta),
			(char *)&vm->map[carriage->position + 2], nb - delta);
		s2 = ft_strncpy(ft_strnew(delta), (char *)&vm->map[0], delta);
		return(ft_strjoin(s1, s2));
	}
	else
		return (ft_strncpy(ft_strnew(nb),
			(char *)&vm->map[carriage->position + 2], nb));
}

void			op_live(t_vm *vm, t_carriage *carriage)
{
	char		*name;
	t_players	*players;

	carriage->position = 8191;
	name = valid_str(vm, carriage, 8);
	ft_printf("NAME = %s", name);
	carriage->live = vm->cycle;
	players = vm->players;
	while (players)
		if (players->index == (int)(0 - vm_atoi_16(name)))
		{
			players->live = vm->cycle;
			break ;
		}
		else
			players = players->next;
	carriage->position += 10;//переместиться на 8 вперед
}