#include <stdio.h>
#include <stdlib.h>

int find_length(int value)
{
    int count = 0;
    while (value != 0)
    {
        value /= 10;
        ++count;
    }
    return count;
}

void main(void)
{

    FILE *fp;
    FILE *fp_replace;
    int number = 0;

    fp = fopen("test.txt", "r");

    while (fscanf(fp, "%d", &number) == 1) 
    {
        // process buffer
        printf("Number: %i", number);
        fp_replace = fopen("test.txt", "r+");
        int number2;
        int number_of_occurance = 0;
        while (fscanf(fp_replace, "%d", &number2) == 1)
        {
            if (number == number2)
            {
                if (number_of_occurance>0)
                {
                    fseek(fp_replace, -find_length(number), SEEK_CUR);
                    for (int i = 0; i < find_length(number); i++)
                    {
                        fprintf(fp_replace, "%c", ' ');
                    }
                    fflush(fp_replace);
                }
                number_of_occurance++;
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

    fclose(fp);
}

