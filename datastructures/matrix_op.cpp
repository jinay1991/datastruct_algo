/*

 Amazon.in Interview Question: 

    - Input matrix having 1s and 0s.
    - WAP to find 1s in Matrix and make it's corresponding ROW and COLUMN filled with 1s.
    e.g.
        Input:
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 1 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0

        Output:
        0 0 0 0 1 0 0 0 0
        0 0 0 0 1 0 0 0 0
        0 0 0 0 1 0 0 0 0
        0 0 0 0 1 0 0 0 0
        1 1 1 1 1 1 1 1 1
        0 0 0 0 1 0 0 0 0
        0 0 0 0 1 0 0 0 0
        0 0 0 0 1 0 0 0 0
        0 0 0 0 1 0 0 0 0
*/

#include <iostream>
#include <vector>
#include <algorithm>


typedef struct _point_t_
{
    int x;
    int y;
}point_t;

int setOnes(bool *in, int x, int y, int width, int height)
{

    for (int w = 0; w < width; w++)
        in[y * width + w] = true;
    for (int h = 0; h < height; h++)
        in[h * width + x] = true;

    return 0;

}
void extractCoords(int index, int *x, int *y, int width, int height)
{
    *y = (int)(index / width);
    *x = index - ((*y) * width);
}
int process(bool *in, int width, int height) // Total Complexity O(n)
{
    bool res = false;
    std::vector<point_t> stack;
    for (int i = 0; i < width * height; i++) // complexity O(n)
    {
        res |= in[i];
        if(res)
        {
            point_t coord = { 0, 0 };
            extractCoords(i, &coord.x, &coord.y, width, height);
            std::cout << "found coord having 1s: ( " << coord.x << ", " << coord.y << " )" << std::endl;
            stack.push_back(coord);
            res = false;
        }
    }
    for (int i = 0; i < stack.size(); i++) // Complexity O(i * n) = O(n)
    {
        point_t coords = stack[i];
        setOnes(in, coords.x, coords.y, width, height);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    bool matrix[] = {
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false,  true, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false
    };
    bool matrixOut[81] = { false };
    int width = 9;
    int height = 9;
    std::cout << "Input: " << std::endl;
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
            std::cout << matrix[h * width + w] << " ";
        std::cout << std::endl;
    }

    process(matrix, width, height);

    std::cout << "Output: " << std::endl;
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
            std::cout << matrix[h * width + w] << " ";
        std::cout << std::endl;
    }
    return 0;
}