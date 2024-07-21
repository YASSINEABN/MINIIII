

#include "builtins.h"

void	print_unset_error(char *argv, int *check, int *check_exit_status)
{
	*check = 1;
	*check_exit_status = 256;
	printf("minishell: unset: %s: not a valid identifier\n", argv);
}

void	parse_unset_variable(char *argv, int *check, int *check_exit_status)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[0]))
	{
		print_unset_error(argv, check, check_exit_status);
		return ;
	}
	while (argv[i] && *check == 0)
	{
		if ((argv[i] <= 64 \
		&& !ft_isdigit(argv[i])) \
		|| (argv[i] >= 91 && argv[i] <= 96 \
		&& argv[i] != '_') || argv[i] >= 123)
			print_unset_error(argv, check, check_exit_status);
		i++;
	}
}
char *get_value(char *s, t_env_node *env)
{

    while (env) {
        if(!ft_strcmp(s, env->content))
            return ft_strdup(env->name);
        env = env->next;
    }
    return NULL;
}

void	unset(t_parser_node *root, int index)
{
	int	k;
	int	check_exit_status;

	check_exit_status = 0;
	if (root->ac > 1)
	{
		if (root->av[1][0] == '-')
		{
			g_lbv.exit_status = 512;
			printf("minishell: unset: %s: invalid option\n", root->av[1]);
			printf("unset: usage: unset [-f] [name ...]\n");
		}
		else if (root->ac >= 2)
		{
			while (root->av[index])
			{
				k = 0;
				if(env_find3(g_lbv.list,root->av[1]))
				{
				    root->av[index] = get_value(root->av[1],g_lbv.list);
				}
				parse_unset_variable(root->av[index], &k, &check_exit_status);
				if (k == 0 && env_find(g_lbv.list, root->av[index], -1))
					ft_list_remove_if(&g_lbv.list, root->av[index]);
				index++;
			}
		g_lbv.exit_status = check_exit_status;
		}
	}
}
