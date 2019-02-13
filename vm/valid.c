/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:26:56 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/13 19:02:44 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		valid_champ(t_vm *all, char **av, int i)
{
	t_players	*new;
	int			fd;

	if (ft_strstr(av[i], ".cor") == NULL)
		error("BAD_NAME");
	new = init_player();
	fd = open(av[i], O_RDWR);
	if (fd <= 1)
		error("BAD_PLAYER");
	new->champ = parce_champ(fd);
	add_champ(&all, new);
	return (i + 1);
}

int		str_of_num(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int		nbr_champ(t_players *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		valid_num(t_vm *all, int ac, char **av, int i)
{
	int		index;
	int		j;
	int		k;

	if (i == ac - 1)
		error("BAD_INDEX_OF_PLAYER");
	index = ft_atoi(av[i + 1]);
	if (index <= 0 || index > MAX_PLAYERS || !str_of_num(av[i + 1]))
		error("BAD_INDEX_OF_PLAYER");
	j = nbr_champ(all->champs);
	if (all->index_player[j] != 0)
		error("BAD_INDEX");
	k = -1;
	while (++k < j)
		if (all->index_player[k] == index)
			error("DUPLICATE_INDEX");
	all->index_player[j] = index;
	return (i + 2);
}

int		valid_dump(t_vm *all, int ac, char **av, int i)
{
	if (i == ac - 1 || all->nbr_cycles != 0)
		error("BAD_DUMP");
	all->nbr_cycles = ft_atoi(av[i + 1]);
	if (all->nbr_cycles <= 0 || !str_of_num(av[i + 1]))
		error("BAD_DUMP");
	return (i + 2);
}
