/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:04:23 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/31 15:50:44 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/**
 * Prints and error message for a file-related failure.
 * Outputs "pipex: <filename>: <system error message>".
 * Uses perror to include the errno-based description.
 */

void	print_file_error(const char *filename)
{
	write(2, "pipex: ", 7);
	if (filename && filename[0])
		write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	perror(NULL);
}
/**
 * Prints a system call error and exits the program.
 * Outputs "pipex: <message>: <system error>" using perror,
 * then exits with EXIT_FAILURE.
 */

void	system_call_error(const char *message)
{
	write(2, "pipex: ", 7);
	perror(message);
	exit(EXIT_FAILURE);
}
/**
 * Handles internal logic errors in the program.
 * Outputs "pipex: <message>: internal error"
 * and exits the program.
 */

void	logic_error(const char *message)
{
	write(2, "pipex: ", 7);
	write(2, message, ft_strlen(message));
	write(2, ": internal error\n", 17);
	exit(EXIT_FAILURE);
}
/**
 * Prints a "command not found" error to stderr.
 * If command is NULL or empty, only the standard error
 * format is printed.
 */

void	print_command_error(const char *command)
{
	write(2, "pipex: ", 7);
	if (command && command[0])
		write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 20);
}
/**
 * Checks if a given command path exists and is executable.
 * If the file doesn't exist, it prints custom file error,
 * frees allocated memory and exits with status 127 (command not found).
 * If the file exists but not executable, it frees memory, prints error
 * and exits with status 126 (command found but not executable).
 * If execve still failed, it handles the generic execve system call error.
 */

void	handle_execve_error(char *path, char **args)
{
	if (access(path, F_OK) != 0)
	{
		print_file_error(args[0]);
		free(path);
		free_paths(args);
		exit(127);
	}
	else if (access(path, X_OK) != 0)
	{
		free(path);
		free_paths(args);
		perror("Permission denied");
		exit(126);
	}
	else
	{
		free(path);
		free_paths(args);
		system_call_error("execve");
	}
}
