/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:14:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/16 09:43:57 by 0xNino           ###   ########.fr       */
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
		usleep(info->time_sleep + 50);
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
		philo_print(info, info->philos->id, "is sleeping", -1);
		philo_sleep(info, info->time_sleep);
		philo_print(info, info->philos->id, "is thinking", -1);
	}
	return (SUCCESS);
}

static int	one_philo(t_info *info)
{
	t_philo	philo;

	philo = info->philos[0];
	if (pthread_create(&philo.thread_id, NULL, routine, &philo))
		return (error("Error: phtread_create failed\n", FAILURE));
	philo_print(info, 0, "has taken the fork", philo.left_fork_id);
	philo_sleep(info, info->time_die);
	philo_print(info, 0, "has died", -1);
	end_threads(info);
	end_mutexes(info);
	return (SUCCESS);
}

static int	death_monitor(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (!info->enough)
	{
		while (++i < info->nb_philo && check_death(info))
		{
			pthread_mutex_lock(&info->time_check);
			if ((philo_time() - philo->last_meal_time) > info->time_die)
			{
				philo_print(info, philo->id, "has died", -1);
				pthread_mutex_lock(&info->alive);
				info->death = 1;
				pthread_mutex_unlock(&info->alive);
			}
			pthread_mutex_unlock(&info->time_check);
			usleep(50);
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
	if (info->nb_philo == 1)
		return (one_philo(info));
	while (++i < info->nb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]))
			return (error("Error: phtread_create failed\n", FAILURE));
		pthread_mutex_lock(&info->time_check);
		info->philos[i].last_meal_time = philo_time();
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
