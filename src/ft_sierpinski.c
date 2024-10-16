/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sierpinski.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:16:04 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/16 16:40:58 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

// 2点間の直線を描画する関数
void draw_line(t_vars vars, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = abs(x1 - x0) - abs(y1 - y0);
	long color;

	color = ft_hsv_to_color(vars.frac_type->base_color, 1, 1);

	while (1) {
		if (x0 <= WIDTH && y0 <= HEIGHT && x0 >= 0 && y0 >= 0)
		{
			int pos = (y0 * vars.mlx_info->size_line) + (x0 * (vars.mlx_info->bpp / 8));
			*(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
		}
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = err * 2;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void	ft_sierpinski(t_vars vars)
{
	// 全マスを黒で塗りつぶす
	int x;
	int y;
	int pos;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pos = (y * vars.mlx_info->size_line) + 
				(x * (vars.mlx_info->bpp / 8));
			*(unsigned int *)(vars.mlx_info->data_addr + pos) = 
				(20 << 16) | (20 << 8) | 20;
			x++;
		}
		y++;
	}
	// 正三角形を描画
	draw_triangle(vars, 0, 0, 2);
	draw_down_triangle(vars, 0, 0, 1);
}
