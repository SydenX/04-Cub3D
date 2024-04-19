/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:35:02 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/19 13:46:20 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	check_infos_size(char *reader, int i)
{
	int numberoftextures;
	int fc;

	numberoftextures = 0;
	fc = 0;
	while (reader[++i])
	{
		while (reader[i] == '\n' || reader[i] == ' '
			|| (reader[i] >= 9 && reader[i] < 13))
			i++;
		if (!reader[i])
			return 0;
		if ((reader[i] == 'N' && reader[i + 1] == 'O')
			|| (reader[i] == 'E' && reader[i + 1] == 'A')
			|| (reader[i] == 'S' && reader[i + 1] == 'O')
			|| (reader[i] == 'W' && reader[i + 1] == 'E')
			|| (reader[i] == 'F') || (reader[i] == 'C'))
		{
			if ((reader[i] == 'F') || (reader[i] == 'C'))
				fc += 1;
			else
				numberoftextures += 1;
		}
		else
			return 0;
		while (reader[i] != '\n')
			if (reader[i++] == 0)
				return 0;
		if (numberoftextures == 4 && fc == 2)
			break ;
	}
	while (reader[i++] == '\n')
	{
	}
	if (reader[i] == 0)
		return 0;
	return (i - 1);
}

int	count_map(int fd, int x, char *reader)
{
	int		readable;
	int		i;
	int		j;
	int		y;

	readable = 1;
	i = -1;
	j = 0;
	y = 0;
	readable = read(fd, reader, x);
	if (readable == -1)
		return 0;
	close(fd);
	i = check_infos_size(reader, i);
	x = 0;
	while (reader[++i])
	{
		if (reader[i] != '\n')
			j++;
		else
		{
			y++;
			x = 0;
		}
	}
	j++;
	return (j);
}
