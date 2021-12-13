/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 19:44:39 by itkimura          #+#    #+#             */
/*   Updated: 2021/12/12 14:48:31 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#include <fcntl.h>
#include <sys/stat.h>

/*
**copy_line finds the first \n or \0
**If \n was found, strsub until the \n & Line point to the new substr
**tmp will have the next character of \n
**free the current stack[fd] and put the tmp
**If it is the end of line, free stack[fd]
** else -> when the file doesn't have any \n then just use strdup
*/

static int	cpy_line(const int fd, char **line, char **stack)
{
	int		i;
	char	*tmp;

	i = 0;
	while (stack[fd][i] != '\n' && stack[fd][i] != '\0')
		i++;
	if (stack[fd][i] == '\n')
	{
		*line = ft_strsub(stack[fd], 0, i);
		tmp = ft_strdup(stack[fd] + i + 1);
		free(stack[fd]);
		stack[fd] = tmp;
		if (stack[fd][0] == '\0')
			ft_strdel(&stack[fd]);
	}
	else
	{
		*line = ft_strdup(stack[fd]);
		ft_strdel(&stack[fd]);
	}
	return (1);
}

/*
**A static variable is used, so that whenever get_next_line is called,
**it remembers the previous function call.
**When get_next_gen is first call, stack[fd] is empty,
**ret has positive number. so put full text from file to stack[fd].
** While there is stuff left to read, strjoin read chars (buf) and arr[fd],
** into tmp, clears arr[fd] and assigns joined string to arr[fd].
** Check for \n in the string that was read, if found, break loop.
** Basically we keep appending BUFF_SIZE amount of read chars into arr[fd]
** until we run out of stuff to read or we encounter \n in the read chars.
*/

/* 
** return of read, -1: error 0:EOF  n > 0:How many byte have been read
*/

int	get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*stack[MAX_FD];
	char		heap[BUFF_SIZE + 1];
	char		*tmp;

	if ((fd < 0 || fd > MAX_FD) || line == 0)
		return (-1);
	ret = read(fd, heap, BUFF_SIZE);
	while (ret > 0)
	{
		heap[ret] = '\0';
		if (stack[fd] == 0)
			stack[fd] = ft_strnew(1);
		tmp = ft_strjoin(stack[fd], heap);
		free(stack[fd]);
		stack[fd] = tmp;
		if (ft_strchr(stack[fd], '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && stack[fd] == 0)
		return (0);
	else
		return (cpy_line(fd, line, stack));
}
/*
#include <string.h>

int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		status;
	int		count;
	int		i;

	fd = 0;
	count = 0;
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			return (0);
		printf("\x1b[33m[START] file name:\t%s\t", argv[i]);
		if (strlen(argv[i]) < 7)
			printf("\t");
		printf("fd:\t%d\n\033[m", fd);
		do{
			count++;
			status = get_next_line(fd, &line);
			if (status == 1)
			{
				printf("status:%d\tline[%d]: %s\n", status, count, line);
				free(line);
			}
		}while (status == 1);
		printf("\x1b[36m[FINISH] file name:\t%s\t", argv[i]);
		if (strlen(argv[i]) < 7)
			printf("\t");
		printf("status: %d\n\033[m", status);
		close(fd);
		i++;
		if (i != argc)
			printf("\n");
	}
}
*/
