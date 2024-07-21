

#include "builtins.h"
#include<stdlib.h>
#include <unistd.h>
#include<stdio.h>

void	pwd()
{
	char	*cwd;
	char	buffer[4096];

	cwd = getcwd(buffer, 4096);

		if (cwd == NULL)
			printf("%s\n", buffer);
		else
			printf("%s\n", cwd);
		g_lbv.exit_status = 0;
	}
