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

