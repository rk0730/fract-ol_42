
#include "ft_fractol.h"

void	ft_paint(t_vars vars)
{
	if (vars.frac_type->name == 's')
	{
		ft_sierpinski(vars);
		return ;
	}

	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			t_complex_num z;
			t_viewport	*viewport = vars.viewport;

			// (0,0)が左上なので、yの値を逆にする
			z.r = viewport->r_min + (x * (viewport->r_max - viewport->r_min) / WIDTH);
			z.i = viewport->i_max - (y * (viewport->i_max - viewport->i_min) / HEIGHT);
			int iter;
			if (vars.frac_type->name == 'm')
				iter = ft_mandelbrot(z);
			else if (vars.frac_type->name == 'j')
				iter = ft_julia(z, *(vars.frac_type->complex));
			else
			{
				ft_printf("Invalid fraction type\n");
				return ;
			}

			int r, g, b;
			// 収束した場合は黒
			if (iter == 1000){
				r = 20;
				g = 20;
				b = 20;
			}else{
				// HSV to RGB
				float s = 1;
				float v = 1;
				float h = iter / 1000.0 + vars.frac_type->base_color; //base_color(0.66)がないと赤くなり見にくい
				ft_hsv_to_rgb(h, s, v, &r, &g, &b);
			}
			int color = (r << 16) | (g << 8) | b;
			int pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
			*(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
			x++;
		}
		y++;
	}









	// for (int y = 0; y < HEIGHT; y++) {
	// 	for (int x = 0; x < WIDTH; x++) {
	// 		t_complex_num z;
	// 		t_viewport	*viewport = vars.viewport_info;

	// 		// (0,0)が左上なので、yの値を逆にする
	// 		z.r = viewport->r_min + (x * (viewport->r_max - viewport->r_min) / WIDTH);
	// 		z.i = viewport->i_max - (y * (viewport->i_max - viewport->i_min) / HEIGHT);
	// 		int iter;
	// 		if (vars.frac_type->name == 'm')
	// 			iter = ft_mandelbrot(z);
	// 		else if (vars.frac_type->name == 'j')
	// 			iter = ft_julia(z, *(vars.frac_type->complex));
	// 		else
	// 		{
	// 			ft_printf("Invalid fraction type\n");
	// 			return ;
	// 		}

	// 		int r, g, b;
	// 		// 収束した場合は黒
	// 		if (iter == 1000){
	// 			r = 20;
	// 			g = 20;
	// 			b = 20;
	// 		}else{
	// 			// HSV to RGB
	// 			float s = 1;
	// 			float v = 1;
	// 			float h = iter / 1000.0 + vars.frac_type->base_color; //base_color(0.66)がないと赤くなり見にくい
	// 			ft_hsv_to_rgb(h, s, v, &r, &g, &b);
	// 		}
	// 		int color = (r << 16) | (g << 8) | b;
	// 		int pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
	// 		*(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
	// 	}
	// }
}
