/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:14:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/21 16:37:33 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) void_philo;
	info = philo->info;
	if (info->nb_philo == 1)
		return (SUCCESS);
	if (philo->id % 2)
		philo_sleep(info, 50);
	while (check_death(info))
	{
		philo_meal(info, philo);
		pthread_mutex_lock(&info->meals_eaten);
		if (info->enough)
		{
			pthread_mutex_unlock(&info->meals_eaten);
			break ;
		}
		pthread_mutex_unlock(&info->meals_eaten);
		print_sleep(info, philo);
		philo_sleep(info, info->time_sleep);
		print_think(info, philo);
	}
	return (SUCCESS);
}

static int	one_philo(t_info *info)
{
	t_philo	philo;

	philo = info->philos[0];
	if (pthread_create(&philo.thread_id, NULL, routine, &philo))
		return (philo_error("Error: phtread_create failed\n", FAILURE));
	print_fork(info, &philo, philo.left_fork_id);
	philo_sleep(info, info->time_die);
	print_death(info, &philo);
	end_threads(info);
	end_mutexes(info);
	return (SUCCESS);
}

static int	death_monitor(t_info *info, t_philo *philo)
{
	int	i;

	while (!info->enough)
	{
		i = -1;
		while (++i < info->nb_philo && check_death(info))
		{
			pthread_mutex_lock(&info->time_check);
			if ((philo_time() - philo->last_meal_time) > info->time_die)
			{
				print_death(info, philo);
				pthread_mutex_lock(&info->alive);
				info->death = 1;
				pthread_mutex_unlock(&info->alive);
			}
			pthread_mutex_unlock(&info->time_check);
			philo_sleep(info, 10);
		}
		if (info->death)
			break ;
		check_enough(info);
	}
	return (SUCCESS);
}

static int	philo(t_info *info)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = info->philos;
	info->start_time = philo_time();
	printf("%s%s%s\n", WHITE, DASH, DEFAULT);
	if (info->nb_philo == 1)
		return (one_philo(info));
	while (++i < info->nb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]))
			return (philo_error("Error: phtread_create failed\n", FAILURE));
		pthread_mutex_lock(&info->time_check);
		philos[i].last_meal_time = philo_time();
		pthread_mutex_unlock(&info->time_check);
	}
	death_monitor(info, info->philos);
	end_threads(info);
	end_mutexes(info);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_args(argc, argv))
		return (FAILURE);
	if (init_info(argv, &info))
		return (FAILURE);
	if (init_philo(&info))
		return (FAILURE);
	if (init_mutex(&info))
		return (FAILURE);
	if (philo(&info))
		return (FAILURE);
	return (SUCCESS);
}
