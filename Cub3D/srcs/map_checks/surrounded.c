/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrounded.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:32:00 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/17 18:12:10 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	error_surrounded_by_walls(void *toFree, void *toFree2)
{
	exit_error("Map must be surrounded by walls.", NULL, toFree, toFree2);
}

int	surr_check_firstline(char *reader)
{
	int	i;
	int	line;

	i = 0;
	line = 0;

	
	return 1;
	while (reader[i])
	{
		if (reader[i] == '\n')
		{
			if ((reader[i + 1] != '1' && reader[i + 1] != ' ') || (reader[i - 1] != '1' && reader[i - 1] != ' '))
				error_surrounded_by_walls((void *)reader, NULL);
			line++;
		}
		else if (reader[i] == 0)
			break ;
		else if (line == 0 && (reader[i] != '1' && reader[i] != ' '))
			error_surrounded_by_walls((void *)reader, NULL);
		if (reader[i] == ' ' && (reader[i - 1] == '0'))
			error_surrounded_by_walls((void *)reader, NULL);
		if (reader[i] == ' ' && (reader[i + 1] == '0'))
			error_surrounded_by_walls((void *)reader, NULL);
		i++;
	}
	return (1);
}

int	surr_checks(char *reader)
{
	int	i;
	int	line;

	i = ft_strlen(reader) - 1;
	line = 0;
	while (reader[i])
	{
		if (reader[i] == '\n')
		{
			if ((reader[i + 1] != '1' && reader[i + 1] != ' ') || (reader[i - 1] != '1' && reader[i - 1] != ' '))
				error_surrounded_by_walls((void *)reader, NULL);
			line++;
		}
		else if (line == 0)
		{
			if ((reader[i - 1] != '1' && reader[i - 1] != ' '))
				error_surrounded_by_walls((void *)reader, NULL);
			line++;
		}
		else if (reader[i] == 0)
			break ;
		if (reader[i] == ' ' && (reader[i - 1] == '0'))
			error_surrounded_by_walls((void *)reader, NULL);
		if (reader[i] == ' ' && (reader[i + 1] == '0'))
			error_surrounded_by_walls((void *)reader, NULL);
		i--;
	}
	return (surr_check_firstline(reader));
}
