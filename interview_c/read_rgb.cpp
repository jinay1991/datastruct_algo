#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{
	printf("usage: testapp [image_input]\n");
	if (argc < 1)
		return -1;

	char *input_file = argv[1];
	printf("input file is %s\n", input_file);

	cv::Mat in_image = cv::imread(input_file, cv::IMREAD_UNCHANGED);
	if (in_image.rows <= 0 || in_image.cols <= 0)
		return -1;

	cv::imshow("input", in_image);

	unsigned char *ptr = in_image.data;
	int n = in_image.channels();

	for (int h = 0; h < in_image.rows; h++)
	{
		for (int w = 0; w < in_image.cols; w++)
		{
			ptr[((h * in_image.cols) + w) * n] = h > 20 ? 255 : ptr[((h * in_image.cols) + w) * n];
		}
	}

	cv::imshow("updated out", in_image);
	cv::waitKey(0);
	return 0;
}

