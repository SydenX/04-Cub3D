/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_renew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:19:58 by caymard           #+#    #+#             */
/*   Updated: 2024/06/24 17:18:40 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static t_direction	get_direction(t_rays *rc, t_direction *dir)
{
	if (!rc->side)
	{
		if (rc->ray_dir_x < 0)
			*dir = WEST;
		else
			*dir = EAST;
		return (*dir);
	}
	if (rc->ray_dir_y > 0)
		*dir = SOUTH;
	else
		*dir = NORTH;
	return (*dir);
}

void	update_pixel(t_data *data, int x)
{
	t_direction	dir;
	int			pos_tex_x;
	int			colour;
	double		pos_ver;
	double		step;

	colour = 0;
	get_direction(data->rc, &dir);
	pos_tex_x = (int)(data->rc->wall_x * 64); //64 ==texture_size
	if ((!data->rc->side && data->rc->ray_dir_x < 0)
		|| (data->rc->side == 1 && data->rc->ray_dir_y > 0))
		pos_tex_x = 64 - pos_tex_x - 1;
	step = 1.0 * 64 / data->rc->height;
	pos_ver = (data->rc->start - HEIGHT / 2 + data->rc->height / 2) * step;

	int i = 0;

	while(i < HEIGHT / 2)
	{
		my_mlx_pixel_put(&data->img, x, i, data->c);
		i++;
	}
	while(i < HEIGHT)
	{
		my_mlx_pixel_put(&data->img, x, i, data->f);
		i++;
	}

	// printf("%i, %i\n", data->rc->start, data->rc->end);
	// printf("%i, %i\n", data->rc->start, data->rc->height);
	// while (data->rc->start < data->rc->end) //jamais le cas
	while (data->rc->start > HEIGHT)
	{
		printf("-------------------\n");
		pos_ver += step;
		colour = data->buffer[dir][(64 * ((int)pos_ver & (64 - 1))
				+ pos_tex_x)];
		// if (dir == NORTH || dir == SOUTH) //assombri les mur devant toi
		// 	colour = (colour >> 1) & 0x7F7F7F;
		if (colour > 0)
			my_mlx_pixel_put(&data->img, x, data->rc->start, colour);
		data->rc->start++;
	}
}

void	update_img(t_data *d)
{
	// mlx_clear_window(d->mlx, d->win);
	mlx_destroy_image(d->mlx, d->img.img);
	d->img.img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->mlx)
		close_window(d);
	d->img.addr = mlx_get_data_addr(d->img.img, &d->img.bits_pixel,
			&d->img.length, &d->img.endian);
	return ;
}
