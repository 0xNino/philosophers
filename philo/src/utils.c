/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:54:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/16 09:41:31 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error(char *errmsg, int errnum)
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

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error("Error: wrong argument count\n", FAILURE));
	i = 1;
	while (i < argc)
	{
		if (isnumber(argv[i]) == FAILURE)
			return (error("Error: invalid arguments\n", FAILURE));
		i++;
	}
	return (SUCCESS);
}
