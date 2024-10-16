/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:09:45 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/16 18:00:10 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static void	ft_init1(t_complex_num point_complex[3], t_complex_num center,
		double size)
{
	point_complex[0].r = center.r + size * cos(M_PI / 6);
	point_complex[0].i = center.i + size * sin(M_PI / 6);
	point_complex[1].r = center.r + size * cos(5 * M_PI / 6);
	point_complex[1].i = center.i + size * sin(5 * M_PI / 6);
	point_complex[2].r = center.r + size * cos(3 * M_PI / 2);
	point_complex[2].i = center.i + size * sin(3 * M_PI / 2);
}

static void	ft_init2(t_point point[3], t_vars vars,
		t_complex_num point_complex[3])
{
	point[0].x = (int)((point_complex[0].r - vars.viewport->r_min)
			/ (vars.viewport->r_max - vars.viewport->r_min) * WIDTH);
	point[0].y = (int)((vars.viewport->i_max - point_complex[0].i)
			/ (vars.viewport->i_max - vars.viewport->i_min) * HEIGHT);
	point[1].x = (int)((point_complex[1].r - vars.viewport->r_min)
			/ (vars.viewport->r_max - vars.viewport->r_min) * WIDTH);
	point[1].y = (int)((vars.viewport->i_max - point_complex[1].i)
			/ (vars.viewport->i_max - vars.viewport->i_min) * HEIGHT);
	point[2].x = (int)((point_complex[2].r - vars.viewport->r_min)
			/ (vars.viewport->r_max - vars.viewport->r_min) * WIDTH);
	point[2].y = (int)((vars.viewport->i_max - point_complex[2].i)
			/ (vars.viewport->i_max - vars.viewport->i_min) * HEIGHT);
}

static void	ft_rec(t_vars vars, t_complex_num center, double size)
{
	t_complex_num	new_center;

	// 再帰
	new_center.r = center.r + size * cos(M_PI / 2);
	new_center.i = center.i + size * sin(M_PI / 2);
	ft_draw_down_triangle(vars, new_center, size / 2);
	new_center.r = center.r + size * cos(7 * M_PI / 6);
	new_center.i = center.i + size * sin(7 * M_PI / 6);
	ft_draw_down_triangle(vars, new_center, size / 2);
	new_center.r = center.r + size * cos(11 * M_PI / 6);
	new_center.i = center.i + size * sin(11 * M_PI / 6);
	ft_draw_down_triangle(vars, new_center, size / 2);
}

// 下向き正三角形をたくさん描画する関数
void	ft_draw_down_triangle(t_vars vars, t_complex_num center, double size)
{
	t_point			point[3];
	t_complex_num	point_complex[3];
	t_complex_num	center_display;
	t_complex_num	range;
	double			d;

	ft_init1(point_complex, center, size);
	ft_init2(point, vars, point_complex);
	// 一辺が3ピクセル以内になったら描画をやめる
	if (pow(point[0].x - point[1].x, 2) + pow(point[0].y - point[1].y, 2) <= 9)
		return ;
	center_display.r = (vars.viewport->r_max + vars.viewport->r_min) / 2;
	center_display.i = (vars.viewport->i_max + vars.viewport->i_min) / 2;
	range.r = vars.viewport->r_max - vars.viewport->r_min;
	range.i = vars.viewport->i_max - vars.viewport->i_min;
	d = sqrt(pow(center.r - center_display.r, 2) +
		pow(center.i - center_display.i, 2));
	// この下三角形が含まれる上三角形が範囲外なら終わりにする
	if (d > sqrt(pow(range.r / 2, 2) + pow(range.i / 2, 2)) + 2 * size)
		return ;
	// 3つの頂点を結ぶ
	ft_draw_line(vars, point[0], point[1]);
	ft_draw_line(vars, point[1], point[2]);
	ft_draw_line(vars, point[2], point[0]);
	// 再帰
	ft_rec(vars, center, size);
}
