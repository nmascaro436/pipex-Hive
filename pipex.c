/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:38:23 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/20 11:04:24 by nmascaro         ###   ########.fr       */
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
 * Entry point of the program.
 * Validates arguments, opens input/output files, creates a pipe,
 * forks two child processes to run the commands, and waits for them.
 * Handles setup and cleanup of all fd and system resources.
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
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
