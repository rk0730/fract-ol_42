/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:22:30 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/04 19:30:32 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

#include <stdio.h>
#include <ctype.h>

double ft_atof(const char *str) {
	double result = 0.0;
	double fraction = 0.0;
	double divisor = 1.0;
	int sign = 1;
	int fraction_flag = 0;

	//これなくても大丈夫な気がする
	// 先頭の空白文字を無視
	// while (isspace(*str)) {
	// 	str++;
	// }

	// 符号のチェック（-１回のみ認める）
	if (*str == '-') {
		sign = -1;
		str++;
	}
	// 整数部分の処理
	while (ft_isdigit(*str)) {
		result = result * 10.0 + (*str - '0');
		str++;
	}

	// 小数点の処理
	if (*str == '.') {
		str++;
		fraction_flag = 1;
	}

	// 小数部分の処理
	if (fraction_flag) {
		while (isdigit(*str)) {
			fraction = fraction * 10.0 + (*str - '0');
			divisor *= 10.0;
			str++;
		}
	}

	// 最終的な結果
	result += fraction / divisor;
	return result * sign;
}



//エラー　-1を返す
// 2つ目の引数がmで始まる→マンデルブロ集合
// 2つ目の引数がjで始まる→ジュリア集合　3つ目と4つ目の引数が必要
int	ft_arg(int argc, char **argv, double *r, double *i)
{
	if (argc < 2)
	{
		ft_printf("Usage: ./fractol [m/j (double)x (double)y]\n");
		exit(1);
	}
	if (argv[1][0] == 'm')
		return (0);
	if (argv[1][0] == 'j')
	{
		if (argc < 4)
		{
			ft_printf("Usage: ./fractol [m/j (double)x (double)y]\n");
			exit(1);
		}
		*r = ft_atof(argv[2]);
		*i = ft_atof(argv[3]);
		return (1);
	}
	exit(1);
}
