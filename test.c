
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void test(char *data)
{
    strlcpy(data, "hello wor", 10);
}

int main()
{
    char *data;

    data = NULL;
    data = malloc(sizeof(char) * 10);

    printf("%s\n", data);
    test(data);
    printf("%s\n", data);
}