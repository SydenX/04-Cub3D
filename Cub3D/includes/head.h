/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:56:19 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/17 14:28:31 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include "keymap.h"
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
#include <stdio.h>
#include <errno.h>

# define SIZE 100
# define HITBOX 35
# define PLAYER_SIZE 5

typedef enum e_direction {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	LAT,
	LONG
}	t_direction;

typedef enum e_doorstate {
	OPEN,
	CLOSE,
	OPENNING,
	CLOSING
}	t_doorstate;

typedef enum e_type {
	FLOOR,
	WALL,
	SPAWN,
	DOOR,
	NULLT,
	ENDL,
}	t_type;

typedef struct s_prog {
	void	*mlx;
	void	*win;
}	t_prog;

typedef struct s_rgb {
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_img {
	void			*img;
	t_type			type;
	t_direction		direction;
}	t_img;

typedef struct s_node {
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

typedef struct s_player {
	int 		x;
	int			y;
	float 		yaw;
	float		pitch;
	int			newx;
	int			newy;
	int			speed;
	int			sensivity;
	int			forwarding;
	int			lefting;
	int			backwarding;
	int			righting;
	int			righting_yaw;
	int			lefting_yaw;
	int			righting_pitch;
	int			lefting_pitch;
}	t_player;

typedef struct s_data {
	t_prog		*prog;
	t_node		*nodes;
	t_player	player;
	void		*txt_path_north;
	void		*txt_path_east;
	void		*txt_path_south;
	void		*txt_path_west;
	int			*mousex;
	int			*mousey;
	t_rgb		f;
	t_rgb		c;
	int			moves;
}	t_data;

//MAIN
int		map_init(t_data *data);
int		close_window(t_data *data);
//UTILS
int		collectibles_left(t_img *list);
void	exit_win(char *msg, t_data *data, char *prefix);
int		absolute(int i);
void	move_player(t_data *data);
// int		event_key_pressed(int keycode, t_data *data);
//NODESTYPE
t_node	*check_nodes_type(t_node *nodes, int size);
//LINESIZE
int		linesize_checks(char *reader);
//GET_SIZES
int		node_size(char *path);
int		file_chars(char *path);
int		get_fd(char *path, void *toFree, void *toFree2);
//IMAGES_1
t_img	*get_player_image(t_data *data);
t_img	*get_img_at(t_img *list, int x, int y, int isfloor);
t_img	create_image(int x, int y, t_type type, t_prog *prog);
t_img	*load_images(t_img *imgs, t_node *list, t_prog *prog);
void	*get_image(t_prog *prog, t_type type);
//ERROR_1
void	clear(t_data *data, void *toFree, void *toFree2);
void	exit_error(char *error, t_data *data, void *toFree, void *toFree2);
void	error_notcorrectinterest(void *toFree, void *toFree2, t_data *data);
void	error_nopathfound(void *toFree, void *toFree2, t_data *data);
void	error_inputfile(void *toFree, void *toFree2, t_data *data);
void	error_notformatted(void *toFree, void *toFree2, t_data *data);
void	error_notsurrounded(void *toFree, void *toFree2, t_data *data);
void	error_doornotparsedcorrectly(void *toFree, void *toFree2, t_data *data);
void	error_allocation(void *toFree, void *toFree2, t_data *data);
void	error_filedonotexist(void *path, void *toFree2, t_data *data);
void	error_fileerror(void *path, void *toFree2, t_data *data);
void	error_texturefileincorect(void *path, void *toFree2, t_data *data);
//NODE_1
void	check_to_door(t_data *data, int x, int y);
t_node	create_node(char name, int x, int y);
t_node	find_exit_point(t_node *list);
t_node	find_spawn_point(t_node *list);
t_node	*get_node_at(t_node *list, int x, int y);
int		update_node(t_node node, t_node *list);
int		is_node_free(float x, float y, t_data *data);
int		toggle_door(t_node *cpy, t_data *data);
//NODE_UTILS
int		get_list_size(t_node *list);
int		get_list_xlen(t_node *list);
int		get_list_ylen(t_node *list);
//MAP_INIT
int		do_map_checks(int fd, char *reader);
t_node	*read_map(int fd, int fc, char *reader, t_data *data);
void	write_cubes(int color, int startX, int startY, t_data *data, int taille);
//MAP_SIZE
int	count_map(int fd, int x, char *reader);

#endif