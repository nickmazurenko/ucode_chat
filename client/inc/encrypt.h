#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long int encryption_key();
long int cd(long int, int f);
char *encrypt_pswd(char *msg);

#endif