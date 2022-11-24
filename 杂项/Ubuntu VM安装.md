
## VMware workstation安装

[VMware链接直达车](https://customerconnect.vmware.com/cn/downloads/info/slug/desktop_end_user_computing/vmware_workstation_pro/16_0)

- VM16 产品密钥

```txt
ZF3R0-FHED2-M80TY-8QYGC-NPKYF

YF390-0HF8P-M81RQ-2DXQE-M2UT6

ZF71R-DMX85-08DQY-8YMNC-PPHV8

FA1M0-89YE3-081TQ-AFNX9-NKUC0 
```

- 可被重复使用，若失效，请自行寻找

## Ubuntu ISO

[Ubuntu官网链接直达车](https://ubuntu.com/)

> 暂时只推荐这两个版本，不推荐另外的

[华为镜像站18.04链接直达车](https://repo.huaweicloud.com/ubuntu-releases/18.04/)

[华为镜像站20.04链接直达车](https://repo.huaweicloud.com/ubuntu-releases/20.04/)

## Rufus

[rufus官网链接直达车](https://rufus.ie/zh/)

- Vectory

> 如果不满足于双系统的人~

[ventory官网链接直达车](https://www.ventoy.net/cn/)

## Ubuntu安装

- 制作启动盘
- 运行启动盘
- 根据自带的安装图形化界面选择相应的配置，完成安装

## Root和User

- Linux中，Root和User是两个很鲜明的角色

## 换源

- 进入apt源目录

```linux
$ cd /etc/apt
$ ls
apt.conf.d   preferences.d  sources.list    trusted.gpg
auth.conf.d  sources.list.d  trusted.gpg.d
[root]# vi sources.list
```

- 建议：
	- 不要将官方源删除，只需要注释掉即可
	- 为了以防万一，可以添加两或三个镜像站的源，包管理器的检索规则是，从上到下依次检索。如果失败，则下一条，直到检索完整个文件

- [阿里巴巴开源镜像站-OPSX镜像站-阿里云开发者社区 (aliyun.com)](https://developer.aliyun.com/mirror/)
- [清华大学开源软件镜像站 | Tsinghua Open Source Mirror](https://mirrors.tuna.tsinghua.edu.cn/)
- [华为开源镜像站_软件开发服务_华为云 (huaweicloud.com)](https://mirrors.huaweicloud.com/home)

- 换完源后，执行更新操作

```linux
$ sudo apt-get update
```

## Ubuntu包管理

- 使用apt的发行版本大致以Debian系发行版为主
	- 包括：Debian、Ubuntu、Deepin
	- deb包
- 简单的apt使用
	- 官方建议，以后的apt不再单独使用，都使用apt-get，~~虽然apt单独使用依旧可行~~
	- list
	- update
	- upgrade
	- install
	- remove
	- purge
	- clean(慎用)
	- autoclean(慎用)

```linux
update - 取回更新的软件包列表信息
upgrade - 进行一次升级
install - 安装新的软件包（注：软件包名称应当类似 libc6 而非 libc6.deb）
remove - 卸载软件包
purge - 卸载并清除软件包的配置
clean - 删除所有已下载的包文件
autoclean - 删除已下载的旧包文件
check - 核对以确认系统的依赖关系的完整性
source - 下载源码包文件
```

### 其他发行版包管理及其使用

- 以yum为主的发行版本，主要是RedHat系
	- 包括：CentOS，Fedora，RHEL(red hat enterprise)
	- rpm包
- 简单的yum使用
	- Fedora有自己的包管理器dnf
	- list
	- update(upgrade)
	- remove
	- search
	- clean

```linux
install：安装rpm软件包；
update：更新rpm软件包；
check-update：检查是否有可用的更新rpm软件包；
remove：删除指定的rpm软件包；
list：显示软件包的信息；
search：检查软件包的信息；
info：显示指定的rpm软件包的描述信息和概要信息；
clean：清理yum过期的缓存；
```

## Linux基本命令

### ls

- -a
- -l
- -h

### cd

- -
- ~

### cat

- -b
- -n

### pwd

### touch

### mkdir

- -p

### rmdir

### rm

- -r
- -f

### grep

```shell
^    # 锚定行的开始 如：'^grep'匹配所有以grep开头的行。    
$    # 锚定行的结束 如：'grep$' 匹配所有以grep结尾的行。
.    # 匹配一个非换行符的字符 如：'gr.p'匹配gr后接一个任意字符，然后是p。    
*    # 匹配零个或多个先前字符 如：'*grep'匹配所有一个或多个空格后紧跟grep的行。    
.*   # 一起用代表任意字符。   
[]   # 匹配一个指定范围内的字符，如'[Gg]rep'匹配Grep和grep。    
[^]  # 匹配一个不在指定范围内的字符，如：'[^A-FH-Z]rep'匹配不包含A-R和T-Z的一个字母开头，紧跟rep的行。    
\(..\)  # 标记匹配字符，如'\(love\)'，love被标记为1。    
\<      # 锚定单词的开始，如:'\<grep'匹配包含以grep开头的单词的行。    
\>      # 锚定单词的结束，如'grep\>'匹配包含以grep结尾的单词的行。    
x\{m\}  # 重复字符x，m次，如：'0\{5\}'匹配包含5个o的行。    
x\{m,\}   # 重复字符x,至少m次，如：'o\{5,\}'匹配至少有5个o的行。    
x\{m,n\}  # 重复字符x，至少m次，不多于n次，如：'o\{5,10\}'匹配5--10个o的行。   
\w    # 匹配文字和数字字符，也就是[A-Za-z0-9]，如：'G\w*p'匹配以G后跟零个或多个文字或数字字符，然后是p。   
\W    # \w的反置形式，匹配一个或多个非单词字符，如点号句号等。   
\b    # 单词锁定符，如: '\bgrep\b'只匹配grep。 
```

### find

```linux
sudo find /usr -name "stdio.h" | xargs grep -i "printf"

sudo find /usr -name "iostream" | xargs grep -i "cout"
```

### pipe

- 管道符 “|”， 将前一个命令的输出作为后一个命令的输入

### head

- -n
- -c

### tail

- -n
- -c

### tar

```linux
tar -cf archive.tar foo bar  # 从文件 foo 和 bar 创建归档文件 archive.tar。
tar -tvf archive.tar         # 详细列举归档文件 archive.tar 中的所有文件。

tar -rf all.tar *.gif
# 这条命令是将所有.gif的文件增加到all.tar的包里面去。-r是表示增加文件的意思。

tar -uf all.tar logo.gif
# 这条命令是更新原来tar包all.tar中logo.gif文件，-u是表示更新文件的意思。

tar -zcvf file.tar.gz xxx

tar -zxvf file.tar.gz
```

- 注意：**-f参数是归档文件名称，必须处于归档文件名前，也就是最后一个参数位置**

### zip

```linux
zip -r xxx.zip xxx xxx

unzip xxx.zip
```


## Vim的基本使用

- 普通模式/命令模式
	- ESC
- 插入模式
	- a/i/o三种方式
- 底行模式
	- :

- 移动光标
	- h、j、k、l
	- g：文章开头
	- G：文章最后
	- ^：移动到行首
	- $：移动到行尾
- 删除文字
	- x：按一次，删除光标所在位置的字符
	- \#x：删除n个
	- X：按一次，删除光标前位置的字符
	- \#X
	- dd：删除一行
	- ndd：删除n行
- 复制：
	- yy：复制一行到缓冲区
	- nyy：复制n行到缓冲区
	- p：将缓冲区中的复制信息粘贴出来
- 替换：
	- R：替换模式
- 撤销：
	- u：撤销上一次的操作
	- ctrl + r：撤销的恢复
- 转跳：
	- nG：转跳到指定行首
- 行号：
	- set nu
- 查找：
	- /key：往后查找
	- ?key：往前查找

## Git的基本使用

```linux
$ sudo apt-get install git
$ git config --global user.name        
$ git config --global user.email 
$ git config list
```

- 加入
- 提交
- 推送