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
