#include "encrypt.h"


//function to encrypt the message
char *encrypt_pswd(char *msg)
{   
    int i;
    char *str = mx_strdup(msg);
    int key = 2;

    printf("\n\n\n\n\n");
    printf("THERETHERE");
    printf("\n\n\n\n\n");

    for(i = 0; (i < 100 && str[i] != '\0'); i++) {
        if (str[i] % 2 == 0) {
            str[i] += key;
        } else {
            str[i] -= key;
        }
    }
    printf("ENCRYPT_PSWD encrypted: %s\n", str);

    return str;
}

char *decrypt_pswd(char *msg)
{
    int i;
    char *str = mx_strdup(msg);
    int key = 2;
    for(i = 0; (i < 100 && str[i] != '\0'); i++) {
        if (str[i] % 2 == 0) {
            str[i] -= key;
        } else {
            str[i] += key;
        }
    }
    return str;
}

