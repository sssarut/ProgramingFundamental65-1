#include <stdio.h>

int main(void)
{
    FILE *fp;
    struct player
    {
        char    name[50];
        int     level;
        int     score;
    };
    int i;
    typedef struct player player;
    player  p[5], ptr;
    i = 0;

    fp = fopen("my.txt", "w");
    while (i < 5)
    {
        printf("Insert the name, level, score of player %d : ", i + 1);
        scanf("%s %d %d", &p[i].name, &p[i].level, &p[i].score);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        fprintf(fp, "Name : %s Level : %d Score : %d\n", p[i].name, p[i].level, p[i].score);
        i++;
    }
    fclose(fp);
}