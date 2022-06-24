/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:28:46 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/24 11:28:46 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine_satiated(void *void_info)
{
	t_info	*info;
	int		i;

	info = (t_info *) void_info;
	while (check_death(info))
	{
		philo_sleep(info, 5);
		i = 0;
		pthread_mutex_lock(&info->satiated);
		if (info->satiated_nb == info->nb_philo)
		{
			pthread_mutex_lock(&info->alive);
			info->death = 2;
			pthread_mutex_unlock(&info->alive);
			break ;
		}
		return (philo_unlock(&info->satiated));
	}
	pthread_mutex_unlock(&info->satiated);
	return ((void *) FAILURE);
}

void	*routine_service(void *void_info)
{
	t_info	*info;

	info = (t_info *) void_info;
	while (check_death(info))
	{
		if (info->served >= info->nb_philo)
		{
			pthread_mutex_lock(&info->service);
			info->current++;
			info->served = 0;
			pthread_mutex_unlock(&info->service);
		}
		philo_sleep(info, 5);
	}
	return (SUCCESS);
}

void	*routine_philo(void *void_philo)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) void_philo;
	info = philo->info;
	if (info->nb_philo == 1)
		return (SUCCESS);
	if (philo->id % 2)
		philo_sleep(info, 200);
	while (check_death(info))
	{
		while (philo->nb_meals != info->current && (philo->starvation_time
				- (philo_time() - info->start_time) > info->time_eat / 2))
			philo_sleep(info, 5);
		philo_meal(info, philo);
		if (check_satiated(info, philo) == SUCCESS)
			return (SUCCESS);
		if (info->enough)
			return (philo_unlock(&info->meals_eaten));
		print_sleep(info, philo);
		philo_sleep(info, info->time_sleep);
		print_think(info, philo);
	}
	return (SUCCESS);
}
