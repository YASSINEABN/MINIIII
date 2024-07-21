/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:10:40 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/07/21 21:10:43 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#define NO_EXPANSION	((char *)-1)

char	*ft_exp(char *expnd, char **s)
{
	expnd = exit_status(s);
	if (expnd == NO_EXPANSION)
		expnd = exp_var(s);
	return (expnd);
}
