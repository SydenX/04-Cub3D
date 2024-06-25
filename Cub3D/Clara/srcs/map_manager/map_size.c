/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:35:02 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/24 16:33:38 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	check_infos_size_condition(char *reader, int *i, int *fc, int *not)
{
	if ((reader[*i] == 'N' && reader[*i + 1] == 'O')
		|| (reader[*i] == 'E' && reader[*i + 1] == 'A')
		|| (reader[*i] == 'S' && reader[*i + 1] == 'O')
		|| (reader[*i] == 'W' && reader[*i + 1] == 'E')
		|| (reader[*i] == 'F') || (reader[*i] == 'C'))
	{
		if ((reader[*i] == 'F') || (reader[*i] == 'C'))
			*fc += 1;
		else
			*not += 1;
	}
	else
		return (0);
	return (1);
}

int	check_infos_size(char *reader, int i)
{
	int	numberoftextures;
	int	fc;

	numberoftextures = 0;
	fc = 0;
	while (reader[++i])
	{
		while (reader[i] == '\n' || reader[i] == ' '
			|| (reader[i] >= 9 && reader[i] < 13))
			i++;
		if (!reader[i])
			return (0);
		if (!check_infos_size_condition(reader, &i, &fc, &numberoftextures))
			return (0);
		while (reader[i] != '\n')
			if (reader[i++] == 0)
				return (0);
		if (numberoftextures == 4 && fc == 2)
			break ;
	}
	while (reader[i] == '\n')
		i++;
	if (reader[i] == 0)
		return (0);
	return (i - 1);
}

int	count_map_loop(int i, char *reader, int j, int y)
{
	while (reader[++i])
	{
		if (reader[i] != '\n')
			j++;
		else
		{
			y++;
		}
	}
	return (j);
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
		return (0);
	close(fd);
	i = check_infos_size(reader, i);
	j = count_map_loop(i, reader, j, y);
	j++;
	return (j);
}
