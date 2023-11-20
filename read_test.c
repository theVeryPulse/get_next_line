#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int fd0 = open("test1.txt", O_RDONLY);
	if (fd0 == -1)
		return (-1);
	int fd1 = open("test2.txt", O_RDONLY);
	if (fd1 == -1)
		return (-1);
	char *s0 = (char *)calloc(10, sizeof(char));
	char *s1 = (char *)calloc(10, sizeof(char));
	for (int i = 0; i < 2; i++) {
		int j = 0;
		int result;
		do {
			result = read(fd0, &s0[j], 1);
			if (result <= 0) {
				break;
			}
			j++;
		} while (s0[j - 1] != '\n');
		printf("fd0: (%s)\n", s0);
		int k = 0;
		do {
			result = read(fd1, &s1[k], 1);
			k++;
			if (result <= 0) {
				break;
			}
		} while (s1[k - 1] != '\n');
		printf("fd1: (%s)\n", s1);
	}
	close(fd0);
	close(fd1);
}