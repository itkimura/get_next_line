
#include "get_next_line.h"
#include <stdio.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

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
	if (argc == 1)
	{
		printf("\x1b[33mLet's test standard input! Type \"exit\" for quit\033[m\n");
		do{
			count++;
			status = get_next_line(0, &line);
			if (strcmp(line, "exit") != 0)
				printf("status:%d\tline[%d]: %s\n", status, count, line);
		}while (strcmp(line, "exit") != 0);
	}
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
		line = 0;
		printf("\x1b[36m[FINISH] line = %s\nfile name:\t%s\t", line, argv[i]);
		if (strlen(argv[i]) < 7)
			printf("\t");
		printf("status: %d\n\033[m\n", status);
		system("leaks a.out");
		close(fd);
		i++;
		if (i != argc)
			printf("\n");
		count = 0;
	}
}
