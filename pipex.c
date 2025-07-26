/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:38:23 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/26 12:22:45 by nmascaro         ###   ########.fr       */
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

static int	wait_for_children(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}
/**
 * Entry point of the program.
 * Validates arguments, opens input/output files, creates a pipe,
 * forks two child processes to run the commands, and waits for them.
 * Handles setup and cleanup of all fd and system resources.
 * Reuses 'infile' variable to store exit status, since infile fd
 * is no longer needed.
 */

int	main(int argc, char *argv[], char *const envp[])
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(1);
	}
	infile = open_infile(argv[1]);
	outfile = open_outfile(argv[4]);
	if (pipe(pipefd) == -1)
		system_call_error("pipe");
	pid1 = first_child(argv[2], infile, pipefd, envp);
	pid2 = second_child(argv[3], outfile, pipefd, envp);
	close_fds(infile, outfile, pipefd);
	infile = wait_for_children(pid1, pid2);
	if (outfile == -1)
		exit(EXIT_FAILURE);
	return (infile);
}
