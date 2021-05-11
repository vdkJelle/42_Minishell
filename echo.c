/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 10:21:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/11 10:32:48 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data *data)
{
	int		newline;
	int		i;
	int		fd;
	char	**args;

	args = data->args;
	fd = data->our_fd[1];
	i = 1;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		i++;
		newline = 0;
	}
	else
		newline = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (newline == 1)
		ft_putchar_fd('\n', fd);
	data->exit_status = 0;
}
