#include <raylib.h>
#include <vector>
#include <iostream>
#include <algorithm>

void swap(int& a, int& b)
{
    int temp = b;
    b = a;
    a = temp;
}

void selectionSort(std::vector<int>& arr, int& i)
{
    const int n = arr.size();
    // One by one move boundary of
    // unsorted subarray
    for (; i < n - 1; i++)
    {
        // Find the minimum element in
        // unsorted array
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element
        // with the first element
        if (min_idx != i)
        {
            swap(arr[min_idx], arr[i]);
            return;
        }
    }
}

int main()
{
    Color darkBlue = {44, 44, 127, 255};
    const int wWidth = 900, wHeight = 720;
    InitWindow(wWidth, wHeight, "Raylib Tetris");
    SetTargetFPS(60);
    srand(time(NULL)*time(NULL));

    const int nMin = 10, nMax = 700, nCount = 80;
    std::vector<int> nums;
    nums.reserve(nCount);


    for (size_t i = 0; i < nCount; i++)
    {
        nums.push_back(rand()%(nMax-nMin) + nMin);
    }
    

    int i = 0;
    double lastUpdateTime = 0;

    std::vector<Color> colors = {
        {0, 255, 0, 255},       // green
        {50, 205, 50, 255},     // lime green
        {173, 255, 47, 255},    // yellow green
        {255, 255, 0, 255},     // yellow
        {255, 165, 0, 255},     // orange
        {255, 69, 0, 255},      // orange red
        {255, 0, 0, 255},       // red
        {128, 0, 0, 255},       // maroon
        {139, 0, 0, 255},       // dark red
        {165, 42, 42, 255}      // brown
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        
        for (size_t i = 0; i < nums.size(); i++)
        {
            int value = std::clamp(nums[i], nMin, nMax);

            // Calculate the index in the color list
            int range = nMax - nMin;
            int numColors = colors.size();
            int colorIndex = (value - nMin) * (numColors - 1) / range;

            Color c =  colors[colorIndex];


            float x = (i+1)*11, y = wHeight-nums[i], w = 8, h =nums[i];
            // DrawRectangle(x, y, w, h, WHITE);
            DrawRectangleRounded({x, y, w, h}, 2, 32, c);
        }
        
        const double currentTime = GetTime();
        if(currentTime-lastUpdateTime > 0.6)
        {
            lastUpdateTime = currentTime;
            selectionSort(nums, i);
        }

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}