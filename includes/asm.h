/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:38:58 by yyakoven          #+#    #+#             */
/*   Updated: 2019/03/26 15:22:26 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H
# define __ASM_H

# include "vm.h"
# include <fcntl.h>

# define SPACE 32
# define OOPS 999999999
# define TAB 9
# define NL 10
# define HSH COMMENT_CHAR

extern	int				g_lnstp;
int						g_bytes;

typedef struct s_plr	t_plr;
typedef struct s_instr	t_instr;
typedef struct s_label	t_label;

struct					s_plr
{
	char				*name;
	char				*filename;
	int					done;
	char				*comment;
	char				*args;
	char				*cur_args[3];
	t_instr				*instr;
	t_label				*label;
	t_instr				*last;
	int					ins_num;
	unsigned char		*output;
	int					boi;
	char				*c;
};

struct					s_instr
{
	char				*command;
	int					bytes;
	int					total_bytes;
	int					code;
	char				*args[3];
	int					arg_codes[3];
	t_instr				*next;
	char				*cmd;
};

struct					s_label
{
	char				*name;
	t_instr				*instr;
	t_label				*next;
};

void					read_execution(int fd, t_plr *plr, char **line);
void					add_label(t_label *label, t_label **head);
t_label					*create_label(char *str);
void					add_instr(t_instr *instr, t_plr *plr);
t_instr					*create_instr(char *name);
int						process_instr(t_instr *inst, t_plr *plr);
void					encode(t_instr *instr, int fd_cor);
void					apply_labels(t_plr *plr);
void					e2(char *message, char *delay);
unsigned int			reverse_int(unsigned int b);
unsigned short			reverse_short(unsigned short b);
int						check_arg_num(char *line, int arg_num, t_plr *plr);
int						skip_valid_char(char *line, int mode);
int						find_instruction_id(char *name);
int						detect_direct_char(char *cmd, t_instr *instr,
						int index);
int						detect_indi_char(char *cmd, t_instr *instr, int index);
char					*send_nudes(char *str);
int						valid_arg(char *str, int mode);
void					read_commands(int fd, t_plr *plr, char **line);
char					*is_label(char **line);
char					*is_instruction(char *line);
t_instr					*search_for_instr_or_label(int fd, char **line,
						t_plr *plr);
void					check_for_validity(char *ptr);
void					check_length(t_plr *plr);
void					create_file(int *fd_cor, char *name);
char					*open_file(int argc, char **argv, int *fd_s);
void					error(char *message);
int						find_instruction_id(char *name);
int						get_command_type(char *ptr);
int						is_comment(char *line);
int						is_empty(char *line);
int						read_file(int fd, t_plr *plr);
char					*skip_whitespace(char *line);
void					skip_empty_lines(int fd, char **line);

#endif
