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

### 创建工作空间(Python)

> [!done] 创建工作空间

```linux
$ mkdir -p dir_name/scripts
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
	// 初始化ros节点，注意，初始化节点的名称不允许出现空格
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

### 编写配置文件（Python)

> [!done] 编辑配置文件

- 在CMakeLists.txt中，找到代码

> [!warning] 在修改之前，必须将需要编译的Python文件添加可执行权限

```linux
$ chmod +x my_python_script.py
```

```CMakeLists.txt
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

catkin_install_python(PROGRAMS
  scripts/param_svr_set_p.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
```

- 注意：**my_python_script需要更改为自己的.py文件**

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

### 解决输出中文乱码问题

> [!done] 中文乱码问题，那么在源文件中加入**setlocale(LC_ALL, "")** 即可解决

```c++
#include "ros/ros.h" // ros的头文件

int main(int argc, char* argv[]){
	//解决中文乱码
	setlocale(LC_ALL, "");
	// setlocale(LC_CTYPE, "zh_CN.utf8");
	// 初始化ros节点
    ros::init(argc, argv, "hello_node);
    // 输出日志
    ROS_INFO("hello world!");
    return 0;
}
```

## ROS通信机制

> 机器人是一种高度复杂的系统性实现，在机器人上可能集成各种传感器以及运动控制实现，**为了解耦合，ROS中的每一个功能点都是单独的进程**。 准确的说，**ROS是进程(Nodes)的分布式框架**。

### ROS的基本通信机制

> [!example] ROS中的基本通信机制有如下三种：
> 1. 话题通信(发布订阅模式)
> 2. 服务通信(请求响应模式)
> 3. 参数服务器(参数共享模式)

#### 话题通信

> 话题通信的实现模型是比较复杂的，主要涉及到三个角色

> [!example] 话题通信中的三个角色：
> 1. ROS Master(管理者)
> 2. Talker(发布者)
> 3. Listener(订阅者)

##### 话题通信的基本流程

- Master**负责保管Takler和Listener注册的信息，并且匹配话题相同的Talker和Listener**，帮助Talker和Listener建立连接，连接建立后，Talker可以发布信息，且会被Listener订阅
	- 其实就很像TCP中的bind，绑定之后，双方建立信道可以listen和connect

![[ROS话题通信模型.png]]

###### Talker发布订阅 

> [!todo] Talker通过advertise(msg, RPC)将数据和RPC地址发送到Matser中，等待匹配

###### Listener生成话题

> [!todo] Listener通过subscribe(msg)生成对应话题

###### Master匹配话题

> [!todo] Matser通过发布和生成的话题进行匹配，将匹配上的话题的RPC地址发送到Listener处

###### Listener通过地址访问Talker

> [!todo] Listener通过connect("scan", TCP)，通过RPC向talker发送连接请求、话题名、消息类型、通讯协议。**此处是建立TCP通信**。

###### Talker向Listener确认连接信息

> [!todo] Talker通过RPC地址携带TCP协议向Listener确认连接

###### Listener向Talker确定可以发送数据

> [!todo] Listener通过connect(TCP)发送TCP协议请求数据传递

###### Talker收到请求向Listener发送数据

> [!todo] Talker发送数据

- 注意：

> [!warning] 其实在后面的TCP通信就是一个最基础的四次握手，**第一步和第二步没有顺序关系**，上述流程在ROS中已经封装好了，只需要调用接口即可

##### 话题通信案例

> [!todo] 需求：编写发布订阅实现，需要发布以10HZ(每秒10次)的频率发布文本信息，订阅方订阅消息并将消息内容打印输出

> 针对需求分析，该模型实现主要关注三个点：发布、接受、数据。
>> 1. 编写发布方实现
>> 2. 编写订阅方实现
>> 3. 编辑配置文件
>> 4. 编译并执行

###### 编写发布方实现

> [!done] 编写发布方源代码

```c++
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "erGouZi");    // 初始化节点
    ros::NodeHandle nh;                  // 创建ROS句柄
    // 发布方对象的话题和消息队列数的创建
    ros::Publisher pub = nh.advertise<std_msgs::String>("fang", 10);
    std_msgs::String msg;                // 发布消息
    ros::Rate rate(10);                  // 设置发送频率
    int count = 0;                       // 定义发布编号
    
    while (ros::ok) {                    // ros::ok判断节点是否有效
        // msg.data = "hello";
        std::string str = "hello ---> "; // 通过stringstream可以流式拼接对象
        str += std::to_string(count);
        msg.data = ss.c_str();           // 初始化发布消息
        pub.publish(msg);                // 发布消息
        ROS_INFO("The pub data: %s", ss.c_str());
        rate.sleep();                    // 延时
        count++;
        ros::spinOnce();                 // 官方建议添加，处理回调函数
    }
    
    return 0;
}
```

```c++
ros::Publisher advertise<M>(
	const std::string &topic, uint32_t queue_size, bool latch = false
)

