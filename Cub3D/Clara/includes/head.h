/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:56:19 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/24 18:30:33 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include "keymap.h"
# include "../mlx/mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>

# define WIDTH 960
# define HEIGHT 540
# define HITBOX 35
# define PLAYER_SIZE 5

# define ERROR_INPUTFILE "Unable to read the input file."
# define ERROR_NOTFORMATTED "File is not correctly formatted."
# define ERROR_NOTINTERESTS "Map doesn't contains the interest points needed."
# define ERROR_NOTSURROUNDED "Map must be surrounded by walls."
# define ERROR_DOORNOTPARSED "Doors must be between only 2 walls on the same axis."
# define ERROR_ALLOCATION "Error during allocation."
# define ERROR_ ""

# define FOV (M_PI / 3) // Field of view

typedef enum e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	LAT,
	LONG
}	t_direction;

typedef enum e_doorstate
{
	OPEN,
	CLOSE,
	OPENNING,
	CLOSING
}	t_doorstate;

typedef enum e_type
{
	FLOOR,
	WALL,
	SPAWN,
	DOOR,
	NULLT,
	ENDL,
}	t_type;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_pixel;
	int			length;
	int			endian;
	int			width;
	int			height;
	t_type		type;
	t_direction	direction;
}	t_img;

typedef struct s_pixel
{
	int				y;
	int				x;
	unsigned int	colour;
}	t_pixel;

typedef struct s_node
{
	int				x;
	int				y;

	t_img			img_top;
	t_img			img_floor;
	t_img			img_N;
	t_img			img_E;
	t_img			img_S;
	t_img			img_W;

	t_type			type;

	t_doorstate		door_state;
	int				running_door;
	int				door_loc;

	int				is_free;

	t_direction		direction;
}	t_node;

typedef struct s_player
{
	int			x;
	int			y;
	float		yaw;
	float		pitch;

	int			newx;
	int			newy;

	int			oldx;
	int			oldy;
	int			oldyaw;
	int			oldpitch;

	int			speed;
	int			sensivity;

	int			forwarding;
	int			lefting;
	int			backwarding;
	int			righting;

	int			righting_yaw;
	int			lefting_yaw;
	int			righting_yaw_key;
	int			lefting_yaw_key;

	int			righting_pitch;
	int			lefting_pitch;
}	t_player;

typedef struct s_rays
{
	//which box of the map we're in
	int		map_x;
	int		map_y;

	double	ray_dir_x;
	double	ray_dir_y;
	//length of ray from current position to next x or y-side
	double	side_dist_x;
	double	side_dist_y;
	//length of ray from one x or y-side to next x or y-side
	double	delta_dist_x;
	double	delta_dist_y;

	double	pp_wall_dist;

	char	side;

	int		start;
	int		end;
	int		height;
	double	wall_x;
}	t_rays;

typedef struct s_data
{
	t_node		*nodes;
	t_player	player;

	t_rgb		f_rgb;
	t_rgb		c_rgb;

	int			*mousex;
	int			*mousey;

	int			in_menu;
	int			moves;

	t_rays		*rc;
	t_pixel		*pix;
	void		*mlx;
	void		*win;
	t_img		img;
	// int			**screen;
	int			c;
	int			f;
	int			*buffer[4];
}	t_data;

//MAIN
int		map_init(t_data *data);
int		close_window(t_data *data);
int		open_menu(t_data *data);
//UTILS
void	move_player(t_data *data);
//LINESIZE
int		linesize_checks(char *reader);
//GET_SIZES
int		node_size(char *path);
int		file_chars(char *path);
int		get_fd(char *path, void *toFree, void *toFree2);
//IMAGES_1
t_img	*get_player_image(t_data *data);
t_img	*get_img_at(t_img *list, int x, int y, int isfloor);
//ERROR_1
void	clear(t_data *data, void *toFree, void *toFree2);
void	exit_error(char *error, t_data *data, void *toFree, void *toFree2);
void	error_filedonotexist(void *path, void *toFree2, t_data *data);
void	error_fileerror(void *path, void *toFree2, t_data *data);
void	error_texturefileincorect(void *path, void *toFree2, t_data *data);
//NODE_1
void	check_to_door(t_data *data, int x, int y);
t_node	create_node(char name, int x, int y);
t_node	find_exit_point(t_node *list);
int		update_node(t_node node, t_node *list);
int		is_node_free(float x, float y, t_data *data);
int		toggle_door(t_node *cpy, t_data *data);
//MAP_INIT
int		do_map_checks(int fd, char *reader);
t_node	*read_map(int fd, int fc, char *reader, t_data *data);
void	write_cubes(int color, int startX, int startY, t_data *data, int tailleX, int tailleY);
int	map_loop(t_data *data);
//MAP_SIZE
int	count_map(int fd, int x, char *reader);

// P2 ----------------=----------------=----------------=----------------=----------------=----------------

//PLAYER_MANAGER
t_player	init_player(t_node spawn);

//HOOKS_MANAGER
int		key_released(int key, t_data *data);
void	key_pressed(int key, t_data *data);
int		event_key_pressed(int keycode, t_data *datav);

int 	mouse_hook(int keycode, int x,int y,t_data *data);
void	get_mouse_move(t_data *data);

void	init_hooks(t_data *data);

//NODES_MANAGER
int		get_list_ylen(t_node *list);
int		get_list_xlen(t_node *list);
int		get_list_size(t_node *list);

t_node	*get_node_at(t_node *list, int x, int y);
t_node	find_spawn_point(t_node *list);
int		update_node(t_node node, t_node *list);
int		is_node_free(float x, float y, t_data *data);

void	check_to_door(t_data *data, int x, int y);
int		toggle_door(t_node *cpy, t_data *data);

//MAP_MANAGER
t_node	*check_nodes_type(t_node *nodes, int size);

//UTILS
int		ulimitor(int	tolimit, int limit);
int		limitor(int	tolimit, int limit);



//Clara
int		visual(t_data *data);
void	update_img(t_data *d);
// void	get_pixels(t_data *d);
int		preparing_window(t_data *d, int i);
void	update_pixel(t_data *data, int x);
void	raycast(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int colour);

#endif