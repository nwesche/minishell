/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwesche <nwesche@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:05:45 by nwesche           #+#    #+#             */
/*   Updated: 2022/08/03 15:33:02 by nwesche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	The Fork Function
**	it creates a copy (child process) of the current process (parent process)
**	man fork -> for more info.
**	after that there will be two processes one is parent and the other is child
**	the child executes the cmd_args with the environment given on the parameters
**	the parent waits the child to finish
*/

static void	forkit(char *full_path, char **cmd_args, t_list **env)
{
	int		status;
	pid_t	father;
	char	**env_tab;

	env_tab = env_to_tab(*env);
	father = fork();
	if (father > 0)
	{
		wait(&status);
		ft_free_strtab(env_tab);
	}
	else if (father == 0)
		execve(full_path, cmd_args, env_tab);
}

/*
**	the command given need to be executed without searching in $PATH
**	because it's have with it the path like : /bin/ls
**	the function check if it's exist and it's permission to execute is OK
**	then sends it to forkit function 
**	otherwise, it prints an error msg.
*/

static void	exec_local(char **cmd_args, t_list **env)
{
	if (access(*cmd_args, F_OK) == 0)
	{
		if (access(*cmd_args, X_OK) == 0)
			forkit(*cmd_args, cmd_args, env);
		else
			ft_printf_fd(2, "%s: Permission denied.\n", *cmd_args);
	}
	else
		ft_printf_fd(2, "%s: Command not found.\n", *cmd_args);
}

/*
**	the command given to be search in all paths stored in environment variable $PATH
**	then if it's exist (F_OK) it checks it's permission (X_OK) to execute
**	then sends it to forkit function
**	otherwise, it prints an error msg.
*/

void		exec_cmd(char **cmd_args, char **path, t_list **env)
{
	char	*full_path;
	char	*error;
	char	**head_path;

	error = NULL;
	head_path = path;
	if (*cmd_args != NULL)
	{
		while (*path)
		{
			//full_path = ft_strjoin_pre(*path, "/", *cmd_args); str_join_pre function needs to be added
			if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			{
				forkit(full_path, cmd_args, env);
				//free_exec_cmd(error, full_path, head_path); ->free function needs to be added
				return ;
			}
			else if (error != NULL && access(full_path, F_OK) == 0)
				error = ft_strjoin(full_path, ": Permission denied.\n");
			path++;
			free(full_path);
		}
		print_error(error, *cmd_args);
	}
	//ft_free_strtab(head_path); ft_free_strtab needs to be added
}
