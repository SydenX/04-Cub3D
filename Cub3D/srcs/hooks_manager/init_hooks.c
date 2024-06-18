/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:05:06 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/18 12:05:25 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	init_hooks(t_data *data)
{
	mlx_mouse_hide();
	mlx_do_key_autorepeaton((*data).prog->mlx);
	mlx_mouse_move(data->prog->win, (SIZE * 10 / 2), (SIZE * 10 / 2));
	mlx_hook((*data).prog->win, 2, 0, &event_key_pressed, (data));
	mlx_hook((*data).prog->win, 3, 0, &key_released, (data));
	mlx_hook((*data).prog->win, 17, 0, &close_window, (data));
	mlx_mouse_hook((*data).prog->win, &mouse_hook, (data));
	mlx_loop_hook(data->prog->mlx, map_init, data);
	mlx_loop((*data).prog->mlx);
}
