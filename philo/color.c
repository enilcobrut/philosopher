/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:34:02 by cjunker           #+#    #+#             */
/*   Updated: 2023/01/07 17:41:25 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	hsl_to_r(double h, double s, double l)
{
	const double	c = (1 - ft_fabs(2 * l - 1)) * s;
	const double	x = c * (1 - ft_fabs(ft_fmod(h / 60.0, 2) - 1));
	const double	m = l - c / 2;

	if (h < 60)
		return ((c + m) * 255.0);
	else if (h < 120)
		return ((x + m) * 255.0);
	else if (h < 240)
		return ((m) * 255.0);
	else if (h < 300)
		return ((x + m) * 255.0);
	else
		return ((c + m) * 255.0);
}

int	hsl_to_g(double h, double s, double l)
{
	const double	c = (1 - ft_fabs(2 * l - 1)) * s;
	const double	x = c * (1 - ft_fabs(ft_fmod(h / 60.0, 2) - 1));
	const double	m = l - c / 2;

	if (h < 60)
		return ((x + m) * 255.0);
	else if (h < 180)
		return ((c + m) * 255.0);
	else if (h < 240)
		return ((x + m) * 255.0);
	else
		return ((m) * 255.0);
}

int	hsl_to_b(double h, double s, double l)
{
	const double	c = (1 - ft_fabs(2 * l - 1)) * s;
	const double	x = c * (1 - ft_fabs(ft_fmod(h / 60.0, 2) - 1));
	const double	m = l - c / 2;

	if (h < 120)
		return ((m) * 255.0);
	else if (h < 180)
		return ((x + m) * 255.0);
	else if (h < 300)
		return ((c + m) * 255.0);
	else
		return ((x + m) * 255.0);
}

void	print_color(char *message, t_philo *p)
{
	printf("\033[38;2;%d;%d;%dm%ld %d %s\n\033[0m", \
	p->r, p->g, p->b, get_time() - p->global->start, p->id, message);
}
