
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char plaintext[] = "Hello this is a test!";
    int size = sizeof(plaintext) / sizeof(plaintext[0]) - 1;
    char ciphertext[500];
    int i, j, height, width, counter = 0;
    for (height = 2; height < size / 2; height++)
    {
        width = (size % 2 == 0) ? (int)(size / height) : (int)((size + 1) / height);
        printf("Height: %d, Width: %d\n", height, width);
        for (i = 0; i < height; i++)
        {
            for (j = i; j < size; j += height)
            {
                ciphertext[counter] = plaintext[j];
                counter++;
            }
        }
        for (i = 0; i < size; i++)
        {
            printf("%c", ciphertext[i]);
            ciphertext[i] = '\0';
        }
        printf("\n");
        counter = 0;
    }
}