/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:09:45 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/16 16:09:55 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

// 上向き正三角形を描画する関数
void draw_triangle(t_vars vars, double center_r, double center_i, double size)
{
		
	double r1 = center_r + size * cos(M_PI/2);
	double i1 = center_i + size * sin(M_PI/2);
		
	double r2 = center_r + size * cos(7*M_PI/6);
	double i2 = center_i + size * sin(7*M_PI/6);
		
	double r3 = center_r + size * cos(11*M_PI/6);
	double i3 = center_i + size * sin(11*M_PI/6);

	int x1 = (int)((r1-vars.viewport->r_min)/(vars.viewport->r_max-vars.viewport->r_min)*WIDTH);
	int y1 = (int)((vars.viewport->i_max-i1)/(vars.viewport->i_max-vars.viewport->i_min)*HEIGHT);

	int x2 = (int)((r2-vars.viewport->r_min)/(vars.viewport->r_max-vars.viewport->r_min)*WIDTH);
	int y2 = (int)((vars.viewport->i_max-i2)/(vars.viewport->i_max-vars.viewport->i_min)*HEIGHT);

	int x3 = (int)((r3-vars.viewport->r_min)/(vars.viewport->r_max-vars.viewport->r_min)*WIDTH);
	int y3 = (int)((vars.viewport->i_max-i3)/(vars.viewport->i_max-vars.viewport->i_min)*HEIGHT);
	// 3つの頂点を結ぶ
	draw_line(vars, x1, y1, x2, y2);
	draw_line(vars, x2, y2, x3, y3);
	draw_line(vars, x3, y3, x1, y1);
}