/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwesche <nwesche@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:44:01 by nwesche           #+#    #+#             */
/*   Updated: 2022/08/08 10:39:16 by nwesche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(char *cmd, t_struct *mini)
{
	if ((!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4)
		|| (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2)
		|| (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6)
		|| (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5)
		|| (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("exit", cmd, 4) && ft_strlen(cmd) == 4))
		mini->is_builtin = true;
	else
		mini->is_builtin = false;
}

void	run_builtin(t_struct *mini)
{
	if (!ft_strncmp(mini->tokens[0], "exit", 4))
		ft_exit(mini);
	if (!ft_strncmp(mini->tokens[0], "pwd", 3))
		ft_pwd(mini);
	if (!ft_strncmp(mini->tokens[0], "echo", 4))
		ft_echo(mini);
	if (!ft_strncmp(mini->tokens[0], "cd", 2))
		ft_cd(mini);
	if (!ft_strncmp(mini->tokens[0], "env", 3))
		ft_env(mini);
	if (!ft_strncmp(mini->tokens[0], "export", 6))
		ft_export(mini);
	if (!ft_strncmp(mini->tokens[0], "unset", 5))
		ft_unset(mini);
}

void	ft_exit(t_struct *mini)
{
	free_char_array2(mini->commands);
	if (mini->path)
		free_char_array(mini->path);
	free (mini->home);
	printf("exit\n");
	exit(0);
}

void	free_char_array2(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}
