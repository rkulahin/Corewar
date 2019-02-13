/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:21:40 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/13 19:02:28 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libftprintf/includes/ft_printf.h"
# include <fcntl.h>
# include "op.h"

typedef struct s_vm			t_vm;
typedef struct s_players	t_players;

/*
** 1
*/

struct						s_players
{
	int						index;
	header_t				*champ;
	t_players				*next;
};

struct						s_vm
{
	int						index_player[MAX_PLAYERS];
	int						nbr_cycles;
	t_players				*champs;
};

/*
** 2
*/
t_vm						*init_vm(void);
t_players					*init_player(void);
void						error(char *line);
unsigned int				reverse(unsigned int b);

header_t					*parce_champ(int fd);
void						change_champ_index(t_vm *all);
void						add_champ(t_vm **all, t_players *new);
t_vm						*parce_argv(int ac, char **av);

int							valid_champ(t_vm *all, char **av, int i);
int							str_of_num(char *str);
int							nbr_champ(t_players *tmp);
int							valid_num(t_vm *all, int ac, char **av, int i);
int							valid_dump(t_vm *all, int ac, char **av, int i);

void						vm_map(int nb, unsigned int plr[CHAMP_MAX_SIZE + 1],
										unsigned int size);
#endif
