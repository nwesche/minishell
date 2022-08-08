/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwesche <nwesche@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:16:18 by nwesche           #+#    #+#             */
/*   Updated: 2022/08/08 14:19:46 by nwesche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
** env is a shell command 
** It can print a list of the current environment variables
** Executing env with no options displays the current environment variables and their values
*/

int	ms_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putstr(env->value);
		env = env->next;
	}
	if (env)
		ft_putstr(env->value);
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
//maybe if(str==0) return ;
void	ft_putstr(char *str) 
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}
