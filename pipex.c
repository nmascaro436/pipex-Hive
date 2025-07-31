/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:38:23 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/31 15:38:25 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/**
 * Closes the file descriptors used by the parent process.
 * Closes input file, output file and pipe ends if they are valid.
 * Used after forking to avoid descriptor leaks.
 */

static void	close_fds(int infile, int outfile, int pipefd[2])
{
	if (infile != -1)
		close (infile);
	if (outfile != -1)
		close (outfile);
	close(pipefd[0]);
	close(pipefd[1]);
}
/**
 * Waits for two child processes to end.
 * It retrieves their exit statuses, if the second child
 * terminated normally, its exit status is returned.
 * Otherwise, the function returns 1.
 */

static int	wait_for_children(pid_t pid2)
{
	int		status;
	pid_t	wpid;
	int		exit_status;

	exit_status = 0;
	wpid = waitpid(-1, &status, 0);
	if (wpid == -1)
		system_call_error("waitpid");
	if (wpid == pid2 && WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	wpid = waitpid(-1, &status, 0);
	if (wpid == -1)
		system_call_error("waitpid");
	if (wpid == pid2 && WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}
/**
 * Entry point of the program.
 * Validates arguments, opens input/output files, creates a pipe,
 * forks two child processes to run the commands, and waits for them.
 * Handles setup and cleanup of all fd and system resources.
 * Returns the appropriate exit status.
 */

int	main(int argc, char *argv[], char *const envp[])
{
	int		pipefd[2];
	int		fds[2];
	pid_t	pid1;
	pid_t	pid2;
	int		exit_status;

	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	fds[0] = open_infile(argv[1]);
	fds[1] = open_outfile(argv[4]);
	if (pipe(pipefd) == -1)
		system_call_error("pipe");
	pid1 = first_child(argv[2], fds, pipefd, envp);
	pid2 = second_child(argv[3], fds, pipefd, envp);
	close_fds(fds[0], fds[1], pipefd);
	exit_status = wait_for_children(pid2);
	return (exit_status);
}
