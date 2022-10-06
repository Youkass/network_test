/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:22:28 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/06 14:15:14 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub.h"
#include <unistd.h>

void	get_key(int keycode)
{
	if (keycode == A)
		_var()->key.a = 1;
	if (keycode == W)
		_var()->key.w = 1;
	if (keycode == S)
		_var()->key.s = 1;
	if (keycode == D)
		_var()->key.d = 1;
	if (keycode == ESC)
		_var()->key.esc = 1;
}

int	ft_release(int keycode)
{
	if (keycode == A)
		_var()->key.a = 0;
	if (keycode == W)
		_var()->key.w = 0;
	if (keycode == S)
		_var()->key.s = 0;
	if (keycode == D)
		_var()->key.d = 0;
	if (keycode == ESC)
		_var()->key.esc = 0;
	return (0);
}

void	ft_init_player_pos(void)
{
	//_player()->angle = 0;
	_player()->x = 5;
	_player()->y = 3;
	_player()->dx = -1;
	_player()->dy = 0;
	_ray()->plane = (t_vector2F){0, -0.66};
	_ray()->time = 0;
	_ray()->old_time = 0;
	_player()->hb.hit.radius = 0.5;
	_ray()->max_y = -1;
	_ray()->min_y = -1;
	
}

void	ft_print_tab(char **s)
{
	int	i;
	int	line;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		line = ft_strlen(s[i]);
		++i;
	}
	_img()->map_width = line;
	_img()->map_height = i;
}

int	ft_hook(int keycode)
{
	get_key(keycode);
	//if (_var()->mode == GAME)
	//	ft_game_hook(keycode);
	if (_var()->mode == MENU)
		menu_hook(keycode);
	return (0);
}

int	ft_mouse_hook(int keycode)
{
	if (_var()->mode == MENU)
		menu_mouse_hook(keycode);
	return (0);
}

int	ft_loop_hook(void)
{
	ft_fps();
	key_hook();
	if (_var()->mode == GAME)
		ft_loop();
	else if (_var()->mode == MENU)
		menu_loop();
	return (0);
}

int	ft_mouse_release(int keycode)
{
	if (keycode == 1)
		_var()->key.mouse = 0;
	return (0);
}

int	ft_game(void)
{
	mlx_hook(_mlx()->mlx_win, 2, 1L << 0, &ft_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 3, 1L << 1, &ft_release, NULL);
	mlx_loop_hook(_mlx()->mlx, &ft_loop_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 5, 1L << 3, &ft_mouse_release, NULL);
	mlx_mouse_hook(_mlx()->mlx_win, &menu_mouse_hook, NULL);
	return (0);
}

void	init_key(void)
{
	_var()->key.a = 0;
	_var()->key.d = 0;
	_var()->key.esc = 0;
	_var()->key.mouse = 0;
	_var()->key.s = 0;
	_var()->key.w = 0;
}

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

int main(int argc, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	_ray()->clock = start_clock();
	if (fd < 0)
		exit(139);
	_img()->map = resize_map(ft_split(read_file(fd), '\n'));
	if (!_img()->map)
		exit(139);
	ft_print_tab(_img()->map);
	(void)argc;
	ft_init_client();
	ft_init_mlx();
	ft_init_img();
	ft_init_player_pos();
	ft_malloc_map();
	init_key();
	gen_menu_images();
	_var()->mode = GAME;
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}