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

int	end_threads(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		pthread_join(info->philos[i].thread_id, NULL);
	pthread_join(info->satiated_monitor, NULL);
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
