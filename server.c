/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:22:27 by osarikay          #+#    #+#             */
/*   Updated: 2024/01/10 19:31:09 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "minitalk.h"

void	pid_frame(void)
{
	if (1)
	{
		write(1, "\033[1;33mPID HAZIRLANIYOR : ", 26);
		usleep(500000);
		write(1, ". ", 2);
		usleep(500000);
		write(1, ". ", 2);
		usleep(500000);
		write(1, ". ", 2);
		usleep(1000000);
		write(1, "\n", 1);
		write(1, "\n", 1);
		write(1, "\033[1;32mPID HAZIRLANDI : \033[32m✅", 32);
		usleep(700000);
		write(1, "\n\033[1;0m\n#########################\n#\
                       #\n#     \033[34mPID --> ", 79);
		ft_putnbr(getpid());
		write(1, "\033[1;0m     #\n#                       #\n\
#########################\n\n\033[0m", 69);
	}
}

void	ft_handle(int sig)
{
	static int	bit = 128;
	static int	ch = 0;
	static int	flag = 0;

	if (sig == SIGUSR1)
		ch = ch + bit;
	bit /= 2;
	if (bit == 0)
	{
		if (ch < 128)
		{
			write(1, &ch, 1);
			flag = 0;
		}
		else if(!flag)
		{
			write(1, "\033[1;31mThis character is UNICODE\033[0m", 36);
			flag = 1;
			bit = 128;
			ch = 0;
			return;
		}
		bit = 128;
		ch = 0;
	}
}

int	main(void)
{
	pid_frame();
	signal(SIGUSR1, ft_handle);
	signal(SIGUSR2, ft_handle);
	while (1)
		pause();
}
