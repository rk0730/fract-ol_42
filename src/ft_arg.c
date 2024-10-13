/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:22:30 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/13 19:00:42 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

#include <stdio.h>
#include <ctype.h>

double ft_atof(char *str)
{
	double result = 0.0;
	double fraction = 0.0;
	double divisor = 1.0;
	int sign = 1;
	int fraction_flag = 0;

	// 先頭の空白文字を無視
	while (*str == ' ' || (9 <= *str && *str <= 13)) {
		str++;
	}

	// 符号のチェック（-１回のみ認める）
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	char *point = str;
	// 整数部分の処理
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}

	//整数部分が0桁なら終わり
	if (str == point)
		return (NAN);

	// 小数点の処理
	if (*str == '.')
	{
		str++;
		fraction_flag = 1;
	}

	// 小数部分の処理
	if (fraction_flag)
	{
		point = str;
		while (isdigit(*str))
		{
			fraction = fraction * 10.0 + (*str - '0');
			divisor *= 10.0;
			str++;
		}
		// 小数部分が0桁なら終わり
		if (str == point)
			return (NAN);
	}

	// 最終的な結果
	result += fraction / divisor;
	return result * sign;
}



//エラー　-1を返す
// 2つ目の引数がmで始まる→マンデルブロ集合
// 2つ目の引数がjで始まる→ジュリア集合　3つ目と4つ目の引数が必要
int	ft_arg(int argc, char **argv, t_complex_num *complex_num)
{
	if (argc < 2)
	{
		ft_printf("Usage: ./fractol [m/j (double)x (double)y/s]\n");
		exit(1);
	}
	if (argv[1][0] == 'm')
		return (0);
	if (argv[1][0] == 's')
		return (2);
	if (argv[1][0] == 'j')
	{
		if (argc < 4)
		{
			ft_printf("Usage: ./fractol [m/j (double)x (double)y]\n");
			exit(1);
		}
		complex_num->r = ft_atof(argv[2]);
		complex_num->i = ft_atof(argv[3]);
		if (isnan(complex_num->r) || isnan(complex_num->i))
		{
			ft_printf("Invalid argument\n");
			exit(1);
		}
		return (1);
	}
	exit(1);
}
