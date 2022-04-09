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
    return false;
}
bool Image::savePPM(string filename)
{
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
    const float r = 0.299F;
    const float g = 0.587F;
    const float b = 0.114F;

    int size = this->w * this->h * 3;
    for (int i = 0; i < size; i++)
    {
        this->pixels[i] = (this->pixels[i].r) + (this->pixels[i].g) + (this->pixels[i].b);
        this->pixels[i+1] = (this->pixels[i+1].r) + (this->pixels[i+1].g) + (this->pixels[i+1].b);
        this->pixels[i+2] = (this->pixels[i+2].r) + (this->pixels[i+2].g) + (this->pixels[i+2].b);
    }
}
void Image::flipHorizontal()
{


}
void Image::flipVertically()
{


}
void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
{

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