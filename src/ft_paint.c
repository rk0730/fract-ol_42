
#include "ft_fractol.h"

// マンデルブロ集合の描画

static void hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b) {
	float c = v * s;
	float x = c * (1 - abs((int)(h * 6) % 2 - 1));
	float m = v - c;
	float r_prime, g_prime, b_prime;

	if (h < 1.0 / 6.0) {
		r_prime = c; g_prime = x; b_prime = 0;
	} else if (h < 2.0 / 6.0) {
		r_prime = x; g_prime = c; b_prime = 0;
	} else if (h < 3.0 / 6.0) {
		r_prime = 0; g_prime = c; b_prime = x;
	} else if (h < 4.0 / 6.0) {
		r_prime = 0; g_prime = x; b_prime = c;
	} else if (h < 5.0 / 6.0) {
		r_prime = x; g_prime = 0; b_prime = c;
	} else {
		r_prime = c; g_prime = 0; b_prime = x;
	}

	*r = (r_prime + m) * 255;
	*g = (g_prime + m) * 255;
	*b = (b_prime + m) * 255;
}



void	ft_paint(t_vars vars)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			t_complex_num z;
			t_viewport	*viewport = vars.viewport_info;

			z.r = viewport->r_min + (x * (viewport->r_max - viewport->r_min) / WIDTH);
			z.i = viewport->i_min + (y * (viewport->i_max - viewport->i_min) / HEIGHT);
			int iter;
			if (vars.frac_type->name == 'm')
				iter = ft_mandelbrot(z);
			else if (vars.frac_type->name == 'j')
				iter = ft_julia(z, *(vars.frac_type->complex));
			else
			{
				printf("Invalid fraction type\n");
				return ;
			}
			// HSV to RGB
			float s = 1;
			float v = 1;
			float h = iter / 1000.0 + 0.66; //0.66がないと赤くなり見にくい
			int r, g, b;
			hsv_to_rgb(h, s, v, &r, &g, &b);
			int color = (r << 16) | (g << 8) | b;
			int pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
			*(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
		}
	}
}
