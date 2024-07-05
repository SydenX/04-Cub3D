/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:53:57 by jtollena          #+#    #+#             */
/*   Updated: 2024/07/04 15:19:01 by caymard          ###   ########.fr       */
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

// unsigned long rgb_to_hex(t_rgb rgb)
// {   
//     return ((rgb.r & 0xff) << 16) + ((rgb.g & 0xff) << 8) + (rgb.b & 0xff);
// }

void	rgb_to_int(t_data *data)
{
	data->f = (data->f_rgb.r << 16) + (data->f_rgb.g << 8) + data->f_rgb.b;
	data->c = (data->c_rgb.r << 16) + (data->c_rgb.g << 8) + data->c_rgb.b;
}
