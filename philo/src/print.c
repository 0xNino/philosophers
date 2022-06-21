/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:36:53 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/21 16:33:34 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_death(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->write);
	if (check_death(info))
	{
		printf("%s  💀\t%li ms\t\tPhilo #%d\thas died\n%s", RED,
			philo_time() - info->start_time, philo->id + 1, DEFAULT);
		printf("%s%s\n%s", WHITE, DASH, DEFAULT);
	}
	pthread_mutex_unlock(&info->write);
}

void	print_think(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->write);
	if (check_death(info))
	{
		printf("%s  💭\t%li ms\t\tPhilo #%d\tis thinking\n%s", WHITE,
			philo_time() - info->start_time, philo->id + 1, DEFAULT);
		printf("%s%s\n%s", WHITE, DASH, DEFAULT);
	}
	pthread_mutex_unlock(&info->write);
}

void	print_sleep(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->write);
	if (check_death(info))
	{
		printf("%s  💤\t%li ms\t\tPhilo #%d\tis sleeping\n%s", WHITE,
			philo_time() - info->start_time, philo->id + 1, DEFAULT);
		printf("%s%s\n%s", WHITE, DASH, DEFAULT);
	}
	pthread_mutex_unlock(&info->write);
}

void	print_fork(t_info *info, t_philo *philo, int count)
{
	pthread_mutex_lock(&info->write);
	if (check_death(info))
	{
		printf("%s  🥄\t%li ms\t\tPhilo #%d\thas taken the fork #%d\n%s", WHITE,
			philo_time() - info->start_time, philo->id + 1, count, DEFAULT);
		printf("%s%s\n%s", WHITE, DASH, DEFAULT);
	}
	pthread_mutex_unlock(&info->write);
}

void	print_meal(t_info *info, t_philo *philo, int count)
{
	pthread_mutex_lock(&info->write);
	if (check_death(info))
	{
		if (info->nb_meals_req <= 0)
			printf("%s  🍝\t%li ms\t\tPhilo #%d\tis eating his #%d meal\n%s", WHITE,
				philo_time() - info->start_time, philo->id + 1, count, DEFAULT);
		else if (count >= info->nb_meals_req)
			printf("%s  🍝\t%li ms\t\tPhilo #%d\tis eating his #%d/%d meal\n%s",
				GREEN, philo_time() - info->start_time, philo->id + 1, count,
				info->nb_meals_req, DEFAULT);
		else
			printf("%s  🍝\t%li ms\t\tPhilo #%d\tis eating his #%d/%d meal\n%s",
				YELLOW, philo_time() - info->start_time, philo->id + 1, count,
				info->nb_meals_req, DEFAULT);
		printf("%s%s\n%s", WHITE, DASH, DEFAULT);
	}
	pthread_mutex_unlock(&info->write);
}
