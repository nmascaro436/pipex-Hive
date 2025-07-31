/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:35:51 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/31 13:53:34 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h> //For open() flags like O_RDONLY
# include <stdio.h> //For perror()
# include <stdlib.h> //For exit(), malloc(), free()
# include <sys/wait.h> //For waitpid(), WIFEXITED(), WEXITSTATUS()
# include <unistd.h> //For fork(), pipe(), dup2(), close(), access()

// File operations
int		open_infile(const char *path);
int		open_outfile(const char *path);

// Error handling
void	print_file_error(const char *filename);
void	system_call_error(const char *message);
void	logic_error(const char *message);
void	print_command_error(const char *command);
void	handle_execve_error(char *path, char **args);

// Process management 
pid_t	first_child(char *cmd1, int fds[2], int pipefd[2], char *const envp[]);
pid_t	second_child(char *cmd2, int fds[2], int pipefd[2], char *const envp[]);

// Command path resolution
char	*get_command_path(char *cmd, char *const envp[]);
int		is_cmd_path(char *cmd);
void	free_paths(char **paths);

#endif
