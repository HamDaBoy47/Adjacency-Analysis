#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <array>
#include <set>
#include "Rectangle.h"

using namespace std;

// Constant variables 
const int max_y = 100;
const int max_width = 20;
const int max_height = 30;
int counting = 0;

// *Best case type="-b" 
// *Avr case type="-a"
// *Worst case type="-w"
// *Visualize "-p"
// *No visual "-n"
void BACaseGenerator(Rectangle allRects[], string type, string visual, int noRects) {

    srand(time(NULL) + noRects);
    int inner_limit;
    int outer_limit;

    if (type == "-w") {
        inner_limit = noRects * 0.9;
        outer_limit = 1;
    } else {
        inner_limit = 1 + rand() % (int)(noRects / (noRects * 0.1));
        outer_limit = noRects * 0.9;
    }

    fstream file;
    if (visual == "-p") {
        file.open ("RectDetails.csv", ios::out | ios::app);
        file << "id" << "," << "BLx" << "," << "BLy" << "," << "width" << "," << "height" << "\n";
    }

    // Original Rectangle
    int id = 0;
    int width = max_width + (rand() % max_width);
    int height = max_height + (rand() % max_height);
    int TRx = 0 + width;
    int TRy = 0 + height;

    allRects[0] = Rectangle(id, 0, 0, TRx, TRy);

    if (visual == "-p") {
        file << id << ", " << 0 << ", " << 0 << ", " << width << ", " << height << "\n";
    }

    // Keep track of Right and Left
    int prevRX = width;
    int prevLX = id;
    int prevTY = height;
    int prevW = width;

    for (int i = 0; i < outer_limit; i += inner_limit) {

        // Values for constructing all other rectangles
        int x, y, w, h, TRx, TRy;
        if (type == "-w") {
            inner_limit = noRects * 0.9;
        } else if (type == "-a") {
            inner_limit = 1 + rand() % (int)(noRects / (noRects * 0.1));
        } else if (type == "-b") {
            inner_limit = 1;
        }


        // Generate vertical column of rects
        for (int j = 1; j < inner_limit; ++j) {
            x = prevLX;

            if (type == "-w") {
                y = prevTY;
                w = prevW;
                h = max_height;
            } else if (type == "-a") {
                y = prevTY + (rand() % max_height); // Controls top and bottom touching
                w = prevW;
                h = 5 + (rand() % max_height);
            }
            else {
                y = prevTY + (rand() % max_height); // Controls top and bottom touching
                w = 1 + (rand() % prevW);
                h = 5 + (rand() % max_height);
            }

            
            TRx = x + w;
            TRy = y + h;

            allRects[i+j] = Rectangle(i+j, x, y, TRx, TRy);

            if (visual == "-p") {
                file << i+j << ", " << x << ", " << y << ", " << w << ", " << h << "\n";
            }

            prevTY = y + h;
            // prevBY = y;  
            counting += 1;
        }
        

        // Controls sides touching
        if (type == "-b") {
            x = prevRX + ((rand() % 1) + (rand() % (max_width / 2)));
        } else {
            x = prevRX;
        }
        
        y = rand() % (max_y / 2);
        w = 1 + (rand() % max_width);
        h = 1 + (rand() % max_height);
        TRx = x + w;
        TRy = y + h;

        allRects[i + inner_limit] = Rectangle(i + inner_limit, x, y, TRx, TRy);
        if (visual == "-p") {
            file << i + inner_limit << ", " << x << ", " << y << ", " << w << ", " << h << "\n";
        }

        // Update Left and Right values
        prevRX = x + w;
        prevLX = x;
        prevTY = y + h;
        prevW = w;
        counting += 1;
    }

    if (visual == "-p") {
        file.close();
    }
}

// Function to check if two rectangles are vertically adjacent on the right edge
bool isContact(Rectangle& r1, Rectangle& r2) {
    int rightX1 = r1.getRightX();
    int leftX2 = r2.getLeftX();
    int bottomY1 = r1.getBottomY();
    int topY1 = r1.getTopY();
    int bottomY2 = r2.getBottomY();
    int topY2 = r2.getTopY();

    // Check if the left side of r2 is adjacent to the right side of r1
    if(rightX1 == leftX2){
        // check if the rectangles touch
        if (bottomY1 == bottomY2 && topY1 == topY2){
            return true;
        }
        else if (bottomY1 == bottomY2 && (topY1 > topY2 || topY1 < topY2)) {
            return true;
        }
        else if ((bottomY1 < bottomY2 || bottomY1 > bottomY2) && topY1 == topY2) {
            return true;
        }
        else if(bottomY2 < bottomY1 && topY1 > topY2 && topY2 > bottomY1){
            return true;
        }
        else if(topY2 > topY1 &&  bottomY2 > bottomY1 && bottomY2 < topY1){
            return true;
        }
        else if(bottomY2 > bottomY1 && topY2 < topY1){
            return true;
        }
        else if(bottomY2 < bottomY1 && topY2 > topY1){
            return true;
        }
    }

    return false; // No adjacency found
}

void Solution(Rectangle allRects[], int zise) {

    for (int i = 0; i <= zise; ++i) {
        for (int j = 0; j <= zise; ++j) {
            if (i != j && isContact(allRects[i], allRects[j])) {
                // If the rectangles are in contact, call addToAdjList() method on the first rectangle
                allRects[i].addToAdjList(j);
            }
        }
    }
}

