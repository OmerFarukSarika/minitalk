/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:20:01 by osarikay          #+#    #+#             */
/*   Updated: 2024/01/10 18:23:58 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	pid_frame(int loop, char *str)
{
	char *s;
	int	i;
	int j;
	
	s = ft_strdup(str);
	j = 0;
	i = 0;
	while (i <= loop)
	{
		while (j++ < i)	
			write(1, "*", 1);
		j = 0;
		write(1, "\n", 1);
		write(1, s, i);
		write(1, "\n", 1);
		while (j++ < i)	
			write(1, "*", 1);
		j = 0;
		usleep(150000);
		write(1, "\033[2J\033[H", 7);
		i++;
	}
	free(s);
}
void	frame(int x)
{
	char *a = "*     PID HAZIRLANIYOR : . . . .   *";
	char *b = "*     PID HAZIRLANDI : OK!       *";
	char *c = "*     --> --> PID --> -->        *";
	if (x == 1)
	{
		write(1, "\033[1;33m", 7);
		pid_frame(36, a);
		frame(2);
	}
	if (x == 2)
	{
		write(1, "\033[1;32m", 7);
		pid_frame(34, b);
		frame(3);
	}
	if (x == 3)
	{
		write(1, "\033[1;34m", 7);
		pid_frame(34, c);
		write(1, "**********************************\n\
*   --> --> PID --> -->  ", 60);
		putnbr(getpid());
		write(1, "   *\n**********************************", 39);
		write(1, "\n\033[0m", 5);
	}
}


void	ft_handle(int sig, siginfo_t *info, void *context)
{
	static int	bit = 128;
	static int	c = 0;

	(void)context;
	if (sig == SIGUSR1)
		c = c + bit;
	bit = bit / 2;
	if (bit == 0)
	{
		write(1, &c, 1);
		if (c == '\0')
			kill(info->si_pid, SIGUSR1);
		bit = 128;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	frame(1);
	act.sa_sigaction = ft_handle;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
