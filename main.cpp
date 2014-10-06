#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
/*declarations*/
void print_greeting();
void print_scoreboard(int,int);
int play_nim(int);
void get_human_move(int& , int& , int&  , char&, int& );
void get_computer_move(int& , int& , int&  , char&, int& );
void print_heaps(int,int,int);
bool user_wishes_to_continue();
int toggle_players(int);

int main()
{
    print_greeting();
    //int starting_player = 1;
    int starting_player = rand() % 2;
    int human_score = 0;
    int computer_score = 0;
    do{
        starting_player = play_nim(starting_player);
        if (starting_player == 1)
          computer_score++;
        else
          human_score ++;
     print_scoreboard(human_score, computer_score);
    }while(user_wishes_to_continue());

    return 0;
}

void print_greeting(){
  cout << "Welcome to the Ancient Game of Nim!" << endl;
}

void print_scoreboard(int human_score, int computer_score){
    cout << "****************************" << endl;
    cout << "Player 1 (Human):      " << human_score << endl;
    cout << "Player 2 (Computer):   " << computer_score << endl;
}

int toggle_players(int current_player){
    return current_player == 1 ? 2 : 1;
};

int play_nim(int starting_player){
    int heap1 = 3;
    int heap2 = 4;
    int heap3 = 5;

    int current_player = starting_player;
    char chosen_heap='Z';
    int number_removed=0;

    cout << "Player "<<starting_player<<" goes first this time."<< endl;

    do{

        cout << "Player " << current_player << " enter your move." << endl;
        print_heaps(heap1,heap2,heap3);
        if(current_player == 1){
            get_human_move(heap1,heap2,heap3,chosen_heap,number_removed);
        }else{
            get_computer_move(heap1,heap2,heap3,chosen_heap,number_removed);
        }
        current_player = toggle_players(current_player);
    }while(heap1+heap2+heap3 > 0);
    return current_player;
}

bool user_wishes_to_continue(){

    string user_input;
    bool valid = false;
    bool contin = false;
    do{
        cout<<"Would you like to continue? (y/n)";
        getline(cin,user_input);
        if (user_input == "y" ||
            user_input == "Y"){
            valid = true;
            contin = true;
            }else if(
            user_input == "n" ||
            user_input == "N"){
           valid = true;
           contin = false;
        }else{
            valid = false;
            cout << "Bad input!  Try Again." << endl;
        }
    }while (!valid);
    return contin;
}
void get_human_move(int &heap1, int &heap2, int &heap3, char &chosen_heap, int &number_removed ){

    bool isGoodHeap = false;
    bool isGoodQuant = false;
    int heap_size = 0;
    int selected_heap = 0;
    string user_input;
    do{
        isGoodHeap = false;
        isGoodQuant = false;
        getline(cin,user_input);
        chosen_heap = user_input[0];
        number_removed = atoi(&user_input[1]);
        if((chosen_heap == 'A' || chosen_heap == 'a') && heap1 > 0) {
            heap_size = heap1;
            selected_heap = 1;
            isGoodHeap = true;
        }else if((chosen_heap == 'B' || chosen_heap == 'b') && heap2 > 0) {
           heap_size = heap2;
            selected_heap = 2;
            isGoodHeap = true;
        }else if((chosen_heap == 'C' || chosen_heap == 'c') && heap3 > 0) {
            heap_size = heap3;
            selected_heap = 3;
            isGoodHeap = true;
        }else{
            isGoodHeap = false;
        }
        if(isGoodHeap){
            if(number_removed <= heap_size && number_removed > 0){
                isGoodQuant = true;
            }else{
                isGoodQuant = false;
            }
        }
        if(!isGoodHeap){
            cout << "The heap you selected, " << chosen_heap << ", was invalid" << endl;
        }else if(isGoodHeap && !isGoodQuant){
            cout << "The heap you selected was acceptable, but the quantity, " << number_removed << ", was invalid" << endl;
        }

    }while(!(isGoodHeap && isGoodQuant));

    switch(selected_heap){
    case 1: heap1 -= number_removed;break;
    case 2: heap2 -= number_removed;break;
    case 3: heap3 -= number_removed;break;
    }
    return;
}
void get_computer_move(int &heap1, int &heap2, int &heap3, char &chosen_heap, int &number_removed ){

//    get_human_move(heap1,heap2,heap3,chosen_heap,number_removed);
    int nim_number = heap1 ^ heap2 ^ heap3;
    //No good move
    if (nim_number == 0){
      if (heap1 > 0){
        chosen_heap = 'A';
        heap1 -= 1;
      }else if(heap2 > 0){
        chosen_heap = 'B';
        heap2 -= 1;
      }else{
        chosen_heap = 'C';
        heap3 -= 1;
      }
        number_removed = 1;
    }else{
        if((heap1 ^ nim_number) < heap1){
            chosen_heap = 'A';
            number_removed = heap1-(heap1 ^ nim_number);
            heap1 -= number_removed;
        }else if((heap2 ^ nim_number) < heap2){
            chosen_heap = 'B';
            number_removed = heap2-(heap2 ^ nim_number);
            heap2 -= number_removed;
        }else{
            chosen_heap = 'C';
            number_removed = heap3-(heap3 ^ nim_number);
            heap3 -= number_removed;
        }
    }
    cout << "Computer move is " << chosen_heap << number_removed<< endl;

}
void print_heaps(int heap1, int heap2, int heap3){
    cout << "A: " << heap1 << endl;
    cout << "B: " << heap2 << endl;
    cout << "C: " << heap3 << endl;
}
