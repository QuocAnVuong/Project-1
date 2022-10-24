#include <math.h>
#include <stdio.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include ".\headers\stb_image.h.txt"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include ".\headers\stb_image_write.h.txt"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *edit_img(unsigned char *background, unsigned char *foreground,unsigned char *weather, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int kt=0;
            for(int k=0;k<channel;k++){
                if(abs(foreground[i * width * channel + j * channel + k] - background[i * width * channel + j * channel + k]) < 80 ){
                    kt++;
                }
            }
            for(int k=0;k<channel;k++){
                if(kt==3){
                    temp_array[i * width * channel + j * channel + k]=weather[i * width * channel + j * channel + k];
                }
                else{
                    temp_array[i * width * channel + j * channel + k]=foreground[i * width * channel + j * channel + k];
                }
            }
        }
    }
    return temp_array;
}

int main()
{
    int width, height, channel;
    char save_path[] = "./images/res.jpg";

    unsigned char *weather = stbi_load("./images/new_background.jpg", &width, &height, &channel, 0);
    if (weather == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);

    unsigned char *background = stbi_load("./images/background.jpg", &width, &height, &channel, 0);
    if (background == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);

    unsigned char *foreground = stbi_load("./images/foreground.jpg", &width, &height, &channel, 0);
    if (foreground == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);

    unsigned char *mimage = edit_img(background,foreground,weather, width, height, channel);
    stbi_write_jpg(save_path, width, height, channel, mimage, 100);
    printf("New image saved to %s\n", save_path);
    return 0;
}