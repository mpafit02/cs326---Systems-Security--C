
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // char ciphertext[] = "xxrrkqxi!nddmupiljgtdalnd i!znv dxjiyla";
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz! ";
    // char ciphertext[] = "abcdefghijklmnopqrstuvwxyz! ";
    char ciphertext[] = "xxrrkqxi!nddmupiljgtdalnd i!znv dxjiyla"; // Key 1 = 4, Key 2 = 9
    int size_c = sizeof(ciphertext) / sizeof(ciphertext[0]) - 1;
    int size_a = sizeof(alphabet) / sizeof(alphabet[0]) - 1;
    char plaintext[500];
    int i, k1, k2, k, j, counter = 0;

    for (k2 = 1; k2 < size_a; k2++)
    {
        for (k1 = 1; k1 < size_a; k1++)
        {
            printf("Key 1: %d\n", k1);
            printf("Key 2: %d\n", k2);
            for (i = 0; i < size_c; i++) //-1 to not ceck the null character
            {
                // For the even numbers is key 1 and for the odd numebr is the key 2
                if (i % 2 == 0)
                {
                    k = k1;
                }
                else
                {
                    k = k2;
                }

                for (j = 0; j <= size_a; j++)
                {
                    if (ciphertext[i] == alphabet[j])
                    {
                        if (j - k < 0)
                        {
                            plaintext[counter] = alphabet[(size_a + (j - k)) % size_a];
                        }
                        else
                        {
                            plaintext[counter] = alphabet[(j - k) % size_a];
                        }
                        counter++;
                        break;
                    }
                }
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

    return 0;
}
