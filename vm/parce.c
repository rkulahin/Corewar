/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:32:24 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/17 17:19:34 by rkulahin         ###   ########.fr       */
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
	new->next = NULL;
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

static void	ch_magic(char *s, char *s1)
{
	if (ft_strcmp(s, s1))
		error("BAD_MAGIC");
	free(s);
	free(s1);
}

t_header	*parce_champ(int fd, unsigned int i, char *s, char *s1)
{
	t_header		*champ;
	unsigned int	read_n;
	unsigned int	head_len;

	i = 0;
	champ = (t_header *)malloc(sizeof(t_header));
	head_len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	read_n = read(fd, champ, head_len);
	if (read_n != head_len)
		error("BAD_HEADER");
	champ->magic = reverse(champ->magic);
	s = ft_itoa_base_x(COREWAR_EXEC_MAGIC, 16);
	s1 = ft_itoa_base_x(champ->magic, 16);
	ch_magic(s, s1);
	champ->prog_size = reverse(champ->prog_size);
	read_n = read(fd, champ->prog, CHAMP_MAX_SIZE + 1);
	if (read_n != champ->prog_size || champ->prog_size > CHAMP_MAX_SIZE)
		error("BAD_CHAMP_SIZE");
	while (i < champ->prog_size / 4)
	{
		champ->prog[i] = reverse(champ->prog[i]);
		i++;
	}
	champ->prog[i] = reverse(champ->prog[i]);
	return (champ);
}
