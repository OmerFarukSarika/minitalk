/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:29:29 by osarikay          #+#    #+#             */
/*   Updated: 2024/01/10 18:23:39 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include <signal.h>
#include <unistd.h>
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
		usleep(200000);
		write(1, "\033[2J\033[H", 7);
		i++;
	}
}

static	int	pid_check(int pid)
{
	if (pid == -1 || (pid >= 0 && pid <= 9))
	{
		write(1, "\033[1;31m", 7);
		pid_frame(40, "*      Please enter a valid PID!       *");
		exit(0);
	}
	if (kill(pid, 0) == -1)
	{
		write(1, "\033[1;31m", 7);
		pid_frame(31, "*     This PID is wrong!      *");
		exit(0);
	}
	return (0);
}

static	void	received_signal(int sig)
{
	if (sig == SIGUSR1)
	{
		char *a = "*     Checking the status of the message . . . .    *";
		char *b = "*     Your message has been sent successfully.      *";
	
		write(1, "\033[1;33m", 8);
		pid_frame(53, a);
		write(1, "\033[0m", 8);
		write(1, "\033[1;32m", 8);
		pid_frame(53, b);
		write(1, "\033[0m", 8);
	}
}

void	ft_sendbit(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c >> bit & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit--;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	int		i;

	i = 0;
	if (argc != 3)
	{
		write(1, "\033[1;31m", 7);
		pid_frame(49,  "*    Check Argument ./client <PID> <String>     *");
		exit(0);
	}
	signal(SIGUSR1, received_signal);
	pid = atoi(argv[1]);
	pid_check(pid);
	message = "\033[1;35mClient'ten Gelen Mesaj -->\033[0m ";
	while (message[i])
		ft_sendbit(pid, message[i++]);
	while (*argv[2])
		ft_sendbit(pid, *(argv[2]++));
	ft_sendbit(pid, '\n');
	usleep(100);
	ft_sendbit(pid, '\0');
	return (0);
}
