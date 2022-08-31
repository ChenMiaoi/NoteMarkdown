# 高级IO

---

- IO
> IO本身是站在硬件角度(进程或者线程)进行输入输出。

- IO步骤
	- 等待IO就绪
	- 拷贝IO数据到内核或者到外设

## 五种IO模型

### 同步IO

#### 阻塞IO

> 在内核将数据准备好之前，系统调用会一直等待，所有的套接字，默认都是阻塞状态

![[Pasted image 20220827170329.png]]

#### 非阻塞IO

> 如果内核还未将数据准备好，系统调用仍然会直接返回，并且返回EWOULDBLOCK(Windows)错误码(如果在Linux上，则返回EAGAIN)

![[Pasted image 20220827172701.png]]

- 注意，**非阻塞IO往往需要程序员循环的方式反复尝试读写文件描述符，这个过程被称为轮询。这对CPU来说是一个较大的浪费，一般只有在特定的场景下才使用**
- **所谓的阻塞，是用户层的感受！在内核中本质是进程被挂起(S or T or D)，需要等待某种事件就绪

#### 信号驱动IO

> 内核将数据准备好的时候，使用SIGIO信号通知应用程序进行IO操作

![[Pasted image 20220828145119.png]]

#### 多路复用(多路转接)

> 最核心在于IO多路转接能够等待多个文件描述符

![[Pasted image 20220828150536.png]]

### 异步IO

> 内核在数据拷贝完成时，通知应用程序做对应的处理

![[Pasted image 20220828150230.png]]

## 非阻塞IO

#### fcntl

- int fcntl(int fd, int cmd, ...);
	- cmd参数值
		- 复制一个现有的描述符(cmd = F_DUPFD)
		- 获得/设置文件描述符标记(cmd = F_GETFD/F_SETFD)
		- 获得/设置文件状态标记(cmd = F_GETFL/F_SETFL)
		- 获得/设置异步I/O所有权(cmd = F_GETOWN/F_SETOWN)
		- 获得/设置记录所(cmd = F_GETLK/F_SETLK/F_SETKW)

#### 设置非阻塞

```c
bool SetNoBlock (int fd) {
  int fl = fcntl(fd, F_GETFL);
  if (fl < 0) {
    std::cerr << "fcntl error" << std::endl;
    return false;
  }

  fcntl(fd, F_SETFL, fl | O_NONBLOCK);
  return true;
}

void handler(int sign) {
  std::cout << "signal: " << sign << std::endl;
}

int main() {
  //SetNoBlock(0);
  signal(2, handler);
  while (true) {
    char buffer[1024] = {};
    ssize_t size = read(0, buffer, sizeof(buffer) - 1);
    if (size < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        std::cout << "wait for data msg" << std::endl;
        sleep(1);
        continue;
      }else if (errno == EINTER) {
	      std::cout << "底层数据是否就绪未知，被信号打断" << std::endl;
	      continue;
      }else {
        std::cerr << "read error: " << size << " errno: " << errno << std::endl;
        break;
      }
      //break;
      continue;
    } 

    buffer[size] = 0;
    std::cout << "echo# " << buffer << std::endl;
  }
}
```

- 注意：
	- **如果非阻塞，读取数据的时候，如果数据没有就绪，read会以出错的形式返回**
	- 因此，需要使用EAGAIN或EWOULDNBLOCK(errno被设置为11)
	- 同时，如果被信号打断，则会返回EINTER，此时不论数据就绪还是未就绪，都会被返回

## Select

### 初始Select

> 系统提供select函数来实现多路复用输入/输出模型

- select系统调用是用来让我们的程序监视多个文件描述符的状态变化
- 程序会停在select这里等待，知道被监视的文件描述符有一个或多个发生了状态改变

### Select原型

```c
#include <sys/select.h>

int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout);
```

- 参数：
	- nfds：是需要监视的最大的文件描述符值 + 1，对多个文件描述符进行轮询检测
	- fd_set 类似 sigset_t，是一个位图，可以将特定的fd添加到图中。**是输入输出型参数**
	- readfds，writefds，exceptfds分别对应于需要检测的可读文件描述符的集合，可写文件描述符的集合及异常文件描述符的集合
