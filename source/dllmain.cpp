#include "mylib.h"
//// dllmain.cpp : 定义 DLL 应用程序的入口点。
//#include "pch.h"
//#include<opencv2/opencv.hpp>
//
//using namespace cv;
//
//BOOL APIENTRY DllMain( HMODULE hModule,
//                       DWORD  ul_reason_for_call,
//                       LPVOID lpReserved
//                     )
//{
//    switch (ul_reason_for_call)
//    {
//    case DLL_PROCESS_ATTACH:
//    case DLL_THREAD_ATTACH:
//    case DLL_THREAD_DETACH:
//    case DLL_PROCESS_DETACH:
//        break;
//    }
//    return TRUE;
//}

// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "mylib.h"
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdexcept>
#include <commctrl.h>

using namespace std;
using namespace cv;



BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


void ShowImage(const char* imagePath)
{
    Mat image = imread(imagePath);
    if (image.empty())
    {
        MessageBoxA(NULL, "Could not open or find the image.", "Error", MB_OK);
        return;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    destroyWindow("Display Image");
}


// 返回一个指向缩略图数据的指针，并通过引用参数返回图像的宽度、高度和通道数
unsigned char* GenerateThumbnail(const char* imagePath, int& width, int& height, int& channels)
{
    Mat image = imread(imagePath);
    if (image.empty())
    {
        MessageBoxA(NULL, "Could not open or find the image.", "Error", MB_OK);
        return nullptr;
    }

    Mat thumbnail;
    resize(image, thumbnail, Size(50, 50));

    width = thumbnail.cols;
    height = thumbnail.rows;
    channels = thumbnail.channels();

    // 返回缩略图数据的指针
    unsigned char* data = new unsigned char[width * height * channels];
    memcpy(data, thumbnail.data, width * height * channels * sizeof(unsigned char));

    return data;
}

//测量一个jpg文件的全局R通道的亮度
int getBritness_RJPG(const char* imagePath) {
    // 读取图像
    cv::Mat image = cv::imread(imagePath);

    // 检查图像是否成功加载
    if (image.empty()) {
        return -1; // 如果图像加载失败，返回-1
    }

    // 提取R通道
    std::vector<cv::Mat> channels;
    cv::split(image, channels);
    cv::Mat redChannel = channels[2]; // OpenCV使用BGR格式，所以索引2是R通道

    // 下采样 redChannel
    cv::Mat resizedRedChannel;
    int downSampleFactor = 16; // 下采样因子
    cv::resize(redChannel, resizedRedChannel, cv::Size(redChannel.cols / downSampleFactor, redChannel.rows / downSampleFactor), 0, 0, cv::INTER_LINEAR);

    // 计算R通道的平均亮度
    cv::Scalar meanValue = cv::mean(resizedRedChannel);
    int brightness = static_cast<int>(meanValue[0]);

    return brightness;
}

//测量一个jpg文件的全局指定通道的亮度
int getBritness_XJPG(const char* imagePath, int channel) {
    // 读取图像
    cv::Mat image = cv::imread(imagePath);

    // 检查图像是否成功加载
    if (image.empty()) {
        return -1; // 如果图像加载失败，返回-1
    }

    // 提取R通道
    std::vector<cv::Mat> channels;
    cv::split(image, channels);
    cv::Mat redChannel = channels[channel]; // OpenCV使用BGR格式，0B/1G/2R

    // 下采样 redChannel
    cv::Mat resizedRedChannel;
    int downSampleFactor = 16; // 下采样因子
    cv::resize(redChannel, resizedRedChannel, cv::Size(redChannel.cols / downSampleFactor, redChannel.rows / downSampleFactor), 0, 0, cv::INTER_LINEAR);

    // 计算R通道的平均亮度
    cv::Scalar meanValue = cv::mean(resizedRedChannel);
    int brightness = static_cast<int>(meanValue[0]);

    return brightness;
}

// 创建一个新的控制台窗口
void CreateConsole() {
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);
    std::cout.clear();
    std::cerr.clear();
    std::cin.clear();
    SetConsoleTitle(TEXT("Processing Progress"));
}

std::vector<int> getBritness_RJPG_List_Value(const char* Path_folder) {
    // 获取排序后的 JPG 文件路径
    const char** filePaths = GetSortedJpgFilesByDateC(Path_folder);

    if (filePaths == nullptr) {
        throw std::runtime_error("Failed to retrieve file paths.");
    }

    std::vector<int> brightnessList;
    int fileCount = 0;

    // 计算文件总数
    while (filePaths[fileCount] != nullptr) {
        fileCount++;
    }

    // 创建控制台窗口
    CreateConsole();

    for (int i = 0; filePaths[i] != nullptr; ++i) {
        // 获取单个 JPG 文件的 R 通道亮度
        int brightness = getBritness_RJPG(filePaths[i]);
        brightnessList.push_back(brightness);

        // 输出进度
        std::cout << "Processed " << (i + 1) << " of " << fileCount << " files." << std::endl;
    }

    // 释放动态分配的内存
    for (size_t i = 0; filePaths[i] != nullptr; ++i) {
        delete[] filePaths[i];
    }
    delete[] filePaths;

    return brightnessList;
}

