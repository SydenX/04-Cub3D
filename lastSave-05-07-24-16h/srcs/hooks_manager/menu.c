/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:23:57 by caymard           #+#    #+#             */
/*   Updated: 2024/07/04 18:49:42 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void draw_menu(t_data *data)
{
    int	x;
	int	y;

    for (x = 0; x < WIDTH; x++)
        for (y = 0; y < HEIGHT; y++)
            mlx_pixel_put(data->mlx, data->win, x, y, 0x000000);
    for (x = 100; x < 180; x++)
        for (y = 100; y < 150; y++)
            mlx_pixel_put(data->mlx, data->win, x, y, 0x00FF00);
    for (x = 200; x < 280; x++)
        for (y = 100; y < 150; y++)
            mlx_pixel_put(data->mlx, data->win, x, y, 0xAFC2D2);
	for (x = 300; x < 380; x++)
        for (y = 100; y < 150; y++)
            mlx_pixel_put(data->mlx, data->win, x, y, 0xFF0000);
}

int	open_menu(t_data *data)
{
	if (!data->in_menu)
	{
		data->in_menu = 1;
		mlx_mouse_show();
		draw_menu(data);
		return (0);
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_mouse_hide();
	mlx_mouse_move(data->win, (WIDTH / 2), (HEIGHT / 2));
	data->in_menu = 0;
	// map_init(data);
	return (1);
}
