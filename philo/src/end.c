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

int	end_monitor(t_info *info)
{
	int	i;
	int	time_die;

	time_die = info->time_die;
	while (!info->enough)
	{
		i = -1;
		while (++i < info->nb_philo && check_end(info))
		{
			pthread_mutex_lock(&info->time_check);
			if ((philo_time() - info->philos[i].last_meal_time) > time_die)
			{
				print_death(info, &info->philos[i]);
				pthread_mutex_lock(&info->exit);
				info->end = 1;
				pthread_mutex_unlock(&info->exit);
			}
			pthread_mutex_unlock(&info->time_check);
			philo_sleep(info, 1);
		}
		if (info->end)
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
		pthread_join(info->philos[i].thread, NULL);
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
	pthread_mutex_destroy(&info->meals_eaten);
	pthread_mutex_destroy(&info->time_check);
	pthread_mutex_destroy(&info->satiated);
	pthread_mutex_destroy(&info->starvation);
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->exit);
	free(info->forks);
	return (SUCCESS);
}

int	end(t_info *info)
{
	int	meals_req;

	end_monitor(info);
	end_threads(info);
	end_mutexes(info);
	meals_req = info->nb_meals_req;
	if (info->satiated_nb >= info->nb_philo && info->end != 1 && meals_req == 1)
		printf(END1, BG, info->satiated_nb, info->nb_meals_req, RESET);
	if (info->satiated_nb >= info->nb_philo && info->end != 1 && meals_req > 1)
		printf(END2, BG, info->satiated_nb, info->nb_meals_req, RESET);
	return (SUCCESS);
}
