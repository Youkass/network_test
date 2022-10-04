/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:28:09 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/04 13:50:54 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

typedef struct	s_user
{
	char	name[30];
	int		age;
}	t_user;

typedef struct	s_server
{
	int					socket;
	struct sockaddr_in	addr;
}	t_server;
