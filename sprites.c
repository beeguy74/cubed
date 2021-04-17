/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:21:40 by tphung            #+#    #+#             */
/*   Updated: 2021/04/17 15:51:21 by tphung           ###   ########.fr       */
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

void	draw_sprite(t_vars *vars, double *z_buffer)
{
	//SPRITE CASTING
  sprite_dist_calc(vars->config, vars->plr, vars->config->sprite_mas);
  int j = 0;
  printf("UNsorted: \n");
  while (j < vars->config->sprite_num)
  {
   // j = vars->config->sprite_order[i++];
    printf("x = %f y = %f dist = %f\n", vars->config->sprite_mas[j]->pos_x,
                                    vars->config->sprite_mas[j]->pos_y,
                                    vars->config->sprite_mas[j]->dist);
                                    j++;
  }
  sprite_sort(vars->config, vars->config->sprite_mas);
  printf("SORTED: \n");
  j = 0;
  while (j < vars->config->sprite_num)
  {
   // j = vars->config->sprite_order[i++];
    printf("x = %f y = %f dist = %f\n", vars->config->sprite_mas[j]->pos_x,
                                    vars->config->sprite_mas[j]->pos_y,
                                    vars->config->sprite_mas[j]->dist);
                                    j++;
  }

    //sort sprites from far to close
  if (z_buffer)
    return;
  return ;

}
		//sprite_sort(vars->config, vars->plr, vars->config->sprite_mas);
 /*   sort_sprites(spriteOrder, spriteDistance, numSprites);

    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < numSprites; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = sprite[spriteOrder[i]].x - posX;
      double spriteY = sprite[spriteOrder[i]].y - posY;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

      //calculate height of the sprite on screen
      int spriteHeight = abs(int(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + h / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + h / 2;
      if(drawEndY >= h) drawEndY = h - 1;

      //calculate width of the sprite
      int spriteWidth = abs( int (h / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= w) drawEndX = w - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
          Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
          if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
    }*/