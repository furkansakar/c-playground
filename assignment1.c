#include <stdio.h>
#include <stdlib.h>

int find_length(int value)
{
    int count = 0;
    while (value != 0)
    {
        // n = n/10
        value /= 10;
        ++count;
    }
    return count;
}

void main(void)
{
    // buffer
    FILE *fp;
    FILE *fp_replace;

    fp = fopen("test.txt", "r");

    int number;
    while (fscanf(fp, "%d", &number) == 1) // expect 1 successful conversion
    {
        // process buffer
        printf("Number: %i", number);
        fp_replace = fopen("test.txt", "r+");
        int number2;
        int any_occur = 0;
        while (fscanf(fp_replace, "%d", &number2) == 1) // expect 1 successful conversion
        {
            if (number == number2)
            {
                if (any_occur>0)
                {
                    fseek(fp_replace, -find_length(number), SEEK_CUR);
                    for (int i = 0; i < find_length(number); i++)
                    {
                        fprintf(fp_replace, "%c", ' ');
                    }
                    fflush(fp_replace);
                }
                any_occur=1;
            }
        }
        fclose(fp_replace);
    }
    if (feof(fp))
    {
        // hit end of file
    }
    else
    {
        // some other error interrupted the read
    }

    //fputs("This is testing for fputs...\n", fp);

    fclose(fp);
}

