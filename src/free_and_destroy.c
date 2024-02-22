/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:55:35 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/21 12:37:46 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_and_destroy(t_data *data, t_philo *philo, int out)
{
	int	i;

	i = -1;
	if (philo)
		free(philo);
	if (data)
	{
		if (data->fork)
		{
			while (++i < data->philos_num)
				pthread_mutex_destroy(&data->fork[i]);
			free(data->fork);
		}
		pthread_mutex_unlock(&data->print);
		pthread_mutex_destroy(&data->print);
		pthread_mutex_unlock(&data->start);
		pthread_mutex_destroy(&data->start);
		free(data);
	}
	return (out);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = malloc(count * (sizeof(char) * size));
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, (count * size));
	return (ptr);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = ((unsigned char)c);
		i++;
	}
	return (b);
}

int	ft_atoi(char *str)
{
	int	num;
	int	sign;
	int	i;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	return (num * sign);
}
