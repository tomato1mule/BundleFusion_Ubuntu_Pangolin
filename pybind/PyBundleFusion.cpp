#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <BundleFusion.h>
#include <GlobalAppState.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class BundleFusionWrapper {
private:
    bool initialized;

public:
    BundleFusionWrapper(const std::string& app_config, const std::string& bundle_config) {
        initialized = initBundleFusion(app_config, bundle_config);
        if(!initialized) {
            std::cerr << "BundleFusion init failed." << std::endl;
        }
    }

    ~BundleFusionWrapper() {
        if (initialized) {
            deinitBundleFusion();
        }
    }

    bool process(cv::Mat& rgbImage, cv::Mat& depthImage) {
        if(!initialized) {
            std::cerr << "BundleFusion not initialized!" << std::endl;
            return false;
        }
        
        return processInputRGBDFrame(rgbImage, depthImage);
    }

    void saveCurrentMesh() {
        auto meshPath = GlobalAppState::get().s_generateMeshDir + "/mesh.ply";
        std::cout << "Saving mesh to " << meshPath << std::endl;
        saveMeshIntoFile(meshPath, true);
    }
};


PYBIND11_MODULE(PyBundleFusion, m) {
    py::class_<BundleFusionWrapper>(m, "BundleFusion")
        .def(py::init<const std::string&, const std::string&>())
        .def("process", [](BundleFusionWrapper &self, py::array_t<unsigned char> rgbArray, py::array_t<unsigned char> depthArray) {
            py::buffer_info rgbInfo = rgbArray.request();
            py::buffer_info depthInfo = depthArray.request();

            cv::Mat rgbImage(rgbInfo.shape[0], rgbInfo.shape[1], CV_8UC3, (unsigned char*)rgbInfo.ptr);
            cv::Mat depthImage(depthInfo.shape[0], depthInfo.shape[1], CV_8UC1, (unsigned char*)depthInfo.ptr);

            return self.process(rgbImage, depthImage);
        })
        .def("saveCurrentMesh", &BundleFusionWrapper::saveCurrentMesh);
}