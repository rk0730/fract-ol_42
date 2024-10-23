/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:10:06 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/23 13:43:09 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

# include "ft_printf.h"
# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <stdint.h>

# define WIDTH 500
# define HEIGHT 500

# define M_PI 3.14159265358979323846

typedef struct s_complex_num
{
	double			r;
	double			i;
}					t_complex_num;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_mlx_info
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bpp;
	int				size_line;
	int				endian;
}					t_mlx_info;

typedef struct s_viewport
{
	double			r_max;
	double			r_min;
	double			i_max;
	double			i_min;
}					t_viewport;

typedef struct s_frac_type
{
	char			name;
	t_complex_num	*complex;
	double			base_color;
}					t_frac_type;

typedef struct s_vars
{
	t_mlx_info		*mlx_info;
	t_viewport		*viewport;
	t_frac_type		*frac_type;
}					t_vars;

enum				e_event
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum				e_mouse_event
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	MIDDLE_CLICK = 3,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
};

enum				e_keycode
{
	KEY_SPACE = 32,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_W = 119,
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
	KEY_ESC = 65307
};

void				ft_sierpinski(t_vars vars);
void				ft_paint(t_vars vars);
int					ft_mandelbrot(t_complex_num c);
int					ft_julia(t_complex_num z, t_complex_num c);
int					ft_zoom(int event, int x, int y, t_vars *vars);
int					ft_arg(int argc, char **argv, t_complex_num *complex_num);
long				ft_hsv_to_color(float h, float s, float v);
int					ft_key_hook(enum e_keycode keycode, t_vars *vars);
int					ft_close(t_mlx_info *mlx_info);
void				ft_draw_triangle(t_vars vars, t_complex_num center,
						double size);
void				ft_draw_down_triangle(t_vars vars, t_complex_num center,
						double size);
void				ft_draw_line(t_vars vars, t_point p1, t_point p2);

#endif