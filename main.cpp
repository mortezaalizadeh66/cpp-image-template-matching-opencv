#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Read in the big and small images
    Mat big_img = imread("bigimage.png", IMREAD_GRAYSCALE);
    Mat small_img = imread("smallimage.jpg", IMREAD_GRAYSCALE);

    if (big_img.empty() || small_img.empty())
    {
        cout << "Could not open or find one or both of the images!" << endl;
        return -1;
    }

    // Perform template matching to find the location of the small image in the big image
    Mat result;
    matchTemplate(big_img, small_img, result, TM_CCOEFF_NORMED);

    // Find the location of the best match
    Point best_match;
    minMaxLoc(result, NULL, NULL, NULL, &best_match);

    // Draw a rectangle around the found location
    rectangle(big_img, best_match, Point(best_match.x + small_img.cols, best_match.y + small_img.rows), Scalar(0, 255, 0), 2);

    // Display the results
    namedWindow("Big Image", WINDOW_NORMAL);
    namedWindow("Small Image", WINDOW_NORMAL);
    imshow("Big Image", big_img);
    imshow("Small Image", small_img);
    waitKey(0);

    return 0;
}
