/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:37:10 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/04 14:34:06 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.h"

int	main(void)
{
	t_server	client;
	t_user		user;

	client.socket = socket(AF_INET, SOCK_STREAM, 0);
	client.addr.sin_addr.s_addr = inet_addr("10.12.6.1");
	client.addr.sin_family = AF_INET;
	client.addr.sin_port = htons(30000);
	connect(client.socket, (const struct sockaddr *)&(client.addr), sizeof(client.addr));
	printf("connecté\n");
/*=============================================================================*/
	recv(client.socket, &user, sizeof(user), 0);
	printf("%s %d\n", user.name, user.age);
	close(client.socket);

	return (0);
}
