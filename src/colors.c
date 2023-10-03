/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:24 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/03 12:14:32 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int	get_a(int rgba)
{
	return (rgba & 0xFF);
}

int	correct_color(uint32_t px)
{
	int	g;
	int	b;
	int	a;
	int	color;
	int	r;

	r = get_r(px);
	g = get_g(px);
	b = get_b(px);
	a = get_a(px);
	color = rgb_to_argb(a, b, g, r);
	return (color);
}