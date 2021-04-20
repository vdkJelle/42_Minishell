/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_handle_arg_chars.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 14:29:30 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/12 15:30:46 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_char(t_data *data, char **ret, char *s)
{
	if (!s)
		return (-1);
	(void)data;
	*ret = ft_strjoin_char(*ret, s[0]);
	if (!(*ret))
		exit(1);
	return (1);
}

int		handle_doublequotes(t_data *data, char **ret, char *s)
{
	int		i;
	
	if (s[1] && s[1] == '\"')
		return (2);
	i = 1;
	handle_char(data, ret, "\'");
	while (s[i] && (s[i] != '\"' || (s[i] == '\"' && count_backslash(s, i) % 2)))
	{
		if (s[i] == '\\' && s[i + 1] && ft_strchr("\\\"$", s[i + 1]))
		{
			handle_char(data, ret, s + i + 1);
			i++;
		}
		else if (s[i] == '$' && count_backslash(s, i) % 2 == 0 && s[i + 1] && s[i + 1] != '\"' && !(s[i + 1] != '_' && !ft_isalpha(s[i + 1])))
			i += handle_environment_variable(data, ret, s + i) - 1;
		else
			handle_char(data, ret, s + i);
		i++;
	}
	handle_char(data, ret, "\'");
	return (i + 1);
}

//Implement exit status
int		handle_environment_variable(t_data *data, char **ret, char *s)
{
	char	*key;
	char	*value;
	int		len;

	if (s[0] == '$' && s[1] == '?')
	{
		*ret = ft_strjoin_char(*ret, 0 + '0');
		if (!(*ret))
			exit(1);
		return (2);
	}
	len = 0;
	while (s[len + 1] && (s[len + 1] == '_' || ft_isalnum(s[len + 1])))
		len++;
	key = ft_substr(s, 1, len);
	if (!key)
		exit(1);
	value = get_env(data->our_env, key);
	free(key);
	if (!value || value[0] == '\0')
		return (len + 1);
	*ret = ft_strjoin_free_s1(*ret, value);
	if (!(*ret))
		exit(1);
	return (len + 1);
}

int		handle_metacharacter(t_data *data, char **ret, char *s)
{
	int		i;

	(void)data;
	i = skip_whitespaces_int(s);
	while (is_metacharacter(s[i]) && !is_whitespace(s[i]) && !is_control_operator(s[i]))
	{
		handle_char(data, ret, s + i);
		i++;
	}
	i += skip_whitespaces_int(s + i);
	return (i);
}

int		handle_singlequotes(t_data *data, char **ret, char *s)
{
	int		i;
	int		len;

	(void)data;
	i = 0;
	if (s[i + 1] && s[i + 1] == '\'')
		return (2);
	handle_char(data, ret, "\'");		
	len = skip_until_char_excl(s + 1, '\'');
	if (len > 0)
	{
		*ret = ft_strjoin_free_both(*ret, ft_substr(s, 1, len));
		if (!(*ret))
			exit(1);
	}
	handle_char(data, ret, "\'");
	return (len + 2);
}