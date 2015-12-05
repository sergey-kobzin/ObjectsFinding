#ifndef OBJECT_H
#define OBJECT_H


#include "vector.h"


/**
 * The Pixel struct.
 */
struct Pixel{
    int x;
    int y;
};


/**
 * The Object class.
 */
class Object {
    private:
        Vector<Pixel> silhouette;
        int number;
        int left;
        int right;
        int top;
        int bottom;
        int width;
        int height;
    public:
        Object();
        Object(Vector<Pixel> silhouette, int number);
        int getNumber();
        int getLeft();
        int getRight();
        int getTop();
        int getBottom();
        int getWidth();
        int getHeight();
        bool isHuman();
};


#endif // OBJECT_H
