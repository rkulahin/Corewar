/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:32:24 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/13 19:02:18 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		change_champ_index(t_vm *all)
{
	int			i;
	int			j;
	t_players	*tmp;

	i = 0;
	tmp = all->champs;
	while (tmp)
	{
		if (all->index_player[i] != 0)
			tmp->index = all->index_player[i];
		i++;
		tmp = tmp->next;
	}
	tmp = all->champs;
	j = nbr_champ(all->champs);
	while (tmp)
	{
		if (j < tmp->index)
			error("BAD_INDEX");
		tmp = tmp->next;
	}
}

void		add_champ(t_vm **all, t_players *new)
{
	t_players	*tmp;

	tmp = (*all)->champs;
	if (!(*all)->champs)
	{
		(*all)->champs = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	tmp->next->index = tmp->index + 1;
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
	if (ac >= (MAX_PLAYERS * 2) + 2)
		error("BAD_INPUT");
	while (i < ac)
	{
		if (ft_strequ("-dump", av[i]))
			i = valid_dump(all, ac, av, i);
		else if (ft_strequ("-n", av[i]))
			i = valid_num(all, ac, av, i);
		else if (ft_strstr(av[i], ".cor") != NULL)
			i = valid_champ(all, av, i);
		else
			error("BAD_ARGUMENT");
	}
	change_champ_index(all);
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
