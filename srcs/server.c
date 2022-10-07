/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:31:12 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/07 13:04:29 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.h"

void	ft_strcpy(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		++i;
	}
	s2[i] = 0;
}

int	main(void)
{
	t_server	server;
	t_server	client;
	socklen_t	csize;
	char		msg[]="Salut Darian, t'es beau aujourd'hui\n";
	int			size;

	server.socket = socket(AF_INET, SOCK_STREAM, 0);
	server.addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server.addr.sin_family = AF_INET;
	server.addr.sin_port = htons(30000);
/*===========================================================================*/
	bind(server.socket, (const struct sockaddr *)&(server.addr), sizeof(server.addr));
	printf("bind : %d\n", server.socket);
	printf("addr : %d\n", INADDR_ANY);
/*===========================================================================*/
	listen(server.socket, 5);
	printf("listen\n");
/*===========================================================================*/
	size = strlen(msg);
	printf("size : %d\n", size);
	csize = sizeof(client.addr);
	client.socket = accept(server.socket, (struct sockaddr *)&(client.addr), &csize);
	printf("accepted\n");
/*===========================================================================*/
	send(client.socket, &size, sizeof(size), 0);
	send(client.socket, &msg, sizeof(msg), 0);
	close(client.socket);
	close(server.socket);
	return (0);
}
