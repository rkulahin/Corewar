/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:46:53 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/14 13:24:58 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*vm_itoa_16(long long numb)
{
	char		*str;
	int			i;
	long long	v1;

	i = 8;
	str = ft_memset(ft_strnew(i), '0', 8);
	while (i-- != 0)
	{
		if (ABS(numb % 16) > 9)
			v1 = ABS(numb % 16) - 10 + 'a';
		else
			v1 = ABS(numb % 16) + '0';
		str[i] = v1;
		numb /= 16;
	}
	return (str);
}

int		find_cycle(char c1, char c2)
{
	if (c1 == '1' && c2 == '0')
		return (2);
	else if (c1 == '0' && (c2 == '2' || c2 == '3'))
		return (5);
	else if (c1 == '0' && (c2 == '6' || c2 == '7' || c2 == '8'))
		return (6);
	else if (c1 == '0' && (c2 == '1' || c2 == '4' || c2 == '5' || c2 == 'd'))
		return (10);
	else if (c1 == '0' && c2 == '9')
		return (20);
	else if (c1 == '0' && (c2 == 'a' || c2 == 'b'))
		return (25);
	else if (c1 == '0' && c2 == 'e')
		return (50);
	else if (c1 == '0' && c2 == 'c')
		return (800);
	else if (c1 == '0' && c2 == 'f')
		return (1000);
	return (0);
}

// void	vm_carriage(t_vm *vm, int index, int position)
// {
// 	t_carriage	*tmp;

// 	tmp = (t_carriage *)malloc(sizeof(t_carriage));
// 	tmp->carry = 0;
// 	tmp->live = 0;
// 	tmp->nbr_plr = index;
// 	tmp->position = position;
// 	tmp->operation[0] = vm->map[position];
// 	tmp->operation[1] = vm->map[position + 1];
// 	tmp->cycle = find_cycle(vm->map[position], vm->map[position + 1]);
// 	tmp->regist
// }

void	vm_map(t_vm	*vm, t_players *plr)
{
	int				i;
	unsigned int	j;
	int				k;
	int				bytes;
	char			*str;

	bytes = MEM_SIZE * 2 / vm->nbr_plrs;
	i = 0;
	while (plr)
	{
		i = (plr->index - 1) * bytes;
		j = 0;
		while (j < plr->champ->prog_size / 4)
		{
			k = -1;
			str = vm_itoa_16(plr->champ->prog[j]);
			while (str[++k])
			{
				vm->map[i] = str[k];
				i++;
			}
			free(str);
			j++;
		}
		//carriage
		// vm_carriage();
		//
		plr = plr->next;
	}
}