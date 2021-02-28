/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/28 12:24:14 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path)
{
	int		i;
	int		ret;

	i = 0;
	while (path[i] == ' ')
		i++;
	if (path[i] == '\0')
		ret = chdir(get_env(environ, "HOME"));
	else
		ret = chdir(path + i);
	if (ret < 0)
		printf("%s\n", strerror(errno));
	return ;
}
