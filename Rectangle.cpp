#include "Rectangle.h"
#include <iostream>
#include <vector>

// Constructors
Rectangle::Rectangle(){}

Rectangle::Rectangle(int id, int Bx, int By, int Tx, int Ty) {
    rect_id = id;
    BL_x = Bx;
    BL_y = By;
    TR_x = Tx;
    TR_y = Ty;
    width = Tx - Bx;
    height = Ty - By;
}

// Setters
void Rectangle::setRectId(int id) {
    rect_id = id;
}

void Rectangle::setBLeftCoords(int x, int y) {
    BL_x = x;
    BL_y = y;
}

void Rectangle::setTRightCoords(int x, int y) {
    TR_x = x;
    TR_y = y;
}

void Rectangle::setAdjSize(int no_rects) {
    adj_size = no_rects;
}

void Rectangle::addToAdjList(int id) {
    adj_list.push_back(id);
    adj_size += 1; 
}

// Getters
int Rectangle::getRectId() {
    return rect_id;
}

int Rectangle::getLeftX() {
    return BL_x;
}

int Rectangle::getRightX() {
    return TR_x;
}

int Rectangle::getBottomY(){
    return BL_y;
}

int Rectangle::getTopY() {
    return TR_y;
}

std::vector<int> Rectangle::getAdjList() {
    return adj_list;
}

int Rectangle::getAdjListSize() {
    return adj_list.size();
}