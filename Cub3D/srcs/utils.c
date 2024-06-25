/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:53:57 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/25 09:14:20 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

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

int		get_map_width(t_data *data)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	t_node *list = (data->nodes);
	while (list[i].type != ENDL) {
		if (list[i].type == WALL)
			if (list[i].x > max)
				max = list[i].x;
		i++;
	}
	return (max + 1);
}

int		get_map_height(t_data *data)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	t_node *list = (data->nodes);
	while (list[i].type != ENDL) {
		if (list[i].type == WALL)
			if (list[i].y > max)
				max = list[i].y;
		i++;
	}
	return (max + 1);
}
