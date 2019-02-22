/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:32:24 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/22 13:55:11 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parce_champ_index(t_vm *all)
{
	int		i;
	int		k;
	int		l;

	all->nbr_plrs = nbr_champ(all->players);
	l = -1;
	k = 1;
	while (k <= all->nbr_plrs)
	{
		i = -1;
		if (l != -1)
			all->index_player[l] = k;
		l = -1;
		while (++i < all->nbr_plrs)
			if (all->index_player[i] > all->nbr_plrs)
				error("BAD_INDEX");
			else if (all->index_player[i] == k)
			{
				k++;
				i = -1;
			}
			else if (all->index_player[i] == 0 && l == -1)
				l = i;
	}
}

void		put_champ_index(t_vm *all)
{
	t_players	*tmp;
	int			i;

	i = 0;
	tmp = all->players;
	while (tmp)
	{
		tmp->index = all->index_player[i];
		i++;
		tmp = tmp->next;
	}
}

void		add_champ(t_vm **all, t_players *new)
{
	t_players	*tmp;
	int			i;

	i = 0;
	tmp = (*all)->players;
	if (!(*all)->players)
	{
		(*all)->players = new;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	tmp->next = new;
	if (tmp->next->index > MAX_PLAYERS)
		error("TOO_MUCH_PLAYERS");
}

t_vm		*parce_argv(int ac, char **av)
{
	int		i;
	int		index_champ;
	t_vm	*all;

	i = 1;
	index_champ = 1;
	all = init_vm();
	// if (ac > 15)
	// 	error("BAD_INPUT");
	while (i < ac)
	{
		if (ft_strequ("-dump", av[i]))
			i = valid_dump(all, ac, av, i);
		else if (ft_strequ("-n", av[i]))
			i = valid_num(all, ac, av, i);
		else if (ft_strstr(av[i], ".cor") != NULL)
			i = valid_champ(all, av, i);
		else if (ft_strequ("-v", av[i]))
			i = valid_log(all, ac, av, i);
		else
			error("BAD_ARGUMENT");
	}
	parce_champ_index(all);
	put_champ_index(all);
	return (all);
}

header_t	*parce_champ(int fd)
{
	header_t		*champ;
	unsigned int	read_n;
	unsigned int	head_len;
	unsigned int	i;

	i = 0;
	champ = (header_t *)malloc(sizeof(header_t));
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
	return (champ);
}
