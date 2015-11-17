#include "gedt/gedt.h"

GEDT::GEDT(Mesh &mesh, int treeDepth) :
        mesh(mesh), boundingBox(mesh), tree(mesh, boundingBox, treeDepth), grid(tree.getGrid()) {

    list<Mesh::FaceHandle> faces;
    std::copy(mesh.faces_begin(), mesh.faces_end(), std::back_inserter(faces));
    tree.computeMesh(faces);
    values = Tensord(grid.size, grid.size, grid.size, 0.0);

    initializeSeeds();
    for (Vec3i seed : seeds) {
        regionGrowth(seed, seed, GEDT_MAXD * GEDT_MAXD, GEDT_SIGMA2);
    }

//    norm = computeNorm();

//    image = cv::Mat::zeros(grid.size, grid.size, CV_32F);
//    for (int x = 0; x < grid.size; x++) {
//        for (int y = 0; y < grid.size; y++) {
//            image.at<float>(image.rows - y - 1, x) = values(x, y, grid.size / 2);
//
//
//        }
//    }
//
//    std::cout << image;
//    cv::imshow("dd", image);
//
//    cv::convertScaleAbs(image, image, 255);
//    cv::imwrite(ASSETS_DIR "/tea.jpg", image);
//    cv::waitKey();
}


void GEDT::initializeSeeds() {

    for (int x = 0; x < grid.size; x++) {
        for (int y = 0; y < grid.size; y++) {
            for (int z = 0; z < grid.size; z++) {
                if (tree.getVoxelValue(x, y, z) > 0) {
                    Vec3i c(x, y, z);
                    seeds.push_back(c);
                    values(c) = 1.0;
                }
            }
        }
    }
}

void GEDT::regionGrowth(const Vec3i &c, const Vec3i &seed, double maxD2, double sigma2) {

    double d2 = (seed - c).sqrnorm(), v = std::exp(-d2 / sigma2);
    if (d2 > maxD2 || values(c) > v) return;

    values(c) = v;
    for (int i = 0; i < 6; i++) {
        Vec3i d = immediateNeighbor(i);

        if (areCoordsInGrid(c + d) && values(c + d) < values(c)) {
            regionGrowth(c + d, seed, maxD2, sigma2);
        }
    }

}


double GEDT::computeNorm() {
    double V = grid.getVoxelVolume(), n = 0;
    for (double d : values.getData()) {
        n += d;
    }
    return n / V;

}
