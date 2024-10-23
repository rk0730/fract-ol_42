/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:39:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/23 12:44:24 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//commit test
#include "ft_fractol.h"

static void	ft_init(t_vars *vars, char *title)
{
	vars->viewport->r_max = 2.0;
	vars->viewport->r_min = -2.0;
	vars->viewport->i_max = 2.0;
	vars->viewport->i_min = -2.0;
	vars->mlx_info->mlx = mlx_init();
	vars->mlx_info->win = mlx_new_window(vars->mlx_info->mlx,
			WIDTH, HEIGHT, title);
	vars->mlx_info->img = mlx_new_image(vars->mlx_info->mlx, WIDTH, HEIGHT);
	vars->mlx_info->data_addr = mlx_get_data_addr(vars->mlx_info->img,
			&(vars->mlx_info->bpp), &(vars->mlx_info->size_line),
			&(vars->mlx_info->endian));
}

// コマンドライン引数に応じて初期化する
static void	main_help(int argc, char **argv, t_vars *vars)
{
	if (ft_arg(argc, argv, vars->frac_type->complex) == 0)
	{
		//マンデルブロ集合
		vars->frac_type->name = 'm';
		ft_init(vars, "Mandelbrot");
	}
	else if (ft_arg(argc, argv, vars->frac_type->complex) == 1)
	{
		//ジュリア集合
		vars->frac_type->name = 'j';
		ft_init(vars, "Julia");
	}
	else if (ft_arg(argc, argv, vars->frac_type->complex) == 2)
	{
		//シェルピンスキーのギャスケット
		vars->frac_type->name = 's';
		ft_init(vars, "Sierpinski Gasket");
	}
}

int	main(int argc, char **argv)
{
	t_vars			vars;
	t_mlx_info		mlx_info;
	t_viewport		viewport;
	t_frac_type		frac_type;
	t_complex_num	complex_num;

	vars.mlx_info = &mlx_info;
	vars.viewport = &viewport;
	vars.frac_type = &frac_type;
	frac_type.base_color = 0.66;
	frac_type.complex = &complex_num;
	main_help(argc, argv, &vars);
	ft_paint(vars);
	mlx_put_image_to_window(mlx_info.mlx, mlx_info.win, mlx_info.img, 0, 0);
	mlx_mouse_hook(mlx_info.win, ft_zoom, &vars);
	mlx_hook(mlx_info.win, ON_DESTROY, 0, ft_close, &mlx_info);
	mlx_key_hook(mlx_info.win, ft_key_hook, &vars);
	mlx_loop(mlx_info.mlx);
	return (0);
}
