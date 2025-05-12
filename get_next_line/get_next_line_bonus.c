/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:42:46 by tkurukul          #+#    #+#             */
/*   Updated: 2025/01/08 15:05:42 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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
	static char	*buffer[1024];
	char		*read_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_buff(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	read_line = make_line(buffer[fd]);
	if (read_line == NULL)
		return (NULL);
	buffer[fd] = save_prev(buffer[fd]);
	return (read_line);
}

/* int	main(void)
{
	char	*str;
	int		fd[1024];

	if ((str = get_next_line(fd[0])) != NULL)
	{
		printf("%s", str);
		free(str);
	}
} */
