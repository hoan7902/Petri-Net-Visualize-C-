#include "main.h"
//set console screen 
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 1200;
int main() {
    bool quit = false;
    textcolor(14);
    printMainMenu();  // define in PrintFunction.h 
    while (!quit) { 
         if (_kbhit()) { 
             char ch = _getch();
             switch (ch)
             {
             case '1':
                 system("cls");
                 resizeConsole(SCREEN_HEIGHT - 200, SCREEN_WIDTH);
                 item1();
                 break;
             case '2':
                 system("cls");
                 resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);
                 
                 item2();
                 break;
             case '3':
                 system("cls");
                 resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);
                 item3();
                 break;
             case '4':
                 system("cls");
                 resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);
                 item4();
                 break;
             default:
                 quit = true;
                 break;
             }
         } 
    }
    system("cls");
    return 0; 
}
