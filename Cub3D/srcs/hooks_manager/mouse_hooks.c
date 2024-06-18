/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:04:36 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/18 12:10:27 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int mouse_hook(int keycode, int x,int y,t_data *data)
{
	if (keycode == 1)
	{
		if (x > 100 && x < 180 && y > 100 && y < 150)
			data->player.sensivity--;
		else if (x > 200 && x < 280 && y > 100 && y < 150)
			data->player.sensivity++;
	}
	return 0;
}

void	get_mouse_move(t_data *data)
{
	int	deadangle = 15;

	mlx_mouse_get_pos(data->prog->win, (data->mousex), (data->mousey));
	if ((*data->mousex) > (SIZE * 10 / 2) + deadangle)
	{
		data->player.righting_yaw = (limitor(*data->mousex, SIZE * 10) - (SIZE * 10 / 2)) / data->player.sensivity;
		data->player.lefting_yaw = 0;
	}
	else if ((*data->mousex) < (SIZE * 10 / 2) - deadangle)
	{
		data->player.lefting_yaw = ((-1 * (limitor(*data->mousex, - (SIZE * 10)) - (SIZE * 10 / 2)))) / data->player.sensivity;
		data->player.righting_yaw = 0;
	}
	else if ((*data->mousex) >= (SIZE * 10 / 2) - deadangle && (*data->mousex) <= (SIZE * 10 / 2) + deadangle)
	{
		data->player.righting_yaw = 0;
		data->player.lefting_yaw = 0;
	}
	mlx_mouse_move(data->prog->win, (SIZE * 10 / 2), (SIZE * 10 / 2));
}
