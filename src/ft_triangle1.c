/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:09:45 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/16 17:52:45 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

// 上向き正三角形を描画する関数
void	ft_draw_triangle(t_vars vars, t_complex_num center, double size)
{
	t_point			point[3];
	t_complex_num	point_complex[3];

	point_complex[0].r = center.r + size * cos(M_PI / 2);
	point_complex[0].i = center.i + size * sin(M_PI / 2);
	point_complex[1].r = center.r + size * cos(7 * M_PI / 6);
	point_complex[1].i = center.i + size * sin(7 * M_PI / 6);
	point_complex[2].r = center.r + size * cos(11 * M_PI / 6);
	point_complex[2].i = center.i + size * sin(11 * M_PI / 6);
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
	// 3つの頂点を結ぶ
	ft_draw_line(vars, point[0], point[1]);
	ft_draw_line(vars, point[1], point[2]);
	ft_draw_line(vars, point[2], point[0]);
}
