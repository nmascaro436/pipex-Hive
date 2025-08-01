/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:33:19 by nmascaro          #+#    #+#             */
/*   Updated: 2025/08/01 09:58:36 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/**
* Resolves the full executable path of a command.
* Takes the split command arguments and environment variables,
* and determines the absolute path to the executable:
* -If the command is empty, prints error and exits.
* -If the command is direct path, duplicates it.
* -If not, searches for the command in the PATH environment.
* -If the command can't be found, prints error and exits.
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
 * Validates the command input. If it's empty or NULL, handles it
 * accordingly. Splits the command string into list of arguments.
 * Finds the full path to the executable, calls execve with the resolved
 * path, the argument list, and envp. If execve fails, calls function
 * to report the issue and exit with appropiate status code
 */

static void	run_command(char *cmd, char *const envp[])
{
	char	**args;
	char	*path;

	if (!cmd || !cmd[0])
	{
		print_command_error("");
		exit (127);
	}
	args = ft_split(cmd, ' ');
	if (!args)
		logic_error("ft_split");
	path = resolve_path(args, envp);
	execve(path, args, envp);
	handle_execve_error(path, args);
}

/**
* Creates the first child process to run the first command.
* Forks a new process. In the child:
 * - Closes the read end of the pipe (`pipefd[0]`).
 * - Closes the output file descriptor if it is valid (`fds[1]`).
 * - If the input file descriptor (`fds[0]`) is invalid (-1), closes stdin.
 *   Otherwise, duplicates it to stdin and closes the original descriptor.
 * - Redirects stdout to the write end of the pipe (`pipefd[1]`).
 * - Closes the used pipe descriptor after redirection.
 * - Executes the command via `run_command()`.
*/

pid_t	first_child(char *cmd1, int fds[2], int pipefd[2], char *const envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		system_call_error("fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		if (fds[1] != -1)
			close(fds[1]);
		if (fds[0] == -1)
			close(STDIN_FILENO);
		else
		{
			if (dup2(fds[0], STDIN_FILENO) == -1)
				system_call_error("dup2");
			close(fds[0]);
		}
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			system_call_error("dup2");
		close(pipefd[1]);
		run_command(cmd1, envp);
	}
	return (pid);
}

/**
* Creates the second child process to run the second command.
* Forks a new process. In the child:
 * - Closes the write end of the pipe (`pipefd[1]`).
 * - Closes the input file descriptor if it is valid (`fds[0]`).
 * - Redirects stdin to read from the pipe (`pipefd[0]`).
 * - Validates and redirects stdout to the output file descriptor (`fds[1]`).
 * - Closes the used descriptors after redirection.
 * - Executes the command via `run_command()`.
* Returns the PID of the forked child process.
*/

pid_t	second_child(char *cmd2, int fds[2], int pipefd[2], char *const envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		system_call_error("fork");
	if (pid == 0)
	{
		close(pipefd[1]);
		if (fds[0] != -1)
			close(fds[0]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			system_call_error("dup2");
		close(pipefd[0]);
		if (fds[1] == -1)
			exit(EXIT_FAILURE);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			system_call_error("dup2");
		close(fds[1]);
		run_command(cmd2, envp);
	}
	return (pid);
}
