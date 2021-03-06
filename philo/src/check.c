/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:49:21 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/21 16:38:21 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (philo_error("Error: wrong argument count\n", FAILURE));
	i = 1;
	while (i < argc)
	{
		if (isnumber(argv[i]) == FAILURE)
			return (philo_error("Error: invalid arguments\n", FAILURE));
		i++;
	}
	return (SUCCESS);
}

int	check_end(t_info *info)
{
	int	exit;

	exit = FALSE;
	pthread_mutex_lock(&info->exit);
	if (info->end)
		exit = TRUE;
	pthread_mutex_unlock(&info->exit);
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
	if (meals_req <= 0)
		return (SUCCESS);
	pthread_mutex_lock(&info->meals_eaten);
	while (i < nb_philo && philos[i].nb_meals >= max(meals_req - 1, 1))
		i++;
	if (i == info->nb_philo)
		info->enough = 1;
	pthread_mutex_unlock(&info->meals_eaten);
	return (SUCCESS);
}

void	*check_satiated(t_info *info, t_philo *philo)
{
	int	nb_philo;

	nb_philo = info->nb_philo;
	pthread_mutex_lock(&info->meals_eaten);
	pthread_mutex_lock(&info->satiated);
	if (philo->nb_meals == info->nb_meals_req && info->satiated_nb < nb_philo)
	{
		info->satiated_nb++;
		if (info->satiated_nb >= info->nb_philo)
		{
			pthread_mutex_unlock(&info->meals_eaten);
			return (philo_unlock(&info->satiated));
		}
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->meals_eaten);
	return ((void *) FAILURE);
}
