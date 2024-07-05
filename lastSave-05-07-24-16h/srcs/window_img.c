/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:46:36 by caymard           #+#    #+#             */
/*   Updated: 2024/07/04 15:58:05 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	close_window(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	free(data->mlx);
	clear(data, NULL, NULL);
	write(1, "cub3D has been successfully closed.\n", 36);
	// system("leaks cub3d");
	exit(0);
}

int	preparing_window(t_data *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		return (strerror(errno), close_window(d));
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "cub3D");
	if (!d->win)
		return (strerror(errno), close_window(d));
	d->img.img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->img.img)
		return (strerror(errno), close_window(d));
	d->img.addr = (int *)mlx_get_data_addr(d->img.img,
			&d->img.bits_pixel, &d->img.length, &d->img.endian);
	return (0);
}

void	update_img(t_data *d)
{
	mlx_clear_window(d->mlx, d->win);
	mlx_destroy_image(d->mlx, d->img.img);
	d->img.img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->mlx)
		close_window(d);
	d->img.addr = (int *)mlx_get_data_addr(d->img.img, &d->img.bits_pixel,
			&d->img.length, &d->img.endian);
	return ;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int colour)
{
	char	*dst;

	if ((x < 0) || (y < 0) || (WIDTH <= x) || (HEIGHT <= y))
		return ;
	dst = (char *)img->addr + (y * img->length + x * (img->bits_pixel / 8));
	*(unsigned int *)dst = colour;
}

// int	visual(t_data *data)
// {
// 	// char	*moves;

// 	move_player(data);
// 	update_img(data);
// 	raycast(data);
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
// 	// moves = get_moves(ft_itoa(data->moves++));
// 	// mlx_string_put(data->mlx, data->win, 15, 15, 0xFFFFFF, moves);
//     // mlx_pixel_put(data->mlx, data->win, data->playerx, data->playery, 0xFFFFFF);
// 	// free(moves);
// 	return (0); //int necessaire pour mlx_loop_hook
// }
