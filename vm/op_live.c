/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:21:23 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/22 16:59:59 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char			*valid_str(t_vm *vm, int position, int nb)
{
	char	*str;
	int		i;

	i = 0;
	if (position < 0)
		position = position + 8192;
	str = (char *)malloc(sizeof(char) * nb + 1);
	while (i < nb)
	{
		str[i] = vm->map[(position + 2 + i) % 8192];
		i++;
	}
	str[nb] = '\0';
	return (str);
}

// char			*valid_str(t_vm *vm, int position, int nb)
// {
// 	char		*s1;
// 	char		*s2;
// 	int			delta;
// 	char		*s3;

// 	position = ABS(position % 8192);
// 	if (position == 8191)
// 		return (ft_strncpy(ft_strnew(nb), (char *)&vm->map[1], nb));
// 	else if (position + 2 + nb - 1 > 8191)
// 	{
// 		delta = (position + 2 + nb) % 8192;
// 		s1 = ft_strncpy(ft_strnew(nb - delta),
// 			(char *)&vm->map[position + 2], nb - delta);
// 		s2 = ft_strncpy(ft_strnew(delta), (char *)&vm->map[0], delta);
// 		s3 = ft_strjoin(s1, s2);
// 		free(s1);
// 		free(s2);
// 		return (s3);
// 	}
// 	else
// 		return (ft_strncpy(ft_strnew(nb),
// 			(char *)&vm->map[position + 2], nb));
// }

void			op_live(t_vm *vm, t_carriage *carriage)
{
	char		*name;
	t_players	*players;

	vm->live++;
	name = valid_str(vm, carriage->position, 8);
	carriage->live = vm->cycle;
	players = vm->players;
	if ((vm->nbr_log & 4) == 4)
		ft_printf("P %4d | live %d\n", carriage->index, vm_atoi_16(name));
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
	free(name);
	carriage->position = carriage->position + 10;
}
