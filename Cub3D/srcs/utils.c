/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:53:57 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/18 14:26:33 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	exit_win(char *msg, t_data *data, char *prefix)
{
	ft_printf("%s\n%s\nNumber of moves: %d\n", prefix, msg, data->moves + 1);
}

int	absolute(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

int		limitor(int	tolimit, int limit)
{
	if (limit >= 0)
	{
		if (tolimit > limit)
			return limit;
		else
			return tolimit;
	}
	if (tolimit < limit)
		return limit;
	else
		return tolimit;
}

int		ulimitor(int	tolimit, int limit)
{
	if (limit >= 0)
	{
		if (tolimit < limit)
			return limit;
		else
			return tolimit;
	}
	if (tolimit > limit)
		return limit;
	else
		return tolimit;
}