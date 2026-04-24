#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include <mlx_int.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define WIN_W 2560
# define WIN_H 1440
# define MINI_PIXEL_CELL 10
# define MINI_SIZE 6
# define PLAYER_SIZE 3
# define COLOR_MINI_WALL 0x888888
# define COLOR_MINI_FLOOR 0x222222
# define COLOR_MINI_PLAYER 0xFF0000
# define TRUE 1
# define FALSE 0
# define KEY_W      119
# define KEY_S      115
# define KEY_A      97
# define KEY_D      100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.02
# define MOUSE_SENSITIVITY 0.0007
# define CEIL_ID 5
# define FLOOR_ID 4
# define WALL_MARGIN 0.1

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_texture
{
	void	*imge;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;

	char	**texturepath;
	int		pos_x;
	int		pos_y;
	char	*direction;
}	t_texture;

typedef struct s_ray
{
	int		text_x;
	int		text_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		height;
	int		draw_start;
	int		draw_end;
	int		floor_tex_x;
	int		floor_tex_y;
	int		ceil_tex_x;
	int		ceil_tex_y;
	double	wall_x;
	double	floor_wall_x;
	double	floor_wall_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	walldist;
}	t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_game
{
	size_t		map_w;
	size_t		map_h;
	int			win_w;
	int			win_h;
	void		*mlx;
	void		*win;
	t_keys		keys;
	t_data		img;
	int			size_square;
	int			ceil_color;
	int			floor_color;
	Bool		use_ceil_text;
	Bool		use_floor_text;
	t_texture	texture[6];
	t_texture	*txt;
	int			current_text_id;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			**map;
	int			mouse_x;
}	t_game;

int			render(t_game *g);
int			close_window(t_game *g);
void		init_struct_ray(t_ray *r);
void		mouse_controls(t_game *g);
void		cast_ray(t_game *g, int x);
void		init_struct_keys(t_game *g);
int			key_press(int key, t_game *g);
int			key_release(int key, t_game *g);
void		draw_minimap(t_game *g);
t_texture	load_texture(t_game *g, void *mlx, char *path);
void		draw_map(t_game *g, t_ray *r, int x);
void		init_texture(t_game *g, t_texture *txt);
void		find_floor_position_on_wallbase(t_ray *r);
void		init_struct_game(t_game *g, t_texture *txt);
void		my_mlx_pixel_put(t_game *g, int x, int y, int color);
void		find_id_texture(t_game *g, int side, double raydir_x,
				double raydir_y);

#endif