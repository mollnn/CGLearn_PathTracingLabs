#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <bits/stdc++.h>
#include "ColorSpace.hpp"

struct Image
{
    int size_x;
    int size_y;

    Radiance3 **buffer;

    Image(int size_x = 0, int size_y = 0) : size_x(size_x), size_y(size_y)
    {
        buffer = new Radiance3 *[size_y];
        for (int i = 0; i < size_y; i++)
        {
            buffer[i] = new Radiance3[size_x];
            for (int j = 0; j < size_x; j++)
            {
                buffer[i][j] = Radiance3();
            }
        }
    }

    Image(const Image &image)
    {
        size_x = image.size_x;
        size_y = image.size_y;
        buffer = new Radiance3 *[size_y];
        for (int i = 0; i < size_y; i++)
        {
            buffer[i] = new Radiance3[size_x];
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
        buffer = new Radiance3 *[size_y];
        for (int i = 0; i < size_y; i++)
        {
            buffer[i] = new Radiance3[size_x];
            for (int j = 0; j < size_x; j++)
            {
                buffer[i][j] = Radiance3();
            }
        }
    }

    // 写入 PPM 文件
    void WriteToPPM(std::string filename)
    {
        FILE *f = fopen(filename.c_str(), "w"); // Write image to PPM file.
        fprintf(f, "P3\n%d %d\n%d\n", size_x, size_y, 255);

        for (int i = 0; i < size_y; i++)
        {
            for (int j = 0; j < size_x; j++)
            {
                auto tmp = (Clamp(IntensityToBrightness(buffer[i][j])) * 255);
                fprintf(f, "%d\n%d\n%d\n", (int)tmp.x, (int)tmp.y, (int)tmp.z);
            }
        }
    }

    // 像素读
    Radiance3 GetPixel(int x, int y)
    {
        return buffer[y][x];
    }

    // 获取像素引用
    Radiance3 &GetPixelRef(int x, int y)
    {
        return buffer[y][x];
    }

    // 像素写
    void SetPixel(int x, int y, Radiance3 color)
    {
        buffer[y][x] = color;
    }

    // 像素加
    void IncPixel(int x, int y, Radiance3 color)
    {
        buffer[y][x] += color;
    }
};

/////////////////////////////////////////////////////////////////////////////

struct ImageGrayscale
{
    int size_x;
    int size_y;

    double **buffer;

    ImageGrayscale(int size_x = 0, int size_y = 0) : size_x(size_x), size_y(size_y)
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

    ImageGrayscale(const ImageGrayscale &image)
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

    // 写入 PPM 文件
    void WriteToPPM(std::string filename)
    {
        FILE *f = fopen(filename.c_str(), "w"); // Write image to PPM file.
        fprintf(f, "P3\n%d %d\n%d\n", size_x, size_y, 255);

        for (int i = 0; i < size_y; i++)
        {
            for (int j = 0; j < size_x; j++)
            {
                int tmp = (int)(Clamp(IntensityToBrightness(buffer[i][j])) * 255);
                fprintf(f, "%d\n%d\n%d\n", tmp, tmp, tmp);
            }
        }
    }

    // 像素读
    double GetPixel(int x, int y)
    {
        return buffer[y][x];
    }

    // 获取像素引用
    double &GetPixelRef(int x, int y)
    {
        return buffer[y][x];
    }

    // 像素写
    void SetPixel(int x, int y, double color)
    {
        buffer[y][x] = color;
    }

    // 像素加
    void IncPixel(int x, int y, double color)
    {
        buffer[y][x] += color;
    }
};

#endif