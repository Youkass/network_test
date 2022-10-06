/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:31:12 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/06 12:37:14 by yobougre         ###   ########.fr       */
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
	t_user		user = {.name = "Arthur", .age = 42};
	char		msg[]="Salut Darian, t'es beau aujourd'hui\n";
	char		*fix_msg;
	int			size;

	server.socket = socket(AF_INET, SOCK_STREAM, 0);
	server.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.addr.sin_family = AF_INET;
	server.addr.sin_port = htons(30000);
	(void)user;
/*===========================================================================*/
	bind(server.socket, (const struct sockaddr *)&(server.addr), sizeof(server.addr));
	printf("bind : %d\n", server.socket);
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
	fix_msg = malloc(sizeof(char) * strlen(msg) + 1);
	ft_strcpy(msg, fix_msg);
	printf("before send : %s\n", fix_msg);
	send(client.socket, &size, sizeof(size), 0);
	//send(client.socket, &msg, sizeof(msg), 0);
	send(client.socket, &fix_msg, sizeof(fix_msg), 0);
	close(client.socket);
	close(server.socket);
	return (0);
}
