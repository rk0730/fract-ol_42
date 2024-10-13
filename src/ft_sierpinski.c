/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sierpinski.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:16:04 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/13 17:12:57 by rkitao           ###   ########.fr       */
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
	for (int y=0;y<HEIGHT;y++){
		for (int x=0;x<WIDTH;x++){
			int pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
			*(unsigned int *)(vars.mlx_info->data_addr + pos) = (20 << 16) | (20 << 8) | 20;
		}
	}

	// 正三角形を描画
	draw_triangle(vars, 0, 0, 2);
	draw_down_triangle(vars, 0, 0, 1);
	// int color = (r << 16) | (g << 8) | b;
	// int pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
	// *(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
}


// void	ft_paint(t_vars vars)
// {
// 	for (int y = 0; y < HEIGHT; y++) {
// 		for (int x = 0; x < WIDTH; x++) {
// 			t_complex_num z;
// 			t_viewport	*viewport = vars.viewport_info;

// 			// (0,0)が左上なので、yの値を逆にする
// 			z.r = viewport->r_min + (x * (viewport->r_max - viewport->r_min) / WIDTH);
// 			z.i = viewport->i_max - (y * (viewport->i_max - viewport->i_min) / HEIGHT);
// 			int iter;
// 			if (vars.frac_type->name == 'm')
// 				iter = ft_mandelbrot(z);
// 			else if (vars.frac_type->name == 'j')
// 				iter = ft_julia(z, *(vars.frac_type->complex));
// 			else
// 			{
// 				ft_printf("Invalid fraction type\n");
// 				return ;
// 			}

// 			int r, g, b;
// 			// 収束した場合は黒
// 			if (iter == 1000){
// 				r = 20;
// 				g = 20;
// 				b = 20;
// 			}else{
// 				// HSV to RGB
// 				float s = 1;
// 				float v = 1;
// 				float h = iter / 1000.0 + vars.frac_type->base_color; //base_color(0.66)がないと赤くなり見にくい
// 				hsv_to_rgb(h, s, v, &r, &g, &b);
// 			}
// 			int color = (r << 16) | (g << 8) | b;
// 			int pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
// 			*(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
// 		}
// 	}
// }