// advertise<M> 提前告知泛型类型
// const std::string &topic 发布者发布的话题名
// uint32_t queue_size 消息队列的容量
```

- 注意：
	- **ROS中的字符串类型需要使用std_msgs库中的String**
	- 通过句柄来调用advertise函数来创建话题
	- 发送频率通过ros::Rate来设置，ros::Rate::sleep来使用
	- std_msgs::String类型的对象需要通过std_msgs::String::data来赋值
	- **最终的数据发布是由ros::Publisher::publish来发布的**

###### 编写订阅方实现

> [!done] 编写订阅方源代码

```c++
#include "ros/ros.h"
#include "std_msgs/String.h"

void doMsg(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("cuiHua pub data: %s", msg->data.c_str());
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "cuiHua");
    ros::NodeHandle nh;
    // ros::Subscriber sub = nh.subscribe("fang", 10, doMsg); 
    // 创建订阅者，定义想要订阅的话题，以及处理事件
    ros::Subscriber sub = nh.subscribe("fang", 10, doMsg); 
    ros::spin();
    return 0;
}
```

```c++

ros::Subscriber subscribe<M>(
	const std::string &topic, 
	uint32_t queue_size, 
	void (*fp)(const boost::shared_ptr<const M> &), 
	const ros::TransportHints &transport_hints = ros::TransportHints()
);

// ros::Subscriber subscribe<M>在此处可以不需要声明泛型，因为可以从发布方接受到的数据中自动推导数据类型
// const std::string &topic, 想要订阅的话题名
// void (*fp)(const boost::shared_ptr<const M> &)， 回调函数，用于处理接收到的数据
// std_msgs::String::ConstPtr&，const std_msgs::String*& 

ros::spin(); 

// 用于解决回调函数问题，如果不加，那么将会直接导致进程结束，回调函数无法运行，加上之后，可以每次都返回到回调函数处
```

- 注意：
	- **创建的节点不能与之前创建且运行的节点同名，否则会被干扰**
	- **订阅者的topic必须与发布者的topic一致才能接受消息**

> [!tip] 可以使用rostopic echo topic_name命令查看是否发布完成

###### 使用计算图查看发布订阅

> [!tip] 使用rqt_graph启动计算图

![[发布模型计算图.png]]

> 计算图其实没有任何功能，但是可以展现不同节点、模块之间的关系

###### C++和Python解耦合

> 在ROS中，不论是使用C++还是Python作为语言都是一样的，最大的差距就在于，**C++编写比较复杂但运行效率高，Python编写快捷但运行效率低**，因此ROS提供了让C++和Python互相运行的机制

> [!success] C++发布方

```c++
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "erGouZi");    // 初始化节点
    ros::NodeHandle nh;                  // 创建ROS句柄
    // 发布方对象的话题和消息队列数的创建
    ros::Publisher pub = nh.advertise<std_msgs::String>("fang", 10);
    std_msgs::String msg;                // 发布消息
    ros::Rate rate(10);                  // 设置发送频率
    int count = 0;                       // 定义发布编号
    
    while (ros::ok) {                    // ros::ok判断节点是否有效
        // msg.data = "hello";
        std::string str = "hello ---> "; // 通过stringstream可以流式拼接对象
        str += std::to_string(count);
        msg.data = ss.c_str();           // 初始化发布消息
        pub.publish(msg);                // 发布消息
        ROS_INFO("The pub data: %s", ss.c_str());
        rate.sleep();                    // 延时
        count++;
        ros::spinOnce();                 // 官方建议添加，处理回调函数
    }
    
    return 0;
}
```

> [!success] Python订阅方

```python
#! /usr/bin/env python
import rospy
from std_msgs.msg import String

def doMsg(msg: String):
    rospy.loginfo("sub data: %s", msg.data)

if __name__ == "__main__":
    rospy.init_node("huaHua")
    sub = rospy.Subscriber("fang", String, doMsg, queue_size = 10)
    rospy.spin()
```

> 只需要运行两个编译好的文件，就可以互相通信，并不需要多余操作

##### 话题通信自定义Msg

> 在ROS中，数据载体是一个较为重要的部分，ROS通过std_msgs封装了一些原生数据类型：String、int32、Char、Bool等，**但是一般都只包含了一个data字段， 因此描述性较差，所以需要学习自定义消息类型**

- msgs字段类型

| 类型 | 含义 | 类型 | 含义 |
| --- | --- | --- | --- |
| int8 | 8位的无符号int | int16 | 16位无符号int |
| int32 | 32位的无符号int | int64 | 64位无符号int |
| string | 字符串类型 | time | 时间 |
| duration | 时间 | other msg files | 其他msg文件类型 | 
| variable-length arrar[] | 可变的数组长度 | fixed-length array[C] | 固定的数组长度 |
| Header | 标头，包含时间戳和ROS中的坐标帧 |

> [!example]  自定义msg有以下几步：
> 1. 按照固定格式创建msg文件
> 2. 编辑配置文件
> 3. 编译生成可以被C++或Python调用的中间文件

> 需求：创建自定义信息，该消息包含人的姓名、身高、年龄信息

###### 创建msg文件

> [!todo] 在功能包中创建msg文件夹，创建file_name.msg，设置字段

```linux
$ mkdir msg
$ cd msg
$ touch Person.msg
$ vim Person.msg
```

```msg
string  name
int32   age
float32 height
```

###### 编辑配置文件

> [!todo] 分别编辑package.xml和CMakeLists.txt文件

```xml
<build_depend>roscpp</build_depend>
<build_depend>rospy</build_depend>
<build_depend>std_msgs</build_depend>

