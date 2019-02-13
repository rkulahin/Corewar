/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:34:35 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/13 19:47:54 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_players		*init_player(void)
{
	t_players	*new;

	new = (t_players *)malloc(sizeof(t_players));
	new->champ = NULL;
	new->index = 1;
	new->next = NULL;
	return (new);
}

t_vm			*init_vm(void)
{
	t_vm	*new;

	new = (t_vm *)malloc(sizeof(t_vm));
	new->champs = NULL;
	ft_bzero(new->index_player, 32);
	new->nbr_cycles = 0;
	return (new);
}

void			error(char *line)
{
	ft_printf("%s\n", line);
	exit(1);
}

unsigned int	reverse(unsigned int b)
{
	b = (b >> 16 | b << 16);
	b = ((b & 0xFF00FF00) >> 8 | (b & 0x00FF00FF) << 8);
	return (b);
}

int				main(int ac, char **av)
{
	t_vm	*all;

	all = parce_argv(ac, av);
	// vm_map(1, champ->prog, champ->prog_size);
	return (0);
}
