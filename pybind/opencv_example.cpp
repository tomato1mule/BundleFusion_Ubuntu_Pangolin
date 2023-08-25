#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>

namespace py = pybind11;

void display_image(py::array_t<uint8_t> input_array) {
    // Convert py::array_t to cv::Mat
    py::buffer_info buf_info = input_array.request();
    cv::Mat img(buf_info.shape[0], buf_info.shape[1], CV_8UC3, (uint8_t*)buf_info.ptr);

    // Display image
    cv::imshow("Display Window", img);
    cv::waitKey(0);
}

PYBIND11_MODULE(opencv_example, m) {
    m.def("display_image", &display_image, "Display an image using OpenCV");
}