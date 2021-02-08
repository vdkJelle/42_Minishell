/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/08 11:04:14 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path)
{
	int		i;

	i = 2;
	while (path[i] == ' ')
		i++;
	i = chdir(path + i);
	if (i < 0)
		printf("Path does not exist\n");
	return ;
}
