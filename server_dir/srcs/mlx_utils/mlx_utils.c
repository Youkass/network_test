/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:29:30 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/06 13:24:55 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub.h" 
/*
===============================================================================
The following function will initialize our mlx pointer and our mlx window
===============================================================================
*/
void	ft_init_mlx()
{
	_mlx()->mlx = mlx_init();
	_mlx()->mlx_win = mlx_new_window(_mlx()->mlx, WIN_W, WIN_H, PRG_NAME);
}

/*
===============================================================================
The following function will initialize our frames inside the window
    if (argc != 2)
    {
        printf("Arguments error\n");
        return (1);
    }
===============================================================================
*/
void	ft_init_img()
{
	_img()->img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_img()->addr = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
		&(_img()->line_length), &(_img()->endian));
	_img()->bits_per_pixel /= 8;
//	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}

/*
===============================================================================
As you can see, if you followed the @Harm_smits tutorial, our pixel put function
is quite different, in our pixel_put function you can see a condition that will
prevent any segmentation fault that could  occure if you tried to put a pixel
outside the window.
-> this function will be call by other functions before pushing the image into the window
===============================================================================
*/
void	ft_pixel_put(float x, float y, int color)
{
	t_data	*img;
	char	*dst;

	img = _img();
	if (x < 0 || y < 0 || x > WIN_W - 1 || y > WIN_H)
		return ;
	dst = img->addr + (int)(y * img->line_length + x * 
		(img->bits_per_pixel / 8)); 
	*(unsigned int*)dst = color;
}

void	ft_reload_frame()
{
	// mlx_destroy_image(_mlx()->mlx, _img()->img);
	// _img()->img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_img()->addr = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
		&(_img()->line_length), &(_img()->endian));
//	_img()->bits_per_pixel /= 8;
	//mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}

void	ft_fps(void)
{
	_ray()->old_time = _ray()->time;
	_ray()->time = get_clock(_ray()->clock);
	_ray()->frame_time = (get_clock(_ray()->clock) - _ray()->old_time) / 1000000.0;
	//printf("FPS = %d\n",  (int)(1.0 / _ray()->frame_time));ft_
	_player()->move_speed = _ray()->frame_time * 5.0;
	_player()->rot_speed = _ray()->frame_time * 2.0;
}

void	ft_draw_void()
{
	t_int	var;
	int		min;

	var.i = 0;
	while (var.i < WIN_W)
	{
		var.j = _ray()->max_y;
		if (var.j < 0)
			var.j = 0;
		min = _ray()->min_y;
		if (min < 0)
			min = 0;
		while (var.j < min)
		{
			if (var.j < WIN_H / 2)
				ft_pixel_put(var.i, var.j, 0xD3D3D3);
			else
				ft_pixel_put(var.i, var.j, 0x32a852);
			var.j++;
		}
		var.i++;
	}
}

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

int	ft_loop()
{
	t_obj	player;

	player = ft_get_data(_player());
	send(_img()->socket, &player, sizeof(player), 0);
	printf("my player.x : %f my player.y : %f\n", player.x, player.y);
	recv(_img()->socket, &player, sizeof(player), 0);
	printf("other player.x : %f other player.y : %f\n", player.x, player.y);
	ft_draw_void();
	ft_draw_map();
	ft_reload_frame();
	if (_ray()->max_y < 0)
		_ray()->max_y = 0;
	if (_ray()->min_y < 0)
		_ray()->min_y = WIN_H;
	return (0);
}