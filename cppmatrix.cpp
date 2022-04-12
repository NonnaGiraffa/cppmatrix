#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

const int width = 75, height = (int)(width / 2);
const int vectorial_height = 1; //Dedicated arrays wich apply to every column
char base[height + vectorial_height][width];
bool bitmap[height][width];

char rand_letter() {
    char character = (rand() % (90 - 65 + 1)) + 65;
    if (rand() % 2) {
        character += 32;
    }
    return character;
}

int rand_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void generate(int column) {
    int gen_rate = 5; // %
    int regen_rate = 75; // %
    if (bitmap[1][column] ){
        if (rand_int(0, 100) <= regen_rate) {
        bitmap[0][column] = true;
        }
    }
    else {
        if (rand_int(0, 100) < gen_rate) {
            bitmap[0][column] = true;
        }
    }
}

void vectorial_view() {
    for (int i = 0; i < vectorial_height; i++) {
        for (int j = 0; j < width; j++) {
            cout << (int)base[height + i][j];
        }
        cout << "\n";
    }

}

void view() {
    system("clear");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (bitmap[i][j]) {
                if(i != height - 1 && bitmap[i + 1][j]) {
                    cout << "\033[33m" << base[i][j];
                }
                else {
                    cout << "\033[0m" <<base[i][j];
                }
            }
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }
}

void slide(int column) {
    for (int i = height - 1; i >= 0; i --) {
        if (bitmap[i][column]) {
            bitmap[i][column] = false;
            if (i != height - 1) {
                bitmap[i + 1][column] = true;
            }
        }
    }
}

void init_base() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            base[i][j] = rand_letter();
        }
    }
    //Speed gen
    for (int i = 0; i < width; i++) {
        base[height + /*Vectorial height*/ 0][i] = rand_int(1, 5);
    }
}


void update() {
    bool updating = true;
    while (updating) {
        usleep(50000);
        for (int i = 0; i < width; i++) {
            if (rand_int(1, 5) <= base[height + /*Vectorial height*/ 0][i]) {
                slide(i);
                generate(i);
            }
        }
        view();
    }
}

int main() {
    srand(time(NULL));
    init_base();
    view();
    update();
}