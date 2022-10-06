

t_obj	ft_get_data(t_obj *player)
{
	t_obj	data;

	data.id = player->id;
	data.x = player->x;
	data.y = player->y;
	data.c = player->c;
	data.dx = player->dx;
	data.dy = player->dy;
	data.old_dx = player->old_dx;
	data.old_dy = player->old_dy;
	data.angle = player->angle;
	data.move_speed = player->move_speed;
	data.rot_speed = player->rot_speed;
	data.hb = player->hb;
	return (data);
}
typedef struct	s_server
{
	int					socket;
	struct sockaddr_in	addr;
}	t_server;
/*SERVEUR */
void	ft_init_server(void)
{
	socklen_t	csize;
	t_server	server;
	t_server	client;

	server.socket = socket(AF_INET, SOCK_STREAM, 0);
	server.addr.sin_addr.s_addr = inet_addr("10.12.6.1");
	server.addr.sin_family = AF_INET;
	server.addr.sin_port = htons(30000);
	bind(server.socket, (const struct sockaddr *)&(server.addr), sizeof(server.addr));
	printf("bind : %d\n", server.socket);
	listen(server.socket, 5);
	printf("listen\n");
	csize = sizeof(client.addr);
	client.socket = accept(server.socket, (struct sockaddr *)&(client.addr), &csize);
	_img()->socket = client.socket;
	printf("accepted\n");
}

	t_obj	player;

	player = ft_get_data(_player());
	send(_img()->socket, &player, sizeof(player), 0);
	printf("my player.x : %f my player.y : %f\n", player.x, player.y);
	recv(_img()->socket, &player, sizeof(player), 0);
	printf("other player.x : %f other player.y : %f\n", player.x, player.y);
/*CLIENT */

void	ft_init_client(void)
{
	t_server	client;

	client.socket = socket(AF_INET, SOCK_STREAM, 0);
	client.addr.sin_addr.s_addr = inet_addr("10.12.6.1");
	client.addr.sin_family = AF_INET;
	client.addr.sin_port = htons(30000);
	connect(client.socket, (const struct sockaddr *)&(client.addr), sizeof(client.addr));
	printf("connecté\n");
	_img()->socket = client.socket;
}

	t_obj	player;

	recv(_img()->socket, &player, sizeof(player), 0);
	printf("other player.x : %f other player.y : %f\n", player.x, player.y);
	player = ft_get_data(_player());
	send(_img()->socket, &player, sizeof(player), 0);
	printf("my player.x : %f my player.y : %f\n", player.x, player.y);
