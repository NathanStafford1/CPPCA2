//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"



bool Image::load(string filename)
{
    ifstream ifs(filename,std::ios::binary);
    string magicNumber;
    ifs >> magicNumber;
    ifs >> this->w;
    ifs >> this->h;
    int p;
    ifs >> p;
    ifs.ignore(256,'\n');
    if (p==255)
    {
        delete[] pixels;
        pixels = new Rgb[w*h];
        unsigned char pix[3];
        for (int i = 0; i < w*h; ++i)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];

        }
        return true;
    }
    return false;

}
bool Image::loadRaw(string filename)
{
    ifstream ifs(filename);
    if (ifs.good())
    {
        ifs >> this->w;
        ifs >> this->h;
        for (int i = 0; i < w*h; ++i)
        {
            float r,g,b;
            ifs >> r >> g >> b;
            pixels[i].r = r*255;
            pixels[i].g = g*255;
            pixels[i].b = b*255;
            cout << r << pixels[i].r << endl;
        }
        ifs.close();
        return true;
    }
    return false;
}
bool Image::savePPM(string filename)
{
    if (w == 0 || h == 0)
    {
        fprintf(stderr, "Can't save without an image!\n");
        return false;
    }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary);
        if (ofs.fail()) throw("Can't open file");
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char pix[3];
        for (int i = 0; i < w * h; ++i) {
            pix[0] = static_cast<unsigned char>(this->pixels[i].r);
            pix[1] = static_cast<unsigned char>(this->pixels[i].g);
            pix[2] = static_cast<unsigned char>(this->pixels[i].b);
            ofs.write(reinterpret_cast<char *>(pix), 3);
        }
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
    return false;
}


void Image::filterRed()
{
    for (int i = 0; i < w* h; ++i)
    {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{
    for (int i = 0; i < w* h; ++i)
    {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    for (int i = 0; i < w* h; ++i)
    {
        this->pixels[i].g = 0;
        this->pixels[i].r = 0;
    }
}
void Image::greyScale()
{
    //Greyscale assistance reference https://stackoverflow.com/questions/28923676/convert-ppm-image-to-greyscale-c
    for (int i = 0; i < h*w; i++)
    {
        unsigned char temp = ((this->pixels[i].r) + (this->pixels[i].g) + (this->pixels[i].b))/3;

        this->pixels[i].r = temp;
        this->pixels[i].g = temp;
        this->pixels[i].b = temp;
    }
}
void Image::flipHorizontal()
{
        unsigned int pixel1;
        unsigned int pixel2;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w / 2; x++)
            {
                pixel1 = x + y * w;
                pixel2 = (w - 1 - x) + y * w;

                swap(this->pixels[pixel1].r,this->pixels[pixel2].r);
                swap(this->pixels[pixel1].g,this->pixels[pixel2].g);
                swap(this->pixels[pixel1].b,this->pixels[pixel2].b);
            }
        }
}
void Image::flipVertically()
{
    unsigned int pixel1;
    unsigned int pixel2;

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h / 2; y++)
        {
            pixel1 = x + y * w;
            pixel2 = x + (h -1 - y) * w;

            swap(this->pixels[pixel1].r,this->pixels[pixel2].r);
            swap(this->pixels[pixel1].g,this->pixels[pixel2].g);
            swap(this->pixels[pixel1].b,this->pixels[pixel2].b);
        }
    }
}
void Image::AdditionalFunction2()
{
    //Darkens the image
    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].r *= 0.5;
        this->pixels[i].g *= 0.5;
        this->pixels[i].b *= 0.5;
    }
}
void Image::AdditionalFunction3()
{
    //Randomly swaps the RGB colors
    for (int i = 0; i < w*h; ++i)
    {
        if (rand() % 100 <= 30)
        {
            this->pixels[i].r = this->pixels[i].g;
            this->pixels[i].g = this->pixels[i].b;
            this->pixels[i].b = this->pixels[i].r;
        }
        else if (rand() % 100 <=50 && rand() % 100 >= 30)
        {
            this->pixels[i].r = this->pixels[i].r;
            this->pixels[i].g = this->pixels[i].g;
            this->pixels[i].b = this->pixels[i].b;
        }
        else if (rand() % 100 >=70)
        {
            this->pixels[i].r = this->pixels[i].b;
            this->pixels[i].g = this->pixels[i].g;
            this->pixels[i].b = this->pixels[i].r;
        }
    }
}
void Image::AdditionalFunction1()
{
    //Inverting image color
    for (int i = 0; i < w*h; ++i)
    {
        this->pixels[i].r = 255 - pixels[i].r;
        this->pixels[i].g = 255 - pixels[i].g;
        this->pixels[i].b = 255 - pixels[i].b;
    }
}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}