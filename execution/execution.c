/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaiss <ibenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:27:29 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/07/21 22:27:34 by ibenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../redirection/redirection.h"
#include "./builtins/builtins.h"
#include "execution.h"
#include <fcntl.h>
#include <string.h>
#include <sys/errno.h>

void	execution_cmd(t_parser_node *root)
{
	char	*copy;

	copy = ft_strdup(root->av[0]);
	str_tolower(copy);
	if (ft_strcmp(copy, "echo") == 0)
		echo(root);
	else if (ft_strcmp(copy, "env") == 0)
		env_cmd(root);
	else if (ft_strcmp(root->av[0], "cd") == 0)
		cd(root);
	else if (ft_strcmp(copy, "pwd") == 0)
		pwd();
	else if (ft_strcmp(root->av[0], "unset") == 0)
		unset(root, 1);
	else if (ft_strcmp(root->av[0], "exit") == 0)
		exit_cmd(root);
	else if (ft_strcmp(root->av[0], "export") == 0)
		export(root);
	else
		launch_executabl(root, env_listsize(g_lbv.list));
	free(copy);
}

void	execute_left(int *fd, t_parser_node *left)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execution(left);
	exit(127);
}

void	execute_right(int *fd, t_parser_node *right)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	execution(right);
	exit(0);
}

void	pipe_fork(t_parser_node *root)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
		execute_left(fd, root->left);
	pid = fork();
	if (pid == 0)
		execute_right(fd, root->right);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, &g_lbv.exit_status, 0);
	waitpid(-1, &g_lbv.exit_status, 0);
}

void	execution(t_parser_node *root)
{
	if (root == NULL)
		return ;
	if (root->type == PIPE)
		pipe_fork(root);
	else if (root->type == CMD)
	{
		if (root->rdrlst)
			redirection(root);
		else
			execution_cmd(root);
	}
}
