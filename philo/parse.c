/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:44:30 by cjunker           #+#    #+#             */
/*   Updated: 2023/01/07 17:46:48 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_error(int ac, char **av)
{
	if (ac > 6 || ac < 5)
	{
		ft_putstr_fd(2, "\033[91;1musage : ./philo number_of_philosophers"
			" time_to_die time_to_eat time_to_sleep"
			" [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (!is_dig(av[1]) || !is_dig(av[2]) || !is_dig(av[3])
		|| !is_dig(av[4]) || (ac == 6 && !is_dig(av[5])))
	{
		ft_putstr_fd(2, "\033[91;1mOnly numerique arguments is allowed!\n");
		return (0);
	}
	return (1);
}

void	parse(t_global *global, int ac, char **av)
{
	int	i;

	i = -1;
	if (ac == 6)
		global->number_eat = ft_atoi(av[5]);
	else
		global->number_eat = -1;
	global->size = ft_atoi(av[1]);
	global->time_to_sleep = ft_atoi(av[4]);
	global->time_to_die = ft_atoi(av[2]);
	global->time_to_eat = ft_atoi(av[3]);
	global->fork = malloc(global->size * sizeof(pthread_mutex_t));
	global->philo = malloc(global->size * sizeof(t_philo));
	global->start = get_time();
	pthread_mutex_init(&global->access_global, NULL);
	while (++i < global->size)
		pthread_mutex_init(&global->fork[i], NULL);
}

int	only_1(t_global *global)
{
	if (global->size == 1)
	{
		printf("\033[38;2;%d;%d;%dm0 %d %s\n\033[0m", \
				hsl_to_r(360.0, .54, .7), \
				hsl_to_g(360.0, .54, .7), \
				hsl_to_b(360.0, .54, .7), \
				1, "has taken a fork");
		printf("\033[38;2;%d;%d;%dm%d %d %s\n\033[0m", \
				hsl_to_r(360.0, .54, .7), \
				hsl_to_g(360.0, .54, .7), \
				hsl_to_b(360.0, .54, .7), \
				global->time_to_die, 1, "died");
		return (0);
	}
	return (1);
}

void	init_philo(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->size)
	{
		global->philo[i].id = i + 1;
		global->philo[i].global = global;
		global->philo[i].last_meal = global->start;
		global->philo[i].r = hsl_to_r(360.0 / global->size * (i + 1), .54, .7);
		global->philo[i].g = hsl_to_g(360.0 / global->size * (i + 1), .54, .7);
		global->philo[i].b = hsl_to_b(360.0 / global->size * (i + 1), .54, .7);
		pthread_create(&global->philo[i].philo, NULL,
			(void *(*)(void *))routine, global->philo + i);
	}
}