<exec_depend>roscpp</exec_depend>
<exec_depend>rospy</exec_depend>
<exec_depend>std_msgs</exec_depend>

 <!-- 找到上面六条语句，仿写依赖 -->
<build_depend>roscpp</build_depend>
<build_depend>rospy</build_depend>
<build_depend>std_msgs</build_depend>
<build_depend>message_generation</build_depend>

<exec_depend>roscpp</exec_depend>
<exec_depend>rospy</exec_depend>
<exec_depend>std_msgs</exec_depend>
<exec_depend>message_runtime</exec_depend>
```

- 主要在package.xml文件中添加两条依赖
	- <build_depend>message_generation\</build_depend>
	- <exec_depend>message_runtime\</exec_depend>

```cmakelists
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

# 第一步在find_package中加入message_generation

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

# 第二步，找到add_message_files取消注释，添加自己的.msg文件
add_message_files(
  FILES
  Person.msg
)

# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

# 第三步，放开generate_message，不需要做任何更改

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES custom_msg
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

# 第四步，放开CATKIN_DEPENDS roscpp rospy std_msgs， 添加message_runtime
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES custom_msg
 CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)
```

> [!done] 到此，配置文件就编辑完毕

###### 编译

> [!todo] 使用catkin编译后，会生成C++或Python需要调用的中间文件

```linux
Scanning dependencies of target std_msgs_generate_messages_py
[  0%] Built target std_msgs_generate_messages_py
Scanning dependencies of target _custom_msg_generate_messages_check_deps_Person
Scanning dependencies of target std_msgs_generate_messages_nodejs
[  0%] Built target std_msgs_generate_messages_nodejs
Scanning dependencies of target std_msgs_generate_messages_cpp
[  0%] Built target std_msgs_generate_messages_cpp
Scanning dependencies of target std_msgs_generate_messages_eus
[  0%] Built target std_msgs_generate_messages_eus
Scanning dependencies of target std_msgs_generate_messages_lisp
[  0%] Built target _custom_msg_generate_messages_check_deps_Person
[  0%] Built target std_msgs_generate_messages_lisp
Scanning dependencies of target custom_msg_generate_messages_nodejs
[ 14%] Generating Javascript code from custom_msg/Person.msg
Scanning dependencies of target custom_msg_generate_messages_py
[ 28%] Generating Python from MSG custom_msg/Person
[ 28%] Built target custom_msg_generate_messages_nodejs
Scanning dependencies of target custom_msg_generate_messages_cpp
[ 42%] Generating C++ code from custom_msg/Person.msg
[ 42%] Built target custom_msg_generate_messages_cpp
Scanning dependencies of target custom_msg_generate_messages_eus
[ 57%] Generating EusLisp code from custom_msg/Person.msg
[ 71%] Generating Python msg __init__.py for custom_msg
[ 85%] Generating EusLisp manifest code for custom_msg
[ 85%] Built target custom_msg_generate_messages_py
Scanning dependencies of target custom_msg_generate_messages_lisp
[100%] Generating Lisp code from custom_msg/Person.msg
[100%] Built target custom_msg_generate_messages_lisp
[100%] Built target custom_msg_generate_messages_eus
Scanning dependencies of target custom_msg_generate_messages
[100%] Built target custom_msg_generate_messages
```

- 当出现如上提示后，则说明编译成功

> [!warning] 生成的C++需要的中间文件全在workspace/devel/include文件夹中

```c++
namespace custom_msg
{
template <class ContainerAllocator>
struct Person_
{
  typedef Person_<ContainerAllocator> Type;

