/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:39:43 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/11 16:40:27 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vm		*parce_argv(int ac, char **av, int i)
{
	int		index_champ;
	t_vm	*all;

	index_champ = 1;
	all = init_vm();
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
		else if (ft_strequ("-a", av[i]))
			i = valid_aff(all, i);
		else if (ft_strequ("-c", av[i]))
			i = valid_curses(all, i);
		else
			error("BAD_ARGUMENT");
	}
	parce_champ_index(all);
	put_champ_index(all);
	return (all);
}
