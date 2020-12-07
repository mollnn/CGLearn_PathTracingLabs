#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <bits/stdc++.h>

/*
fprintf(f, "P3\n%d %d\n%d\n", img_w, img_h, 255);
for (int i = 0; i < img_w * img_h; i++)
    fprintf(f, "%d\n%d\n%d\n", ColorFloat2Int(img_buffer[i].x), ColorFloat2Int(img_buffer[i].y), ColorFloat2Int(img_buffer[i].z));
*/

struct Image
{
    int size_x;
    int size_y;

    double **buffer;

    Image(int size_x = 0, int size_y = 0) : size_x(size_x), size_y(size_y)
    {
        buffer = new double *[size_y];
        for (int i = 0; i < size_y; i++)
        {
            buffer[i] = new double[size_x];
            for (int j = 0; j < size_x; j++)
            {
                buffer[i][j] = 0;
            }
        }
    }

    Image(const Image &image)
    {
        size_x = image.size_x;
        size_y = image.size_y;
        buffer = new double *[size_y];
        for (int i = 0; i < size_y; i++)
        {
            buffer[i] = new double[size_x];
            for (int j = 0; j < size_x; j++)
            {
                buffer[i][j] = image.buffer[i][j];
            }
        }
    }

    // 释放缓冲区
    void Release()
    {
        for (int i = 0; i < size_y; i++)
        {
            delete[] buffer[i];
        }
        delete[] buffer;
        buffer = NULL;
    }

    // 重新分配图像大小，分配后缓冲区会被清空（背景色）
    void Resize(int size_x_, int size_y_)
    {
        Release();
        size_x = size_x_;
        size_y = size_y_;
        buffer = new double *[size_y];
        for (int i = 0; i < size_y; i++)
        {
            buffer[i] = new double[size_x];
            for (int j = 0; j < size_x; j++)
            {
                buffer[i][j] = 0;
            }
        }
    }

    // 生成测试图像
    void GenerateTestImage()
    {
        if (size_x == 0 || size_y == 0)
        {
            return;
        }
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                int tmp = 3 * x + y;
                buffer[y][x] = 1.0 * tmp / (size_x * 3 + size_y);
            }
        }
    }

    // 写入 PPM 文件
    void WriteToPPM(std::string filename)
    {
        std::ofstream output_stream(filename);

        using namespace std;
        output_stream << "P3" << endl;
        output_stream << size_x << " " << size_y << endl;
        output_stream << 255 << endl;

        for (int i = 0; i < size_y; i++)
        {
            for (int j = 0; j < size_x; j++)
            {
                output_stream << (int)(buffer[i][j] * 255);
                output_stream << endl;
                output_stream << (int)(buffer[i][j] * 255);
                output_stream << endl;
                output_stream << (int)(buffer[i][j] * 255);
                output_stream << endl;
            }
        }

        output_stream.close();
    }
};

#endif