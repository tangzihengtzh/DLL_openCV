## DLL OpenCV库

该库提供了处理图像的各种功能，包括显示图像、生成缩略图、计算亮度以及创建图像。以下是库中每个函数的详细说明。

### 函数

#### ShowImage
```cpp
extern "C" MYLIB_API void ShowImage(const char* imagePath);
```
显示指定路径的图像。

- **参数:**
  - `imagePath`: 图像文件的路径。

#### GenerateThumbnail
```cpp
extern "C" MYLIB_API unsigned char* GenerateThumbnail(const char* imagePath, int& width, int& height, int& channels);
```
生成指定路径图像的缩略图。

- **参数:**
  - `imagePath`: 图像文件的路径。
  - `width`: 生成的缩略图的宽度（输出参数）。
  - `height`: 生成的缩略图的高度（输出参数）。
  - `channels`: 生成的缩略图的颜色通道数（输出参数）。

- **返回值:**
  - 指向生成的缩略图图像数据的指针。

#### getBritness_RJPG
```cpp
extern "C" MYLIB_API int getBritness_RJPG(const char* imagePath);
```
计算指定路径图像的亮度。

- **参数:**
  - `imagePath`: 图像文件的路径。

- **返回值:**
  - 图像的亮度值。

#### getBritness_XJPG
```cpp
extern "C" MYLIB_API int getBritness_XJPG(const char* imagePath, int channel);
```
计算指定路径图像中特定通道的亮度。

- **参数:**
  - `imagePath`: 图像文件的路径。
  - `channel`: 要计算亮度的特定颜色通道。

- **返回值:**
  - 图像中指定通道的亮度值。

#### create_img
```cpp
extern "C" MYLIB_API int create_img(const char** imagepath_list, int num, int agl);
```
根据图像路径列表创建图像。

- **参数:**
  - `imagepath_list`: 图像路径列表。
  - `num`: 列表中的图像数量。
  - `agl`: 图像创建的角度参数。

- **返回值:**
  - 表示操作成功或失败的状态码。

#### C_getBritness_RJPG_List_Value
```cpp
extern "C" MYLIB_API BrightnessResult C_getBritness_RJPG_List_Value(const char* Path_folder);
```
计算指定文件夹中JPG图像的亮度，并返回结果。

- **参数:**
  - `Path_folder`: 包含JPG图像的文件夹路径。

- **返回值:**
  - 包含亮度值数组和处理图像数量的 `BrightnessResult` 结构体。

#### freeBrightnessResult
```cpp
extern "C" void freeBrightnessResult(BrightnessResult result);
```
释放亮度结果分配的内存。

- **参数:**
  - `result`: 要释放的 `BrightnessResult` 结构体。

#### GetSortedJpgFilesByDateC
```cpp
extern "C" MYLIB_API const char** GetSortedJpgFilesByDateC(const char* folderPath);
```
检索指定文件夹中按日期排序的JPG文件列表。

- **参数:**
  - `folderPath`: 包含JPG文件的文件夹路径。

- **返回值:**
  - 按日期排序的JPG文件路径列表。

### 结构体

#### BrightnessResult
```cpp
struct BrightnessResult {
    int* brightnessArray;
    int count;
};
```
包含亮度计算结果。

- **成员:**
  - `brightnessArray`: 亮度值数组。
  - `count`: 处理的图像数量。

### 注意事项

- 确保在使用完亮度结果后，通过调用 `freeBrightnessResult` 释放分配的内存。
- 这些函数使用标准C调用约定，以确保与各种可以接口C库的编程语言兼容。

该库利用OpenCV的图像处理能力，并提供一个兼容C的接口以用于各种应用程序。

## DLL OpenCV Library

This library provides various functions to work with images, including displaying images, generating thumbnails, calculating brightness, and creating images. Below is a detailed description of each function available in the library.

### Functions

#### ShowImage
```cpp
extern "C" MYLIB_API void ShowImage(const char* imagePath);
```
Displays the image located at the specified path.

- **Parameters:**
  - `imagePath`: The path to the image file.

#### GenerateThumbnail
```cpp
extern "C" MYLIB_API unsigned char* GenerateThumbnail(const char* imagePath, int& width, int& height, int& channels);
```
Generates a thumbnail for the image located at the specified path.

- **Parameters:**
  - `imagePath`: The path to the image file.
  - `width`: The width of the generated thumbnail (output parameter).
  - `height`: The height of the generated thumbnail (output parameter).
  - `channels`: The number of color channels in the generated thumbnail (output parameter).

- **Returns:**
  - A pointer to the generated thumbnail image data.

#### getBritness_RJPG
```cpp
extern "C" MYLIB_API int getBritness_RJPG(const char* imagePath);
```
Calculates the brightness of the image located at the specified path.

- **Parameters:**
  - `imagePath`: The path to the image file.

- **Returns:**
  - The brightness value of the image.

#### getBritness_XJPG
```cpp
extern "C" MYLIB_API int getBritness_XJPG(const char* imagePath, int channel);
```
Calculates the brightness of a specific channel in the image located at the specified path.

- **Parameters:**
  - `imagePath`: The path to the image file.
  - `channel`: The specific color channel to calculate the brightness for.

- **Returns:**
  - The brightness value of the specified channel in the image.

#### create_img
```cpp
extern "C" MYLIB_API int create_img(const char** imagepath_list, int num, int agl);
```
Creates an image based on a list of image paths.

- **Parameters:**
  - `imagepath_list`: A list of image paths.
  - `num`: The number of images in the list.
  - `agl`: The angle parameter for image creation.

- **Returns:**
  - Status code indicating the success or failure of the operation.

#### C_getBritness_RJPG_List_Value
```cpp
extern "C" MYLIB_API BrightnessResult C_getBritness_RJPG_List_Value(const char* Path_folder);
```
Calculates the brightness for a list of JPG images in a specified folder and returns the results.

- **Parameters:**
  - `Path_folder`: The path to the folder containing the JPG images.

- **Returns:**
  - A `BrightnessResult` structure containing an array of brightness values and the count of images processed.

#### freeBrightnessResult
```cpp
extern "C" void freeBrightnessResult(BrightnessResult result);
```
Frees the memory allocated for the brightness results.

- **Parameters:**
  - `result`: The `BrightnessResult` structure to free.

#### GetSortedJpgFilesByDateC
```cpp
extern "C" MYLIB_API const char** GetSortedJpgFilesByDateC(const char* folderPath);
```
Retrieves a list of JPG files sorted by date in the specified folder.

- **Parameters:**
  - `folderPath`: The path to the folder containing the JPG files.

- **Returns:**
  - A list of JPG file paths sorted by date.

### Structs

#### BrightnessResult
```cpp
struct BrightnessResult {
    int* brightnessArray;
    int count;
};
```
Contains the results of brightness calculations.

- **Members:**
  - `brightnessArray`: An array of brightness values.
  - `count`: The number of images processed.

### Notes

- Ensure that you free the memory allocated for brightness results by calling `freeBrightnessResult` when you are done using the results.
- The functions use the standard C calling convention to ensure compatibility with various programming languages that can interface with C libraries.

This library leverages the capabilities of OpenCV for image processing and provides a C-compatible interface for use in various applications.
