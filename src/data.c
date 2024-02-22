/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:45:17 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/21 14:41:06 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (free_and_destroy(data, NULL, 0));
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (free_and_destroy(data, NULL, 0));
	if (pthread_mutex_init(&data->start, NULL) != 0)
		return (free_and_destroy(data, NULL, 0));
	return (0);
}

int	giving_data(t_data *data, char **argv)
{
	data->someone_died = 0;
	data->start_time = get_time();
	data->philos_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->fork = ft_calloc(data->philos_num, sizeof(pthread_mutex_t));
	if (!data->fork)
		exit(1);
	return (init_mutex(data));
}
