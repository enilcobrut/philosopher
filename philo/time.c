/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:42:24 by cjunker           #+#    #+#             */
/*   Updated: 2023/01/07 17:43:15 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_usleep(long int ms, t_philo *p)
{
	long int	time;
	long int	start;

	start = get_time();
	while (!p->global->is_end)
	{
		time = get_time();
		if (time - start >= ms)
			break ;
		usleep((ms - (time - start)) * 150);
	}
}
