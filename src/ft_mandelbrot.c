
#include "ft_fractol.h"

# include <stdio.h>

// マンデルブロ集合の描画

void hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b) {
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

static int	mandelbrot(double real, double imag)
{
	int		max_iter;
	double	zr = 0.0, zi;
	int		iter;
	double	tmp;

	max_iter = 1000;
	zr = 0.0, zi = 0.0;
	iter = 0;
	while (zr * zr + zi * zi < 4.0 && iter < max_iter)
	{
		tmp = zr * zr - zi * zi + real;
		zi = 2.0 * zr * zi + imag;
		zr = tmp;
		iter++;
	}
	return (iter);
}

void draw_mandelbrot(t_mlx *mlx) {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			double real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
			double imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
			int iter = mandelbrot(real, imag);
			if (x % 40 == 0 && y % 30 == 0) {
				printf("x: %d, y: %d, iter: %d\n", x, y, iter);
			}
			if (iter == 1000 || iter == 1) {
				//黒にする
				int pos = (y * mlx->size_line) + (x * (mlx->bpp / 8));
				*(unsigned int *)(mlx->data_addr + pos) = 0x000000;
				continue;
			}
			float s = 1;
			float v = 1;
			float h;
			if (iter == 2 || iter == 3)
				h = 0.66;
			else if (4 <= iter && iter <= 6)
				h = 0.33;
			else if (7 <= iter && iter <= 9)
				h = 0.16;
			else if (10 <= iter && iter <= 100)
				h = 0.08;
			else
				h = 0.04;
			int r, g, b;
			hsv_to_rgb(h, s, v, &r, &g, &b);
			int color = (r << 16) | (g << 8) | b;
			int pos = (y * mlx->size_line) + (x * (mlx->bpp / 8));
			*(unsigned int *)(mlx->data_addr + pos) = color;
		}
	}
}