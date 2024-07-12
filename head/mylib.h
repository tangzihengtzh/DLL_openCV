#pragma once

#ifdef MYLIB_EXPORTS
#define MYLIB_API __declspec(dllexport)
#else
#define MYLIB_API __declspec(dllimport)
#endif
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
extern "C" MYLIB_API void ShowImage(const char* imagePath);

extern "C" MYLIB_API unsigned char* GenerateThumbnail(const char* imagePath, int& width, int& height, int& channels);

extern "C" MYLIB_API int getBritness_RJPG(const char* imagePath);
extern "C" MYLIB_API int getBritness_XJPG(const char* imagePath,int channel);

extern "C" MYLIB_API int create_img(const char** imagepath_list, int num,int agl);




std::vector<int> getBritness_RJPG_List_Value(const char* Path_folder);
struct BrightnessResult {
    int* brightnessArray;
    int count;
};
//���ڷ�װ
//std::vector<int> getBritness_RJPG_List_Value(const char* Path_folder)
//�Է���C��׼
extern "C" MYLIB_API BrightnessResult C_getBritness_RJPG_List_Value(const char* Path_folder);
extern "C" void freeBrightnessResult(BrightnessResult result);


//extern "C" MYLIB_API std::vector<std::string> GetSortedJpgFilesByDate(const std::string& folderPath);
extern "C" MYLIB_API const char** GetSortedJpgFilesByDateC(const char* folderPath);
/*
* �������ܣ�����һ���ļ��������е�jpg·����ʹ�÷������£�
    const char** filePaths = myfuc::GetSortedJpgFilesByDateC("E:\\photo\\test");

    if (filePaths == nullptr) {
        std::cerr << "Failed to retrieve file paths." << std::endl;
        return 1;
    }

    // ��ӡ�����ļ�·��
    for (size_t i = 0; filePaths[i] != nullptr; ++i) {
        std::cout << filePaths[i] << std::endl;
    }
*/
//extern "C" MYLIB_API QImage GenerateThumbnail(const char* imagePath);


//
//extern "C" MYLIB_API std::vector<int> GetBrightnessRList(const char* folderPath);

