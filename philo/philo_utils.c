/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:53:11 by cjunker           #+#    #+#             */
/*   Updated: 2023/01/07 17:39:06 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

int	is_dig(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+')
		i++;
	while (s[i])
	{
		if (!is_digit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long int	r;
	long int	sign;
	long int	i;

	r = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * sign);
}
