/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:10:50 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/07/21 21:48:07 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*exit_status(char **s)
{
	if (!ft_strncmp(*s, "$?", 2))
	{
		*s += 2;
		return (ft_itoa(g_lbv.exit_status / 256));
	}
	return ((char *)-1);
}

char	*str_add(char *full, char c, char *s)
{
	char	*dest;
	char	*str;

	dest = NULL;
	if (s == (char *)-1)
		return (full);
	if (!s)
	{
		if (c == DEF_SINGEL_Q)
			return (full);
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = c;
		str[1] = '\0';
		dest = ft_strjoin(full, str);
		free(full);
		free(str);
		return (dest);
	}
	dest = ft_strjoin(full, s);
	free(full);
	free(s);
	return (dest);
}

char	*exp_var(char **sp)
{
	char	*s;
	int		i;
	char	*value;

	s = *sp;
	if (s[0] != '$' || (!ft_isalpha(s[1]) && s[1] != '_'))
		return ((char *)-1);
	s++;
	i = 1;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	*sp = s + i;
	value = env_find2(g_lbv.list, s, i);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*lex_var2(char **str, char *full, char *s, char *expnd)
{
	int	i;
	int	mode;

	i = 0;
	mode = 0;
	while (str[i])
	{
		s = str[i];
		while (full && *s)
		{
			mode = change_mode2(mode, *s);
			expnd = (char *)-1;
			if (mode != 1)
			{
				if (*s == '$')
					expnd = ft_exp(expnd, &s);
			}
			if (expnd == (char *)-1)
				full = str_add(full, *s++, NULL);
			else
				full = str_add(full, 0, expnd);
		}
		i++;
	}
	return (full);
}

t_token	lex_var(t_lexer lexer, int len)
{
	char	*s;
	char	**str;
	char	*expnd;
	char	*full;

	expnd = NULL;
	if (lexer.prev_type.type == HERDOC)
		return (t_init(WORD, len, lexer.str));
	full = ft_strdup("");
	s = ft_substr(lexer.str, 0, len);
	str = ft_split(s, DEF_DOUBEL_Q);
	free(s);
	full = lex_var2(str, full, s, expnd);
	ft_clear_av(str);
	if (full)
		return (t_init(VAR, len, full));
	return (t_init(WORD, len, lexer.str));
}
