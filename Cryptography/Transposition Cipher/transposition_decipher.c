
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // char ciphertext[] = "Snf  r!tt riy usUonp d Cc t eoYkCo"; // A correct one with !
    // char ciphertext[] = "Snf  r!tt riyusUonpd Cc teoYkCo"; // The one given
    // char ciphertext[] = "Hloti sats!el hsi  et";
    char ciphertext[] = "Snf  rtt riyusUonpd Cc teoYkCo"; // Height = 5, Width == 6
    int size = sizeof(ciphertext) / sizeof(ciphertext[0]) - 1;
    char plaintext[500];
    int i, width, height, counter = 0;

    for (height = 2; height < size / 2; height++)
    {
        width = (size % 2 == 0) ? (int)(size / height) : (int)((size + 1) / height);
        printf("Height: %d Width: %d\n", height, width);
        i = 0;
        int last_i;
        while (i < width)
        {
            last_i = i;
            while (i < size)
            {
                plaintext[counter] = ciphertext[i];
                counter++;
                i += width;
            }
            i = last_i + 1;
        }
        for (i = 0; i <= counter; i++)
        {
            printf("%c", plaintext[i]);
            plaintext[i] = '\0';
        }
        printf("\n");
        counter = 0;
    }
}