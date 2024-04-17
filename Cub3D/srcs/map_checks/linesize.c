/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linesize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:56:10 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/17 17:57:26 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	linesize_checks(char *reader)
{
	return 1;
	int	i;
	int	fline;
	int	newline;

	i = 0;
	fline = 0;
	while (reader[i] != '\n')
	{
		fline++;
		if (reader[++i] == 0)
			exit_error("Map format is not correct.", NULL, NULL, NULL);
	}
	while (reader[i] != 0)
	{
		i++;
		newline = 0;
		while (reader[i] != '\n' && reader[i] != 0)
		{
			newline++;
			i++;
		}
		if (newline != fline)
			exit_error("Map lines are not at same size.", NULL, NULL, NULL);
	}
	return (1);
}
