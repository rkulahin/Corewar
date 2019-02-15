/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:21:40 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/15 17:53:59 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libftprintf/includes/ft_printf.h"
# include <fcntl.h>
# include "op.h"

/*
** color types
*/

# define EOC "\033[0m"

# define RED "\033[1;31m"
# define GRE "\033[32m"
# define BLU "\033[34m"
# define YEL "\033[1;33m"
# define VIO "\033[35m"
# define BLA "\033[30m"
# define WHI "\033[1;37m"

/*
** structers
*/

typedef struct s_vm			t_vm;
typedef struct s_players	t_players;
typedef struct s_carriage	t_carriage;
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
	int						nbr_plrs;

	unsigned char			map[MEM_SIZE * 2];

	t_players				*champs;
	t_carriage				*carriage;
	t_op					optab[17];
};

struct						s_carriage
{
	int						position;
	int						carry;
	int						nbr_plr;

	unsigned int			regist[REG_NUMBER];

	int						live;
	char					operation[2];
	int						cycle;

	t_carriage				*next;
};

/*
** 2
*/
t_vm						*init_vm(void);
t_players					*init_player(void);
void						error(char *line);
unsigned int				reverse(unsigned int b);

t_vm						*parce_argv(int ac, char **av);
header_t					*parce_champ(int fd);
void						add_champ(t_vm **all, t_players *new);
void						parce_champ_index(t_vm *all);
void						put_champ_index(t_vm *all);

int							valid_champ(t_vm *all, char **av, int i);
int							valid_num(t_vm *all, int ac, char **av, int i);
int							valid_dump(t_vm *all, int ac, char **av, int i);
int							str_of_num(char *str);
int							nbr_champ(t_players *tmp);

void						vm_map(t_vm *vm, t_players *plr, int i, int k);
int							find_cycle(char c1, char c2);
void						add_carriage(t_vm *vm, t_carriage *new);
t_carriage					*init_carriage(t_vm *vm, int index, int position);

int							vm_atoi_16(char *str);
char						*vm_itoa_16(long long numb);
int							*check_arg(int nb);

#endif
