/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 15:38:40 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/18 19:08:15 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Removes an environmental variable
** Frees the string and moves the other strings up one place
** Decrements the size of the array
** No return value
*/

static void	destroy_entry(char ***our_env, int *env_size, int i)
{
	free((*our_env)[i]);
	(*our_env)[i] = NULL;
	while ((*our_env)[i])
	{
		(*our_env)[i] = (*our_env)[i + 1];
		i++;
	}
	(*env_size)--;
}

/*
** Checks if there is a match between the key and an environmental variable
** If the key is a match the environmental variable is destroyed
** No return value
*/

static void	check_for_entry(char *arg, char ***our_env, int *env_size)
{
	int		i;
	int 	j;

	i = 0;
	while ((*our_env)[i])
	{
		j = 0;
		while ((*our_env)[i][j] && (*our_env)[i][j] != '=')
			j++;
		if (!ft_strncmp((*our_env)[i], arg, j))
			return (destroy_entry(our_env, env_size, i));
		i++;
	}
	return ;
}

/*
** Checks if the identifier is valid
** An argument is invalid if 
**		the first character is not a letter or '_'
** 		the following characters up to the '=' are not alphanumerical or '_'
** Returns 0 if the argument is valid
** Returns 1 if the argument is invalid
*/

static int	check_if_valid(char *input)
{
	int		i;

	i = 0;
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (1);
	while (input[i])
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

/*
** Removes environmental variables
** An environmental variable is removed from the array if
**		the argument is valid
**		the key exists
** No return value
*/

void	ft_unset(t_data *data)
{
	char	**args;
	int		i;

	args = data->args;
	data->exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (check_if_valid(args[i]))
			print_error(data, 1, 3,
			"🐶 > unset: `", args[i], "': not a valid identifier");
		else
			check_for_entry(args[i], &data->our_env, &data->env_size);
		i++;
	}
}
