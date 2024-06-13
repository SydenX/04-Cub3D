/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sizes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:12:20 by jetol             #+#    #+#             */
/*   Updated: 2024/06/13 13:03:45 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	node_size(char *path)
{
	char	reader[1];
	int		readable;
	int		fd;
	int		wc;

	wc = 0;
	readable = 1;
	fd = open(path, O_RDONLY, 0);
	if (fd <= 0)
		error_inputfile(NULL, NULL, NULL);
	while (readable > 0)
	{
		readable = read(fd, reader, 1);
		if (readable == -1)
			error_inputfile(NULL, NULL, NULL);
		if (reader[0] == '1' || reader[0] == '0' || reader[0] == 'N' || reader[0] == 'D'
			|| reader[0] == 'E' || reader[0] == 'S' || reader[0] == 'W' || reader[0] == ' ')
			wc++;
		// else if (reader[0] != '\n' && reader[0] != 0)
		// 	error_notformatted(NULL, NULL);
	}
	close(fd);
	return (wc + 1);
}

int	ext_match(const char *name)
{
	size_t	nl;
	size_t	el;

	nl = ft_strlen(name);
	el = ft_strlen(".cub");
	return (nl >= el && !strcmp(name + nl - el, ".cub"));
}

int	file_chars(char *path)
{
	char	reader[1];
	int		readable;
	int		fd;
	int		wc;

	if (ext_match(path) == 0)
		exit_error("File is not '.cub' type.", NULL, NULL, NULL);
	wc = 0;
	readable = 1;
	fd = open(path, O_RDONLY, 0);
	if (fd <= 0)
		error_inputfile(NULL, NULL, NULL);
	while (readable > 0)
	{
		readable = read(fd, reader, 1);
		if (readable == -1)
			error_inputfile(NULL, NULL, NULL);
		wc++;
	}
	close(fd);
	return (wc);
}

int	get_fd(char *path, void *toFree, void *toFree2)
{
	int	fd;

	fd = open(path, O_RDONLY, 0);
	if (fd <= 0)
		error_inputfile(toFree, toFree2, NULL);
	return (fd);
}
