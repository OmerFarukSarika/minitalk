/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:17:29 by osarikay          #+#    #+#             */
/*   Updated: 2024/01/10 12:28:40 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	rt;
	int	sign;
	int	i;

	rt = 0;
	sign = 1;
	i = 0;
	while (str[i] == 9 || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 0 && str[i] <= 9)
	{
		rt = (rt * 10) + (str[i] - '0');
		i++;
	}
	return (rt * sign);
}

void	ft_putnbr(int nbr)
{
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
	{
		nbr += 48;
		write(1, &nbr, 1);
	}
}

int ft_strlen(char *str)
{
	int i;
	i = 0;

	while (str[i])
		i++;
	return (i);
}
