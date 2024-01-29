#ifndef rectangle_h
#define rectangle_h
#include <vector>

class Rectangle {
    public:
        // Current rectangle information
        int rect_id;
        int BL_x, BL_y, TR_x, TR_y, width, height;

        // Adjacent rectangle infromation
        int adj_size = 0;
        std::vector<int> adj_list;

        // ructors
        Rectangle();
        Rectangle(int id, int Bx, int By, int width, int height);

        // Setters
        void setRectId(int id);

        void setBLeftCoords(int x, int y);

        void setTRightCoords(int x, int y);

        void setAdjSize(int no_rects);

        void addToAdjList(int id);

        // Getters
        int getRectId();

        int getLeftX();

        int getRightX() ;

        int getBottomY() ;

        int getTopY() ;

        std::vector<int> getAdjList();

        int getAdjListSize();

};
#endif 