/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:35:26 by tkurukul          #+#    #+#             */
/*   Updated: 2025/01/27 17:16:46 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/* #define BUFFER_SIZE 2 */

static char	*read_buff(int fd, char *buffer)
{
	char		*tmp;
	ssize_t		buf_count;
	char		*mod_buffer;

	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (1)
	{
		buf_count = read(fd, tmp, BUFFER_SIZE);
		if (buf_count == -1)
			return (free(tmp), free(buffer), NULL);
		if (buf_count == 0)
			break ;
		tmp[buf_count] = '\0';
		if (buffer)
			mod_buffer = ft_strjoin(buffer, tmp);
		else
			mod_buffer = ft_strdup(tmp);
		free(buffer);
		buffer = mod_buffer;
		if (ft_check_char(tmp, '\n'))
			break ;
	}
	return (free(tmp), buffer);
}

static char	*make_line(char *buffer)
{
	char		*nline;
	size_t		len;
	size_t		check;

	if (!buffer)
		return (NULL);
	len = 0;
	check = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		check++;
	nline = malloc(((len + check) + 1) * sizeof(char));
	if (!nline)
		return (NULL);
	ft_memcpy(nline, buffer, len + check);
	nline[len + check] = '\0';
	return (nline);
}

static char	*save_prev(char *buffer)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while (buffer[len] != '\n' && buffer[len])
		len++;
	if (buffer[len] == '\0' || buffer[len + 1] == '\0')
		return (free(buffer), NULL);
	tmp = ft_strdup(&buffer[len + 1]);
	return (free(buffer), tmp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*read_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buff(fd, buffer);
	if (!buffer)
		return (NULL);
	read_line = make_line(buffer);
	if (read_line == NULL)
		return (NULL);
	buffer = save_prev(buffer);
	return (read_line);
}

/*   int	main(void)
{
	int	fd;
	char *line;

	fd = open("txt.txt", O_RDWR);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */
/*int	main(void)
{
	int	fd;
	int	i;
	char *line;

	i= 0;
	fd = open("txt.txt", O_RDONLY);
	while((line = get_next_line(fd)) != NULL)
	{
		i++;
		free(line);
	}
	printf("%d\n", i);
	close(fd);
	return(0);
}*/

//malloc test for NULL;
