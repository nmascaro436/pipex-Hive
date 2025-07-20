/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:33:19 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/20 10:06:45 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/**
* Splits the command string into arguments, 
* resolves the command path using the environment variable PATH
* (unless it already is) and executes it using execve.
* If anything fails, appropriate error handling is performed.
*/
static char	*resolve_path(char **args, char *const envp[])
{
	char	*path;
	
	if (!args[0] || !args[0][0])
	{
		print_command_error("");
		free_paths(args);
		exit(127);
	}
	if (is_cmd_path(args[0]))
		path = ft_strdup(args[0]);
	else
		path = get_command_path(args[0], envp);
	if (!path)
	{
		print_command_error(args[0]);
		free_paths(args);
		exit(127);
	}
	return (path);
}
/**
 * 
 */
static void	run_command(char *cmd, char *const envp[])
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		logic_error("ft_split");
	path = resolve_path(args, envp);
	execve(path, args, envp);
	free(path);
	free_paths(args);
	system_call_error("execve");
}

/**
* Creates the first child process to run the first command.
* Sets up redirection from infile to the command's stdin and pipe to stdout,
* then executes the command.
* Returns the PID of the forked child process.
*/

pid_t	first_child(char *cmd1, int infile, int pipefd[2], char *const envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		system_call_error("fork");
	if (pid == 0)
	{
		if (infile != -1)
		{
			if (dup2(infile, STDIN_FILENO) == -1)
				system_call_error("dup2");
		}
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			system_call_error("dup2");
		close(pipefd[0]);
		close(pipefd[1]);
		if (infile != -1)
			close(infile);
		run_command(cmd1, envp);
	}
	return (pid);
}

/**
* Creates the second child process to run the second command.
* Sets up redirection from pipe to stdin and outfile to stdout,
* then executes the command.
* Returns the PID of the forked child process. 
*/

pid_t	second_child(char *cmd2, int outfile, int pipefd[2], char *const envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		system_call_error("fork");
	if (pid == 0)
	{
		if(dup2(pipefd[0], STDIN_FILENO) == -1)
			system_call_error("dup2");
		if (outfile != -1)
		{
			if(dup2(outfile, STDOUT_FILENO) == -1)
				system_call_error("dup2");
		}
		close(pipefd[1]);
		close(pipefd[0]);
		if (outfile != -1)
			close(outfile);
		run_command(cmd2, envp);
	}
	return (pid);
}
