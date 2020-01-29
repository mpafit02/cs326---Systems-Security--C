// An implementation of the Simplified DES algorithm.
// For execution run the command make and then simplifiedDES for the default plaintext and key
// If you would like to provide your data you should execute it with the command:
// simplifiedDES 10101010 1111001111
// with your values as plaintext and key.
// plaintext should be 8 characters long and given first as argument
// kay should be 10 characters long and given second as argument
// Both the kay and the plaintext should only contain 1's ans 0's.
// Author: Marios Pafitis

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 8
#define K 10

void print(int size, char *n)
{
    for (int i = 0; i < size; i++)
    {
        printf("%c", n[i]);
    }
    printf("\n");
}

void shift_right(int c, char *n, char *res)
{
    for (int i = 0; i < N; i++)
    {
        if (i - c < 0)
        {
            res[i] = n[(N + (i - c)) % N];
        }
        else
        {
            res[i] = n[(i - c) % N];
        }
    }
}

void shift_left(int c, int size, char *n, char *res)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = n[(i + c) % size];
    }
}

void xor (int size, char *n1, char *n2, char *res) {
    for (int i = 0; i < size; i++)
    {
        if (n1[i] == n2[i])
        {
            res[i] = '0';
        }
        else
        {
            res[i] = '1';
        }
    }
}

    void expansion(char *n, char *res)
{
    res[0] = n[3];
    res[1] = n[0];
    res[2] = n[1];
    res[3] = n[2];
    res[4] = n[1];
    res[5] = n[2];
    res[6] = n[3];
    res[7] = n[0];
}

void initial_permutation(char *n, char *res)
{
    res[0] = n[1];
    res[1] = n[5];
    res[2] = n[2];
    res[3] = n[0];
    res[4] = n[3];
    res[5] = n[7];
    res[6] = n[4];
    res[7] = n[6];
}

void final_permutation(char *n, char *res)
{
    res[0] = n[3];
    res[1] = n[0];
    res[2] = n[2];
    res[3] = n[4];
    res[4] = n[6];
    res[5] = n[1];
    res[6] = n[7];
    res[7] = n[5];
}

void permutation(char *n, char *res)
{
    res[0] = n[1];
    res[1] = n[3];
    res[2] = n[2];
    res[3] = n[0];
}

void merge(int size, char *n, char *left, char *right)
{
    for (int i = 0; i < size; i++)
    {
        if (i < size / 2)
        {
            n[i] = left[i];
        }
        else
        {
            n[i] = right[i - (size / 2)];
        }
    }
}

void split(int size, char *n, char *left, char *right)
{
    for (int i = 0; i < size; i++)
    {
        if (i < size / 2)
        {
            left[i] = n[i];
        }
        else
        {
            right[i - (size / 2)] = n[i];
        }
    }
}
void swap(char *n)
{
    int j = N / 2;
    for (int i = 0; i < N / 2; i++)
    {
        char temp = n[i];
        n[i] = n[j];
        n[j] = temp;
        j++;
    }
}

void s_box0(char *n, char *res)
{
    int m[N / 2];
    int sbox0[N / 2][N / 2] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}};

    for (int i = 0; i < N / 2; i++)
    {
        if (n[i] == '0')
        {
            m[i] = 0;
        }
        else
        {
            m[i] = 1;
        }
    }

    int x = (m[3] * 1) + (m[0] * 2);
    int y = (m[2] * 1) + (m[1] * 2);
    int r = sbox0[x][y];

    if (r >= 2)
    {
        res[0] = '1';
    }
    else
    {
        res[0] = '0';
    }

    if (r % 2 == 0)
    {
        res[1] = '0';
    }
    else
    {
        res[1] = '1';
    }
}

void s_box1(char *n, char *res)
{
    int m[N / 2];
    int sbox1[N / 2][N / 2] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}};

    for (int i = 0; i < N / 2; i++)
    {
        if (n[i] == '0')
        {
            m[i] = 0;
        }
        else
        {
            m[i] = 1;
        }
    }

    int x = (m[3] * 1) + (m[0] * 2);
    int y = (m[2] * 1) + (m[1] * 2);
    int r = sbox1[x][y];

    if (r >= 2)
    {
        res[0] = '1';
    }
    else
    {
        res[0] = '0';
    }

    if (r % 2 == 0)
    {
        res[1] = '0';
    }
    else
    {
        res[1] = '1';
    }
}

