#include "gedt/gedt.h"

GEDT::GEDT(Mesh &mesh) : mesh(mesh), boundingBox(mesh) {
    list<Mesh::FaceHandle> faces;
    std::copy(mesh.faces_begin(), mesh.faces_end(), std::back_inserter(faces));
    tree = new OCTree(mesh, boundingBox, faces, 6);
    values = new Tensor(tree->getGridSize(), tree->getGridSize(), tree->getGridSize(), 0.0);
    list<Pair> queue;

    for (int x = 0; x < tree->getGridSize(); x++) {
        for (int y = 0; y < tree->getGridSize(); y++) {
            for (int z = 0; z < tree->getGridSize(); z++) {
                if (tree->getVoxelValue(x, y, z) > 0) {
                    Vec3i c(x, y, z);
                    queue.push_back(Pair(c, c));
                    (*values)(c) = 1.0;
                }
            }
        }
    }

    for (Pair p : queue) {
        regionGrowth(p.first, p.first, 10, 4.4814201);
    }

//    int count = 0;
//    while (!queue.empty()) {
//        Pair p = queue.front();
//        queue.pop_front();
////        std::cout << p.first << std::endl;
//        int x = p.first[0], y = p.first[1], z = p.first[2];
//
//        double d = (p.first - p.second).norm();
//        double v = std::exp(-d * d / SIGMA2);
////        std::cout << d << std::endl;
//        if (d > getValue(p.first)) {
//            count++;
////            count++;
////            std::cout << "d2/s2 = " << d2 << " exp = " << std::exp(-d2 / SIGMA2) << std::endl;
//            setValue(p.first, v);
//        }
////        if (d > 2) break;
//
//
//        for (int i = 0; i < 6; i++) {
//            Vec3i c = p.first + immediateNeighbor(i);
//            if (areCoordsInGrid(c) && d < 3) {
//                queue.push_back(Pair(c, p.second));
//            }
//        }
////        for (int u = -1; u <= 1; u++) {
////            for (int v = -1; v <= 1; v++) {
////                for (int w = -1; w <= 1; w++) {
////                    if ((u != 0 || v != 0 || w != 0) && x + u >= 0 && y + v >= 0 && z + w >= 0 &&
////                        x + u < tree->getGridSize() && y + v < tree->getGridSize() && z + w < tree->getGridSize() &&
////                        getValue(x + u, y + v, z + w) == 0) {
////
////                    }
////
////                }
////            }
////        }
//
////        if (count > 1000) {
////            break;
////        }
////        count++;
//        if (count % 1000 == 0) {
//            std::cout << count << std::endl;
//        }
//
//    }
//    std::cout << cv::createGa << std::endl;


//    Tensor kernel = Tensor::createGaussianKernel(3, 1.9);
//    Tensor *temp = new Tensor(tree->getGridSize(), tree->getGridSize(), tree->getGridSize());
//    int N = 3;
//    for (int x = 0; x < tree->getGridSize(); x++) {
//        for (int y = 0; y < tree->getGridSize(); y++) {
//            for (int z = 0; z < tree->getGridSize(); z++) {
//                double max = 0, product;
//
//                for (int u = -N; u <= N; u++) {
//                    for (int v = -N; v <= N; v++) {
//                        for (int w = -N; w <= N; w++) {
//                            Vec3i c(x + u, y + v, z + w);
//                            if (areCoordsInGrid(c)) {
//                                product = kernel(u + N, v + N, w + N) * (*values)(c);
//                                if (product > max) {
//
////                                std::cout << c << std::endl;
//                                    max = product;
//
//                                }
//                            }
//                        }
//                    }
//                }
//                (*temp)(x, y, z) = max;
//
//            }
//        }
//        std::cout << x << std::endl;
//    }

//    delete (values);
//    values = temp;

    image = cv::Mat::zeros(tree->getGridSize(), tree->getGridSize(), CV_32F);
    for (int x = 0; x < tree->getGridSize(); x++) {
        for (int y = 0; y < tree->getGridSize(); y++) {
//            for (int z = 0; z < tree->getGridSize(); z++) {
            image.at<float>(image.rows - y - 1, x) = (*values)(x, y, tree->getGridSize() / 2);

//            if (tree->getVoxelValue(x, y, tree->getGridSize() / 2) > 0) {
//                image.at<float>(image.rows - y, x) = 1.0;
////                pairs.push_back(Pair(Vec3i()))
//            }
        }
    }

//    cv::resize(temp, temp, cv::Size(image.cols * 2, image.rows * 2), 2, 2);


//    for (int x = 0; x < tree->getGridSize2() * tree->getGridSize(); x++) {
//        if (values[x] > 0 && values[x] < 1) {
//            std::cout << values[x] << " ";
//        }
//    }
//    std::copy(values.begin(), values.end(), std::ostream_iterator<double>(std::cout, "\n"));
//    std::cout << image << std::endl;
    cv::imshow("dd", image);

    cv::convertScaleAbs(image, image, 255);
    cv::imwrite(ASSETS_DIR "/tea.jpg", image);
    cv::waitKey();
}


void GEDT::regionGrowth(const Vec3i &c, const Vec3i &seed, double maxD2, double sigma2) {

    double d2 = (seed - c).sqrnorm(), v = std::exp(-d2 / sigma2);
    if (d2 > maxD2 || (*values)(c) > v) return;

//    std::cout << "Growing " << d2 << "--" << std::exp(-d2 / sigma2) << std::endl;
    (*values)(c) = v;
    for (int i = 0; i < 6; i++) {
        Vec3i d = immediateNeighbor(i);

        if (areCoordsInGrid(c + d) && (*values)(c + d) < (*values)(c)) {
            regionGrowth(c + d, seed, maxD2, sigma2);
        }
    }

}

GEDT::~GEDT() {
    delete (tree);
    delete (values);
}
