/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:05:06 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/20 15:42:30 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	init_hooks(t_data *data)
{
	mlx_mouse_hide();
	// mlx_do_key_autorepeatoff(data->prog->mlx);
	mlx_mouse_move(data->prog->win, (WIDTH / 2), (HEIGHT / 2));
	mlx_hook((*data).prog->win, 2, 0, &event_key_pressed, (data));
	mlx_hook((*data).prog->win, 3, 0, &key_released, (data));
	mlx_hook((*data).prog->win, 6, 0, &mouse_hook, (data));
	mlx_hook((*data).prog->win, 17, 0, &close_window, (data));
	map_init(data);
	mlx_loop_hook(data->prog->mlx, &map_loop, data);
	mlx_loop((*data).prog->mlx);
}
