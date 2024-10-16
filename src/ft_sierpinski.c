/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sierpinski.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:16:04 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/16 18:21:24 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static void	ft_draw_line_init(t_point *sx_sy, int *err, t_point p1, t_point p2)
{
	if (p1.x < p2.x)
		sx_sy->x = 1;
	else
		sx_sy->x = -1;
	if (p1.y < p2.y)
		sx_sy->y = 1;
	else
		sx_sy->y = -1;
	*err = abs(p2.x - p1.x) - abs(p2.y - p1.y);
}

static void	ft_draw_line_h(t_vars vars, t_point p1, const long color)
{
	int	pos;

	if (p1.x <= WIDTH && p1.y <= HEIGHT && p1.x >= 0 && p1.y >= 0)
	{
		pos = (p1.y * vars.mlx_info->size_line) + (p1.x * (vars.mlx_info->bpp
					/ 8));
		*(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
	}
}

// 2点間の直線を描画する関数
void	ft_draw_line(t_vars vars, t_point p1, t_point p2)
{
	const t_point	dx_dy = {abs(p2.x - p1.x), abs(p2.y - p1.y)};
	t_point			sx_sy;
	int				err;
	const long		color = ft_hsv_to_color(vars.frac_type->base_color, 1, 1);
	int				e2;

	ft_draw_line_init(&sx_sy, &err, p1, p2);
	while (1)
	{
		ft_draw_line_h(vars, p1, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = err * 2;
		if (e2 > -dx_dy.y)
		{
			err -= dx_dy.y;
			p1.x += sx_sy.x;
		}
		if (e2 < dx_dy.x)
		{
			err += dx_dy.x;
			p1.y += sx_sy.y;
		}
	}
}

void	ft_sierpinski(t_vars vars)
{
	int					x;
	int					y;
	int					pos;
	const t_complex_num	z0 = {0, 0};

	// 全マスを黒で塗りつぶす
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp
						/ 8));
			*(unsigned int *)(vars.mlx_info->data_addr
					+ pos) = (20 << 16) | (20 << 8) | 20;
			x++;
		}
		y++;
	}
	// 正三角形を描画
	ft_draw_triangle(vars, z0, 2);
	ft_draw_down_triangle(vars, z0, 1);
}
