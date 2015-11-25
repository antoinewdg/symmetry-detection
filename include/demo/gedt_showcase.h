//
// Created by antoinewdg on 11/25/15.
//

#ifndef SYMMETRY_DETECTION_GEDT_SHOWCASE_H
#define SYMMETRY_DETECTION_GEDT_SHOWCASE_H

#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "common/common.h"
#include "gedt/gedt.h"


using std::vector;

class GEDTShowcase {
public:

    static void displaySlices(const GEDT &f) {
        const int n = f.getGrid().size;
        vector<cv::Mat> images(n);

        for (int i = 0; i < n; i++) {
            images[i] = cv::Mat::zeros(f.getGrid().size, f.getGrid().size, CV_32F);
            for (int x = 0; x < f.getGrid().size; x++) {
                for (int y = 0; y < f.getGrid().size; y++) {
                    images[i].at<float>(images[i].rows - y - 1, x) = 1 - f(Vec3i(x, y, i));


                }

            }
        }

        for (int i = 0; i < n; i++) {
            cv::imshow("GEDT", images[i]);
            cv::waitKey();
        }
    }
};

#endif //SYMMETRY_DETECTION_GEDT_SHOWCASE_H
