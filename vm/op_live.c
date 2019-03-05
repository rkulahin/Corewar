/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:21:23 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/05 16:21:22 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char			*valid_str(t_vm *vm, int position, int nb)
{
	char		*s1;
	char		*s2;
	int			delta;

	if (position == 8191)
		return (ft_strncpy(ft_strnew(nb), (char *)&vm->map[1], nb));
	else if (position + 2 + nb - 1 > 8191)
	{
		delta = (position + 2 + nb) - 8192;
		s1 = ft_strncpy(ft_strnew(nb - delta),
			(char *)&vm->map[position + 2], nb - delta);
		s2 = ft_strncpy(ft_strnew(delta), (char *)&vm->map[0], delta);
		return (ft_strjoin(s1, s2));
	}
	else
		return (ft_strncpy(ft_strnew(nb),
			(char *)&vm->map[position + 2], nb));
}

void			op_live(t_vm *vm, t_carriage *carriage)
{
	char		*name;
	t_players	*players;

	vm->live++;
	name = valid_str(vm, carriage->position, 8);
	carriage->live = vm->cycle;
	players = vm->players;
	if ((vm->nbr_log & 4) == 4)
		ft_printf("P%5d | live %d\n", carriage->index, vm_atoi_16(name));
	while (players)
	{
		if (players->index == (int)(0 - vm_atoi_16(name)))
		{
			players->live = vm->cycle;
			if ((vm->nbr_log & 1) == 1)
				ft_printf("Player %i (%s) is said to be alive\n",
				players->index, players->champ->prog_name);
			break ;
		}
		else
			players = players->next;
	}
	carriage->position = (carriage->position + 10) % 8192;
}
