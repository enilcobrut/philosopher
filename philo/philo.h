/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:41:32 by cjunker           #+#    #+#             */
/*   Updated: 2023/01/07 17:47:32 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_global	t_global;

typedef struct s_philo
{
	int					id;
	long int			last_meal;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	pthread_t			philo;
	t_global			*global;
}	t_philo;

typedef struct s_global
{
	t_philo					*philo;
	pthread_mutex_t			*fork;
	pthread_mutex_t			access_global;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_eat;
	int						size;
	int						count;
	long int				start;
	int						is_end;
}	t_global;

void		*routine(t_philo *p);

/*UTILS*/

int			ft_strlen(char *str);
void		ft_putstr_fd(int fd, char *str);
int			ft_atoi(const char *str);
int			is_dig(char *s);

/*PARSE*/

int			parse_error(int ac, char **av);
void		parse(t_global *global, int ac, char **av);
int			only_1(t_global *global);
void		init_philo(t_global *global);

/*COLORS*/

void		print_color(char *message, t_philo *p);
int			hsl_to_r(double h, double s, double l);
int			hsl_to_g(double h, double s, double l);
int			hsl_to_b(double h, double s, double l);

/*TIME*/

long int	get_time(void);
void		ft_usleep(long int ms, t_philo *p);

static inline int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static inline double	ft_fmod(double x, double y)
{
	return (x - y * (double)(int)(x / y));
}

static inline double	ft_fabs(double x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

#endif