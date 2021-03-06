/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 16:30:26 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/18 19:07:35 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Terminates the calling process
** If there there are no arguments the process is terminated with exit code 0
** If there is one argument and it's numeric (n)
**		the process is terminated with exit code n
** If there is one argument and isn't numeric
**		the error is printed and the process is terminated with exit code 1
** If there is more than one argument the error is printed and the process is
**		not terminated
** No return value
*/

void	ft_exit(t_data *data)
{
	char	**args;
	int		i;

	args = data->args;
	if (args[1] && args[2] != NULL)
	{
		print_error(data, 1, 1, "🐶 > exit: too many arguments");
		return ;
	}
	ft_putstr_fd("exit\n", data->our_fd[1]);
	if (args[1] && args[2] == NULL)
	{
		i = 0;
		while (args[1][i] && ft_isdigit(args[1][i]))
			i++;
		if (args[1][i] != '\0')
			print_error(data, 2, 3,
			"🐶 > exit: ", args[1], ": numeric argument required");
		data->exit_status = ft_atoi(args[1]);
	}
	exit(data->exit_status);
}
