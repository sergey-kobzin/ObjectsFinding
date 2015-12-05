#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "gbufferedimage.h"
#include "object.h"
using namespace std;


/**
 * Open the image file and binarize it.
 *
 * @param fileName - The image file name.
 * @return - The binarized image stored in 2D vector.
 */
Vector<Vector<bool> > loadImage(string fileName) {
    GBufferedImage* image = new GBufferedImage();
    image->load(fileName);
    int imageWidth = image->getWidth();
    int imageHeight = image->getHeight();
    Vector<Vector<bool> > result(imageHeight, Vector<bool> (imageWidth, 1));
    for (int y = 0; y < imageHeight; y++)
        for (int x = 0; x < imageWidth; x++) {
            int pixelColor = image->getRGB(x, y);
            if ((image->getRed(pixelColor) < 128) && (image->getGreen(pixelColor) < 128) &&
                    (image->getBlue(pixelColor) < 128))
                result[y][x] = 0;
        };
    delete image;
    return result;
}


/**
 * Find an all pixels of the silhouette.
 *
 * @param image - The binarized image.
 * @param x - The current pixel x coordinate.
 * @param y - The current pixel y coordinate.
 * @param silhouette - The vector of the silhouette pixels.
 */
void getSilhouette(Vector<Vector<bool> > &image, int x, int y, Vector<Pixel> &silhouette) {
    if (image[y][x]) {
        return;
    }
    Pixel pixel;
    pixel.x = x;
    pixel.y = y;
    silhouette.add(pixel);
    image[y][x] = 1;
    getSilhouette(image, x - 1, y, silhouette);
    getSilhouette(image, x + 1, y, silhouette);
    getSilhouette(image, x, y - 1, silhouette);
    getSilhouette(image, x, y + 1, silhouette);
    getSilhouette(image, x - 1, y - 1, silhouette);
    getSilhouette(image, x + 1, y + 1, silhouette);
    getSilhouette(image, x + 1, y - 1, silhouette);
    getSilhouette(image, x - 1, y + 1, silhouette);
}

/**
 * Get the object found at the starting pixel.
 *
 * @param image - The binarized image.
 * @param x - The starting pixel x coordinate.
 * @param y - The starting pixel y coordinate.
 * @param objectNumber - The object number.
 * @return - The created object.
 */
Object getObject(Vector<Vector<bool> > &image, int x, int y, int objectNumber) {
    Vector<Pixel> silhouette;
    getSilhouette(image, x, y, silhouette);
    Object result(silhouette, objectNumber);
    return result;
}

/**
 * Get an all objects.
 *
 * @param image - The binarized image.
 * @return - The vector of the found objects.
 */
Vector<Object> getObjects(Vector<Vector<bool> > &image) {
    int objectNumber = 0;
    int imageWidth = image[0].size();
    int imageHeight = image.size();
    Vector<Object> result;
    for (int y = 0; y < imageHeight; y++)
        for (int x = 0; x < imageWidth; x++)
            if (!image[y][x]) {
                objectNumber++;
                Object object = getObject(image, x, y, objectNumber);
                result.add(object);
            }
    return result;
}


/**
 * Count the objects and the humans on the image.
 * @param fileName - The image file name.
 */
void countSilhouettes(string fileName) {
    Vector<Vector<bool> > image = loadImage(fileName);
    Vector<Object> objects = getObjects(image);
    int objectsCounter = 0;
    int humanCounter = 0;
    for (Object object : objects) {
        objectsCounter++;
        humanCounter += object.isHuman();
    }
    cout << "On the file " << fileName << " was found " << objectsCounter << " objects. "
         << humanCounter << " of them can be the human silhouette(s)." << endl;
}


int main() {
    countSilhouettes("image04.png");
    countSilhouettes("image05.gif");
    countSilhouettes("image15.png");
    return 0;
}
