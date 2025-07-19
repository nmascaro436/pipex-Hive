/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:53:13 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/19 15:57:15 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/**
* Checks if a command is a direct path and is executable,
* used to determine whether a command should be executed directly,
* or searched in the PATH environment variable.
* Returns 1 on success, 0 otherwise.
*/

int	is_cmd_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			if (access(cmd, X_OK) == 0)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/**
* Creates a candidate full path by joining 'dir' and 'cmd'.
* Uses access() to check if it's executable,
* if it is the candidate path is returned.
* If not, memory is freed and NULL is returned.
*/

static char	*build_and_check(char *dir, char *cmd)
{
	char	*temp;
	char	*candidate;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	candidate = ft_strjoin(temp, cmd);
	free(temp);
	if (!candidate)
		return (NULL);
	if (access(candidate, X_OK) == 0)
		return (candidate);
	free(candidate);
	return (NULL);
}

/**
* Splits the PATH string by ':' to get a list of directories,
* and tries to find an executable command inside each of them.
* Returns a malloc'd string with the full path to the command,
* or NULL if not found.
*/

static char	*search_in_paths(char *cmd, char *path_env)
{
	char	**paths;
	char	*candidate;
	int		i;

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		candidate = build_and_check(paths[i], cmd);
		if (candidate)
		{
			free_paths(paths);
			return (candidate);
		}
		i++;
	}
	free_paths(paths);
	return (NULL);
}

/**
* Looks for the "PATH=" entry inside the envp array,
* and calls search_in_paths to attempt locating the command in those directories.
*/

char	*get_command_path(char *cmd, char *const envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	return (search_in_paths(cmd, envp[i] + 5));
}
