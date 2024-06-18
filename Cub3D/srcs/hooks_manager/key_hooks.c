/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:02:55 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/18 13:27:29 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	event_key_pressed(int keycode, t_data *datav)
{
	if ((keycode == KEY_W || keycode == KEY_A
			|| keycode == KEY_D || keycode == KEY_S
			|| keycode == KEY_UP || keycode == KEY_RIGHT
			|| keycode == KEY_LEFT || keycode == KEY_DOWN)
		&& !datav->in_menu)
		key_pressed(keycode, datav);
	else if (keycode == KEY_ESCAPE)
		close_window(datav);
	else if (keycode == KEY_M)
		open_menu(datav);
	return (1);
}

void	key_pressed(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.forwarding = data->player.speed;
	else if (key == KEY_S)
		data->player.backwarding = data->player.speed;
	else if (key == KEY_A)
		data->player.lefting = data->player.speed;
	else if (key == KEY_D)
		data->player.righting = data->player.speed;
	else if (key == KEY_RIGHT)
		data->player.righting_yaw_key = data->player.sensivity;
	else if (key == KEY_LEFT)
		data->player.lefting_yaw_key = data->player.sensivity;
}

int	key_released(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.forwarding = 0;
	else if (key == KEY_S)
		data->player.backwarding = 0;
	else if (key == KEY_A)
		data->player.lefting = 0;
	else if (key == KEY_D)
		data->player.righting = 0;
	else if (key == KEY_RIGHT)
		data->player.righting_yaw_key = 0;
	else if (key == KEY_LEFT)
		data->player.lefting_yaw_key = 0;
	return (0);
}
