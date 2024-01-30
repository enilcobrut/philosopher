/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:38:57 by cjunker           #+#    #+#             */
/*   Updated: 2023/01/07 17:48:14 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

void	mutex_print(char *message, t_philo *p)
{
	pthread_mutex_lock(&p->global->access_global);
	if (p->global->is_end)
	{
		pthread_mutex_unlock(&p->global->access_global);
		return ;
	}
	print_color(message, p);
	pthread_mutex_unlock(&p->global->access_global);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(&p->global->fork[p->id - 1]);
	mutex_print("has taken a fork", p);
	if (p->id == p->global->size)
		pthread_mutex_lock(&p->global->fork[0]);
	else
		pthread_mutex_lock(&p->global->fork[p->id]);
	mutex_print("has taken a fork", p);
	pthread_mutex_lock(&p->global->access_global);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->global->access_global);
	mutex_print("is eating", p);
	ft_usleep(p->global->time_to_eat, p);
	pthread_mutex_unlock(&p->global->fork[p->id - 1]);
	if (p->id == p->global->size)
		pthread_mutex_unlock(&p->global->fork[0]);
	else
		pthread_mutex_unlock(&p->global->fork[p->id]);
}

void	*routine(t_philo *p)
{
	if (p->id % 2 == 0)
		ft_usleep(100, p);
	while (!p->global->is_end)
	{
		ft_eat(p);
		if (p->global->number_eat != -1)
		{
			pthread_mutex_lock(&p->global->access_global);
			p->global->count++;
			if (p->global->count / p->global->size >= p->global->number_eat)
			{
				p->global->is_end = !!"CC";
				pthread_mutex_unlock(&p->global->access_global);
				break ;
			}
			pthread_mutex_unlock(&p->global->access_global);
		}
		mutex_print("is sleeping", p);
		ft_usleep(p->global->time_to_sleep, p);
		mutex_print("is thinking", p);
	}
	return (NULL);
}

void	check_end(t_global *global)
{
	int	i;

	while (!global->is_end)
	{
		i = -1;
		pthread_mutex_lock(&global->access_global);
		while (++i < global->size)
		{
			if (get_time() - global->philo[i].last_meal > global->time_to_die
				&& !global->is_end)
			{
				print_color("died", global->philo + i);
				global->is_end = !!"💀";
				pthread_mutex_unlock(&global->access_global);
				break ;
			}
		}
		pthread_mutex_unlock(&global->access_global);
		usleep(150);
	}
}

int	main(int ac, char **av)
{
	t_global		global;
	int				i;

	global.is_end = 0;
	global.count = 0;
	i = -1;
	if (!parse_error(ac, av))
		return (EXIT_FAILURE);
	parse(&global, ac, av);
	if (!only_1(&global))
		return (EXIT_SUCCESS);
	init_philo(&global);
	check_end(&global);
	while (++i < global.size)
		pthread_join(global.philo[i].philo, NULL);
}
