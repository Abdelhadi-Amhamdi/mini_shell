#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *data;
    int len;
    int i = 0;
    int index;

    scanf("%d %s %s %s %s", &len, data);
    while (data[i])
    {
        printf("%s\n", data);
        // if (strlen(data[i]) <= len)
        //     printf("%s\n", data[i]);
        // else
        // {
        //     index = 0;
        //     printf("%c", data[i][index]);
        //     data[i]++;
        //     while (data[i][index] && data[i][index + 1] != '\0')
        //         index++;
        //     printf("%d", index);
        //     printf("%c\n", data[i][index]);
        // }
        i++;
    }
    return (0);
}