/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:25:17 by caymard           #+#    #+#             */
/*   Updated: 2024/06/24 18:40:41 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static int	init_ray(t_data *data, int x) //pense aue pb est pcq angle et pas vecteur
{
	double	angle;

	angle = data->player.yaw + (x - WIDTH / 2.0) * (FOV / WIDTH);
	data->rc->ray_dir_x = cos(angle); // change quand player move
	data->rc->ray_dir_y = sin(angle);
	data->rc->map_x = data->player.x;
	data->rc->map_y = data->player.y;
	data->rc->delta_dist_x = fabs(1 / data->rc->ray_dir_x);
	data->rc->delta_dist_y = fabs(1 / data->rc->ray_dir_y);
	return (0);
}



static void	get_step_sidedist(t_data *data, int *stepx, int *stepy)
{
	if (data->rc->ray_dir_x < 0)
	{
		*stepx = -1;
		data->rc->side_dist_x = (data->player.x - data->rc->map_x)
			* fabs(1 / data->rc->ray_dir_x);
	}
	else
	{
		*stepx = 1;
		data->rc->side_dist_x = (data->rc->map_x + 1.0 - data->player.x)
			* fabs(1 / data->rc->ray_dir_x);
	}
	if (data->rc->ray_dir_y < 0)
	{
		*stepy = -1;
		data->rc->side_dist_y = (data->player.y - data->rc->map_y)
			* fabs(1 / data->rc->ray_dir_y);
	}
	else
	{
		*stepy = 1;
		data->rc->side_dist_y = (data->rc->map_y + 1.0 - data->player.y)
			* fabs(1 / data->rc->ray_dir_y);
	}
}

static void	dda(t_data *data, int step_x, int step_y)
{
	while (data->nodes->type != WALL)
	{
		// Avancer le rayon vers le côté le plus proche
		if (data->rc->side_dist_x < data->rc->side_dist_y)
		{
			data->rc->side_dist_x += data->rc->delta_dist_x;
			data->rc->map_x += step_x;
			data->rc->side = 0; // 0 for a wall x
		}
		else
		{
			data->rc->side_dist_y += data->rc->delta_dist_y;
			data->rc->map_y += step_y;
			data->rc->side = 1; // 0 for a wall y
		}
		data->nodes++;
	}
	if (!data->rc->side)
		data->rc->pp_wall_dist = (data->rc->map_x - data->player.x
				+ (1 - step_x) / 2) / data->rc->ray_dir_x;
	else
		data->rc->pp_wall_dist = (data->rc->map_y - data->player.y
				+ (1 - step_y) / 2) / data->rc->ray_dir_y;
}

static void	get_x_hit_wall(t_rays *rc, t_player player)
{
	// Calcul de la hauteur du mur à dessiner
	rc->height = (int)(HEIGHT / rc->pp_wall_dist);

	// Calcul du point de départ pour le dessin du mur sur l'écran //540->270
	rc->start = -(rc->height / 2) + (HEIGHT / 2);
	if (rc->start < 0)
		rc->start = 0;
	if (rc->start > HEIGHT)
		rc->start = HEIGHT;

	// Calcul du point de fin pour le dessin du mur sur l'écran //270->0
	rc->end = (rc->height / 2) + (HEIGHT / 2);
	if (rc->end >= HEIGHT)
		rc->end = HEIGHT - 1;
	if (rc->end < 0)
		rc->end = 0;

	// Calcul de la position X sur le mur pour le texturage
	if (!rc->side)
		rc->wall_x = player.y + rc->pp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = player.x + rc->pp_wall_dist * rc->ray_dir_x;
	// On rend plus precis la position X sur le mur
	if (rc->wall_x >= 0)
		rc->wall_x -= (int)rc->wall_x;
	else
		rc->wall_x -= (int)rc->wall_x - rc->wall_x - 1;
}

void	raycast(t_data *data)
{
	int		stepx;
	int		stepy;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, x);
		get_step_sidedist(data, &stepx, &stepy);
		dda(data, stepx, stepy);
		// printf("pp_wall_dist: .%f.\n", data->rc->pp_wall_dist);
		get_x_hit_wall(data->rc, data->player);
		update_pixel(data, x);
		x++;
	}
}
