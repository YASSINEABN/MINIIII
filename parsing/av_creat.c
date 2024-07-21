/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av_creat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:06:27 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/07/21 21:06:29 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**iter_lst(t_cmd **lst, t_wc_node *tmp, t_cmd *cmd, char **av)
{
	int	i;

	i = 0;
	while (*lst)
	{
		if ((*lst)->wc)
		{
			while ((*lst)->wc)
			{
				av[i++] = (*lst)->wc->d_name;
				tmp = (*lst)->wc;
				(*lst)->wc = (*lst)->wc->next;
				free(tmp);
			}
		}
		else
			av[i++] = remove_q((*lst)->word);
		cmd = *lst;
		*lst = (*lst)->next;
		free(cmd);
	}
	av[i] = 0;
	return (av);
}

char	**av_creat(t_cmd **lst)
{
	char		**av;
	int			size;
	t_cmd		*cmd;
	t_wc_node	*tmp;

	cmd = NULL;
	tmp = NULL;
	size = cmd_size(*lst);
	av = malloc(sizeof(char *) * (size + 1));
	if (!av)
		return (NULL);
	av = iter_lst(lst, tmp, cmd, av);
	return (av);
}
