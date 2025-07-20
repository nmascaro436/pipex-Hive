/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:04:23 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/20 10:20:05 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_file_error(const char *filename)
{
	write(2, "pipex: ", 7);
	if (filename && filename[0])
		write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	perror(NULL);
}

void	system_call_error(const char *message)
{
	write(2, "pipex: ", 7);
	perror(message);
	exit(EXIT_FAILURE);
}
void	logic_error(const char *message)
{
	write(2, "pipex: ", 7);
	write(2, message, ft_strlen(message));
	write(2, ": internal error\n", 17);
	exit(EXIT_FAILURE);
}
void	print_command_error(const char *command)
{
	write(2, "pipex: ", 7);
	if (command && command[0])
		write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 20);
}
