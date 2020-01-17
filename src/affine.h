#ifndef AFFINE_H
#define AFFINE_H

#define AFFINE_ALPHABET_SIZE 26

char affineToPlain(char affine, intmax_t a, intmax_t b);
char plainToAffine(char plain, intmax_t a, intmax_t b);
char* affineEncrypt(char* plain, intmax_t a, intmax_t b);
char* affineDecrypt(char* encrypted, intmax_t a, intmax_t b);

#endif