- 特别注意：
	- **select调用，每一次都需要进行对所关心的fd进行重新设置**
	- 如果是链接到来事件就绪，在多路转接看来，都统一当作读事件就绪

- 用户调用select，select是一个系统调用，所有的参数是给OS的

> user -> kernel[是用户想告诉内核什么呢？]：请OS检测一下在readfds中，所有的fd的状态
>> 是否是[读事件]就绪的
>
>kernel -> user[是内核想告诉用户什么呢？]：返回检测的readfds中的特定fd，已经有读数据就绪了

#### fd_set

```c
void FD_CLR(int fd, fd_set* set);    // 用来清除描述词组set中相关fd的位
int  FD_ISSET(int fd, fd_set* set);    // 用来测试描述词组set中相关fd的位是否为真
void FD_SET(int fd, fd_set* set);    // 用来设置描述词组set中相关fd的位
void FD_ZERD(fd_set* set);    // 用来清除描述词组set的全部位
```

#### struct timeval

```c
struct timeval {
	long    tv_sec;         /* seconds */
    long    tv_usec;        /* microseconds */
};
```

- 设置阻塞时间，若超时就返回
- NULL：表示select没有timeout，select将一直被阻塞，直到某个文件描述符上发生了事件
- 0：仅检测描述符集合状态，然后立即返回，并不等待外部事件的发生
- 特定的时间值：如果在指定的时间段里没有事件发生，select将超时返回

### Select Code

#### sock.hpp
``` c++
#ifndef __SOCK_H__
#define __SOCK_H__

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

namespace ns_sock{
  class Sock {
  public:
    static int Socket() {
      int sock = socket(AF_INET, SOCK_STREAM, 0);
      if (sock < 0) {
        std::cerr << "socket error" << std::endl;
        exit(1);
      }
      return sock;
    }

    static bool Bind(int sock, unsigned short port) {
      struct sockaddr_in local;
      memset(&local, 0, sizeof(0));
      local.sin_family = AF_INET;
      local.sin_port = htons(port);
      local.sin_addr.s_addr = INADDR_ANY;

      if (bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0) {
        std::cerr << "bind error" << std::endl;
        exit(2);
      }
      return true;
    }

    static bool Listen(int sock, int backlog) {
      if (listen(sock, backlog) < 0) {
        std::cerr << "listen error" << std::endl;
        exit(3);
      }
      return true;
    }
  };
}
#endif // !__SOCK_H__
```

#### select_server.hpp

