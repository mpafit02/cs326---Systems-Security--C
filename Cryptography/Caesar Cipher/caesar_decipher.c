
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz! ";
	char ciphertext[] = "! almv !h!pwatlhjmh! aleqvohpizlmz";
	// char ciphertext[] = "abcdefghijklmnopqrstuvwxyz! ";
	// char ciphertext[] = "xxrrkqxi!nddmupiljgtdalnd i!znv dxjiyla";
	int size_c = sizeof(ciphertext) / sizeof(ciphertext[0]) - 1;
	int size_a = sizeof(alphabet) / sizeof(alphabet[0]) - 1;
	char plaintext[500];
	int i, k1, j, counter = 0;

	for (k1 = 1; k1 < size_a; k1++)
	{
		printf("Key: %d\n", k1);
		for (i = 0; i < size_c; i++) //-1 to not ceck the null character
		{
			for (j = 0; j <= size_a; j++)
			{
				if (ciphertext[i] == alphabet[j])
				{
					if (j - k1 < 0)
					{
						plaintext[counter] = alphabet[(size_a + (j - k1)) % size_a];
					}
					else
					{
						plaintext[counter] = alphabet[(j - k1) % size_a];
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

	return 0;
}
