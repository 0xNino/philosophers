/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:49:21 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/16 08:53:40 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_info *info)
{
	int	exit;

	exit = FALSE;
	pthread_mutex_lock(&info->alive);
	if (info->death)
		exit = TRUE;
	pthread_mutex_unlock(&info->alive);
	return (exit);
}

int	check_enough(t_info *info)
{
	int		i;
	int		meals_req;
	int		nb_philo;
	t_philo	*philos;

	i = 0;
	meals_req = info->nb_meals_req;
	nb_philo = info->nb_philo;
	philos = info->philos;
	pthread_mutex_lock(&info->meals_eaten);
	while (meals_req > 0 && i < nb_philo && philos[i].nb_meals >= meals_req - 1)
		i++;
	if (i == info->nb_philo)
		info->enough = 1;
	pthread_mutex_unlock(&info->meals_eaten);
	return (SUCCESS);
}
