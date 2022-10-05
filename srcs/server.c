/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:31:12 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/05 17:51:58 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.h"

int	main(void)
{
	t_server	server;
	t_server	client;
	socklen_t	csize;
	t_user		user = {.name = "Arthur", .age = 42};
	char		msg[]="Salut Valentin, t'es beau aujourd'hui\n";
	char		fix_msg[]="Salut Valentin, t'es beau aujourd'hui\n";
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
	csize = sizeof(client.addr)fix_;
	client.socket = accept(server.socket, (struct sockaddr *)&(client.addr), &csize);
	printf("accepted\n");
/*===========================================================================*/
	send(client.socket, &size, sizeof(size), 0);
	send(client.socket, &msg, sizeof(msg), 0);
	send(client.socket, &fix_msg, sizeof(fix_msg), 0);
	close(client.socket);
	close(server.socket);
	return (0);
}
