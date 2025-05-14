/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;
int pontuacao = 0;
int x_paddle = MAXX*0.5, y_paddle = MAXY*0.9;
int incX = 1, incY = 1;

void printPaddle(int nextX) {
    screenSetColor(CYAN, DARKGRAY);
    
    screenGotoxy(x_paddle, y_paddle);
    printf("     ");

    x_paddle = nextX;
    screenGotoxy(x_paddle, y_paddle);
    printf("=====");
}

void printHello(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf(" ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("9");
}

void printKey(int ch)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");
    
    if (ch == 27) screenGotoxy(36, 23);
    else screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

void printPontuacao()
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(0, 0);
    printf("Pontuação: ");

    screenGotoxy(12, 0);
    printf(" ");
    screenGotoxy(12, 0);
    printf("%d ", pontuacao);
}

int main() 
{
    static int ch = 0;
    static long timer = 0;

    screenInit(1);
    keyboardInit();
    timerInit(100);

    printHello(x, y);
    screenUpdate();

    while (ch != 10) //enter or 5s
    {
        // Handle user input
        if (keyhit()) 
        {
            ch = readch();
            printKey(ch);

            switch (ch)
            {
                case 97:
                    if (x_paddle - 1 > MINX)
                        printPaddle(x_paddle-1);
                    break;
                case 100:
                    if (x_paddle + strlen("=====") + 1 < MAXX)
                        printPaddle(x_paddle+1);
                    break;

            }

            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {
            int newX = x + incX;
            if (newX >= (MAXX -strlen("O") -1) || newX <= MINX+1) incX = -incX;
            int newY = y + incY;
            if (newY >= MAXY-1 || newY <= MINY+1) incY = -incY;

            if ( (newX >= x_paddle && newX <= x_paddle + strlen("=====") )
                && (newY >= y_paddle && newY <= y_paddle + 1)) {
                // incX *= -1;
                pontuacao++;
                incY *= -1;
            }
        

            printHello(newX, newY);
            printPaddle(x_paddle);
            printPontuacao();
            screenUpdate();
            timer++;
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
