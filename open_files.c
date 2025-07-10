/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:54:22 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/10 11:48:53 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/**
* Opens a file for reading.
* Returns file descriptor if successful, -1 if the file
* couldn't be opened and prints error message.
*/
int	open_infile(const char *path)
{
	int	infile_fd;

	infile_fd = open(path, O_RDONLY);
	if (infile_fd < 0)
	{
		print_file_error(path);
		return (-1);
	}
	return (infile_fd);
}

/**
* Opens (or creates) a file for writing.
* If the file exists, its content is cleared (truncated) before writing.
* If a new file is created we give permissions to it:
* owner can read/write, group and others can read only.
* Returns file descriptor if successful, -1 if the file
* couldn't be opened or created and prints error message.
*/
int	open_outfile(const char *path)
{
	int	outfile_fd;

	outfile_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		print_file_error(path);
		return (-1);
	}
	return (outfile_fd);
}