void LineSweep(Rectangle allRects[], Rectangle temp[], int size) {
    // Step 1: Sort rectangles based on left edge (x-coordinate)
    std::sort(temp, temp + size, [](Rectangle& a,Rectangle& b) {
        return a.getLeftX() < b.getLeftX();
    });

    // Step 2: Initialize active set
    std::set<int> activeSet;  // Store indices of rectangles

    // Step 3-5: Traverse sorted rectangles and find adjacent rectangles
    for (int i = 0; i <= size; ++i) {
        int currentRectIndex = temp[i].getRectId();

        // Step 4a: Add current rectangle to active set
        activeSet.insert(currentRectIndex);

            // Step 4b: Check for adjacency with potential adjacent rectangles
        for (int rectIndex : activeSet) {
            if (isContact(allRects[rectIndex], temp[i])) {
                // Step 4c: Adjacency found, add to adjacency list
                allRects[rectIndex].addToAdjList(currentRectIndex);
            }
        }

        // Step 4d: Remove rectangles from active set
        auto it = activeSet.begin();
        // cout << endl << i << " Active set: ";
        while (it != activeSet.end()) {
            // cout << *it << " | ";
            int rectIndex = *it;
            if (allRects[rectIndex].getRightX() < temp[i].getLeftX()) {
                it = activeSet.erase(it);
            } else {
                ++it;
            }
        }
    }

    delete[] temp;
}

bool Checker(Rectangle bruteforce[], Rectangle linesweep[], int size) {
    for (int i = 0; i <= size; ++i) {
            if (bruteforce[i].getAdjListSize() != linesweep[i].getAdjListSize()) {
               return false;
            }
        }
    return true;
}

int main(int argc, char** argv) {
// Block 1: Single Rectangle set
    if (strcmp(argv[1],"-s") == 0) {
        const int size = stoi(argv[4]);
        Rectangle* bestRects = new Rectangle[size];
        Rectangle *temp = new Rectangle[size];

        BACaseGenerator(bestRects, argv[2], argv[3], size);

        for (int j = 0; j <= counting ; ++j) {
            temp[j] = bestRects[j];
        }
    
        time_t start = clock();
        if (strcmp(argv[5], "-bruteForce") == 0) {
            Solution(bestRects, counting);
        } else if (strcmp(argv[5], "-lineSweep") == 0) {
            LineSweep(bestRects, temp, counting);
        }
        time_t stop = clock();

        double duration = (double)(stop - start) / CLOCKS_PER_SEC * 1000;
        cout << size << ", " << duration << "\n";

        cout << endl;
        for (int i=0; i <= counting; ++i) {
            vector<int> adjs = bestRects[i].getAdjList();

            cout << i << ", ";
            for (int j=0; j < int(adjs.size()); ++j) {
                cout << adjs.at(j) << ", " << bestRects[adjs.at(j)].getLeftX() << ", " << bestRects[adjs.at(j)].getBottomY() << ", " << bestRects[adjs.at(j)].getRightX() << ", " << bestRects[adjs.at(j)].getTopY() << " | ";
            }
            cout << endl;
        }
        delete[] bestRects;  
    } 

// Block 2: Multiple Rectangle sets
    else if (strcmp(argv[1],"-m") == 0) {
        fstream avrfile;
        
        if (strcmp(argv[2], "-b") == 0) {
            avrfile.open ("bestCase.csv", ios::out | ios::app);
        } else if (strcmp(argv[2], "-a") == 0) {
            avrfile.open ("averageCase.csv", ios::out | ios::app);
        } else if (strcmp(argv[2], "-w") == 0) {
            avrfile.open ("worstCase.csv", ios::out | ios::app);
        } else if (strcmp(argv[5], "-bruteForce") == 0 && strcmp(argv[2], "-r") == 0) {
            avrfile.open ("bruteForce.csv", ios::out | ios::app);
        } else {
            cout << "Invalid argument. Please try again." << endl;
            return 0;
        }
        
        avrfile << "input, time\n";

        for (int i = 100; i < stoi(argv[4]); i += 100) {
            Rectangle* Rects = new Rectangle[i];
            Rectangle *temp = new Rectangle[i];

            // Rectangle generation
            BACaseGenerator(Rects, argv[2], "-n", i);

            for (int j = 0; j <= counting ; ++j) {
                temp[j] = Rects[j];
            }

            // Timers
            time_t start = clock();
            if (strcmp(argv[5], "-bruteForce") == 0) {
                Solution(Rects, counting);
            } else if (strcmp(argv[5], "-lineSweep") == 0) {
                LineSweep(Rects, temp, counting);
            }
            time_t stop = clock();

            double duration = (double)(stop - start) / CLOCKS_PER_SEC * 1000;
            avrfile << i << ", " << duration << "\n";

            counting = 0;
            delete[] Rects;
        }
        avrfile.close();
    }
    else if (strcmp(argv[1],"-c") == 0) {
        Rectangle* Rects = new Rectangle[stoi(argv[4])];
        Rectangle* Rects2 = new Rectangle[stoi(argv[4])];
        Rectangle *temp = new Rectangle[stoi(argv[4])];

        // Rectangle generation
        BACaseGenerator(Rects, argv[2], "-n", stoi(argv[4]));

        for (int j = 0; j <= counting ; ++j) {
            temp[j] = Rects[j];
            Rects2[j] = Rects[j];
        }

        Solution(Rects2, counting);
        LineSweep(Rects, temp, counting);

        if (Checker(Rects2, Rects, counting)) {
            cout << "\nLine Sweep is correct" << endl;
        } else {
            cout << "\nLine Sweep is Incorrect" << endl;
        }

        // delete[] Rects;
        // delete[] Rects2;
        // delete[] temp;
    }
    return 0;
}