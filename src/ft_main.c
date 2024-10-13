/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:39:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/13 17:48:16 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static void	ft_init(t_vars *vars, char *title)
{
	vars->viewport_info->r_max = 2.0;
	vars->viewport_info->r_min = -2.0;
	vars->viewport_info->i_max = 2.0;
	vars->viewport_info->i_min = -2.0;
	vars->mlx_info->mlx = mlx_init();
	vars->mlx_info->win = mlx_new_window(vars->mlx_info->mlx, WIDTH, HEIGHT, title);
	vars->mlx_info->img = mlx_new_image(vars->mlx_info->mlx, WIDTH, HEIGHT);
	vars->mlx_info->data_addr = mlx_get_data_addr(vars->mlx_info->img,
		&(vars->mlx_info->bpp), &(vars->mlx_info->size_line),
		&(vars->mlx_info->endian));
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_mlx_info	mlx_info;
	t_viewport	viewport;
	t_frac_type	frac_type;
	t_complex_num complex_num;

	vars.mlx_info = &mlx_info;
	vars.viewport_info = &viewport;
	vars.frac_type = &frac_type;
	frac_type.base_color = 0.66;
	frac_type.complex = &complex_num;
	if (ft_arg(argc, argv, &complex_num) == 0)
	{
		//マンデルブロ集合
		frac_type.name = 'm';
		ft_init(&vars, "Mandelbrot");
		ft_paint(vars);
	}
	else if (ft_arg(argc, argv, &complex_num) == 1)
	{
		//ジュリア集合
		frac_type.name = 'j';
		ft_init(&vars, "Julia");
		ft_paint(vars);
	}
	else if (ft_arg(argc, argv, &complex_num) == 2)
	{
		//シェルピンスキーのギャスケット
		frac_type.name = 's';
		ft_init(&vars, "Sierpinski Gasket");
		ft_paint(vars);
	}
	mlx_put_image_to_window(mlx_info.mlx, mlx_info.win, mlx_info.img, 0, 0);
	mlx_mouse_hook(mlx_info.win, ft_zoom, &vars);
	mlx_hook(mlx_info.win, ON_DESTROY, 0, ft_close, &mlx_info);
	mlx_key_hook(mlx_info.win, ft_key_hook, &vars);
	mlx_loop(mlx_info.mlx);
	return (0);
}
