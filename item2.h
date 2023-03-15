#ifndef ITEM2_H_
#define ITEM2_H_ 
#include "main.h"
#include "graphics.h" 
#include "PrintFunctions.h" 
using namespace std; 
// L, R , T , B is defined in item1.h 

//Draw the petri net of item2 
void drawPetriNetItem2(map<string, int> marking) {
    //print the container petri net
    textcolor(5);
    printRectangle(L, R, T, B);
    //print transitions
    textcolor(12);
    printRectangle(L + 24, L + 30, T + 9, T + 11); 
    gotoxy(L + 25, T + 10); cout << "start";      
    printRectangle(L + 65, L + 72, T + 9, T + 11);
    gotoxy(L + 66 ,T + 10); cout << "change"; 
    ///print places
    textcolor(15);
    gotoxy(L + 5, T + 10); cout << "wait( )";
    gotoxy(L + 45,T + 10); cout << "inside( ) ";
    gotoxy(L + 85,T + 10); cout << "done( ) ";
    //set marking
    printNumOftoken(marking, "wait", L + 10, T + 10);
    printNumOftoken(marking, "inside", L + 52, T + 10);
    printNumOftoken(marking, "done", L + 90, T + 10);
    //print arcs 
    textcolor(8);
    inngang(L + 12, L + 24, T + 10);
    inngang(L + 30, L + 45, T + 10);
    inngang(L + 54, L + 65, T + 10);
    inngang(L + 72, L + 85, T + 10);
    //==============

    gotoxy (L + 1, T + 1) ; textcolor(11) ;
    cout<<"Item 2: Specialist network" ;
}

//display item 2 

// Firing transition automatically 
void auto_firingItem2(PetriNet N) {
    bool terminal = false;
    map<string, int> marking = N.getMarking();
    while (!terminal) {
        if (_kbhit()) {
            char c = _getch();
            if (c == '0') return;
        }
        terminal = true;
        if (N.firing("start")) {
            marking = N.getMarking();
            textcolor(9);
            inngang_Color(L + 12,L + 24 , T + 10);
            inngang_Color(L + 30, L + 45, T+ 10);
            drawPetriNetItem2(marking);
            gotoxy(L +2, T + 15);
            textcolor(15);
            cout << "Current state: ";  N.printMarking();
            terminal = false;
        }
        else if (N.firing("change")) {
            marking = N.getMarking();
            textcolor(9);
            inngang_Color(L + 54, L + 65, T + 10);
            inngang_Color(L + 72, L + 85, T + 10);
            drawPetriNetItem2(marking);
            gotoxy(L + 2, T + 15); textcolor(15);
            cout << "Current state: ";  N.printMarking();
            terminal = false;
        }
    }
}
// print menu 
void showMenuItem2() {
    int marginTop = T + 8;
    textcolor(10);
    printRectangle(R + 5, R + 55, marginTop - 5, marginTop - 1);
    textcolor(7);
    gotoxy(R + 6, marginTop - 4); cout << " This PetriNet describe the course of business";
    gotoxy(R + 6, marginTop - 3); cout << " around a specialist in this outpatient clinic ";
    gotoxy(R + 6, marginTop - 2); cout << " of hospital X. ";
    textcolor(3);
    printRectangle(R + 5, R + 55, marginTop, marginTop + 2);
    gotoxy(R + 6, marginTop + 1); cout << "Press 1 to set initial marking.";

    printRectangle(R + 5, R + 55, marginTop + 3, marginTop + 5);
    gotoxy(R + 6, marginTop + 4); cout << "Press 2 to start/stop auto firing";

    printRectangle(R + 5, R + 55, marginTop + 6, marginTop + 8);
    gotoxy(R + 6, marginTop + 7); cout << "Press 3 quit";
}


void item2() {
    //build the petri net 
    PetriNet N;
    //Init all place 
    N.pushPlace("wait");
    N.pushPlace("inside");
    N.pushPlace("done");
    //Init all transition
    N.pushTransition("start");
    N.pushTransition("change");
    // Init arcs between place and transition  
    N.arcPT("wait", "start");
    N.arcTP("start", "inside");
    N.arcPT("inside", "change");
    N.arcTP("change", "done");
    //==========================

    
    textcolor(7);
    map<string, int> marking = N.getMarking();     // get marking from petri net
    cout << "\n   Initial Marking :"; N.printMarking(); 
    drawPetriNetItem2(marking);
    showMenuItem2();
    bool quit = false;  // use to exits while loop 
    while (!quit) {
        if (_kbhit()) {  
            char ch = _getch();
            switch (ch) {
            case '1':
                gotoxy(L, B + 1);
                N.setMarking();
                system("cls");
                marking = N.getMarking();
                cout << "\nInitial Marking :"; N.printMarking();
                drawPetriNetItem2(marking);
                showMenuItem2();
                break;
            case '2':
                system("cls") ;
                marking = N.getMarking();
                cout << "\nInitial Marking :"; N.printMarking();
                drawPetriNetItem2(marking);
                printRectangle(R + 5, R + 55, T + 11, T + 13);
                gotoxy(R + 6, T + 12); cout << "Press 0 to start/stop auto firing";
                auto_firingItem2(N);
                showMenuItem2() ;
                break;
            case '3':
                quit = true;
                break;
            default:
                break;
            }
        }
    }
    N.cleanUp();
    printMainMenu();
}
#endif // !ITEM2_H_

