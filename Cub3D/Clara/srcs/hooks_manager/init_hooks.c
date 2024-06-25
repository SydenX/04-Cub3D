/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:05:06 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/21 16:55:12 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	init_hooks(t_data *data)
{
	mlx_mouse_hide();
	mlx_do_key_autorepeaton(data->mlx);
	mlx_mouse_move(data->win, (WIDTH / 2), (HEIGHT / 2));
	mlx_hook(data->win, 2, 0, &event_key_pressed, (data));
	mlx_hook(data->win, 3, 0, &key_released, (data));
	mlx_hook(data->win, 17, 0, &close_window, (data));
	mlx_mouse_hook(data->win, &mouse_hook, (data));
	map_init(data);
	mlx_loop_hook(data->mlx, &map_loop, data);
	mlx_loop(data->mlx);
}
