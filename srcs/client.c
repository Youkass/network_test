/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:37:10 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/07 13:12:45 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.h"

int	main(void)
{
	t_server	client;
	char		fix_msg[90];
	int			size;
	
	client.socket = socket(AF_INET, SOCK_STREAM, 0);
	client.addr.sin_addr.s_addr = inet_addr("10.11.6.21");
	client.addr.sin_family = AF_INET;
	client.addr.sin_port = htons(30000);
	connect(client.socket, (const struct sockaddr *)&(client.addr), sizeof(client.addr));
	printf("connecté\n");
/*=============================================================================*/
	recv(client.socket, &size, sizeof(size), 0);
	printf("size : %d\n", size);
	
	recv(client.socket, &fix_msg, sizeof(fix_msg), 0);
	printf("%s\n", fix_msg);

	close(client.socket);

	return (0);
}