```c++
#ifndef __SELECT_SERVER_H__
#define __SELECT_SERVER_H__

#include "sock.hpp"
#include <sys/select.h>
#include <sys/time.h>

#define BACK_LOG 5
#define NUM 1024
#define DEL_FD -1

namespace ns_select {
  class SelectServer {
  public:
    SelectServer(unsigned short port) : _port(port)
    {}

    ~SelectServer(){}
  public:
    void InitSelectServer() {
      _listen_sock = ns_sock::Sock::Socket();
      ns_sock::Sock::Bind(_listen_sock, _port);
      ns_sock::Sock::Listen(_listen_sock, BACK_LOG);
    }

    void Run() {
      fd_set rfds;
      int fd_array[NUM] = {};
      ClearArray(fd_array, NUM, DEL_FD);
      
      fd_array[0] = _listen_sock;
      for (; ;) {
        int max_fd = DEL_FD;
        FD_ZERO(&rfds);
        for (auto i = 0; i < NUM; i++) {
          if (fd_array[i] == DEL_FD) {
            continue;
          }
          FD_SET(fd_array[i], &rfds);
          if (max_fd < fd_array[i]) {
            max_fd = fd_array[i];
          }
        }
        struct timeval timeout = {5, 0};
        switch (select(max_fd + 1, &rfds, nullptr, nullptr, /*&timeout*/ nullptr)) {
          case 0:
            std::cout << "timeout" << std::endl;
            break;
          case -1:
            std::cout << "select error" << std::endl;
            break;
          default:
            //std::cout << "have event done! timeout: " << timeout.tv_usec << std::endl;
            HandlerEvent(rfds, fd_array, NUM);
            break;
        }
      }
    }

    void HandlerEvent(const fd_set rfds, int fd_array[], int num) {
      for (auto i = 0; i < num; i++) {
        if (fd_array[i] == DEL_FD) {
          continue;
        }

        if (fd_array[i] == _listen_sock && FD_ISSET(fd_array[i], &rfds)) {
          //链接事件
          struct sockaddr_in peer;
          socklen_t len = sizeof(peer);
          int sock = accept(fd_array[i], (struct sockaddr*)&peer, &len);
          if (sock < 0) {
            std::cerr << "accept error" << std::endl;
            continue;
          }

          uint16_t peer_port = htons(peer.sin_port);
          std::string peer_ip = inet_ntoa(peer.sin_addr);

          std::cout << "get a new link" << peer_ip << " : " << peer_port << std::endl;
          //此时不允许进行对应的recv
          //需要将该文件描述符添加到fd_array数组中
          if (!AddFdToArray(fd_array, NUM, sock)) {
            close(sock);
            std::cout << "select server is full, close fd: " << sock << std::endl;
          }
        }else {
          if (FD_ISSET(fd_array[i], &rfds)) {
            //是一个合法的文件描述符，并且是读事件就绪
            char buffer[NUM];
            ssize_t s = recv(fd_array[i], buffer, sizeof(buffer) - 1, 0);
            if (s > 0) {
              buffer[s] = 0;
              std::cout << "echo# " << buffer << std::endl;
            }else if (s == 0) {
              std::cout << "client quit" << std::endl;
              close(fd_array[i]);
              fd_array[i] = DEL_FD; // 清除数组中的文件描述符
            }else {
              std::cerr << "recv error" << std::endl;
              close(fd_array[i]);
              fd_array[i] = DEL_FD; // 清除数组中的文件描述符
            }
          }else {

          }
        }
      }
    }
  private:
    void ClearArray(int fd_array[], int num, int default_fd) {
      for (auto i = 0; i < num; i++) {
        fd_array[i] = default_fd;
      }
    }

    bool AddFdToArray(int fd_array[], int num, int sock) {
      for (auto i = 0; i < num; i++) {
        if (fd_array[i] == DEL_FD) { //相当于为使用的位置
          fd_array[i] = sock;
          return true;
        }
      }

      return false;
    }
  private:
    int _listen_sock;
    unsigned short _port;
  };
}

#endif // !__SELECT_SERVER_H__

```

- 注意：
	- 给定链接的时候，需要给每一个链接定义一个缓冲区(输入输出缓冲区)

```c++
struct buckets{
	buckets() : _in_curr(0), _out_curr(0) {}
	
	std::string _inbuffer;
	std::string _outbuffer;
	int _in_curr;    //已经接收到了多少数据
	int _out_curr;   //已经发送了多少数据
};
```

#### server.cc

```c++
#include "select_server.hpp"
#include <string>
#include <cstdlib>

static void Usage(std::string proc) {
  std::cerr << "Usage: " << "\n\t" << proc << " port " << std::endl;
}
int main(int argc, char* argv[]) {
  if (argc != 2) {
    Usage(argv[0]);
    exit(4);
  }

  unsigned short port = atoi(argv[1]);
  ns_select::SelectServer* select_svr = new ns_select::SelectServer(port);
  select_svr->InitSelectServer();
  select_svr->Run();

  return 0;
}
```

### select的特征

#### 缺点

- **select能够同时等待的文件描述符是有上限的**
- select需要和OS交互数据，涉及到较多数据的来回拷贝。当select面临的链接很多，就绪的数据也很多的时候，会因为数据拷贝而导致效率降低
- select每次调用，都必须重新添加fd，一定会影响程序运行的效率，而且比较麻烦，容易出错
- select(nfds ...)，max(fd) + 1：操作系统在检测fd就绪的时候，需要遍历的，所以当有大量的链接的时候，内核同步select底层遍历，成本会变得越来越高

