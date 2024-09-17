/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlourenc <xlourenc@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-17 14:35:51 by xlourenc          #+#    #+#             */
/*   Updated: 2024-09-17 14:35:51 by xlourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*grab_rest(char *buffer)
{
	char	*next_line;
	size_t	end;
	size_t	i;

	end = 0;
	i = 0;
	while (buffer[end] && buffer[end] != '\n')
		end++;
	if (buffer[end] == '\n')
		end++;
	next_line = malloc((ft_strlen(buffer) - end + 1) * sizeof(char));
	if (!next_line)
		return (free(buffer), NULL);
	while (buffer[end + i])
	{
		next_line[i] = buffer[end + i];
		i++;
	}
	next_line[i] = '\0';
	if (!next_line[0])
		return (free(buffer), free(next_line), NULL);
	return (free(buffer), next_line);
}

static char	*grab_line(char *buffer)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * ft_strlen(buffer) + 1);
	if (!temp)
	{
		return (NULL);
	}
	while (buffer[i] != '\n' && buffer[i] != '\0')
		temp[i++] = buffer[j++];
	if (buffer[i] == '\n')
	{
		temp[i] = buffer[j];
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

static char	*read_file(int fd, char *str)
{
	char	*buffer;
	int		bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	bytes = 1;
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			str = ft_strjoin(str, buffer);
		}
	}
	free(buffer);
	if (bytes == -1)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = grab_line(buffer[fd]);
	buffer[fd] = grab_rest(buffer[fd]);
	return (line);
}
/*
int main()
{
	int fd[3];

	fd[0] = open("test1.txt", O_RDONLY);
	fd[2] = open("test3.txt", O_RDONLY);
	fd[1] = open("test2.txt", O_RDONLY);
	char *test1 = get_next_line(fd[0]);
	char *test2 = get_next_line(fd[1]);
	char *test3 = get_next_line(fd[2]);
	while(test1 || test2 || test3)
	{
		printf("test1: %s\n", test1);
		printf("test2: %s\n", test2);
		printf("test3: %s\n", test3);
		test1 = get_next_line(fd[0]);
		test2 = get_next_line(fd[1]);
		test3 = get_next_line(fd[2]);
        free(test1);
        free(test2);
	    free(test3);
	}
	printf("BUFFER SIZE: %i\n", BUFFER_SIZE);
	
	close(fd[0]);
}
*/