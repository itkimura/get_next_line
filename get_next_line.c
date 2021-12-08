/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:40:12 by itkimura          #+#    #+#             */
/*   Updated: 2021/12/08 17:33:49 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(const int fd, char **line)
{
	int			ret; /*return of read, -1: error 0:EOF Positive number:How many byte have been read*/
	char		buff[BUFF_SIZE + 2];
	static char		*str[1000];
	char		*s;
	printf("fd = %d, BUFF_SIZE = %d\n", fd, BUFF_SIZE);
	if (fd < 0 || line == 0)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		printf("ret = %d\n", ret);
		if (str[fd] == 0)
			str[fd] = ft_strnew(1);
		buff[ret] = '\0';
		s = ft_strjoin(str[fd], (char *)buff);
		free(str[fd]);
		str[fd] = s;
		if (ft_strchr(str[fd], '\n'))
			break;
	}
	return (0);
}

#include <fcntl.h>
#include <sys/stat.h>

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
