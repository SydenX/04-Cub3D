/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_vecteurs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:25:17 by caymard           #+#    #+#             */
/*   Updated: 2024/06/24 18:57:30 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

// static int	init_ray(t_data *data, int x) //pense aue pb est pcq angle et pas vecteur
// {
// 	double	angle;

// 	angle = data->player.yaw + (x - WIDTH / 2.0) * (FOV / WIDTH);
// 	data->rc->ray_dir_x = cos(angle); // change quand player move
// 	data->rc->ray_dir_y = sin(angle);
// 	data->rc->map_x = data->player.x;
// 	data->rc->map_y = data->player.y;
// 	data->rc->delta_dist_x = fabs(1 / data->rc->ray_dir_x);
// 	data->rc->delta_dist_y = fabs(1 / data->rc->ray_dir_y);
// 	return (0);
// }


typedef struct s_vector
{
	double x;
	double y;
} t_vector;

// Addition de vecteurs
t_vector vector_add(t_vector v1, t_vector v2)
{
	return (t_vector){v1.x + v2.x, v1.y + v2.y};
}

// Soustraction de vecteurs
t_vector vector_sub(t_vector v1, t_vector v2)
{
	return (t_vector){v1.x - v2.x, v1.y - v2.y};
}

// Multiplication d'un vecteur par un scalaire
t_vector vector_scale(t_vector v, double scalar)
{
	return (t_vector){v.x * scalar, v.y * scalar};
}

// Calcul de la norme d'un vecteur
double vector_magnitude(t_vector v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

// Normalisation d'un vecteur
t_vector vector_normalize(t_vector v)
{
	double mag = vector_magnitude(v);
	return vector_scale(v, 1 / mag);
}

static int init_ray(t_data *data, int x)
{
	t_vector dir = {cos(data->player.yaw), sin(data->player.yaw)};
	t_vector plane = {-dir.y, dir.x}; // Perpendiculaire à dir

	double camera_x = 2 * x / (double)WIDTH - 1;
	data->rc->ray_dir = (t_vector){dir.x + plane.x * camera_x, dir.y + plane.y * camera_x};

	data->rc->map_pos = (t_vector){data->player.x, data->player.y};
	data->rc->delta_dist = (t_vector){fabs(1 / data->rc->ray_dir.x), fabs(1 / data->rc->ray_dir.y)};
	return 0;
}

static void get_step_sidedist(t_data *data, t_vector *step)
{
	if (data->rc->ray_dir.x < 0)
	{
		step->x = -1;
		data->rc->side_dist.x = (data->player.x - data->rc->map_pos.x) * data->rc->delta_dist.x;
	}
	else
	{
		step->x = 1;
		data->rc->side_dist.x = (data->rc->map_pos.x + 1.0 - data->player.x) * data->rc->delta_dist.x;
	}

	if (data->rc->ray_dir.y < 0)
	{
		step->y = -1;
		data->rc->side_dist.y = (data->player.y - data->rc->map_pos.y) * data->rc->delta_dist.y;
	}
	else
	{
		step->y = 1;
		data->rc->side_dist.y = (data->rc->map_pos.y + 1.0 - data->player.y) * data->rc->delta_dist.y;
	}
}

static void dda(t_data *data, t_vector step)
{
	while (data->nodes->type != WALL)
	{
		if (data->rc->side_dist.x < data->rc->side_dist.y) {
			data->rc->side_dist.x += data->rc->delta_dist.x;
			data->rc->map_pos.x += step.x;
			data->rc->side = 0;
		}
		else
		{
			data->rc->side_dist.y += data->rc->delta_dist.y;
			data->rc->map_pos.y += step.y;
			data->rc->side = 1;
		}
		data->nodes++;
	}
}

static void get_x_hit_wall(t_rays *rc, t_vector player_position)
{
	// Calcul de la hauteur du mur à dessiner
	rc->height = (int)(HEIGHT / rc->pp_wall_dist);

	// Calcul du point de départ pour le dessin du mur sur l'écran
	rc->start = -(rc->height / 2) + (HEIGHT / 2);
	if (rc->start < 0)
        rc->start = 0;
	if (rc->start > HEIGHT)
        rc->start = HEIGHT;

	// Calcul du point de fin pour le dessin du mur sur l'écran
	rc->end = (rc->height / 2) + (HEIGHT / 2);
	if (rc->end >= HEIGHT)
        rc->end = HEIGHT - 1;
	if (rc->end < 0)
        rc->end = 0;

	// Calcul de la position X sur le mur pour le texturage
	if (!rc->side)
		rc->wall_x = player_position.y + rc->pp_wall_dist * rc->ray_dir.y;
	else
		rc->wall_x = player_position.x + rc->pp_wall_dist * rc->ray_dir.x;

	// On rend plus précis la position X sur le mur
	rc->wall_x = rc->wall_x - floor(rc->wall_x);
}

void raycast(t_data *data)
{
	t_vector step;
	int x = 0;
	while (x < WIDTH)
	{
		init_ray(data, x);
		get_step_sidedist(data, &step);
		dda(data, step);
		if (data->rc->side == 0)
			data->rc->pp_wall_dist = (data->rc->map_pos.x - data->player.x
					+ (1 - step.x) / 2) / data->rc->ray_dir.x;
		else
			data->rc->pp_wall_dist = (data->rc->map_pos.y - data->player.y
					+ (1 - step.y) / 2) / data->rc->ray_dir.y;

		// printf("pp_wall_dist: .%f.\n", data->rc->pp_wall_dist);
		get_x_hit_wall(data->rc, (t_vector){data->player.x, data->player.y});
		update_pixel(data, x);
		x++;
	}
}