  Person_()
    : name()
    , age(0)
    , height(0.0)  {
    }
  Person_(const ContainerAllocator& _alloc)
    : name(_alloc)
    , age(0)
    , height(0.0)  {
  (void)_alloc;
    }
...
```

> [!warning] 生成的Python需要的中间文件全在workspace/devel/lib/python3/dist-packages/pkg_name/msg文件夹中

```python
class Person(genpy.Message):
  _md5sum = "0478132ca0c3bd1c734b5491000dabb1"
  _type = "custom_msg/Person"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """string name
int32 age
float32 height"""
  __slots__ = ['name','age','height']
  _slot_types = ['string','int32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       name,age,height

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Person, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.name is None:
        self.name = ''
      if self.age is None:
        self.age = 0
      if self.height is None:
        self.height = 0.
    else:
      self.name = ''
      self.age = 0
      self.height = 0.
```

###### 使用自定义的msg类型

> [!todo] 首先需要配置Vsc中的c_cpp_properties.json，否则导入msg可能会出错

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
        "/home/zack/ros_study/custom_msg/src/custom_msg/include/**",
        "/usr/include/**",
        "../dir_name/devel/include/**" // 此处就是需要添加的中间文件的绝对路径
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

> [!todo] 编写发布方源文件

```c++
#include "ros/ros.h"
#include "custom_msg/Person.h"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "Talker");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<custom_msg::Person>("topic", 10);
    custom_msg::Person person;
    person.name = "Lily";
    person.age  = 18;
    person.height = 1.73;
    ros::Rate rate(1);

    while (ros::ok()) {
        pub.publish(person);
        rate.sleep();
        person.age += 1;
        ros::spinOnce();
    }
    return 0;
}
```

- 注意：
	- 自动生成的Person类，没有有参构造，只能通过调用成员进行赋值，或者通过拷贝构造

> [!todo] 编写订阅方源文件

```c++
#include "ros/ros.h"
#include "custom_msg/Person.h"
#include <functional>

void doMsg(const custom_msg::Person& msg) {
    ROS_INFO("sub msg: %s, %d, %.2f", msg.name.c_str(), msg.age, msg.height);
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "Listener");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic", 10, doMsg);
    // std::function<void(const custom_msg::Person&)> func = [](const custom_msg::Person& msg) {
    //     ROS_INFO("sub msg: %s, %d, %.2f", msg.name.c_str(), msg.age, msg.height);
    // };
    // ros::Subscriber sub = nh.subscribe("topic", 10, func);
    ros::spin();
    return 0;
}
```

> [!warning] 注意，编写完成之后，不能直接编译，必须还得配置以下CMakeLists.txt

```CMakeLists
# add_dependencies(
	${PROJECT_NAME}_node 
	${${PROJECT_NAME}_EXPORTED_TARGETS} 
	${catkin_EXPORTED_TARGETS}
)

add_dependencies(custom_pub ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(custom_sub ${PROJECT_NAME}_generate_messages_cpp)

# 更改上述依赖，是为了在编译源文件的时候确定让自定义的msg已经编译了，从而不会引发冲突
```

> [!fail] 警示，不能直接使用rostopic echo topic_name，因为数据类型是自定义的，需要进入工作目录刷新

```linux
$ rostopic echo topic
ERROR: Cannot load message class for [custom_msg/Person]. Are your messages built?
$ cd workspace
[workspace]$ source ./devel/setup.bash
[workspace]$ rostopic echo topic
name: "Lily"
age: 106
height: 1.7300000190734863
---
```

#### 服务通信

> 服务通信也是ROS中极其常用的通信模式。**服务通信是基于请求响应模式的，是一种应答机制**

##### 服务通信的基本流程

> 以请求响应的方式实现不同节点之间数据交互的通信模式。**用于偶然的、对实时性有要求、有一定逻辑处理需求的数据传输场景**

> [!example] 服务通信略微简单，模型主要涉及到三个角色：
> 1. ROS Master(管理者)
> 2. Server(服务端)
> 3. Client(客户端)

> Master负责保管Server和Client注册的信息，并匹配话题相同的Server与Client，帮助Server与Client建立连接，完成后，**Client发送请求信息，Server返回相应信息**

![[服务通信.png]]

###### Talker注册信息

> [!todo] Talker向Master提交服务名称和自身信息

###### Listener注册信息

> [!todo] Listener向Matser提交需要获取服务名称和自身信息

###### Master匹配服务

> [!todo] Master在注册信息中，匹配服务对应的Talker和Listener

###### Listener发起请求

> [!todo] Listener向Talker发起请求，获取资源

###### Talker响应请求

> [!todo] Talker接受Listener请求，发送资源

##### 服务通信自定义Srv

> [!example]  自定义srv有以下几步：
> 1. 按照固定格式创建srv文件
> 2. 编辑配置文件
> 3. 编译生成可以被C++或Python调用的中间文件

> [!todo] 需求：创建服务器与客户端通信的数据载体

###### 创建srv文件

> 服务器通信中，数据分成两部分，请求与响应，在srv文件中请求和响应使用---分割

> [!todo] 在功能包下新建srv目录，添加file_name.srv文件

```linux
$ mkdir srv
$ cd srv
$ touch AddInts.srv
$ vim AddInts.srv
```

```srv
int32 num1
int32 num2
---
int32 sum
```

> [!warning] 注意：请求和响应使用"---"分割

###### 编辑配置文件

> [!todo] 分别编辑package.xml和CMakeLists.txt文件

```xml
 <!-- package.xml文件的更改和话题通信自定义Msg一样 -->
<build_depend>roscpp</build_depend>
<build_depend>rospy</build_depend>
<build_depend>std_msgs</build_depend>
<build_depend>message_generation</build_depend>

<exec_depend>roscpp</exec_depend>
<exec_depend>rospy</exec_depend>
<exec_depend>std_msgs</exec_depend>
<exec_depend>message_runtime</exec_depend>
```

```CMakeLists.txt
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

# 第一步，还是需要依赖message_generation
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

# 第二步，找到add_service_files依赖，添加自定义的srv
add_service_files(
  FILES
  AddInts.srv
)

# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

# 第三步，因为自定义的messages需要依赖generate_messages
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES server_comm
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

# 第四步，放开catkin的依赖，添加自定义srv
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES server_comm
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)

# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# 第五步，防止所需其他依赖在运行前没有执行
add_dependencies(exec_name ${PROJECT_NAME}_gencpp)
```

> [!success] 到此，配置文件编辑完毕

###### 编译

> [!todo] 使用catkin编译后，会在dir_name/devel文件夹下生成C++或Python需要对应的中间文件

> [!warning] 生成的C++需要的中间文件全在workspace/devel/include文件夹中

```c++
// server_comm/AddInts.h
namespace server_comm {

struct AddInts {

	typedef AddIntsRequest Request;
	typedef AddIntsResponse Response;
	Request request;
	Response response;

	typedef Request RequestType;
	typedef Response ResponseType;

	}; // struct AddInts
} // namespace server_comm

// server_comm/AddIntsRequest.h
namespace server_comm {
	template <class ContainerAllocator>
	struct AddIntsRequest_
	{
		  typedef AddIntsRequest_<ContainerAllocator> Type;
		
		  AddIntsRequest_()
		    : num1(0)
		    , num2(0)  {
		    }
		  AddIntsRequest_(const ContainerAllocator& _alloc)
		    : num1(0)
		    , num2(0)  {
		  (void)_alloc;
		    }
		
		   typedef int32_t _num1_type;
		  _num1_type num1;
		
		   typedef int32_t _num2_type;
		  _num2_type num2;
		
		  typedef boost::shared_ptr< ::server_comm::AddIntsRequest_<ContainerAllocator> > Ptr;
		  typedef boost::shared_ptr< ::server_comm::AddIntsRequest_<ContainerAllocator> const> ConstPtr;
	}; // struct AddIntsRequest_

// server_comm/AddIntsResponse.h
namespace server_comm {
	template <class ContainerAllocator>
	struct AddIntsResponse_ {
		  typedef AddIntsResponse_<ContainerAllocator> Type;
		
		  AddIntsResponse_()
		    : sum(0)  {
		    }
		  AddIntsResponse_(const ContainerAllocator& _alloc)
		    : sum(0)  {
		  (void)_alloc;
		    }
		
		   typedef int32_t _sum_type;
		  _sum_type sum;
		
		  typedef boost::shared_ptr< ::server_comm::AddIntsResponse_<ContainerAllocator> > Ptr;
		  typedef boost::shared_ptr< ::server_comm::AddIntsResponse_<ContainerAllocator> const> ConstPtr;
	
	}; // struct AddIntsResponse_
```

> [!warning] 生成的Python需要的中间文件全在workspace/devel/lib/python3/dist-packages/pkg_name/msg文件夹中

```python
class AddIntsRequest(genpy.Message):
  _md5sum = "c68f3979e1a90aac7d1c75a1096d1e60"
  _type = "server_comm/AddIntsRequest"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """int32 num1
int32 num2
"""
  __slots__ = ['num1','num2']
  _slot_types = ['int32','int32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       num1,num2

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(AddIntsRequest, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.num1 is None:
        self.num1 = 0
      if self.num2 is None:
        self.num2 = 0
    else:
      self.num1 = 0
      self.num2 = 0
```

##### 服务通信案例

> [!todo] 需求：实现两个数字的求和，客户端节点运行会向服务器发送两个数字，服务器端节点接收两个数字求和并将结果响应回客户端

###### 配置自定义Srv路径

> [!fail] 什么玩意？还需要教？

###### 编写服务端源文件

```c++
#include "ros/ros.h"
#include "server_comm/AddInts.h"

bool doNums(server_comm::AddInts::Request& request, 
            server_comm::AddInts::Response& response) {
    ROS_INFO("the recieve num1: %d, num2: %d", request.num1, request.num2);
    response.sum = request.num1 + request.num2;
    ROS_INFO("the gain sum: %d", response.sum);
    return true;
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "server");
    ros::NodeHandle nh;
    ros::ServiceServer server = nh.advertiseService("topic", doNums);
    ros::spin();
    return 0;
}
```

> [!done] 完成服务端编写

###### 编写客户端源文件

```c++
#include "ros/ros.h"
#include "server_comm/AddInts.h"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<server_comm::AddInts>("topic");
    server_comm::AddInts peer;
    while (ros::ok()) {
        std::cin >> peer.request.num1;
        std::cin >> peer.request.num2;

        if (client.call(peer)) {
            ROS_INFO("response success");
            ROS_INFO("recieve the peer result: %d", peer.response.sum);
        }else {
            ROS_INFO("resonse error!");
            exit(1);
        }
    }
    return 0;
}
```

> [!done] 完成客户端编写

###### 配置CMakeLists.txt

> [!warning] 如果需要配置add_dependencies，那么需要做以下调整

```CMakeLists.txt
## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/server_comm_node.cpp)
```

> [!fail] add_dependencies不允许在add_executable之前，*add_dependencies和target_link没有顺序要求*。add_dependencies的target_name必须和add_executable的target_name相同

###### 测试服务通信

> [!tip] 可以通过命令rosservice call topic_name msg

```linux
[bash1]$ roscore
[bash2]$ rosrun pkg_name target_name
[bash3]$ rosservice call topic "num1: 2 num2: 3"
sum: 6
```

#### 参数服务器

> 参数服务器在ROS中主要用于不同节点之间的数据共享。**参数服务器相当于是独立于所有节点的一个公共容器。可以将数据存储在该容器中，被不同的节点调用**

##### 参数服务器的基本流程

> 主要用于**存在数据共享的场景**，以共享的方式实现不同节点之间的数据交互的通信模式。

> [!example] 参数服务器的实现最为简单，依旧涉及三个角色：
> 1. ROS Master(管理者)
> 2. Talker(参数设置者)
> 3. Listener(参数调用者)

> Matser作为一个公共的容器保存参数，Talker可以向容器中设置参数，Listener可以获取参数
![[ROS参数服务器.png]]

> [!warning] 以下步骤全部通过RPC地址进行发送

###### Talker设置参数

> [!todo] Talker通过setParam()来向Master设置参数和对应参数数据

###### Listener获取参数数据

> [!todo] Listener通过getParam()来向Master请求对应参数数据

###### Master发送Listener请求的对应数据

> [!todo] Master向Listener发送匹配的参数数据

###### 参数服务器可使用的数据类型

| 类型 | 含义 | 类型 | 含义 | 
| :---: | :---: | :---: | :---: | 
| 32-bit integers | 32位整型 | booleans | 布尔代数 |
| strings | 字符串 | doubles | 浮点 |
| iso8601 dates | 日期和时间 | lists | 列表 |
| base64-encoded binary data | Base64传输字节码 | 字典 | - |

- ISO 8601是**日期和时间的表示方法**，全称为《数据存储和交换形式·信息交换·日期和时间的表示方法》
- **Base64是网络上最常见的用于传输8Bit 字节码 的编码方式之一**，是一种用64个字符来表示任意 二进制 数据的方法

> [!fail] 注意：参数服务器不是为高性能而设计的，因此最好用存储静态的非二进制简单数据
> 

##### 参数服务器案例(C++)

> [!todo] 需求：实现参数服务器参数的增删查改

- 在C++中的参数服务器，是有着两套API的

```c++
1. ros::NodeHandle
2. ros::param
```

###### 参数服务器的增加和修改

> [!todo] 编写参数服务器的增加和修改源文件

```c++
#include "ros/ros.h"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "param_set_c");
    ros::NodeHandle nh;
    nh.setParam("type", "Type");
    nh.setParam("radius", 0.15);

