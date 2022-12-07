# Git Flow工作流

## git

### 什么是git

> 分布式版本控制的软件

- 文件
	- 多个文件，不同版本
- 本地版本控制
	- 一个文件，多个版本，通过本地版本控制软件后台记录s
	- 弊端：无法协同
- 集中版本控制
	- 解决了协同问题 -> 通过单独建立一个云端，用户向云端传输拉取数据
	- 弊端：极度依赖于云端服务器，且集中版本控制只允许用户拿到其中的一个版本，没办法获取其他版本信息，除非主动拉取其他版本
- 分布式版本控制
	- 用户可以获取所有历史版本，且可以随时回滚，每一个用户就相当于一个云端

### 为什么要版本控制

- 防止当前代码错误，严重BUG产生，或者其他业务原因，能够回滚到之前没有问题的地方 -> 回档

## git flow的介绍

## git flow的作用

## git命令的使用

### git的最先配置

```git
git config --global user.email "xxx@xxx.email.com"
git config --global user.name "user_name"
```

- 且在推送前，还需要再次输入密码进行凭证管理 (此处需要演示)
- **要配置正确，不然可能会在push阶段出错**

### 一次简单的使用

```git
git init
git add file_name1 ...
git commit -m "first to use"

git status
git log
```

### git的三大分区

#### 工作区

- 本地的代码仓库 -> 分为已跟踪和未跟踪

#### 暂存区

- add之后，只是将未跟踪的文件告诉git需要跟踪，**但是此时并没有进行一个版本管理**

#### 版本库

#### git命令的使用

##### help

> git的帮助手册

```git
git help
work on the current change (see also: git help everyday)
   add               Add file contents to the index
   mv                Move or rename a file, a directory, or a symlink
   restore           Restore working tree files
   rm                Remove files from the working tree and from the index
   sparse-checkout   Initialize and modify the sparse-checkout

examine the history and state (see also: git help revisions)
   bisect            Use binary search to find the commit that introduced a bug
   diff              Show changes between commits, commit and working tree, etc
   grep              Print lines matching a pattern
   log               Show commit logs
   show              Show various types of objects
   status            Show the working tree status

grow, mark and tweak your common history
   branch            List, create, or delete branches
   commit            Record changes to the repository
   merge             Join two or more development histories together
   rebase            Reapply commits on top of another base tip
   reset             Reset current HEAD to the specified state
   switch            Switch branches
   tag               Create, list, delete or verify a tag object signed with GPG

collaborate (see also: git help workflows)
   fetch             Download objects and refs from another repository
   pull              Fetch from and integrate with another repository or a local branch
   push              Update remote refs along with associated objects
```

```git
git help -a # 获取全部git命令
git help -g # 输出有用的git指南
git help command # 获取单独命令的详细介绍
```

##### config

> git的配置选项

- \--system
	- 对于编写选项：写入系统范围`$(prefix)/etc/gitconfig`而不是存储库`.git/config`。
	- 对于阅读选项：只能从系统范围内读取，`$(prefix)/etc/gitconfig`而不能从所有可用文件中读取

- \--global

```git
# git的用户配置
git config --global user.email "xxx@xxx.email.com"
git config --global user.name "user_name"
```

- \--list

```git
# 列出git配置
git config --list
	init.defaultbranch=master
	user.name=xxx
	user.email=xxx@xxx.com
	remote.origin.url=https://github.com/xxx/xxx.git
```

- \--unset

```git
# 重置git config信息
git config --unset --global user.name
git config --unset --global user.email
```

- gitconfig文件

```linux
cat ~/.gitconfig
```

##### init

> 初始化一个git仓库

```git
git init
```

##### add

> 让文件被git所跟踪

```git
git add file1 ...

git add .
```

##### commit

> 将本次修改作为一个版本提交 -> 写入仓库中

```git
git commit -m "msg"
```
- **建议每次commit时，都需跟上参数-m，否则git会自动打开文本编辑器让你填入信息，如果不填入，那么就会中断**

- \-a

```git
git commit -m "msg" -a tracked_file
```
- **注意：-a选项必须已经是被追踪的文件**

##### diff

> 显示提交和工作树之间的差别

```git
git diff file_name
```

- 如果比较的文件**修改后还未添加入暂存区，那么是该文件和工作树(也就是repository)中的做对比**
- 如果修改后使用了git add进入暂存区，**那么就会使用暂存区中的文件和工作树中的做对比**
- 如果修改后为加入暂存区，且暂存区中还有一份修改，**那么就会用修改的和暂存区作比较**

- \--staged/--cached

```git
git diff --staged 
# 如果想要查看暂存区和工作树中的区别，那么要加上--staged选项
```

##### rename操作

> 重命名一个git已经跟踪了的文件
> **如果我们只是简单的将文件改名，那么git没办法知道该文件还是原来的文件**

```git
git rm src_file
git add dest_file
```

- 只有这样通过上述操作，才能使得git正确的匹配上文件

###### mv

> git提供的重命名方法

```git
git mv src_file dest_file
```

> **但实际上mv的作用是用于移动上**

```git
git mv file path
```

##### rm

> 删除跟踪的文件

```git
git rm tracked_file
```

- \--cached

```git
git rm --cached tracked_file
# 删除已经处于工作树的跟踪，但在本地保留该文件
```

- \-f 

```git
git rm -f tracked_file
# 强制删除处于工作树的跟踪，不会保留
```

###### 删除后恢复

```git
git checkout HEAD -- rmed_file
```

#### revert

> 用于回滚版本

```git
git revert commit-id

git revert HEAD~n
```
- 注意：当回滚时，会弹出输入回滚的信息。**回滚的版本后的操作将被删除！**



## git flow的使用

### 关于视觉组的规划

