#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd0 = open("out_gnl_1.txt", O_RDONLY);
	// int fd1 = open("test1.txt", O_RDONLY);
	// int fd2 = open("test2.txt", O_RDONLY);
	char *s;

	for (int i = 0; i < 100; i++)
	{
		s = get_next_line(fd0);
		printf("out_gnl_1.txt:>>> \"%s\"\n", s);
		free(s);
		// s = get_next_line(fd1);
		// printf("test1.txt:>>> \"%s\"\n", s);
		// free(s);
		// s = get_next_line(fd2);
		// printf("test2.txt:>>> \"%s\"\n", s);
		// free(s);
	}
}