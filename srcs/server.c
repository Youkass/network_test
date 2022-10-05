/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:31:12 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/05 11:42:40 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.h"

int	main(void)
{
	t_server	server;
	t_server	client;
	socklen_t	csize;
	t_user		user = {.name = "Arthur", .age = 42};
	char		msg[]="Salut Archie, t'es beau aujourd'hui\n";

	server.socket = socket(AF_INET, SOCK_STREAM, 0);
	server.addr.sin_addr.s_addr = inet_addr("10.12.7.1");
	server.addr.sin_family = AF_INET;
	server.addr.sin_port = htons(30000);
/*===========================================================================*/
	bind(server.socket, (const struct sockaddr *)&(server.addr), sizeof(server.addr));
	printf("bind : %d\n", server.socket);
/*===========================================================================*/
	listen(server.socket, 5);
	printf("listen\n");
/*===========================================================================*/
	csize = sizeof(client.addr);
	client.socket = accept(server.socket, (struct sockaddr *)&(client.addr), &csize);
	printf("accepted\n");
/*===========================================================================*/
	send(client.socket, &msg, sizeof(msg), 0);
	close(client.socket);
	close(server.socket);
	return (0);
}
