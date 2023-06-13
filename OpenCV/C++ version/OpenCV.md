# C++ Version OpenCV Compile

## OpenCV Source

> 在C++环境中，如果你想使用OpenCV那么最好的方式就是手动进行cmake编译

- 以下是OpenCV以及contrib的地址
	- [OpenCv](https://github.com/opencv/opencv OpenCV的源码)
	- [OpenCV_contrib](https://github.com/opencv/opencv_contrib)

## OpenCV Compile

> [!todo] you should create a dir to put the source code

```linux
$ mkdir opencv_build
$ cd opencv_build
```

- 注意：看有的博客上说，最好将文件夹名字命名为**opencv_build**

> [!todo] pull code from github

```linux
[opencv_build]$ git clone https://github.com/opencv/opencv.git
[opencv_build]$ git clone https://github.com/opencv/opencv_contrib.git
```

- 注意：选择自己需要的版本后再进行拉取

> [!todo] download dependence for cmake compile

```linux
[opencv_build]$ mkdir opencv/build && cd opencv/build
[opencv_build/opencv/build]$ 
	sudo apt install build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev
```

> [!todo] if dependence install without error, now generate the Makefile by cmake

```linux
[opencv_build/opencv/build]$ 
	cmake -D CMAKE_BUILD_TYPE=RELEASE     \
		  -D CMAKE_INSTALL_PREFIX=/usr/local     \
		  -D INSTALL_C_EXAMPLES=ON     \
		  -D INSTALL_PYTHON_EXAMPLES=ON     \
		  -D OPENCV_GENERATE_PKGCONFIG=ON     \
		  -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules     \
		  -D BUILD_EXAMPLES=ON ..
```

- 注意：**OPENCV_EXTRA_MODULES_PATH**是放置opencv_contrib/modules的位置

- 如果编译成功，就会有如下输出：
```linux
-- Configuring done
-- Generating done
-- Build files have been written to: /home/user/opencv_build/opencv/build
```

> [!todo] start compile

```linux
# Before we start make compile, we should adjust the number of processor cores
[opencv_build/opencv/build]$ make -j12
```

- if you don't know how many cores in your processor

```linux
[opencv_build/opencv/build]$ nproc
12
```

> [!todo] installation

```linux
[opencv_build/opencv/build]$ sudo make install
```

> now, you can use **pkg-config --modversion opencv4** to check whether install successful

## Use In Clion

```CmakeLists.txt
cmake_minimum_required(VERSION 3.24)  
project(test)  
  
set(CMAKE_CXX_STANDARD 17)  
add_executable(test main.cc)  
  
find_package(OpenCV REQUIRED)  
if (OpenCV_FOUND)  
    include_directories(${OpenCV_INCLUDE_DIRS})  
    target_link_libraries(test ${OpenCV_LIBS})  
else (OpenCV_FOUND)  
    message(FATAL_ERROR "OpenCV library not found")  
endif (OpenCV_FOUND)
```

> [!todo] test code

```c++
#include <iostream>  
#include <opencv4/opencv2/opencv.hpp>  
  
int main() {  
    cv::VideoCapture capture(0);  
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);  
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);  
    if (!capture.isOpened()) {  
        std::cout << "open camera error!" << std::endl;  
        return 1;  
    }  
  
    cv::Mat frame;  
    while (true) {  
        capture >> frame;  
        if (frame.empty()) {  
            std::cout << "capature empty frame" << std::endl;  
            continue;  
        }  
  
        cv::Mat shrink_frame;  
        cv::resize(frame, shrink_frame,  
                   cv::Size(frame.cols / 2, frame.rows / 2),  
                   0, 0, 3);  
        cv::imshow("test", shrink_frame);  
  
        int key = cv::waitKey(1);  
        if (key == 'q')  
            break;  
    }  
    return 0;  
}
```

- 注意：你必须在CmakeLists中链接到opencv的库文件才能运行成功。
	- opencv安装的.so位置 -> **/usr/local/lib**

# OpenCV C++ Version

## Mat类

![[Pasted image 20230610231437.png]]

![[Pasted image 20230610233329.png]]

### Mat类的使用

- Mat创建

``` cpp
// rows: 构造矩阵的行数
// cols：矩阵的列数
// type：存储的数据类型，在CV_8UC(n)上可以创建多通道矩阵(512)，其余则是1~4
(1) cv::Mat::Mat(int rows, int cols, int type);
// size：2D数组尺寸量
(2) cv::Mat::Mat(Size isze, int type);
// m：已经构建的Mat类矩阵
// row：在已有矩阵中需要截取的行数范围
// col：在已有矩阵中需要截取的列数范围
(3) cv::Mat::Mat(const Mat& m, const Range& row, const Range& col = Range::all());
// s：给每个矩阵每个像素(通道)赋值的参数变量
(4) cv::Mat::Mat(int rows, int cols, int type, const Scalar& s);

// 单位矩阵
cv::Mat::eye(int rows, int cols, int type);
// 对角矩阵
cv::Mat::diag(...);
// 元素全为1
cv::Mat::ones(...);
// 元素全为0
cv::Mat::zeros(...);


```

### Mat类数据的存储

![[Pasted image 20230611091245.png]]

![[Pasted image 20230611091335.png]]

- Mat读取

```cpp
(1) 单通道
int value = (int)a.at<uchar>(0, 0);
(2)多通道
cv::Vec3b vc3 = b.at<cv::Vec3b>(0, 0);
int first = (int)vc3.val[0];
```

### Mat类的运算

#### 符号运算

> 支持加减乘除

 ![[Pasted image 20230611093134.png]]

#### 内置函数

![[Pasted image 20230611093324.png]]

## 图像加载与显示

### 图像加载

```cpp
// filename: 需要读取图像的文件名
// 读取图像形式的标志
Mat cv::imread(const Stirng& filename, int flags = IMREAD_COLOR);
```

### 图像显示

```cpp
// winname：窗口名称
// flags：窗口属性设置标志
void cv::namedWindow(const String& winname, int flags = WINDOW_AUTOSIZE);

// mat：要显示的图像矩阵
void cv::imshow(const String& winame, InptArray mat);
```

### 图像保存

```cpp
// img：将要保存的Mat类矩阵变量
// params：保存图片格式属性设置
bool cv::imwrite(
    const String& filename, 
    InputArray img, 
    const std::vector<int>& params = std::vector<int>()
);
```

### 视频加载

```cpp
// apiPreference：读取数据时设置的属性，类如编码格式、是否调用OpenNI
cv::VideoCapture::VideoCapture(const String& filename, int apiPreference = CAP_ANY);
```

![[Pasted image 20230611102827.png]]

### 视频保存

```cpp
// fourcc：压缩帧的4字符编解码器代码
// fps：保存视频的帧率
// frameSize：视频帧的尺寸
// isColor：保存视频是否为彩色视频
cv::VideoWriter::VideoWriter(
	const String& filename,
	int fourcc, 
	double fps, 
	Size frameSize, 
	bool isColor = ture
);
```

## 图像颜色空间

### 颜色空间介绍

- RGB颜色

![[Pasted image 20230612103058.png]]

- 图像数据类型间相互转换

```cpp
// m：输出图像
// rtype：转换后的数据类型
// alpha：缩放类型
// beta：平移系数
void cv::Mat::convertTo(
	OutputArray m, 
	int rtype, 
	double alpha = 1, 
	double beta = 0
) const;
```

- HSV颜色

![[Pasted image 20230612103632.png]]

- Gray颜色

![[Pasted image 20230612103724.png]]

- 只能彩色转换灰色

### 颜色空间转换

```cpp
// src：待转换颜色模型的原始图像
// dst：转换后的目标图像
// code：颜色空间转换表示
// dstCn：目标图像中的通道数，为0自动导出
void cv::cvtColor(
	InputArray src,
	OutputArray dst,
	int code,
	int dstCn = 0
);
```

## 多通道分离合并

### 多通道分离

```cpp
// m：待分离的多通道
// mv：分离后的单通道图像
void cv::split(InputArray m, OutputArrayOfArrays mv);
```

### 多通道合并

```cpp
// mv：需要合并的图像向量，每个图像必须拥有相同的尺寸和数据类型
// dst：合并后输出的图像，通道数等于所有输入图像的通道数总和
void cv::merge(InputArrayOfArrays mv, OutputArray dst);
```

## 像素比较

```cpp
// src1：第一个图像矩阵，可以是任意通道数矩阵
// src2：尺寸和通道数以及数据类型需要和src1一致
// dst：保留对应位置较大(较小)灰度值后的图像矩阵
void cv::min(InputArray src1, InputArray src2, OutputArrat dst);
void cv::max(InputArray src1, InputArray src2, OutputArrat dst);
```

- 最大值与最小值寻找

```cpp
// src：输入单通道矩阵
// minVal：指向最小值的指针
// maxVal：指向最大值的指针
// minLoc：指向最小值位置的指针
// maxLoc：指向最大值位置的指针
// mask：掩码矩阵，用于标记范围
void cv::minMaxLoc(
	InputArray src,
	double* minVal,
	double* maxVal = 0,
	Point* minLoc = 0,
	Point* miaxLoc = 0,
	InputArray mask = noArray()
);
```

## 逻辑运算

![[Pasted image 20230612135340.png]]

```cpp
void cv::bitwise_not(InputArray src, OutputArray dst, InputArray mask = noArray());
void cv::bitwise_and(
	InputArray src1, 
	InputArray src2, 
	utputArray dst, 
	InputArray mask = noArray()
);
void cv::bitwise_or(
	InputArray src1, 
	InputArray src2, 
	utputArray dst, 
	InputArray mask = noArray()
);
void cv::bitwise_xor(
	InputArray src1, 
	InputArray src2, 
	utputArray dst, 
	InputArray mask = noArray()
);
```

1. 与（AND）逻辑运算符：用于将两幅二值图像进行合并，即对两幅图像中的相同像素位置逐个进行比较，只有当两幅图像都为白点时，输出图像的该位置才是白点，否则为黑点。**与运算可用于去除二进制图像中不需要保留的区域或色块**。
2. 或（OR）逻辑运算符：用于将两幅二值图像合并成一幅图像，即对比较两个图像每一个像素，只要其中一个像素有白点，则输出图像的该位置就是白点，否则为黑点。**或运算常用于对图像进行腐蚀（逐点比较最小像素值）和膨胀（逐点比较最大像素值）等操作**。
3. 非（NOT）逻辑运算符：用于将二值图像颜色取反，即将白点变为黑点，将黑点变为白点。**它常用于图像轮廓提取、全局阈值化等操作，可以在黑白图像中高速检测边缘和较小的区域**。

## 图像二值化

### 固定阈值二值化

![[Pasted image 20230612151139.png]]

```cpp
// src：待二值化的图像，只能是CV_8U和CV_32F类型
// dst：二值化后的图像
// thresh：二值化的阈值
// maxval：二值化过程中的最大值
// type：选择二值化的方法
double cv::threshold(
	InputArray src, 
	OutputArray dst, 
	double thresh, 
	double maxval, 
	int type
);
```

### 自适应阈值二值化

```cpp
// src：只能是CV_8UC1数据类型
// maxValue：二值化的最大值
// adaptiveMethod：自适应确定阈值的方法，
//     均值法ADAPTIVE_THRESH_MEAN_C和高斯法ADAPTIVE_THRESH_GAUSSIAN_C
// thresholdType：选择图像二值化方法的标志，只能是BINARY和BINARY_INV
// blockSize：自适应确定阈值的像素领域大小，一般为3，5，7
// C：从平均值或加权平均值中减去的常数
void cv::adaptiveThreshold(
	InputArray src,
	OutputArray dst,
	double maxValue,
	int adaptiveMethod,
	int thresholdType,
	int blockSize,
	double C
);
```