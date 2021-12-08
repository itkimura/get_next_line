/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:40:12 by itkimura          #+#    #+#             */
/*   Updated: 2021/12/07 16:28:09 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_file(const int fd, char **line)
{
	char	*buff;
	int		byte;

	buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
		return (0);
	byte = 1;
	while (ft_strchr(, '\n') != 0 && byte)
	{
		byte = read (fd, &buff, BUFF_SIZE);
		if (byte == NULL)
		{
			free(buff);
			return (0);
		}
		buff[byte] = '\0';
	}
	return (buff);
}

int	get_next_line(const int fd, char **line)
{

	if (fd < 0 || BUFF_SIZE <= 0)
		return (0);
	line = read_file(fd, line);
	if (str == NULL)
		return (0);
	return (1);
}

int main(int argc, char *argv[])
{
	char *file_name;
	if (argc == 1)
	{
		file_name = "test.txt";
	}
    else
        file_name = argv[1];
    int fd = open(file_name, O_RDONLY);
    // int fd = 999999;
    char *line;
    int status;

    printf("\n[START] %s\n\tfd: %d\n\n", file_name, fd);
    do{
        status = get_next_line(fd, &line);
        printf("status:  \t%d\n", status);
        printf("read txt:\t%s\n", line);
        free(line);
    }while (status == 1);
    printf("\n[FINISH] %s\n\tstatus: %d\n\n", file_name, status);

    close(fd);
}