#### 优点

- select可以同时多个fd，而且只负责等待，有具体的accept，recv，send来完成实际的IO操作，且不会被阻塞

## Poll

### poll原型

```c
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

#### struct pollfd

```c
struct pollfd {
    int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
```

#### events

```c
POLLIN There is data to read.

POLLPRI There  is  urgent data to read (e.g., out-of-band data on TCP socket; pseudoterminal master  in  packet  mode has seen state change in slave).

POLLOUT Writing now will not block.

POLLRDHUP (since Linux 2.6.17) Stream  socket  peer  closed  connection, or shut down writing half of connection.  The  _GNU_SOURCE  feature  test  macro  must  be  defined  (before  including any header files) in order to obtain this definition.

POLLERR Error condition (output only).

POLLHUP Hang up (output only).

POLLNVAL Invalid request: fd not open (output only).
```

### poll & select

- 解决了select能检测的文件描述符是有上限这一问题
- 分离了用户 -> OS，OS -> 用户
	- **不用在每次调用poll的时候，重新添加fd以及fd关心的事件**

### Poll Code

#### sock.hpp

``` c++
#ifndef __SOCK_H__
#define __SOCK_H__

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

namespace ns_sock{
  class Sock {
  public:
    static int Socket() {
      int sock = socket(AF_INET, SOCK_STREAM, 0);
      if (sock < 0) {
        std::cerr << "socket error" << std::endl;
        exit(1);
      }
      return sock;
    }

    static bool Bind(int sock, unsigned short port) {
      struct sockaddr_in local;
      memset(&local, 0, sizeof(0));
      local.sin_family = AF_INET;
      local.sin_port = htons(port);
      local.sin_addr.s_addr = INADDR_ANY;

      if (bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0) {
        std::cerr << "bind error" << std::endl;
        exit(2);
      }
      return true;
    }

    static bool Listen(int sock, int backlog) {
      if (listen(sock, backlog) < 0) {
        std::cerr << "listen error" << std::endl;
        exit(3);
      }
      return true;
    }
  };
}
#endif // !__SOCK_H__
```

#### poll.hpp

```c++
#include "sock.hpp"
#include <poll.h>

namespace ns_poll {
  class PollServer {
  public:
    PollServer(int port) : _port(port) {}

  public:
    void InitServer() {
      _listen_sock = ns_sock::Sock::Socket();
      ns_sock::Sock::Bind(_listen_sock, _port);
      ns_sock::Sock::Listen(_listen_sock, 5);
    }

