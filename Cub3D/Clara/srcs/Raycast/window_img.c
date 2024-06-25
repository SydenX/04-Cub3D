/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:46:36 by caymard           #+#    #+#             */
/*   Updated: 2024/06/24 16:26:41 by caymard          ###   ########.fr       */
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

int	preparing_window(t_data *d, int i)
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
	d->img.addr = mlx_get_data_addr(d->img.img,
			&d->img.bits_pixel, &d->img.length, &d->img.endian);
			(void)i;
	// d->screen = malloc(sizeof(t_pixel) * (HEIGHT + 1)); //calloc pour tout mettre à NULL?
	// if (!d->screen)
	// 	return (strerror(errno), close_window(d));
	// d->screen[HEIGHT] = NULL;
	// while (i < HEIGHT)
	// {
	// 	d->screen[i] = malloc(sizeof(t_pixel) * (WIDTH + 1));
	// 	if (!d->screen)
	// 		return (strerror(errno), close_window(d));
	// 	i++;
	// }
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int colour)
{
	char	*dst;

	if ((x < 0) || (y < 0) || (WIDTH <= x) || (HEIGHT <= y))
		return ;
	dst = img->addr + (y * img->length + x * (img->bits_pixel / 8));
	*(unsigned int *)dst = colour;
}

// static void	draw_line_2(t_pixel a, t_pixel b, t_data *data, t_draw *l)
// {
// 	int	e2;

// 	while (1)
// 	{
// 		my_mlx_pixel_put(&data->img, a.x + data->offset_x,
// 			a.y + data->offset_y, a.colour);
// 		if ((a.x == b.x) && (a.y == b.y))
// 			break ;
// 		e2 = 2 * l->err;
// 		if (-(l->dy) < e2)
// 		{
// 			l->err -= l->dy;
// 			a.x += l->sx;
// 		}
// 		if (e2 < l->dx)
// 		{
// 			l->err += l->dx;
// 			a.y += l->sy;
// 		}
// 	}
// 	return ;
// }

// static void	draw_line(t_pixel a, t_pixel b, t_data *data)
// {
// 	t_draw	line;

// 	line.dx = abs(b.x - a.x);
// 	line.dy = abs(b.y - a.y);
// 	line.sx = -1;
// 	if (a.x < b.x)
// 		line.sx = 1;
// 	line.sy = -1;
// 	if (a.y < b.y)
// 		line.sy = 1;
// 	line.err = line.dx - line.dy;
// 	draw_line_2(a, b, data, &line);
// 	return ;
// }

// void	printing_pixels_on_image(t_data *d)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (i < HEIGHT)
// 	{
// 		j = 0;
// 		while (j < WIDTH)
// 		{
// 			my_mlx_pixel_put(&d->img, (d->screen[i][j].x) + d->offset_x,
// 				(d->screen[i][j].y) + d->offset_y, d->screen[i][j].colour);
// 			if ((j + 1) != WIDTH)
// 				draw_line(d->screen[i][j], d->screen[i][j + 1], d);
// 			if ((i + 1) != HEIGHT)
// 				draw_line(d->screen[i][j], d->screen[i + 1][j], d);
// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_put_image_to_window(d->mlx, d->win, d->img.img, 0, 0);
// }
