/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sizes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:12:20 by jetol             #+#    #+#             */
/*   Updated: 2024/04/17 18:09:40 by jtollena         ###   ########.fr       */
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
		error_inputfile(NULL, NULL);
	while (readable > 0)
	{
		readable = read(fd, reader, 1);
		if (readable == -1)
			error_inputfile(NULL, NULL);
		if (reader[0] == '1' || reader[0] == '0' || reader[0] == 'P'
			|| reader[0] == 'E' || reader[0] == 'C')
			wc++;
		else if (reader[0] != '\n' && reader[0] != 0 && reader[0] != ' ')
			error_notformatted(NULL, NULL);
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
		error_inputfile(NULL, NULL);
	while (readable > 0)
	{
		readable = read(fd, reader, 1);
		if (readable == -1)
			error_inputfile(NULL, NULL);
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
		error_inputfile(toFree, toFree2);
	return (fd);
}
