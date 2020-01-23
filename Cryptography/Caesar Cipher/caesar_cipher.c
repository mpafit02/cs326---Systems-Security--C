
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char plaintext[] = "abcdefghijklmnopqrstuvwxyz";
	char ciphertext[500];
	int key = 3;
	int i = 0;

	for (; i < sizeof(plaintext) / sizeof(plaintext[0]); i++)
	{
		ciphertext[i] = (plaintext[i] + key) % 26 + 'a';
		printf("%c -> %c %d\n", plaintext[i], ciphertext[i], (plaintext[i] + key) % 26);
	}

	for (i = 0; i < sizeof(plaintext) / sizeof(plaintext[0]); i++)
	{
		printf("%c", ciphertext[i]);
	}
	printf("\n");
	return 0;
}
