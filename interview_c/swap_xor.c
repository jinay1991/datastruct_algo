#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
	printf("usage: testapp [num1] [num2]\n");
	if (argc < 3)
		return -1;

	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);
	printf("inputs: x=%d, y=%d\n", num1, num2);

	num1 = num1 ^ num2;
	num2 = num1 ^ num2;
	num1 = num1 ^ num2;

	printf("swaped output: x=%d, y=%d\n", num1, num2);
	return 0;
}

