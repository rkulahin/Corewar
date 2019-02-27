/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:21:40 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/26 14:42:14 by seshevch         ###   ########.fr       */
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
	int						live;
	header_t				*champ;
	t_players				*next;
};

struct						s_vm
{
	int						index_player[MAX_PLAYERS];	
	int						nbr_cycles;  			// -dump
	int						nbr_plrs;				// кол-во игроков
	int						cycle;					// циклов прошло
	int						live;					// live за vm->cycle_to_die
	int						nbr_checks;				// кол-во проверок, когда vm->cycle_to_die не менялся
	
	int						cycle_to_die;			// циклов до проверки
	int						die;					// циклы смерти

	int						nbr_log;				// бонус вывод
	int						nbr_car;				// кол-во кареток
	unsigned char			map[MEM_SIZE * 2];

	t_players				*players;				// игроки
	
	int						last_index;				// последний игрок который сказал что он жив
	char					*last_name;				// имя последнего игрока

	t_carriage				*carriage;				// каретки
};

struct						s_carriage
{
	int						position;				// позиция каретки на карте
	int						carry;
	int						nbr_plr;				// индекс игрока
	int						index;
	unsigned int			regist[REG_NUMBER];		// регистры

	int						live;					// когда последний зал исполняла команду live
	char					operation[2];			// байт операции
	int						cycle;					// кол-во циклов до исполнения

	t_carriage				*next;
};

/*
** main.c
*/
t_vm						*init_vm(void);
t_players					*init_player(void);
void						error(char *line);
unsigned int				reverse(unsigned int b);
/*
** parce.c
*/
t_vm						*parce_argv(int ac, char **av);
header_t					*parce_champ(int fd);
void						add_champ(t_vm **all, t_players *new);
void						parce_champ_index(t_vm *all);
void						put_champ_index(t_vm *all);
/*
** valid.c
*/
int							valid_champ(t_vm *all, char **av, int i);
int							valid_num(t_vm *all, int ac, char **av, int i);
int							valid_dump(t_vm *all, int ac, char **av, int i);
int							str_of_num(char *str);
int							nbr_champ(t_players *tmp);
/*
** vm_map.c
*/
void						vm_map(t_vm *vm, t_players *plr, int i, int k);
int							find_cycle(int nbr);
void						add_carriage(t_vm *vm, t_carriage *new);
t_carriage					*init_carriage(t_vm *vm, int index, int position);
/*
** corewar.c
*/
void						kill_carriage(t_vm *vm, t_carriage *cr);
void						main_check(t_vm *vm, t_carriage *tmp);
void						check_player(t_vm *vm);
void						check_command(t_vm *vm, t_carriage *cr);
void						main_cycle(t_vm *vm);
/*
** func.c
*/
int							vm_atoi_16(char *str);
char						*vm_itoa_16(long long numb);
int							*check_arg(int nb);
/*
** other.c
*/
void						run_to_command(t_vm *vm,t_carriage *cr);
void						print_and_return(void);						// Написать
void						win_player(t_players *last);
void						replace_map(t_vm *vm, int position, char *ptr, int nb);
/*
** op_live.c
*/
void						op_live(t_vm *vm, t_carriage *cr);
char						*valid_str(t_vm *vm, int position, int	nb);
/*
** op_fork.c
*/
void						copy_regist(t_carriage *new, t_carriage *cr);
t_carriage					*copy_carriage(t_vm * vm, t_carriage *cr);
void						op_fork(t_vm *vm, t_carriage *cr);
void						op_lfork(t_vm *vm, t_carriage *cr);
/*
** op_st.c
*/
void						op_st(t_vm *vm, t_carriage *cr);
void						op_sti(t_vm *vm, t_carriage *cr);
/*
** op_and.c
*/
void						op_and(t_vm *vm, t_carriage *cr);
void						op_or(t_vm *vm, t_carriage *cr);
void						op_xor(t_vm *vm, t_carriage *cr);
/*
** op_add.c
*/
void						op_add(t_vm *vm, t_carriage *car);
void						op_sub(t_vm *vm, t_carriage *car);

/*
** op_aff.c
*/
void						op_aff(t_vm *vm, t_carriage *cr);
char						*space_byte_print(char *ptr);

/*
** op_load_index.c
*/
void						op_load_index(t_vm *vm, t_carriage *cr);

/*
** op_load.c
*/
void						op_load(t_vm *vm, t_carriage *cr);
/*
** op_long_load_index.c
*/
void						op_long_load_index(t_vm *vm, t_carriage *cr);

/*
** op_zjmp.c
*/
void						op_zjmp(t_vm *vm, t_carriage *cr);

/*
** op_long_load.c
*/
void						op_long_load(t_vm *vm, t_carriage *car);

/*
** bonus_parce.c
*/
int							valid_log(t_vm *all, int ac, char **av, int i);

typedef	void	(*t_func)(t_vm *vm, t_carriage *cr);
//T_IND сколько пропускать
extern	t_func					g_func[17];
#endif