void execution_round(char *key, char *temp, char *left_o, char *right_o)
{
    char left_t[N / 2];
    char right_t[N / 2];
    char s_out[N / 2];
    char perm[N / 2];
    char s0[N / 4];
    char s1[N / 4];

    split(N, temp, left_o, right_o);
    // print(N / 2, left_o);
    // print(N / 2, right_o);
    expansion(right_o, temp);
    // print(N, temp);
    xor(N, temp, key, temp);
    // print(N, temp);
    split(N, temp, left_t, right_t);
    // print(N / 2, left_t);
    // print(N / 2, right_t);
    s_box0(left_t, s0);
    s_box1(right_t, s1);
    // print(N / 4, s0);
    // print(N / 4, s1);
    merge(N / 2, s_out, s0, s1);
    // print(N / 2, s_out);
    permutation(s_out, perm);
    // print(N / 2, perm);
    xor(N / 2, left_o, perm, left_o);
    // print(N / 2, left_o);
    // print(N / 2, right_o);
}

void key_permutation10(char *key, char *res)
{
    res[0] = key[2];
    res[1] = key[4];
    res[2] = key[1];
    res[3] = key[6];
    res[4] = key[3];
    res[5] = key[9];
    res[6] = key[0];
    res[7] = key[8];
    res[8] = key[7];
    res[9] = key[5];
}

void key_permutation8(char *l, char *r, char *res)
{
    res[0] = r[0];
    res[1] = l[2];
    res[2] = r[1];
    res[3] = l[3];
    res[4] = r[2];
    res[5] = l[4];
    res[6] = r[4];
    res[7] = r[3];
}

void key_generator(char *key_1, char *key_2, char *key)
{
    char tempk[K];
    char left_ko[K / 2];
    char right_ko[K / 2];
    char left_kt[K / 2];
    char right_kt[K / 2];

    key_permutation10(key, tempk);
    // print(K, tempk);
    split(K, tempk, left_ko, right_ko);
    // print(K / 2, left_ko);
    // print(K / 2, right_ko);
    shift_left(1, K / 2, left_ko, left_kt);
    shift_left(1, K / 2, right_ko, right_kt);
    // print(K / 2, left_kt);
    // print(K / 2, right_kt);
    key_permutation8(left_kt, right_kt, key_1);
    // print(N, key_1);
    shift_left(2, K / 2, left_kt, left_ko);
    shift_left(2, K / 2, right_kt, right_ko);
    // print(K / 2, left_ko);
    // print(K / 2, right_ko);
    key_permutation8(left_ko, right_ko, key_2);
    // print(N, key_2);
}

int main(int argc, char *argv[])
{
    if (argc != 1 && argc != 3)
    {
        printf("Wrong input!\n");
        return 1;
    }
    if (argc == 3 && ((strlen(argv[1]) != N) || (strlen(argv[2]) != K)))
    {
        printf("Wrong input!\n");
        return 1;
    }

    char plaintext[N] = "01010001";
    char key[K] = "0101001100";

    if (argc == 3)
    {
        for (int i = 0; i < N; i++)
        {
            if (argv[1][i] != '0' && argv[1][i] != '1')
            {
                printf("Wrong input!\n");
                return 1;
            }
            plaintext[i] = argv[1][i];
        }
        for (int i = 0; i < K; i++)
        {
            if (argv[2][i] != '0' && argv[2][i] != '1')
            {
                printf("Wrong input!\n");
                return 1;
            }
            key[i] = argv[2][i];
        }
    }
    char ciphertext[N];

    // Key Generation
    char key_1[N];
    char key_2[N];

    key_generator(key_1, key_2, key);

    //Rounds
    char temp[N];
    char left_o[N / 2];
    char right_o[N / 2];

    printf("Plaintext: ");
    print(N, plaintext);

    initial_permutation(plaintext, temp);
    execution_round(key_1, temp, left_o, right_o);
    merge(N, temp, right_o, left_o);
    execution_round(key_2, temp, left_o, right_o);
    merge(N, temp, left_o, right_o);
    final_permutation(temp, ciphertext);

    printf("Ciphertext: ");
    print(N, ciphertext);
    return 0;
}