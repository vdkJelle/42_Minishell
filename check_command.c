/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 12:14:57 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/11 17:28:40 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	closedir_error(DIR **dir_p)
{
	if (closedir(*dir_p) == -1)
		return (print_errno_int());
	return (print_errno_int());
}

static int	check_if_valid_dir(char *dir)
{
	struct dirent	*dir_s;
	DIR				*dir_p;

	dir_p = opendir(dir);
	if (!dir_p)
		return (print_errno_int());
	errno = 0;
	dir_s = readdir(dir_p);
	if (!dir_s && errno)
		closedir_error(&dir_p);
	if (dir_s)
	{
		if (closedir(dir_p) == -1)
			return (print_errno_int());
		return (1);
	}
	return (0);
}

static int	check_in_dir(char *s, char *dir)
{
	struct dirent	*dir_s;
	DIR				*dir_p;

	dir_p = opendir(dir);
	if (!dir_p)
		return (print_errno_int());
	errno = 0;
	dir_s = readdir(dir_p);
	if (!dir_s && errno)
		closedir_error(&dir_p);
	while (dir_s)
	{
		if (!ft_strcmp(s, dir_s->d_name))
		{
			if (closedir(dir_p) == -1)
				return (print_errno_int());
			return (1);
		}
		dir_s = readdir(dir_p);
		if (!dir_s && errno)
			closedir_error(&dir_p);
	}
	if (closedir(dir_p) == -1)
		return (print_errno_int());
	return (0);
}

e_path		check_path(t_data *data, char *s)
{
	e_path	path;
	
	if (check_in_dir(s, "/bin/") == 1)
		path = BIN;
	else if (check_in_dir(s, "/usr/bin/") == 1)
		path = USR_BIN;
	else if (s && s[ft_strlen(s) - 1] == '/' && check_if_valid_dir(s) == 1)
		path = DIRECTORY;
	else if (!ft_strchr(s, '/'))
		path = NOT_FOUND;
	else
		path = STANDARD;
	if (path == DIRECTORY)
	{
		ft_putstr_fd("🐶 > ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		data->exit_status = 126;
	}
	else if (path == NOT_FOUND)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit_status = 127;
	}
	return (path);
}

// int			check_command(t_data *data, char *s)
// {
// 	int		ret;

// 	ret = 1;
// 	if (s && s[ft_strlen(s) - 1] == '/')
// 	{
// 		ft_putstr_fd("🐶 > ", 2);
// 		ft_putstr_fd(s, 2);
// 		ft_putstr_fd(": Is a directory\n", 2);
// 		(void)data; /*add exit status ? here */
// 		return (1);
// 	}
// 	if (ret == 1)
// 		ret = check_in_dir(s, "/bin");
// 	if (ret == 1)
// 		ret = check_in_dir(s, "/usr/bin/");
// 	if (ret == 1)
// 		ret = check_executable(s);
// 	if (ret == -1)
// 	{
// 		ft_putstr_fd(strerror(errno), 2);
// 		(void)data; /*add exit status 1 here */
// 		return (-1);
// 	}
// 	if (ret == 1)
// 	{
// 		ft_putstr_fd(s, 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		(void)data; /*add exit status 127 here */
// 		return (1);
// 	}
// 	return (0);
// }

// int			check_executable(char *s)
// {
// 	// char	*path;
// 	// char	*dir;
// 	int		end;
// 	int		start_path;

// 	end = ft_strlen(s);
// 	start_path = -1;
// 	while (end > 0)
// 	{
// 		if (s[end] == '/')
// 		{
// 			start_path = end + 1;
// 			break ;
// 		}
// 		end--;
// 	}
// 	// if (start_path > -1)
// 	// {
// 	// 	// path = ft_substr(s, start_path, ft_strlen(s) - start_path);
// 	// 	// dir = ft_substr(s, 0, start_path);
// 	// 	// printf("path = %s\tdir = %s\n", path, dir);
// 	// 	// if (!path || !dir)
// 	// 	// 	exit(1);
// 	// 	// return (check_in_dir(path, dir));
// 	// }
// 	if (start_path == -1)
// 		return (1);
// 	else
// 		return (0);
// }