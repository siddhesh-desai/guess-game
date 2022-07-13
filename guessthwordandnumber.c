#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define WORDS 10
#define WORDLEN 40
#define CHANCE 7

bool srand_called = false;

int i_rnd(int i)
{

    if (!srand_called)
    {

        srand(time(NULL) << 10);
        srand_called = true;
    }

    return rand() % i;
}

char *decrypt(char *code)
{

    int hash = ((strlen(code) - 3) / 3) + 2;
    char *decrypt = malloc(hash);
    char *toFree = decrypt;
    char *word = code;

    for (int ch = *code; ch != '\0'; ch = *(++code))
    {

        if ((code - word + 2) % 3 == 1)
        {
            *(decrypt++) = ch - (word - code + 1) - hash;
        }
    }

    *decrypt = '\0';

    return toFree;
}

void printBody(int mistakes, char *body)
{

    printf("\tMistakes :%d\n", mistakes);
}

void printWord(char *guess, int len)
{

    printf("\t");

    for (int i = 0; i < len; ++i)
    {

        printf("%c ", guess[i]);
    }

    printf("\n\n");
}

int main()
{

    int option1;
    int counter = 1;
    int usernum, mynum;

    printf("\nHello! Welcome to Guesses!\n");
    printf("\nWhat would you like to guess?\n\n");
    printf("1 - Word \n2 - Number\n\n");

    scanf("%d", &option1);

    if (option1 == 1)
    {

        printf("\n\tSo let's play 'Guess the Word'");

        printf("\n\n\t Rules : ");
        printf("\n\t - Maximum 7 mistakes are allowed.");
        printf("\n\t - All alphabets are in lower case.");
        printf("\n\t - All words are name of very popular Websites. eg. Google");

        printf("\n\t Syntax : Alphabet");
        printf("\n\t Example : a \n\n");

        char values[WORDS][WORDLEN] = {"N~mqOlJ^tZletXodeYgs", "gCnDIfFQe^CdP^^B{hZpeLA^hv",
                                       "7urtrtwQv{dt`>^}FaR]i]XUug^GI", "aSwfXsxOsWAlXScVQmjAWJG",
                                       "cruD=idduvUdr=gmcauCmg]", "BQt`zncypFVjvIaTl]u=_?Aa}F",
                                       "iLvkKdT`yu~mWj[^gcO|", "jSiLyzJ=vPmnv^`N]^>ViAC^z_",
                                       "xo|RqqhO|nNstjmzfiuoiFfhwtdh~", "OHkttvxdp|[nnW]Drgaomdq"};

        char *body = malloc(CHANCE + 1);

        int id = i_rnd(WORDS);
        char *word = decrypt(values[id]);
        int len = strlen(word);
        char *guessed = malloc(len);
        char falseWord[CHANCE];

        memset(body, ' ', CHANCE + 1);
        memset(guessed, '_', len);
        char guess;
        bool found;
        char *win;

        int mistakes = 0;
        setvbuf(stdin, NULL, _IONBF, 0);

        do
        {

            found = false;
            printf("\n\n");
            printBody(mistakes, body);
            printf("\n\n");
            printf("\tFalse Letters : ");

            if (mistakes == 0)
            {
                printf("None\n");
            }

            for (int i = 0; i < mistakes; ++i)
            {

                printf("%c", falseWord[i]);
            }

            printf("\n\n");
            printWord(guessed, len);
            printf("\tGive me a alphabet in lower case : ");

            do
            {
                scanf("%c", &guess);
            } while (getchar() != '\n');

            for (int i = 0; i < len; ++i)
            {

                if (word[i] == guess)
                {

                    found = true;
                    guessed[i] = guess;
                }
            }

            if (!found)
            {

                falseWord[mistakes] = guess;
                mistakes += 1;
            }

            win = strchr(guessed, '_');
        } while (mistakes < CHANCE && win != NULL);

        if (win == NULL)
        {

            printf("\n");
            printWord(guessed, len);
            printf("\n\tCongrats! You have won.\n");
            printf("\tThe word is %s\n\n", word);
        }
        else
        {

            printf("\n");
            printBody(mistakes, body);
            printf("\n\n\tBetter try next time.");
            printf(" The word was %s\n\n", word);
        }

        free(body);
        free(word);
        free(guessed);
        return EXIT_SUCCESS;
    }

    else if (option1 == 2)
    {

        srand(time(NULL));
        mynum = rand() % 100;

        printf("\n\tSo let's play 'Guess the Number'");
        printf("\n\n\tYou have to guess a number from 0 to 100 in 7 chances");
        printf("\n\tAnd ofcourse, I'll be giving you hints at each step.");
        printf("\n\n\tSo let's begin with you\n");
        printf("\n\tStart with a number - ");

        scanf("%d", &usernum);

        while (1)
        {

            if (counter < 8)
            {

                if (usernum == mynum)
                {

                    printf("\n\n\tYes! You got it right!");
                    break;
                }
                else if (usernum > mynum)
                {

                    printf("\n\tThe number is smaller than your guess\n");
                    printf("\tTry Again - ");
                    scanf("%d", &usernum);
                }
                else
                {

                    printf("\n\tThe number is larger than your guess\n");
                    printf("\tTry Again - ");
                    scanf("%d", &usernum);
                }

                ++counter;
            }
            else
            {

                printf("\n\tSorry! You are out of moves!\n");
                printf("\tThe number was %d.", mynum);
                break;
            }
        }
    }
    else
    {

        printf("\nSorry, couldn't get you. Please enter a valid choice!\n");
        return 0;
    }
}