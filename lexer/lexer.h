/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:11:20 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/07/21 21:11:22 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define DEF_SINGEL_Q -1
# define DEF_DOUBEL_Q -2

# include"../libft/libft.h"
# include"../env1/env.h"
# include"../utils/utils.h"
# include <stdbool.h>

typedef enum token_type
{
	CHAR_NULL,
	TOK,
	ENDF,
	CMD,
	VAR,
	RD_IN,
	RD_OUT,
	HERDOC,
	RD_APP,
	PIPE,
	WORD,
	ERROR,
	END,
}		t_token_type;

typedef struct token
{
	int				len;
	char			*pos;
	t_token_type	type;
}			t_token;

typedef struct s_lexer
{
	char	*full_str;
	char	*str;
	t_token	prev_type;
	t_token	curent_type;
}		t_lexer;

typedef struct s_glb_v
{
	t_env_node	*list;
	int			check_signal;
	int			exit_status;
	int			check_sigquit;
}			t_glb_v;

extern t_glb_v	g_lbv;

int			change_mode(int i, char c);
char		*quote_def(char *str);
t_token		t_init(t_token_type	_tp, int len, char *p);
t_token		lex_search(t_lexer	lexer);
t_lexer		*lex_init(char *s);
t_token		word_collect(t_lexer	*lexer, int var, int len);
t_token		get_token(t_lexer *lexer);
t_token		get_next_token(t_lexer	*lexer);
t_token		check_next_token(t_lexer	lexer, int i);
t_token		t_wc_init(t_token_type	type, int len, t_wc_node *p, char *pos);
t_token		lex_var(t_lexer lexer, int len);
int			change_mode2(int i, char c);
char		*exp_var(char **sp);
char		*exit_status(char **s);
char		*ft_exp(char *expnd, char **s);

#endif
