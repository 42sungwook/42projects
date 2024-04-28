#include "../srcs/cub3d.h"

void	set_color(t_color *color, char *str_rgb)
{
	int		color_cnt;
	char	**rgb;
	char	**tmp_rgb;

	rgb = ft_split(str_rgb, ',');
	tmp_rgb = rgb;
	color_cnt = 0;
	while (*(tmp_rgb++))
		color_cnt++;
	if (color_cnt != 3)
		print_error("Invalid Color\n");
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255)
		print_error("Invalid Color\n");
	if (color->g < 0 || color->g > 255)
		print_error("Invalid Color\n");
	if (color->b < 0 || color->b > 255)
		print_error("Invalid Color\n");
	free_chars(rgb);
}
