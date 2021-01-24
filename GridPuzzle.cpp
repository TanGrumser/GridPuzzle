#include <iostream>

using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const int SIZE_X = 5;
const int SIZE_Y = 5;
const int STARTING_POSITION = 20;
const Direction STARTING_DIRECTION = Direction::UP;

void printField (int *field) {
    for (int i = 0; i < SIZE_X * SIZE_Y; i++) {
        cout << field[i];
        
        if (i % 5 == 4) {
            cout << endl;
        } else {
            cout << "  ";
        }
    }
}

void rotate (Direction *direction) {
    switch (*direction) {
        case Direction::UP:    *direction = Direction::RIGHT; break;
        case Direction::DOWN:  *direction = Direction::LEFT; break;
        case Direction::LEFT:  *direction = Direction::UP; break;
        case Direction::RIGHT: *direction = Direction::DOWN; break;
    }
}

bool simulateWalkPath(int *aField) {
    int steps = 0;
    bool result = false;
    int *field = (int*) malloc (sizeof(int) * SIZE_X * SIZE_Y);
    int position = STARTING_POSITION;
    Direction direction = STARTING_DIRECTION;

    // Create a copy of the field.
    for (int i = 0; i < SIZE_X * SIZE_Y; i++) {
        field[i] = aField[i];
    }

    while (steps < 400) { // Just walk for some time to see if every field was visited.
        // Move to next field and mark old field as already visited.
        field[position] = 2;
        int oldPosition = position;

        switch (direction) {
            case Direction:: UP: 
                if (position < SIZE_X) { // If we're in the upper row.
                    rotate(&direction);
                } else {
                    position -= SIZE_X;
                }
            break;

            case Direction::RIGHT: 
                if (position % SIZE_X == SIZE_X - 1) { // If we're in the right collumn.
                    rotate(&direction);
                } else {
                    position++;
                }
            break;

            case Direction::LEFT: 
                if (position % 5 == 0) { // If we're in the left collumn.
                    rotate(&direction);
                } else {
                    position--;
                }
            break;

            case Direction::DOWN: 
                if (position >= SIZE_X * (SIZE_Y - 1)) { // If we're in the lowest row.
                    rotate(&direction);
                } else {
                    position += SIZE_X;
                }
            break;
        }

        if (field[position] == 1) { // If we ran into a boulder.
            position = oldPosition;
            rotate(&direction);
        } else {
            steps++;
        }
    }
    
    for (int i = 0; i < SIZE_X * SIZE_Y; i++) {
        if (field[i] == 0) { // If theres a empty spot that we haven't reached.
            return false;
        }
    }

    return true;
}

bool findSolution (int *field, int numberOfRocks) {
    if (numberOfRocks <= 0) {
        return simulateWalkPath(field);
    }

    for (int i = 0; i < SIZE_X * SIZE_Y; i++) {
        if (field[i] == 0 && i != STARTING_POSITION) { // If we're at and empty spot that's not the starting position.
            field[i] = 1; // We place a boulder.

            if (findSolution(field, numberOfRocks - 1)) { // A solution was found.
                return true;
            } else {
                field[i] = 0; // Otherwise we remove the bolder to place it on another field.

            }
        } else {
            continue;
        }
    }

    return false;
}

int main() {
    int numberOfRocks;
    int *field = (int*) malloc (sizeof(int) * SIZE_X * SIZE_Y);
    
    cout << "Enter the number of rocks to place: ";
    cin >> numberOfRocks;

    for (int i = 0; i < SIZE_X * SIZE_Y; i++) {
        field[i] = 0; 
    }

    if (!findSolution(field, numberOfRocks)) {
        cout << "No solution was found." << endl;
    } else {
        cout << "A solution was found:" << endl;
        printField(field);
    }
}
