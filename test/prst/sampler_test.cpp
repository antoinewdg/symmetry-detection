#include <gtest/gtest.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "gedt/gedt.h"
#include "prst/sampler.h"
#include "factory/mesh_factory.h"

TEST(Sampler, visualTest) {
//    Mesh mesh;
//    if (!OpenMesh::IO::read_mesh(mesh, ASSETS_DIR "/teapot.off")) {
//        std::cerr << "read error\n";
//        exit(1);
//    }
////    Mesh mesh = MeshFactory::basicCube(0, 0, 0, 1, 1, 1);
//    GEDT f(mesh, OCTREE_DEPTH);
//    Sampler sampler(f);
//
//    cv::Mat image = cv::Mat::zeros(64, 64, CV_32F);
//    for (int i = 0; i < 64 * 64; i++) {
//        Vec p = sampler.next();
//        std::cout << f(p) << std::endl;
//        Vec3i c = f.getTree().gridCoordsFromPoint(p);
//        image.at<float>(c[0], c[1])++;
//    }
//
//    cv::normalize(image, image, 1.0, 0, cv::NORM_MINMAX);
//    cv::imshow("dd", image);
//    cv::waitKey();

}