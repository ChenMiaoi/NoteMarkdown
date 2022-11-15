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

