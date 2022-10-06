/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:37:10 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/06 12:37:10 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.h"

int	main(void)
{
	t_server	client;
	t_user		user;
	char		*msg;
	//char		fix_msg[90];
	int			size;
	
	(void)user;
	client.socket = socket(AF_INET, SOCK_STREAM, 0);
	client.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	client.addr.sin_family = AF_INET;
	client.addr.sin_port = htons(30000);
	connect(client.socket, (const struct sockaddr *)&(client.addr), sizeof(client.addr));
	printf("connecté\n");
/*=============================================================================*/
	recv(client.socket, &size, sizeof(size), 0);
	printf("size : %d\n", size);
	
//	recv(client.socket, &fix_msg, sizeof(fix_msg), 0);
//	printf("%s\n", fix_msg);

	msg = malloc(sizeof(char) * (size + 1));
	recv(client.socket, &msg, sizeof(msg), 0);
	printf("msg : %s\n", msg);
	close(client.socket);

	return (0);
}
