/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:13 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/12 15:12:21 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	get_map_height(char *file)
{
	int		fd;
	int		h;
	char	*line;

	h = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		h++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (h);
}

int	read_map_lines(int fd, char **map, int h)
{
	int		i;
	size_t	len;
	char	*line;

	i = 0;
	while (i < h)
	{
		line = get_next_line(fd);
		if (!line)
			return (free_map(map), -1);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i] = ft_strdup(line);
		if (!map[i])
		{
			free(line);
			free_map(map);
			return (-1);
		}
		free(line);
		i++;
	}
	map[h] = NULL;
	return (0);
}

char	**load_map(char *file)
{
	int		fd;
	int		h;
	char	**map;

	h = get_map_height(file);
	if (!h)
		return (NULL);
	map = ft_calloc(h + 1, sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free_map(map), NULL);
	if (read_map_lines(fd, map, h) == -1)
		return (close(fd), NULL);
	close(fd);
	return (map);
}
