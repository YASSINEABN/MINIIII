/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:26:58 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/07/21 22:27:02 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

unsigned long long	ft_llatoi(const char *str)
{
	unsigned long long	nombre;
	int					signe;
	int					i;

	i = 0;
	nombre = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nombre = nombre * 10;
		nombre = nombre + (int)(str[i] - '0');
		i++;
	}
	if (nombre > 9223372036854775807)
		return (255);
	return (nombre * signe);
}

int	check_if_all_digit(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg) && *arg != '-')
			return (0);
		arg++;
	}
	return (1);
}

void	exit_cmd(t_parser_node *root)
{
	unsigned long long	result;

	printf("exit\n");
	if (root->ac == 1)
		return (node_del(&root), exit(1));
	else if ((root->ac > 1 && !check_if_all_digit(root->av[1]))
		|| (check_if_all_digit(root->av[1]) && ft_strlen(root->av[1]) > 19))
	{
		printf("minishell: exit: %s: numeric argument require\n", root->av[1]);
		node_del(&root);
		exit(255);
	}
	else if (root->ac == 2 && check_if_all_digit(root->av[1]))
	{
		result = ft_llatoi(root->av[1]);
		node_del(&root);
		if ((int)result < 0)
			exit(256 - ((result * -1) % 256));
		exit(result % 256);
	}
	else if (root->ac > 2 && check_if_all_digit(root->av[1]))
		printf("minishell: exit: %s: too many arguments\n", root->av[1]);
	g_lbv.exit_status = 256;
}
