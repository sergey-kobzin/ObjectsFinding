/**
 * The "object.h" implementation.
 */


#include "vector.h"
#include "object.h"
using namespace std;


/**
 * The default object constructor.
 */
Object::Object() {
}


/**
 * The object constructor.
 *
 * @param silhouette - The vector of the pixels that belong to the silhouette.
 * @param number - The object number.
 */
Object::Object(Vector<Pixel> silhouette, int number) {
    this->silhouette = silhouette;
    this->number = number;

    // To define the right and bottom coordinates of the object.
    right = 0;
    bottom = 0;
    for (Pixel pixel : silhouette) {
        if (pixel.x > right)
            right = pixel.x;
        if (pixel.y > bottom)
            bottom = pixel.y;
    };

    // To define the left and bottom coordinates of the object.
    left = right;
    top = bottom;
    for (Pixel pixel : silhouette) {
        if (pixel.x < left)
            left = pixel.x;
        if (pixel.y < top)
            top = pixel.y;
    };

    // Calculate the width and height of the object.
    width = right - left + 1;
    height = bottom - top + 1;
}


/**
 * Get the object number.
 *
 * @return - The object number.
 */
int Object::getNumber() {
    return number;
}


/**
 * Get the left object coordinate.
 *
 * @return - The left object coordinate.
 */
int Object::getLeft() {
    return left;
}


/**
 * Get the right object coordinate.
 *
 * @return - The right object coordinate.
 */
int Object::getRight() {
    return right;
}


/**
 * Get the top object coordinate.
 *
 * @return - The top object coordinate.
 */
int Object::getTop() {
    return top;
}


/**
 * Get the bottom object coordinate.
 *
 * @return - The bottom object coordinate.
 */
int Object::getBottom() {
    return bottom;
}


/**
 * Get the object width.
 *
 * @return - The object width.
 */
int Object::getWidth() {
    return width;
}


/**
 * Get the object height.
 *
 * @return - The object height.
 */
int Object::getHeight() {
    return height;
}


/**
 * To define whether the object is the human.
 *
 * @return - True if the object can be the human or false in other case.
 */
bool Object::isHuman() {
    double ratio = (double)height/width;
    double delta = 1.2;
    return ((ratio >= 3 - delta) && (ratio <= 3 + delta));
}
