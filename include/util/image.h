//
// Created by antoine on 9/16/15.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using std::vector;

template<typename T>
class Image : public Mat {
public:

    Image() : Mat() {
    }

    Image(const Mat &A) : Mat(A) {
    }

    Image(int m, int n, int type) : Mat(m, n, type) {
    }

    Image(const vector<T>& v) : Mat(v) {

    }

    inline T operator()(int x, int y) const {
        if (y < 0 || y >= rows || x < 0 || x > cols) {
            std::cout << "Bad coordinates " << x << ", " << y << std::endl;
//            imshow("Error", *this);
//            waitKey();
        }
        return at<T>(y, x);
    }

    inline T &operator()(int x, int y) {
        if (y < 0 || y >= rows || x < 0 || x > cols) {
            std::cout << "Bad coordinates " << x << ", " << y << std::endl;
//            imshow("Error", *this);
//            waitKey();
        }
        return at<T>(y, x);
    }

    Image<T> sub(const Rect& r) const {
        if (!contains(r)) {
            std::cout << std::endl << "ERROR -- sub rect does not fit" << std::endl << std::endl;
            throw Exception();
        }
        return rowRange(r.y, r.y + r.height).colRange(r.x, r.x + r.width);
    }

    bool contains(const Rect& r) const {
        return r.x >= 0 && r.y >= 0 && r.x + r.width <= cols && r.y + r.height <= rows;
    }




};



#endif