//std::vector<int> getBritness_RJPG_List_Value(const char* Path_folder) {
//    // 获取排序后的 JPG 文件路径
//    const char** filePaths = GetSortedJpgFilesByDateC(Path_folder);
//
//    if (filePaths == nullptr) {
//        throw std::runtime_error("Failed to retrieve file paths.");
//    }
//
//    std::vector<int> brightnessList;
//
//    for (size_t i = 0; filePaths[i] != nullptr; ++i) {
//        // 获取单个 JPG 文件的 R 通道亮度
//        int brightness = getBritness_RJPG(filePaths[i]);
//        brightnessList.push_back(brightness);
//    }
//
//    // 释放动态分配的内存
//    for (size_t i = 0; filePaths[i] != nullptr; ++i) {
//        delete[] filePaths[i];
//    }
//    delete[] filePaths;
//
//    return brightnessList;
//}

struct FileInfo {
    std::string path;
    FILETIME lastWriteTime;
};

// 比较函数用于排序 升序/降序
bool CompareByLastWriteTime(const FileInfo& a, const FileInfo& b) {
    return CompareFileTime(&a.lastWriteTime, &b.lastWriteTime) < 0;
}

bool CompareByLastWriteTimeDesc(const FileInfo& a, const FileInfo& b) {
    return CompareFileTime(&a.lastWriteTime, &b.lastWriteTime) > 0;
}


std::vector<std::string> GetSortedJpgFilesByDate(const std::string& folderPath) {
    std::vector<FileInfo> fileInfos;
    std::string searchPath = folderPath + "\\*.jpg";
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to find files in the specified folder.");
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            FileInfo fileInfo;
            fileInfo.path = folderPath + "\\" + findFileData.cFileName;
            fileInfo.lastWriteTime = findFileData.ftLastWriteTime;
            fileInfos.push_back(fileInfo);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);

    std::sort(fileInfos.begin(), fileInfos.end(), CompareByLastWriteTime);

    std::vector<std::string> sortedFilePaths;
    for (const auto& fileInfo : fileInfos) {
        sortedFilePaths.push_back(fileInfo.path);
    }

    return sortedFilePaths;
}

BrightnessResult C_getBritness_RJPG_List_Value(const char* Path_folder) {
    BrightnessResult result;
    result.brightnessArray = nullptr;
    result.count = 0;

    try {
        // 获取排序后的 JPG 文件路径
        const char** filePaths = GetSortedJpgFilesByDateC(Path_folder);

        if (filePaths == nullptr) {
            throw std::runtime_error("Failed to retrieve file paths.");
        }

        std::vector<int> brightnessList;

        for (size_t i = 0; filePaths[i] != nullptr; ++i) {
            // 获取单个 JPG 文件的 R 通道亮度
            int brightness = getBritness_RJPG(filePaths[i]);
            brightnessList.push_back(brightness);
        }

        // 释放动态分配的内存
        for (size_t i = 0; filePaths[i] != nullptr; ++i) {
            delete[] filePaths[i];
        }
        delete[] filePaths;

        // 将结果转换为 C 兼容的数组
        result.count = static_cast<int>(brightnessList.size());
        result.brightnessArray = new int[result.count];
        for (int i = 0; i < result.count; ++i) {
            result.brightnessArray[i] = brightnessList[i];
        }
    }
    catch (const std::exception& e) {
        // 如果出现异常，确保清理分配的内存
        delete[] result.brightnessArray;
        result.brightnessArray = nullptr;
        result.count = 0;
    }

    return result;
}

void freeBrightnessResult(BrightnessResult result) {
    delete[] result.brightnessArray;
}

const char** GetSortedJpgFilesByDateC(const char* folderPath) {
    try {
        std::vector<std::string> sortedFiles = GetSortedJpgFilesByDate(folderPath);
        //std::cout << "长度[" << sortedFiles.size()<<"]";

        // 动态分配内存用于存储指向字符串的指针
        const char** result = new const char* [sortedFiles.size() + 1];

        for (size_t i = 0; i < sortedFiles.size(); ++i) {
            // 动态分配内存用于存储每个字符串
            char* filePath = new char[sortedFiles[i].size() + 1];
            std::strcpy(filePath, sortedFiles[i].c_str());
            result[i] = filePath;
            //std::cout << filePath << std::endl;
        }

        // 最后一个指针设置为nullptr表示结束
        result[sortedFiles.size()] = nullptr;

        return result;
    }
    catch (const std::exception& e) {
        return nullptr;
    }
}


