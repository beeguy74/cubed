/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:21:40 by tphung            #+#    #+#             */
/*   Updated: 2021/04/17 17:38:11 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

//sort algorithm
//sort the sprites based on distance
/*
void	sortSprites(int* order, double* dist, int amount)
{
  std::vector<std::pair<double, int>> sprites(amount);
  for(int i = 0; i < amount; i++) {
    sprites[i].first = dist[i];
    sprites[i].second = order[i];
  }
  std::sort(sprites.begin(), sprites.end());
  // restore in reverse order to go from farthest to nearest
  for(int i = 0; i < amount; i++) {
    dist[i] = sprites[amount - i - 1].first;
    order[i] = sprites[amount - i - 1].second;
  }
}

void	sprite_sort(t_conf* config, t_pers *plr, t_sprite **sprite_mas)
{
  return ;
}
*/
void  sprite_dist_calc(t_conf* config, t_pers *plr, t_sprite **sprite_mas)
{
  int		i;

	i = 0;
	config->sprite_order = malloc(sizeof(int) * config->sprite_num);
  if (config->sprite_order == NULL)
    err_exit(0);
	if (plr && sprite_mas) 
  {
    while (i < config->sprite_num)
    {
      config->sprite_order[i] = i;
      sprite_mas[i]->dist = ((plr->pos.x - sprite_mas[i]->pos_x) *
                  (plr->pos.x - sprite_mas[i]->pos_x) +
                    (plr->pos.y - sprite_mas[i]->pos_y) *
                      (plr->pos.y - sprite_mas[i]->pos_y));
      
      i++;
      //sqrt not taken, unneeded
    }
  }
}

void sprite_sort(t_conf *config, t_sprite **sprite_mas)
{
  int       i;
  int       j;
  int       tmp;
  t_sprite  *s_tmp;

  i = 0;
  tmp = 0;
  s_tmp = 0;
  while (i < config->sprite_num)
  {
    j = 0;
    while (j < config->sprite_num)
    {
      if (sprite_mas[i]->dist > sprite_mas[j]->dist)
      {
  //      tmp = config->sprite_order[i];
    //    config->sprite_order[i] = config->sprite_order[j];
      //  config->sprite_order[j] = tmp;
          s_tmp = sprite_mas[i];
          sprite_mas[i] = sprite_mas[j];
          sprite_mas[j] = s_tmp;
      }
      j++;
    }
    i++;
  }
}

void  sprite_cam_pos_calc(t_conf *config, t_pers *plr, t_sprite *sprite_mas, t_text *sprite, double *z_buffer, t_vars *vars)
{
  //translate sprite position to relative to camera
  sprite_mas->x = sprite_mas->pos_x - plr->pos.x;
  sprite_mas->y = sprite_mas->pos_y - plr->pos.y;

  //transform sprite with the inverse camera matrix
  // [ plr->cam.x   plr->sight.x ] -1                                       [ plr->sight.y      -plr->sight.x ]
  // [               ]       =  1/(plr->cam.x*plr->sight.y-plr->sight.x*plr->cam.y) *   [                 ]
  // [ plr->cam.y   plr->sight.y ]                                          [ -plr->cam.y  plr->cam.x ]

  double invDet = 1.0 / (plr->cam.x * plr->sight.y - plr->sight.x * plr->cam.y); //required for correct matrix multiplication

  double transformX = invDet * (plr->sight.y * sprite_mas->x - plr->sight.x * sprite_mas->y);
  double transformY = invDet * (-plr->cam.y * sprite_mas->x + plr->cam.x * sprite_mas->y); //this is actually the depth inside the screen, that what Z is in 3D

  int spriteScreenX = (int)((config->res_x / 2) * (1. + transformX / transformY));

  //calculate height of the sprite on screen
  int spriteHeight = abs((int)(config->res_y / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
  //calculate lowest and highest pixel to fill in current stripe
  int drawStartY = -spriteHeight / 2 + config->res_y / 2;
  if(drawStartY < 0)
    drawStartY = 0;
  int drawEndY = spriteHeight / 2 + config->res_y / 2;
  if(drawEndY >= config->res_y)
    drawEndY = config->res_y - 1;

  //calculate width of the sprite
  int spriteWidth = abs((int)(config->res_y / (transformY)));
  int drawStartX = -spriteWidth / 2 + spriteScreenX;
  if(drawStartX < 0)
    drawStartX = 0;
  int drawEndX = spriteWidth / 2 + spriteScreenX;
  if(drawEndX >= config->res_x)
    drawEndX = config->res_x - 1;
  int *sprite_img = (int*)sprite->img->addr; //cast to int* cuz need int color
  //loop through every vertical stripe of the sprite on screen
  for(int stripe = drawStartX; stripe < drawEndX; stripe++)
  {
    int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * sprite->width / spriteWidth) / 256;
    //the conditions in the if are:
    //1) it's in front of camera plane so you don't see things behind you
    //2) it's on the screen (left)
    //3) it's on the screen (right)
    //4) ZBuffer, with perpendicular distance
    if(transformY > 0 && stripe > 0 && stripe < config->res_x && transformY < z_buffer[stripe])
    {
      for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
      {
        int d = (y) * 256 - config->res_y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
        int texY = ((d * sprite->height) / spriteHeight) / 256;
        //Uint32 color = texture[sprite_mas->pos_texture][sprite->width * texY + texX]; //get current color from the texture
        //Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
        int color = sprite_img[sprite->width * texY + texX];
        //buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        if((color & 0x00FFFFFF) != 0)
          my_mlx_pixel_put(vars->img, stripe, y, color);
      }
    }
  }
}

void	draw_sprite(t_vars *vars, double *z_buffer)
{
  int i;
	//SPRITE CASTING
  sprite_dist_calc(vars->config, vars->plr, vars->config->sprite_mas);
  //sort sprites from far to close
  sprite_sort(vars->config, vars->config->sprite_mas);
  //after sorting the sprites, do the projection and draw them
  i = 0;
  while (i < vars->config->sprite_num)
  {
    sprite_cam_pos_calc(vars->config, vars->plr, vars->config->sprite_mas[i++], vars->file->sprite, z_buffer, vars);
  }
}