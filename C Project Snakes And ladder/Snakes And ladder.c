#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int ladder_start[8] = {1, 7, 9, 21, 28, 51, 71, 80};
int ladder_end[8] = {38, 14, 31, 42, 84, 67, 91, 100};
int snake_start[8] = {17, 54, 62, 64, 87, 93, 95, 98};
int snake_end[8] = {7, 34, 19, 60, 24, 73, 75, 79};

char p1_name[100] = {' '}, p2_name[100] = {' '};
int i, j;

int rollDice();
int findIndex(int arr[], int val, int len);

void renderBoard(int player1, int player2)
{
    for (i = 0; i < 10; i++)
    {
        printf("+");
        for (j = 0; j < 10; j++)
        {
            printf("-------+");
        }
        printf("\n|");
        for (j = 0; j < 10; j++)
        {
            int num = i % 2 == 0 ? 100 - (i * 10 + j) : 90 - (i * 10 - j) + 1;
            int ladder_start_indx = findIndex(ladder_start, num, 8);
            int ladder_end_indx = findIndex(ladder_end, num, 8);
            int snake_start_indx = findIndex(snake_start, num, 8);
            int snake_end_indx = findIndex(snake_end, num, 8);

            if (ladder_start_indx > -1)
                printf(" L->%-3d|", ladder_end[ladder_start_indx]);
            else if (ladder_end_indx > -1)
                printf(" L<-%-3d|", ladder_start[ladder_end_indx]);
            else if (snake_start_indx > -1)
                printf(" S->%-3d|", snake_end[snake_start_indx]);
            else if (snake_end_indx > -1)
                printf(" S<-%-3d|", snake_start[snake_end_indx]);
            else
                printf("       |");
        }
        printf("\n|");
        for (j = 0; j < 10; j++)
        {
            int num = i % 2 == 0 ? 100 - (i * 10 + j) : 90 - (i * 10 - j) + 1;
            if (player1 == num)
                printf("    %c%c |", p1_name[0], p1_name[1]);

            else if (player2 == num)
                printf("    %c%c |", p2_name[0], p2_name[1]);

            else
                printf("   %-3d |", num);
        }
        printf("\n");
    }
    printf("+");
    for (j = 0; j < 10; j++)
    {
        printf("-------+");
    }
    printf("\n");
}

int main()
{
    int p1 = 0, p2 = 0;
    int p1_status = FALSE, p2_status = FALSE;
    int dice = 0, temp = 0;

    printf("Enter Player 1 Name : \n");
    scanf("%s", &p1_name);
    printf("Enter Player 2 Name : \n");
    scanf("%s", &p2_name);
    printf("Lets Start Game.........\n\n");

    int i = 0, c;
    c = getchar();
    time_t t;
    srand((unsigned)time(&t));

    renderBoard(p1, p2);
    while (p1 < 100 && p2 < 100)
    {
        temp = 0;
        int status = i % 2 ? p1_status : p2_status;
        int player = i % 2 ? p1 : p2;
        printf("%s Turn : \n", i % 2 ? p1_name : p2_name);

        if (!status)
        {
            do
            {
                dice = rollDice();
                printf("Rolling Dice.....\nYou Got Number %d\n", dice);
                temp += dice;
                if (temp > 6)
                {
                    status = TRUE;
                    player = temp;
                }
            } while (dice == 6);
        }

        else
        {
            int ind;
            do
            {
                dice = rollDice();
                printf("Rolling Dice.....\nYou Got Number %d\n", dice);
                temp += dice;
            } while (dice == 6);

            if ((ind = findIndex(ladder_start, player + temp, 8)) != -1)
            {
                printf("Got a Ladder from %d to %d\n", player + temp, ladder_end[ind]);
                player = ladder_end[ind];
            }
            else if ((ind = findIndex(snake_start, player + temp, 8)) != -1)
            {
                printf("Found a Snake on %d to %d\n", player + temp, snake_end[ind]);
                player = snake_end[ind];
            }
            else if ((player + temp) <= 100)
            {
                player += temp;
            }
        }

        if (i % 2)
        {
            p1 = player;
            p1_status = status;
        }
        else
        {
            p2 = player;
            p2_status = status;
        }

        renderBoard(p1, p2);
        printf("%s is at %d, Press Enter to Continue.........\n", i % 2 ? p1_name : p2_name, player);
        c = getchar();
        i++;
    }
    printf("Game Over\n");
    if (p1 == 100)
    {
        printf("%s Won the Game\n\n", p1_name);
    }
    else if (p2 == 100)
    {
        printf("%s Won the Game\n\n", p2_name);
    }

    return 0;
}

int rollDice()
{
    return 1 + rand() % 6;
}

int findIndex(int arr[], int val, int len)
{
    int check = -1;
    for (int i = 0; i < len; i++)
    {
        if (val == arr[i])
        {
            check = i;
        }
    }
    return check;
}
