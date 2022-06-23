/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:49:17 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/16 09:11:10 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	end_monitor(t_info *info, t_philo *philo)
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
			philo_sleep(info, 5);
		}
		if (info->death)
			break ;
		check_enough(info);
	}
	return (SUCCESS);
}

int	end_threads(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		pthread_join(info->philos[i].thread_id, NULL);
	pthread_join(info->satiated_id, NULL);
	free(info->philos);
	return (SUCCESS);
}

int	end_mutexes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		pthread_mutex_destroy(&info->forks[i]);
	pthread_mutex_destroy(&info->alive);
	pthread_mutex_destroy(&info->meals_eaten);
	pthread_mutex_destroy(&info->time_check);
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->satiated);
	pthread_mutex_destroy(&info->starvation);
	free(info->forks);
	return (SUCCESS);
}