    // ros::param::set("type", "Type");
    // ros::param::set("radius", 0.15);

    nh.setParam("type", "Non-Type");
    nh.setParam("radius", 0.2);

    // ros::param::set("type", "Non-Type");
    // ros::param::set("radius", 0.2);
    return 0;
}
```

```c++
NodeHandle::setParam(key, value);

ros::param::set(key, value);

// 在ROS中，可以使用这两种进行增加参数，使用的方式一模一样，通过键值对传递参数和对应数据
// 如果重复调用增加API，且key值相同，那么会覆盖之前的设置，达到修改的目的
// setParam和set重载了很多版本，包括基本内置类型，和vector，string，map
```

> [!tip] 可以通过rosparam查看ROS所有设置的参数

```linux
$ rosparam list
/radius
/rosdistro
/roslaunch/uris/host_ubuntu__35995
/rosversion
/run_id
/type

$ rosparam get param_name
$ rosparam get /radius
0.15
$ rosparam get /type
Type
```

###### 参数服务器的获取

> [!todo] 编写参数服务器获取的源文件

- 同样的，依旧有两套API

```c++
1. ros::NodeHandle::param(key, defaultVar)
// 如果存在，返回对应结果，否则返回默认值
2. ros::NodeHandle::getParam(key, refVar)
// 如果存在，返回true，且将key对应的值赋值给refVar；如果不存在，返回false，且不赋值
3. ros::NodeHandle::getParamCached(kay, refVar)
// 如果存在，返回true，且将key对应的值赋值给refVar；如果不存咋，返回false，且不赋值
// 提高变量的获取效率 -> 会首先判断是否调用过，如果有过，则直接从本地缓存中获取，提高获取效率
4. ros::NodeHandle::getParamNames(std::vector<std::string>)
// 获取所有的键，并存储在vector中
5. ros::NodeHandle::hasParam(key)
// 如果存在这个键，返回true，否则返回false
6. ros::NodeHandle::searchParam(searchVar, refVar)
// 搜索指定的键，如果存在就将key对应的值赋值给refVar

1. ros::param::param -> ros::NodeHandle::param
2. ros::param::get -> ros::NodeHandle::getParam
3. ros::param::getCached -> ros::NodeHandle::getParamCached
4. ros::param::getParamNames -> ros::NodeHandle::getParamNames
5. ros::param::has -> ros::NodeHandle::hasParam
6. ros::param::search -> ros::NodeHandle::searchParam
```

```c++
#include "ros/ros.h"
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "param_get_c");
    ros::NodeHandle nh;
    double radius = nh.param("radius", 0.5);
    ROS_INFO("radius = %.2f", radius);

    bool ref = nh.getParam("radius", radius);
    if (ref) {
        ROS_INFO("get the radius is: %.2f", radius);
    }else {
        ROS_INFO("radius is not found");
    }

    ref = nh.getParamCached("radius", radius);
    if (ref) {
        ROS_INFO("get the radius is: %.2f", radius);
    }else {
        ROS_INFO("radius is not found");
    }

    std::vector<std::string> names;
    nh.getParamNames(names);
    for (auto&& name: names) {
        ROS_INFO("the key is: %s", name.c_str());
    }

    if (nh.hasParam("radius")) {
        ROS_INFO("the radius exsist");
    }else {
        ROS_INFO("don't exsist");
    }

    std::string key;
    nh.searchParam("radius", key);
    ROS_INFO("seach result is: %s", key.c_str());

    // double radius = ros::param::param("radius", 0.5);
    // ROS_INFO("radius = %.2f", radius);

    // bool ref = ros::param::get("radius", radius);
    // if (ref) {
    //     ROS_INFO("get the radius is: %.2f", radius);
    // }else {
    //     ROS_INFO("radius is not found");
    // }

    // ref = ros::param::getCached("radius", radius);
    // if (ref) {
    //     ROS_INFO("get the radius is: %.2f", radius);
    // }else {
    //     ROS_INFO("radius is not found");
    // }

    // std::vector<std::string> names;
    // ros::param::getParamNames(names);
    // for (auto&& name: names) {
    //     ROS_INFO("the key is: %s", name.c_str());
    // }

    // if (ros::param::has("radius")) {
    //     ROS_INFO("the radius exsist");
    // }else {
    //     ROS_INFO("don't exsist");
    // }

    // std::string key;
    // ros::param::search("radius", key);
    // ROS_INFO("seach result is: %s", key.c_str());
    return 0;
}
```

> [!done] 完成了API的编写

###### 参数服务器的参数删除

> [!todo] 参数服务器的删除源文件编写

```c++
1. ros::NodeHandle::delParam

