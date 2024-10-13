/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sierpinski.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:16:04 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/13 18:20:39 by kitaoryoma       ###   ########.fr       */
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
	int err = dx - dy;

	//直線が四角形の範囲外なら終わり（バグった）
	// int d = abs((-y0+y1)*(WIDTH/2)+(x0-x1)*(HEIGHT/2)+x1*y0-x0*y1);
	// if (pow(d, 2) > pow(WIDTH/2, 2)+pow(HEIGHT/2, 2)) return ;

	int r,g,b;
	float s = 1;
	float v = 1;
	float h = vars.frac_type->base_color;
	ft_hsv_to_rgb(h, s, v, &r, &g, &b);

	while (1) {
		if (x0 <= WIDTH && y0 <= HEIGHT && x0 >= 0 && y0 >= 0)
		{
			int pos = (y0 * vars.mlx_info->size_line) + (x0 * (vars.mlx_info->bpp / 8));
			*(unsigned int *)(vars.mlx_info->data_addr + pos) = (r << 16) | (g << 8) | b;
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

// 下向き正三角形をたくさん描画する関数
void draw_down_triangle(t_vars vars, double center_r, double center_i, double size)
{
		
	double r1 = center_r + size * cos(M_PI/6);
	double i1 = center_i + size * sin(M_PI/6);
		
	double r2 = center_r + size * cos(5*M_PI/6);
	double i2 = center_i + size * sin(5*M_PI/6);
		
	double r3 = center_r + size * cos(3*M_PI/2);
	double i3 = center_i + size * sin(3*M_PI/2);

	int x1 = (int)((r1-vars.viewport_info->r_min)/(vars.viewport_info->r_max-vars.viewport_info->r_min)*WIDTH);
	int y1 = (int)((vars.viewport_info->i_max-i1)/(vars.viewport_info->i_max-vars.viewport_info->i_min)*HEIGHT);

	int x2 = (int)((r2-vars.viewport_info->r_min)/(vars.viewport_info->r_max-vars.viewport_info->r_min)*WIDTH);
	int y2 = (int)((vars.viewport_info->i_max-i2)/(vars.viewport_info->i_max-vars.viewport_info->i_min)*HEIGHT);

	int x3 = (int)((r3-vars.viewport_info->r_min)/(vars.viewport_info->r_max-vars.viewport_info->r_min)*WIDTH);
	int y3 = (int)((vars.viewport_info->i_max-i3)/(vars.viewport_info->i_max-vars.viewport_info->i_min)*HEIGHT);

	// 一辺が3ピクセル以内になったら描画をやめる
	if ((pow(x1-x2,2)+pow(y1-y2,2)) <= 9)
		return ;
	
	double center_display_r = (vars.viewport_info->r_max+vars.viewport_info->r_min)/2;
	double center_display_i = (vars.viewport_info->i_max+vars.viewport_info->i_min)/2;
	double width = vars.viewport_info->r_max-vars.viewport_info->r_min;
	double height = vars.viewport_info->i_max-vars.viewport_info->i_min;
	double d = sqrt(pow(center_r-center_display_r,2)+pow(center_i-center_display_i,2));
	// この下三角形が含まれる上三角形が範囲外なら終わりにする
	if (d > sqrt(pow(width/2,2)+pow(height/2,2))+2*size) return ;
	
	// 3つの頂点を結ぶ
	draw_line(vars, x1, y1, x2, y2);
	draw_line(vars, x2, y2, x3, y3);
	draw_line(vars, x3, y3, x1, y1);

	// 再帰
	draw_down_triangle(vars, center_r+size*cos(M_PI/2), center_i+size*sin(M_PI/2), size/2);
	draw_down_triangle(vars, center_r+size*cos(7*M_PI/6), center_i+size*sin(7*M_PI/6), size/2);
	draw_down_triangle(vars, center_r+size*cos(11*M_PI/6), center_i+size*sin(11*M_PI/6), size/2);
}

// 上向き正三角形を描画する関数
void draw_triangle(t_vars vars, double center_r, double center_i, double size)
{
		
	double r1 = center_r + size * cos(M_PI/2);
	double i1 = center_i + size * sin(M_PI/2);
		
	double r2 = center_r + size * cos(7*M_PI/6);
	double i2 = center_i + size * sin(7*M_PI/6);
		
	double r3 = center_r + size * cos(11*M_PI/6);
	double i3 = center_i + size * sin(11*M_PI/6);

	int x1 = (int)((r1-vars.viewport_info->r_min)/(vars.viewport_info->r_max-vars.viewport_info->r_min)*WIDTH);
	int y1 = (int)((vars.viewport_info->i_max-i1)/(vars.viewport_info->i_max-vars.viewport_info->i_min)*HEIGHT);

	int x2 = (int)((r2-vars.viewport_info->r_min)/(vars.viewport_info->r_max-vars.viewport_info->r_min)*WIDTH);
	int y2 = (int)((vars.viewport_info->i_max-i2)/(vars.viewport_info->i_max-vars.viewport_info->i_min)*HEIGHT);

	int x3 = (int)((r3-vars.viewport_info->r_min)/(vars.viewport_info->r_max-vars.viewport_info->r_min)*WIDTH);
	int y3 = (int)((vars.viewport_info->i_max-i3)/(vars.viewport_info->i_max-vars.viewport_info->i_min)*HEIGHT);
	// 3つの頂点を結ぶ
	draw_line(vars, x1, y1, x2, y2);
	draw_line(vars, x2, y2, x3, y3);
	draw_line(vars, x3, y3, x1, y1);
}

void	ft_sierpinski(t_vars vars)
{
	// 全マスを黒で塗りつぶす
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			int pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
			*(unsigned int *)(vars.mlx_info->data_addr + pos) = (20 << 16) | (20 << 8) | 20;
			x++;
		}
		y++;
	}


	
	// for (int y=0;y<HEIGHT;y++){
	// 	for (int x=0;x<WIDTH;x++){
	// 		int pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
	// 		*(unsigned int *)(vars.mlx_info->data_addr + pos) = (20 << 16) | (20 << 8) | 20;
	// 	}
	// }

	// 正三角形を描画
	draw_triangle(vars, 0, 0, 2);
	draw_down_triangle(vars, 0, 0, 1);
}
