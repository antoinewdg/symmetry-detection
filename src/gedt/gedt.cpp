#include "gedt/gedt.h"

GEDT::GEDT(Mesh &mesh, int treeDepth) : mesh(mesh), boundingBox(mesh) {
    list<Mesh::FaceHandle> faces;
    std::copy(mesh.faces_begin(), mesh.faces_end(), std::back_inserter(faces));
    tree = new OCTree(mesh, boundingBox, faces, treeDepth);
    values = new Tensor(tree->getGridSize(), tree->getGridSize(), tree->getGridSize(), 0.0);

    initializeSeeds();
    for (Vec3i seed : seeds) {
        regionGrowth(seed, seed, GEDT_MAXD * GEDT_MAXD, GEDT_SIGMA2);
    }


    image = cv::Mat::zeros(tree->getGridSize(), tree->getGridSize(), CV_32F);
    for (int x = 0; x < tree->getGridSize(); x++) {
        for (int y = 0; y < tree->getGridSize(); y++) {
            image.at<float>(image.rows - y - 1, x) = (*values)(x, y, tree->getGridSize() / 2);


        }
    }

//    std::cout << image;
//    cv::imshow("dd", image);
//
//    cv::convertScaleAbs(image, image, 255);
//    cv::imwrite(ASSETS_DIR "/tea.jpg", image);
//    cv::waitKey();
}


void GEDT::initializeSeeds() {

    for (int x = 0; x < tree->getGridSize(); x++) {
        for (int y = 0; y < tree->getGridSize(); y++) {
            for (int z = 0; z < tree->getGridSize(); z++) {
                if (tree->getVoxelValue(x, y, z) > 0) {
                    Vec3i c(x, y, z);
                    seeds.push_back(c);
                    (*values)(c) = 1.0;
                }
            }
        }
    }
}

void GEDT::regionGrowth(const Vec3i &c, const Vec3i &seed, double maxD2, double sigma2) {

    double d2 = (seed - c).sqrnorm(), v = std::exp(-d2 / sigma2);
    if (d2 > maxD2 || (*values)(c) > v) return;

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