1. ros::param::del
```

```c++
#include "ros/ros.h"

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "param_del_c");
    ros::NodeHandle nh;

    bool ref = nh.deleteParam("radius");
    if (ref) {
        ROS_INFO("del success");
    }else {
        ROS_INFO("del failed");
    }

    ref = ros::param::del("type");
    if (ref) {
        ROS_INFO("del success");
    }else {
        ROS_INFO("del failed");
    }
    return 0;
}
```

> [!done] 完成删除源文件的编写

##### 参数服务器案例(Python)

###### 参数服务器的增加和修改

> [!todo] 编写参数服务器的增加和修改源文件

```Python
1. rospy.set_param()

# 和C++ API用法一致
```

```Python
#! /usr/bin/env python

import rospy

if __name__ == "__main__":
    rospy.init_node("param_set_py")
    rospy.set_param("type", "Type")
    rospy.set_param("radius", 0.15)

    rospy.set_param("type", "Non-Type")
    rospy.set_param("radius", 0.50)
```

###### 参数服务器的获取

> [!todo] 编写参数服务器获取的源文件

```Python
1. rospy.get_param(key, defaultVar)
# 当键存在时，返回对应的键，反之返回默认值
2. rospy.get_param_cached(key, defaultVar)
# 和get_param一致，只是效率更高
3. rospy.get_param_names()
# 获取所有参数的键的集合
4. rospy.has_param(key)
# 判断是否有这个键
5. rospy.seach_param
# 查找某个键，并返回完整的键名

# 和C++ API用法一致
```

```Python
#! /usr/bin/env python

import rospy

if __name__ == "__main__":
    rospy.init_node("param_get_py")
    radius = rospy.get_param("radius", 0.50)
    radius2 = rospy.get_param("radius_m", 0.82)

    rospy.loginfo("radius = %.2f", radius)
    rospy.loginfo("radius2 = %.2f", radius2)

    radius = rospy.get_param_cached("radius", 0.5)
    radius2 = rospy.get_param_cached("radius_m", 0.82)

    rospy.loginfo("radius = %.2f", radius)
    rospy.loginfo("radius2 = %.2f", radius2)

    names = rospy.get_param_names()
    for name in names:
        rospy.loginfo("name = %s", name)

    if rospy.has_param("type"):
        rospy.loginfo("type exsist")
    else:
        rospy.loginfo("don't exsist")
    
    key = rospy.search_param("type")
    rospy.loginfo("key = %s", key)
```

###### 参数服务器的参数删除

> [!todo] 参数服务器的删除源文件编写

```Python
1. rospy.delete_parm(key)
```

```Python
#! /usr/bin/env python

import rospy

if __name__ == "__main__":
    rospy.init_node("param_del_py")
    try:
        rospy.delete_param("type")
    except Exception as e:
        rospy.loginfo("deleted param is not exsist")
