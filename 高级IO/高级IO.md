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
      }else if (errno == EINTER) {
	      std::cout << "底层数据是否就绪未知，被信号打断" << std::endl;
      }else {
        std::cerr << "read error: " << size << " errno: " << errno << std::endl;
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