//int create_img(const char** imagepath_list, int num, int agl) {
//    std::vector<cv::Mat> images;
//    for (int i = 0; i < num; ++i) {
//        cv::Mat img = cv::imread(imagepath_list[i]);
//        if (img.empty()) {
//            std::cerr << "Error loading image: " << imagepath_list[i] << std::endl;
//            return -1;
//        }
//        images.push_back(img);
//    }
//
//    int width = images[0].cols;
//    int height = images[0].rows;
//    cv::Mat canvas = cv::Mat::zeros(height, width, CV_8UC3);
//
//    int num_lines = num + 2;
//    double angle = agl * CV_PI / 180.0;
//    double line_distance = height / std::cos(angle) / (num_lines - 1);
//
//    for (int i = 0; i < num_lines; ++i) {
//        double x1 = 0;
//        double y1 = i * line_distance;
//        double x2 = width;
//        double y2 = i * line_distance - width * std::tan(angle);
//
//        cv::Point pt1, pt2;
//        if (y1 < height) {
//            pt1 = cv::Point(x1, y1);
//        }
//        else {
//            pt1 = cv::Point((y1 - height) / std::tan(angle), height);
//        }
//
//        if (y2 < height) {
//            pt2 = cv::Point(x2, y2);
//        }
//        else {
//            pt2 = cv::Point(width - (y2 - height) / std::tan(angle), height);
//        }
//
//        cv::line(canvas, pt1, pt2, cv::Scalar(255, 255, 255), 1);
//    }
//
//    cv::imshow("Parallel Lines", canvas);
//        // 保存当前拼接的图像
//    std::ostringstream filename;
//    filename << "output_lines_.jpg";
//    cv::imwrite(filename.str(), canvas);
//    cv::waitKey(0);
//
//    return 0;
//}

//int create_img(const char** imagepath_list, int num, int agl) {
//    std::vector<cv::Mat> images;
//
//    // 加载所有图片并存储在向量中
//    for (int i = 0; i < num; ++i) {
//        cv::Mat img = cv::imread(imagepath_list[i]);
//        if (img.empty()) {
//            std::cerr << "Error loading image: " << imagepath_list[i] << std::endl;
//            return -1;
//        }
//        images.push_back(img);
//    }
//
//    // 输出素材路径列表
//    std::cout << "Loaded images:" << std::endl;
//    for (int i = 0; i < num; ++i) {
//        std::cout << imagepath_list[i] << std::endl;
//    }
//
//    int width = images[0].cols;
//    int height = images[0].rows;
//    cv::Mat canvas = cv::Mat::zeros(height, width, CV_8UC3);
//    cv::Mat lines_canvas = cv::Mat::zeros(height, width, CV_8UC3);
//
//    int num_lines = num + 2; // 计算平行线数量
//    double angle = agl * CV_PI / 180.0; // 将角度转换为弧度
//    //斜率
//    double k_line = tan(angle);
//
//    // 计算左上角和右下角的点
//    cv::Point start_point(0, 0);
//    cv::Point end_point(width, height);
//
//    //确定每一个直线的点位
//    vector<int> p_x{0};
//    for (int i = 1; i < num; i++)
//    {
//        p_x.push_back(int(width*i/num));
//    }
//    p_x.push_back(width);
//
//    vector<int> p_y{0};
//    for (int i = 1; i < num; i++)
//    {
//        p_y.push_back(int(height * i / num));
//    }
//    p_y.push_back(height);
//
//    return 0;
//}

bool isBelowLine(const cv::Point& point, const cv::Point& linePoint, double slope) {
    // 直线方程为 y = k * (x - x0) + y0
    // 判断点 (x, y) 是否在直线下方
    return point.y > slope * (point.x - linePoint.x) + linePoint.y;
}

int create_img(const char** imagepath_list, int num, int agl) {
    std::vector<cv::Mat> images;

    // 加载所有图片并存储在向量中
    for (int i = 0; i < num; ++i) {
        cv::Mat img = cv::imread(imagepath_list[i]);
        if (img.empty()) {
            std::cerr << "Error loading image: " << imagepath_list[i] << std::endl;
            return -1;
        }
        images.push_back(img);
    }

    // 输出素材路径列表
    std::cout << "Loaded images:" << std::endl;
    for (int i = 0; i < num; ++i) {
        std::cout << imagepath_list[i] << std::endl;
    }

    int width = images[0].cols;
    int height = images[0].rows;
    cv::Mat canvas = cv::Mat::zeros(height, width, CV_8UC3);
    double angle = agl * CV_PI / 180.0; // 将角度转换为弧度
    double slope = -std::tan(angle); // 斜率

    // 计算分割线的穿过点
    std::vector<cv::Point> points;
    for (int i = 0; i <= num; ++i) {
        points.push_back(cv::Point(i * width / num, i * height / num));
    }

    // 遍历每个像素点，确定它属于哪一个图像
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cv::Point point(x, y);
            int img_index = 0;

            // 判断点属于哪一条线的下方
            for (int i = 0; i < num; ++i) {
                if (!isBelowLine(point, points[i], slope)) {
                    img_index = i;
                    break;
                }
            }

            // 将对应的像素点复制到画布上
            canvas.at<cv::Vec3b>(y, x) = images[img_index].at<cv::Vec3b>(y, x);
        }
    }

    // 保存最终生成的图像
    cv::imwrite("output_final.jpg", canvas);
    std::cout << "Final image saved as output_final.jpg" << std::endl;

    return 0;
}