```

> [!tip] 建议使用抛异常来防止重复删除

#### ROS常用命令(bash)

> 机器人系统中启动的节点少则几个，多则几十个，不同的节点名称各异，通信时使用的话题、服务、消息、参数等等都各不相同。**因此，ROS提供了一些实用的命令工具，可以用于获取不同的各类信息**

> [!tip] [ROS WIKI 命令 直达车](http://wiki.ros.org/ROS/CommandLineTools)
>> [!tip] 常用的各类命令：

| 命令 | 作用 | 命令 | 作用 |
| :---: | :---: | :---: | :---: |
| rosnode | 操作节点 | rostopic | 操作话题 | 
| rosservice | 操作服务 | rosmsg | 操作msg消息 |
| rossrv | 操作srv信息 | rosparam | 操作参数 |

- 注意：**ROS命令是动态的，可以动态获取想要的信息**

##### rosnode

- 用于获取节点信息命令

```linux
1. rosnode ping    测试到节点的连接状态
2. rosnode list    列出活动节点
3. rosnode info    打印节点信息
4. rosnode machine 列出指定设备上节点
5. rosnode kill    杀死某个节点
6. rosnode cleanup 删除不可连接的节点
```

> [!todo] 单独使用rosnode，可以获得rosnode的使用提示

```linux
$ rosnode
rosnode is a command-line tool for printing information about ROS Nodes.

Commands:
	rosnode ping	test connectivity to node
	rosnode list	list active nodes
	rosnode info	print information about node
	rosnode machine	list nodes running on a particular machine or list machines
	rosnode kill	kill a running node
	rosnode cleanup	purge registration information of unreachable nodes

Type rosnode <command> -h for more detailed usage, e.g. 'rosnode ping -h'
```

###### list

```linux
$ rosnode list
/Listener
/Talker
/rosout
```

###### ping

```linux
$ rosnode ping /Listener
rosnode: node is [/Listener]
pinging /Listener with a timeout of 3.0s
xmlrpc reply from http://ubuntu:37163/	time=7.288218ms
xmlrpc reply from http://ubuntu:37163/	time=0.407696ms
xmlrpc reply from http://ubuntu:37163/	time=0.546932ms
xmlrpc reply from http://ubuntu:37163/	time=0.430822ms
^Cping average: 2.168417ms
```

###### info

```linux
$ rosnode info /Listener
--------------------------------------------------------------------------------
Node [/Listener]    # 节点的名称
Publications:       # 节点的发布信息 
 * /rosout [rosgraph_msgs/Log]

Subscriptions:      # 节点的订阅信息
 * /topic [custom_msg/Person]

Services:           # 节点的服务信息
 * /Listener/get_loggers
 * /Listener/set_logger_level


contacting node http://ubuntu:37163/ ...
Pid: 4560           # 节点的进程号
Connections:        # 节点的连接信息
 * topic: /rosout
    * to: /rosout
    * direction: outbound (43603 - 127.0.0.1:57446) [12]
    * transport: TCPROS
 * topic: /topic
    * to: /Talker (http://ubuntu:45967/)
    * direction: inbound (60076 - ubuntu:39099) [11]
    * transport: TCPROS
```

###### machine

- 在后面跟的是主机名

```linux
# ROS是分布式的
$ rosnode machine ubuntu
/Listener
/Talker
/rosout
```

###### kill

```linux
$ rosnode kill /Listner
killing /Listener
killed
```

![[rosnode kill.png]]

###### cleanup

```linux
$ rosnode cleanup
# 用于清除僵尸节点，因为没有僵尸节点，所以无法演示
```

##### rostopic

> rostopic包含rostopic命令行工具，**用于显示有关ROS主题的调试信息**，还包括一个Python库，用于动态获取有关主题的信息并与之交互

```linux
1. rostopic bw     显示主题使用的宽带
2. rostopic delay  显示带有header的主题延迟
3. rostopic echo   打印信息到屏幕
4. rostopic find   根据类型查找主题
5. rostopic hz     显示主题的发布频率
6. rostopic info   显示主题相关信息
7. rostopic list   显示所有活动状态下的主题
8. rostopic pub    将数据发布到主题
9. rostopic type   打印主题类型
```

```linux
$ rostopic
rostopic is a command-line tool for printing information about ROS Topics.

Commands:
	rostopic bw	display bandwidth used by topic
	rostopic delay	display delay of topic from timestamp in header
	rostopic echo	print messages to screen
	rostopic find	find topics by type
	rostopic hz	display publishing rate of topic    
	rostopic info	print information about active topic
	rostopic list	list active topics
	rostopic pub	publish data to topic
	rostopic type	print topic or field type

Type rostopic <command> -h for more detailed usage, e.g. 'rostopic echo -h'
```

###### rostopic list(-v)

```linux
$ rostopic list
/rosout
/rosout_agg
/topic

$ rostopic list -v
Published topics:
 * /rosout_agg [rosgraph_msgs/Log] 1 publisher
 * /rosout [rosgraph_msgs/Log] 2 publishers
 * /topic [custom_msg/Person] 1 publisher

Subscribed topics:
 * /rosout [rosgraph_msgs/Log] 1 subscriber
 * /topic [custom_msg/Person] 1 subscriber
```

> [!warning] rostopic list -v显示详细信息，包括

###### rostopic echo

```linux
rostopic echo topic
name: "Lily"
age: 1874
height: 1.7300000190734863
---
name: "Lily"
age: 1875
height: 1.7300000190734863
---
name: "Lily"
age: 1876
height: 1.7300000190734863
---
```

###### rostopic echo

###### rostopic echo

###### rostopic echo

###### rostopic echo

###### rostopic echo

###### rostopic echo