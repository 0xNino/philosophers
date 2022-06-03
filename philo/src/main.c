/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:14:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/03 13:38:05 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	error(char *errmsg, int errnum)
{
	printf("%s", errmsg);
	return (errnum);
}

static int	isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			i++;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error("Error: wrong argument count\n", 1));
	i = 1;
	while (i < argc)
	{
		if (isnumber(argv[i]) == FAILURE)
			return (error("Error: invalid arguments\n", 1));
		i++;
	}
	return (SUCCESS);
}

static int	init_info(char **argv, t_info *info)
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
	info->death = 0;
	info->enough = 0;
	if (info->nb_philo < 1 || info->nb_philo > 200)
		return (error("Error: invalid philosopher count\n", FAILURE));
	if (info->time_die < 0 || info->time_eat < 0 || info->time_sleep < 0)
		return (error("Error: invalid time values\n", FAILURE));
	if (info->nb_meals_req <= 0)
		return (error("Error: invalid required meal count\n", FAILURE));
	return (SUCCESS);
}

static int	init_philos(char **argv, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].nb_meals = 0;
		info->philos[i].last_meal_time = 0;



	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	philo;
	
	if (check_args(argc, argv))
		return (FAILURE);
	if (init_info(argv, &info))
		return (FAILURE);
	return (SUCCESS);
}
