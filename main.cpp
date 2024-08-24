#include "raylib.h"
#include <vector>
#include <algorithm>
#include <thread>  // For delay

const int screenWidth = 800;
const int screenHeight = 600;

const int arraySize = 60;
std::vector<int> array(arraySize);

void InitializeArray() {
    for (int i = 0; i < arraySize; i++) {
        array[i] = GetRandomValue(10, screenHeight - 10);
    }
}

//Bubble Sort O(N*N)
void BubbleSortStep(int &i, int &j, bool &swapped) {
    if (i < arraySize - 1) {
        if (j < arraySize - i - 1) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
            j++;
        } else {
            if (!swapped) {
                i = arraySize; // Exit the loop if no swaps were made
            } else {
                j = 0;
                i++;
                swapped = false;
            }
        }
    }
}

//Insertion Sort O(N*N)
void InsertionSortStep(int &i, int &j) {
    if (i < arraySize) {
        int key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
        i++;
    }
}

//Selection Sort O(N*N)
void SelectionSortStep(int &i, int &j, int &minIndex) {
    if (i < arraySize - 1) {
        if (j < arraySize) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
            j++;
        } else {
            std::swap(array[i], array[minIndex]);
            i++;
            j = i + 1;
            minIndex = i;
        }
    }
}

void DrawArray(int currentI, int currentJ) {
    for (int i = 0; i < arraySize; i++) {
        Color color = (i == currentI || i == currentJ) ? RED : WHITE;
        DrawRectangle(i * (screenWidth / arraySize), screenHeight - array[i], screenWidth / arraySize, array[i], color);
    }
}

int main() {
    InitWindow(screenWidth, screenHeight, "Sorting Visualizer - Insertion Sort");

    InitializeArray();

    int i = 1, j = 0,minIndex = 0;
    bool swapped=false;

    SetTargetFPS(240);  // Set a moderate FPS for smoother visualization

    while (!WindowShouldClose()) {
        //BubbleSortStep(i, j,swapped);
        //SelectionSortStep(i, j,minIndex);
        InsertionSortStep(i, j);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawArray(i, j);

        EndDrawing();

        // Introduce a delay to control the speed of the visualization
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    CloseWindow();
    
    return 0;
}