    void Run() {
      struct pollfd rfds[64];
      for (int i = 0; i < 64; i++) {
        rfds[i].fd = -1;
        rfds[i].events = 0;
        rfds[i].revents = 0;
      }

      rfds[0].fd = _listen_sock;
      rfds[0].events |= POLLIN;
      rfds[0].revents = 0;
      for (; ;) {
        switch(poll(rfds, 64, -1)) {
        case 0:
          std::cout << "timeout" << std::endl;
          break;
        case -1:
          std::cerr << "poll error" << std::endl;
          break;
        default:
          for (int i = 0; i < 64; i++) {
            if (rfds[i].fd == -1) {
              continue;
            }
            if (rfds[i].revents & POLLIN) {
              //accept
              std::cout << "get a new link..." << std::endl;
            }else {
              //recv
            }
          }     
          break;
        }
      }
    }
  private:
    int _listen_sock;
    int _port;
  };
}
```

## Epoll

### epoll初识

> 为处理大批量句柄而作了改进的poll

- **公认为Linux2.6性能最好的多路I/O就绪通知方法**

### epoll的相关系统调用

> **epoll在底层采用的是回调机制，检测事件就绪的**

#### epoll_create

```c
int epoll_create(int size);
```

- 创建一个epoll的句柄
	- 自从Linux2.6.8之后，size参数是被忽略的
	- **用完之后必须调用close()关闭**

#### epoll_ctl

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
```

- epoll的事件注册函数
	- 不同于select实在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型
	- 第一个参数是epoll_create()的返回值(epoll的句柄)
	- 第二个参数表示动作，用三个宏来表示
		- EPOLL_CTL_ADD：注册新的fd到epfd中(往红黑树中新增节点)
		- EPOLL_CTL_MOD：修改已经注册的fd的监听事件
		- EPOLL_CTL_DEL：从epfd中删除一个fd
	- 第三个参数是需要监听的fd
	- 第四个参数是告诉内核需要监听什么事

#### epoll_wait

```c
int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
```

- 收集在epoll监控的事件中已经发送的事件
	- 参数events是分配号的epoll_event结构体数组
	- epoll将会把事件赋值到event数组中(**event不可以是空指针，内核只负责把数据赋值到这个events数组中，不会去帮助我们在用户态中分配内存**)
	- maxevent告知内核这个events有多大，这个maxevents的值不能大于创建epoll_create的size
	- timeout是超时时间(毫秒，0会立即返回，-1是永久阻塞)
	- 如果函数调用成功，返回对应I/O已准备好的文件描述符数目，若返回0表示已超时，返回小于0表示函数失败

#### struct epoll_event

```c
typedef union epoll_data{
	void* ptr;
	int fd;
	uint32_t u32;
	uint64_t u64;
}epoll_data_t;

struct epoll_event {
	uint32_t events;    //Epoll events
	epoll_data_t data;  //User data variable
};
```

#### events

- EPOLLIN：表示对应的文件描述符可以读(包括对端SOCKET正常关闭)
- EPOLLOUT：表示对应的文件描述符可以写
- EPOLLPRI：表示对应的文件描述符有紧急的数据可读(**外带数据到来**)
- EPOLLERR：表示对应的文件描述符发生错误
- EPOLLHUP：表示对应的文件描述符被挂断
- EPOLLET：将epoll设为边缘触发(Edge Triggered)模式，这是相对于水平出发(Level Triggered)来说的
- EPOLLONESHOT：只监听一次事件，当监听完这次事件后，如果还需要继续监听这个socket的话，**需要重新再次把这个socket假如到epoll队列中**

### epoll工作原理

- 当某一进程调用epoll_create方法时， Linux内核会创建一个eventpoll结构体，这个结构体中有两个成员与epoll的使用方式密切相关
- 每一个epoll对象都有一个独立的eventpoll结构体，用于存放通过epoll_ctl方法向epoll对象中添加进来的事件
- 这些事件都会挂载在红黑树中，如此，重复添加的事件就可以通过红黑树而高效的识别出来(红黑树的插入时间效率是lgn，其中n为树的高度)
- 而所有添加到epoll中的事件都会与设备(网卡)驱动程序建立回调关系，也就是说，当响应的事件发生时会调用这个回调方法
- 这个回调方法在内核中叫ep_poll_callback,它会将发生的事件添加到rdlist双链表中
- 在epoll中，对于每一个事件，都会建立一个epitem结构体
- 当调用epoll_wait检查是否有事件发生时，只需要检查eventpoll对象中的rdlist双链表中是否有epitem元素即可
- 如果rdlist不为空，则把发生的事件复制到用户态，同时将事件数量返回给用户. 这个操作的时间复杂度是O(1)

#### struct eventpoll

```c
struct eventpoll{  
....  
/*红黑树的根节点，这颗树中存储着所有添加到epoll中的需要监控的事件*/  
	struct rb_root rbr;  
/*双链表中则存放着将要通过epoll_wait返回给用户的满足条件的事件*/  
	struct list_head rdlist;  
....  
};
```

#### struct epitem

```c
struct epitem{  
	struct rb_node rbn;//红黑树节点  
	struct list_head rdllink;//双向链表节点  
	struct epoll_filefd ffd; //事件句柄信息  
	struct eventpoll *ep; //指向其所属的eventpoll对象  
	struct epoll_event event; //期待发生的事件类型  
};
```

