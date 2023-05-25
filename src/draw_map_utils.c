
#include "cub3D.h"

void	player_angle(t_game *data, char orientation)
{
	t_player	player;
	player = data->player_data;

	(void)player;
	if (orientation == 'E')
		player.angle = 0;
	else if (orientation == 'S')
		player.angle = M_PI_2;
	else if (orientation == 'W')
		player.angle = M_PI;
	else 
		player.angle = 3 * M_PI;
}

void	line_draw(struct s_position *pointA, struct s_position *pointB, mlx_image_t* y_img)
{
  double x;
  double y;
  double x1, y1;
  double x2, y2, dx, dy, step;
  int i;
  
  x1 = pointA->x_axis;
  y1 = pointA->y_axis;
  x2 = pointB->x_axis;
  y2 = pointB->y_axis;
  
  dx = (x2 - x1);
  dy = (y2 - y1);
  if (fabs(dx) >= fabs(dy))
    step = fabs(dx);
  else
    step = fabs(dy);
  dx = dx / step;
  dy = dy / step;
  x = x1;
  y = y1;
  i = 1;
  while (i <= step) {
	mlx_put_pixel(y_img, x, y, 0xFAFABB);
    x = x + dx;
    y = y + dy;
    i = i + 1;
  }
}
