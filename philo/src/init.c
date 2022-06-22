/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:45:46 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/21 16:37:33 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_atoi(const char *str)
{
	long	nbr;
	int		minus;

	nbr = 0;
	minus = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			minus = 1;
	while ('0' <= *str && *str <= '9')
	{
		if ((nbr > (__LONG_MAX__ - *str + '0') / 10) && minus)
			return (0);
		if ((nbr > (__LONG_MAX__ - *str + '0') / 10) && !minus)
			return (-1);
		nbr = 10 * nbr + (*str - '0');
		str++;
	}
	if (minus)
		return ((int)-nbr);
	return ((int)nbr);
}

int	init_info(char **argv, t_info *info)
{
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->nb_meals_req = ft_atoi(argv[5]);
	else
		info->nb_meals_req = 0;
	info->philos = malloc (sizeof(t_philo) * info->nb_philo);
	if (!info->philos)
		return (philo_error("Error: philos malloc failed\n", FAILURE));
	info->death = 0;
	info->enough = 0;
	info->satiated_nb = 1;
	if (info->nb_philo < 1 || info->nb_philo > 250)
		return (philo_error("Error: invalid philosopher count\n", FAILURE));
	if (info->time_die < 0 || info->time_eat < 0 || info->time_sleep < 0)
		return (philo_error("Error: invalid time values\n", FAILURE));
	if (info->nb_meals_req < 0)
		return (philo_error("Error: invalid required meal count\n", FAILURE));
	return (SUCCESS);
}

int	init_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		info->philos[i].id = i;
		info->philos[i].nb_meals = 0;
		info->philos[i].left_fork_id = i;
		info->philos[i].right_fork_id = (i + 1) % info->nb_philo;
		info->philos[i].last_meal_time = 0;
		info->philos[i].info = info;
	}
	return (SUCCESS);
}

int	init_mutex(t_info *info)
{
	int				i;

	i = -1;
	info->forks = malloc (sizeof(pthread_mutex_t) * info->nb_philo);
	if (!info->forks)
		return (philo_error("Error: info->forks malloc failed\n", FAILURE));
	while (++i < info->nb_philo)
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (philo_error("Error: mutex init failed\n", FAILURE));
	if (pthread_mutex_init(&info->write, NULL))
		return (philo_error("Error: mutex init failed\n", FAILURE));
	if (pthread_mutex_init(&info->alive, NULL))
		return (philo_error("Error: mutex init failed\n", FAILURE));
	if (pthread_mutex_init(&info->meals_eaten, NULL))
		return (philo_error("Error: mutex init failed\n", FAILURE));
	if (pthread_mutex_init(&info->time_check, NULL))
		return (philo_error("Error: mutex init failed\n", FAILURE));
	if (pthread_mutex_init(&info->satiated, NULL))
		return (philo_error("Error: mutex init failed\n", FAILURE));
	return (SUCCESS);
}
