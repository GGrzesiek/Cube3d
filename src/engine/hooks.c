#include "cube.h"

static int	key_index(int keycode)
{
	if (keycode == K_W)
		return (KEY_W);
	if (keycode == K_A)
		return (KEY_A);
	if (keycode == K_S)
		return (KEY_S);
	if (keycode == K_D)
		return (KEY_D);
	if (keycode == K_LEFT)
		return (KEY_LEFT);
	if (keycode == K_RIGHT)
		return (KEY_RIGHT);
	return (-1);
}

int	on_close(t_game *g)
{
	mlx_loop_end(g->mlx);
	return (0);
}

int	on_key_down(int keycode, t_game *g)
{
	int	i;

	if (keycode == K_ESC)
		return (on_close(g));
	i = key_index(keycode);
	if (i >= 0)
		g->keys[i] = 1;
	return (0);
}

int	on_key_up(int keycode, t_game *g)
{
	int	i;

	i = key_index(keycode);
	if (i >= 0)
		g->keys[i] = 0;
	return (0);
}

/* close button needs mask 0, mlx looks it up by index */
void	register_hooks(t_game *g)
{
	mlx_hook(g->win, EV_KEYPRESS, MASK_KEYPRESS, on_key_down, g);
	mlx_hook(g->win, EV_KEYRELEASE, MASK_KEYRELEASE, on_key_up, g);
	mlx_hook(g->win, EV_DESTROY, 0, on_close, g);
}
