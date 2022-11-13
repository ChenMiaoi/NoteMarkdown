# ROS学习

--- 

## ROS的安装与配置

### ROS脚本

> ROS的安装建议直接使用脚本，自己安装太过费时费力

> [!tip] ROS小鱼脚本
> **注意：环境为Ubuntu20.04或者18.04， 建议虚拟机或双系统安装**

```linux
$ wget http://fishros.com/install -O fishros && . fishros
```

- **[小鱼脚本链接直达车](https://fishros.org.cn/forum/topic/20/%E5%B0%8F%E9%B1%BC%E7%9A%84%E4%B8%80%E9%94%AE%E5%AE%89%E8%A3%85%E7%B3%BB%E5%88%97?lang=zh-CN)**

### ROS环境简单解决

> [!warning] 当使用小鱼脚本安装后，使用以下命令会出现问题

```linux
$ sudo rosdep init
ERROR: cannot download default sources list from:
https://raw.githubusercontent.com/ros/rosdistro/master/rosdep/sources.list.d/20-default.list
Website may be down.
```

- 由于rosdep中的源目标是国外网站，因此极大可能被墙，因此需要修改配置文件中的源

> [!example] 修改配置需要经过以下几步
> 1. 进入目标文件夹
> 2. 查询源所在文件
> 3. 逐个修改目标源

> [!done] 第一步，进入目标源文件夹

```linux
$ cd /usr/lib/python3/dist-packages
```

> [!done] 第二步，查询源所在文件

```linux
$ find . -type f | xargs grep "raw.githubusercontent"
```

> [!done] 逐个修改目标源

```linux
$ sudo gedit ./rosdistro/__init__.py 
$ sudo gedit ./rosdep2/gbpdistro_support.py
$ sudo gedit ./rosdep2/sources_list.py
$ sudo gedit ./rosdep2/rep3.py
```

- 注意：
	- 修改"raw.githubusercontent" -> "gitee.com/zhao-xuzuo/rosdistro/raw/master"
	- 修改完成之后，**不能将改bash(终端)关掉，需要重新开启一个终端，然后运行如下命令**

```linux
$ sudo rosdep init
$ rosdep update
```

> [!success] 期间如果没有报错，则修改成功！

### ROS测试

> [!todo] ROS小乌龟测试
>> [! example] 在三个终端中，分别运行如下三条命令
>> 1. roscore
>> 2. rosrun turtlesim turtlesim_node
>> 3. rosrun turtlesim turtle_teleop_key

```linux
bash 1: $ roscore
bash 2: $ rosrun turtlesim turtlesim_node
bash 3: $ rosrun turtlesim turtle_teleop_key
```

> [!attention] 光标必须聚焦在第三个命令的命令行上，才能进行移动

![[ROS测试.png]]

## ROS开发环境使用(C++)

- ROS和正常代码编写逻辑一样，都有一定的步骤，下面就是一个ROS代码模块的创建流程

> [!example] ROS模块创建流程  
>> 1. 创建工作空间初始化
>> 2. 创建功能包  
>> 3. 编辑源文件  
>> 4. 编辑配置文件  
>> 5. 编译并执行  

### 创建工作空间

> [!done] 创建工作空间

```linux
$ mkdir -p dir_name/src
$ cd dir_name
$ catkin_make
```

- 注意：
	- catkin_make需要在创建的工作空间中使用

### 创建功能包

> [!done] 创建功能包

```linux
[dir_name]$ cd src
[dir_name/src]$ catkin_create_pkg package_name roscpp rospy std_msgs
```

- 注意：
	- catkin_create_pkg命令需要在创建的src文件夹中使用
	- package_name是自定义的功能包的包名，roscpp rospy std_msgs是功能包的三个依赖

### 编辑源文件

> [!done] 编辑源文件

```linux
[dir_name/src]$ cd package_name/src/
[dir_name/src/package_name/src]$ touch file_name.cc
[dir_name/src/package_name/src]$ vim file_name.cc
```

```c++
#include "ros/ros.h" // ros的头文件

int main(int argc, char* argv[]){
	// 初始化ros节点
    ros::init(argc, argv, "hello_node);
    // 输出日志
    ROS_INFO("hello world!");
    return 0;
}
```

### 编辑配置文件

> [!done] 编辑配置文件

```linux
[dir_name/src/package_name/src]$ cd ..
[dir_name/src/package_name]$ vim CMakeLists.txt 
```

- 在CMakeLists.txt中，找到两行代码

```CMakeLists.txt
# add_executable(${PROJECT_NAME}_node src/package_node.cpp)
# target_link_libraries(${PROJECT_NAME}_node
#	${catkin_LABRARIES}
#)
```

- 编写：
	- 将这几行的注释解开，然后将${PROJECT_NAME}\_node换成exec_name(自己想要的名字)，将后面的src/package_node.cpp换成刚刚touch的file_name.cc
	- **注意，两个${PROJECT_NAME}\_node必须是一样的名字, 建议替换的名字是src中源文件的名字**

### 编译执行

> [!done] 编译并执行

```linux
[dir_name/src/package_name]$ cd ../..
[dir_name]$ catkin_make
Scanning dependencies of target hello
[ 50%] Building CXX object hello/CMakeFiles/hello.dir/src/main.cc.o
[100%] Linking CXX executable /home/zack/ros_study/hello/devel/lib/hello/hello
[100%] Built target hello
```

- 当出现如上的提示，就说明编译完成

```linux
[new bash]$ roscore
[dir_name]$ source ./devel/setup.bash
[dir_name]$ rosrun package_name exec_name
[ INFO] [1668348212.208457201]: hello
```

- 当打印出\[INFO]: hello就说明成功了
- **注意：**
	- 必须新起一个终端，运行roscore
	- **在运行rosrun命令前，必须先对devel文件夹下的setup.bash文件进行更新**，否则无法成功运行
	- 如果只是针对devel/setup.bash进行了更新，那么只能在当前路径下进行rosrun命令，**如果需要全局可运行，则可写入source ~/dir_name/devel/setup.bash进.bashrc中**

## ROS -> Vsc

### Vsc安装

> [!fail] 不是吧，阿sir，这都要人教？回家吃米去吧

### ROS工作环境的配置

``` linux
$ cd dir_name
$ code .
```

> [!done] 配置task.json

- 在Vsc中键入ctrl + shift + B，**选择catkin_make build**

```json
{
	"version": "2.0.0",
	"tasks": [
		{
			"command": "catkin_make", // 运行的命令
			"type": "shell", // 可选项shell 和 process
			"args": [ //在命令后面加的后缀，可以不写
				"--directory",
				"/home/zack/ros_study/hello", // ROS工作空间的绝对路径
				"-DCMAKE_BUILD_TYPE=RelWithDebInfo"
			],
			"problemMatcher": [
				"$catkin-gcc"
			],
			// "group": "build",
			"group": {"kind": "build", "isDefault": "true"}
			"label": "catkin_make: build", // 描述性信息
			"presentation": { 
				"reveal": "always"  // 可选项always 和 silence，表示是否输出信息
			}
	]
}
```

### Vsc中创建功能包

> [!done] 直接在Vsc中选定src目录右键在最下面选中catkin_create_pkg根据提示创建即可
>> [!warning] 但是建议，在终端中创建后再用Vsc打开更为方便
>> **如果不在终端中创建完毕，极大可能出现#include "ros/ros.h"出现错误提示**

- 解决方法：
	- 在c_cpp_properties.json文件中修改"cppStandard"的key值为"c++14/17"

```json
{
  "configurations": [
    {
      "browse": {
        "databaseFilename": "${default}",
        "limitSymbolsToIncludedHeaders": false
      },
      "includePath": [
        "/opt/ros/noetic/include/**",
        "/home/zack/ros_study/hello/src/hello/include/**",
        "/usr/include/**"
      ],
      "name": "ROS",
      "intelliSenseMode": "gcc-x64",
      "compilerPath": "/usr/bin/gcc",
      "cStandard": "gnu11",
      "cppStandard": "c++14"
    }
  ],
  "version": 4
}
```

> [!success] 当修改完保存之后，就可正常使用，如果在终端中创建完毕，则打开Vsc会自动检索更改

