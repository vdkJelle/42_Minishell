/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 11:08:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/02/25 15:58:40 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_char(char **s, char c)
{
	if (!(*s))
		return ;
	if (**s && **s == c)
		(*s)++;
}

void	skip_chars(char **s, char c)
{
	if (!(*s))
		return ;
	while (**s && **s == c)
		(*s)++;
}

int		skip_chars_int(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

int		skip_until_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
