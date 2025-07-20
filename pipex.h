/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:35:51 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/20 09:19:39 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int		open_infile(const char *path);
int		open_outfile(const char *path);
void	print_file_error(const char *filename);
void	system_call_error(const char *message);
void	logic_error(const char *message);
void	print_command_error(const char *command);
pid_t	first_child(char *cmd1, int infile, int pipefd[2], char *const envp[]);
pid_t	second_child(char *cmd2, int outfile, int pipefd[2],
			char *const envp[]);
char	*get_command_path(char *cmd, char *const envp[]);
int		is_cmd_path(char *cmd);
void	free_paths(char **paths);

#endif
