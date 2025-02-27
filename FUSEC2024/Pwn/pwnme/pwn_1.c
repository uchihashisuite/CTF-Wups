#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void hacked()
{
    FILE *file = fopen("flag.txt", "r");
    if (file == NULL)
    {
        printf("Could not open file flag.txt\n");
        return;
    }

    char buffer[256]; // Buffer to hold the file contents

    printf("Flag content:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(file);
    printf("\nThis function is TOP SECRET! How did you get in  :O\n");
}

void register_name()
{
    char buffer[16];

    printf("Name:\n");
    fflush(stdout);
    scanf("%s", buffer);
    printf("Hi there, %s\n", buffer);
}

int main()
{
    register_name();

    return 0;
}