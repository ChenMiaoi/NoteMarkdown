# MySQL  

---  

## MySQL前期准备

### 链接MySQL  

```mysql
mysql -h 127.0.0.1 -P 3306 -u root -p
```

- h : 链接那一台主机
- P : 端口号(默认3306)
- u : user
- p : 

## MySQL命令

- 创建数据库

```mysql
create database name;
```

> 创建数据库的本质就是在数据库路径下创建一个目录

- 创建表

```mysql
create table if not exists name(
	...,
	...
);
```

> 创建表的本质就是在指定数据库路径下创建一个普通文件

- 删除库

```mysql 
drop database name;
```

- 查看表

```mysql
desc table_name;
```

- 插入操作

```mysql
insert into table_name (key1, key2, ...) values (var1, var2, ...);
```

- 查询表

```mysql
select * from table_name;
```


### 库的操作

#### 创建数据库

```mysql
create database [if not exists] db_name [create_specification [, create_specification] ...];
```

> []是可选项  
> character set指定数据库采用的字符集
> collate指定数据库字符集的校验规则
> 

- 案例：

```mysql
create database db1 charset=utf8 collate utf8_general_ci

# 可以使用show charset查看字符集
# 可以使用show collation查看字符集校验规则
```

- 注：
	- utf8_general_ci不区分大小写
	- utf8_bin区分大小写

---  

#### 查看数据库

```mysql
show databases;
```

#### 查看创建数据库

```mysql
show create database db_name;
```

#### 修改数据库

```mysql
alter database db_name [alter_spacification [,alter_spacification] ...]
```

- 案例：将数据库的字符编码改为gbk

```mysql
alter database db_name charset=gbk;
```

#### 删除数据库

```mysql 
drop database [if exists] db_name;
```

- 注意：
	- 删除之后，对应的数据库文件夹被删除，级联删除，里面的数据表也会被删除

#### 数据库备份

```mysql
mysqldump -P 3306 -u root -p -B db_name > 数据库备份存储的文件路径
```

> 所谓的备份，本质上是将历史上对mysql指定的数据库的所有历史操作都做备份
> mysql怎么记录呢？
>> binlog, 全量记录对指定数据库的所有操作

- 案例：

```mysql
mysqldump -P 3306 -u root -p -B mytest > \home\user\mytest.sql
```

#### 数据库还原

```mysql
[mysql]> source ./mytest.sql
``` 

- 注意：
	- 如果想要备份数据表

```mysql
mysqldump -u root -p db_name table_name1 tabale_name2 > \home\user\mytest.sql
```

- 如果没有带上-B参数，在恢复的时候，需要先创建空数据库，然后使用数据库，再使用source来还原

#### 查看链接情况

```mysql
show processlist
```

### 表操作

#### 创建表

```mysql
create table table_name(
	field datatype,
	field datatype,
	...
)character set 字符集 collate 校验规则 engine 存储引擎;
```

- 说明
	- field表示列名
	- datatype表示列的类型
	- character set 字符集，如果没有指定的字符集，则以所在数据库的字符集为准
	- collate 校验规则，如果没有指定的校验规则，则以所在的数据库的校验规则为准

- 案例：

```mysql
create table users(
	id int,
	name varchar(20) comment '用户名',
	passwd char(32) comment '密码是32位的md5值',
	birthday date comment '生日'
)character set utf8 engine MyISAM;
```

- 说明
	- comment是对于列的注释
	- 不同的存储引擎，创建表的文件不一样
	- users表存储引擎是MyISAM,在数据目中有三个不同的文件，分别是：
		- users.frm：表结构
		- users.MYD：表数据
		- users.MYI：表索引


#### 查看表

```mysql
desc table_name;
show create table table_name;
```

![[Pasted image 20220703155328.png]]  

- 说明：
	- Field：每一列的列属性
	- Type：每一列的类型
	- Null：是否允许为空，属于约束的一种
	- Key：索引类型
	- Default：默认缺省值
	- Extra：扩充

#### 修改表

```mysql
alter table table_name add (column datatype [default expr] [, column datatype]...);
alter table table_name modify (column datatype [default expr] [, column datatype]...);
alter table table_name drop (column);
alter table table_name rename new_name; #修改表名
alter table table_name change column_name 
new_column
```

- 建议：
	- 在构建表结构的时候就把所需要的属性建立完毕，尽量减少使用alter
	- after：指定添加列位置，在什么之后

#### 删除表

```mysql
drop table table_name;
```


### 数据类型

| 分类 | 数据类型 | 说明 | 
| --- | --- | --- | 
| --- | bit(M) | 位类型。M指定位数，默认为1,范围1-64 |  
| --- | tinyint(unsigned) | 带符号的范围-128～127,无符号范围0～255 | 
| --- | bool | 使用0和1表示真和假 | 
| 数值 | samllint(unsigned) | 带符号是-2^15到2^15-1,无符号是2^16-1 |
|  | int(unsigned) | 带符号是-2^31到2^31-1,无符号是2^32-1 | 
| 类型 | bigint(unsigned) | 带符号是-2^63到2^63-1,无符号是2^64-1 |
| --- | float[(M, D)] (unsigned) | M指定显示长度，d指定小数位数，占用4字节 |
| --- | double[(M, D)] (unsigned) | 表示比float精度更大的数，占用8字节 |
| --- | decimal(M, D) (unsigned) | 定点数M指定长度，D表示小数点的位数 |
| --- | char(size) | 固定长度字符串，最大255 | 
| 文本 | varchar(size) | 可变长度字符串，最大长度65535 | 
| 二进制类型 | blob | 二进制数据 | 
| --- | text | 大文本，不支持全文索引，不支持默认值 |
| 日期类型 | date/datetime/timestamp | 日期类型(yyyy-mm-dd)(yyyy-mm-dd hh:mm:ss) timestamp时间戳 | 
| String | enum类型 | enum是一个字符串对象，其值来自表创建时在列规定中显示枚举的一个常量 | 
| 类型 | set类型 | set是一个字符串对象，可以有零个或多个值，其值来自于表创建时规定允许的一列值。指定包括多个set成员的set列值时各成员之间用逗号间隔开。因此，set成员本身不能包含逗号 |

> MySQL对于数据具有更严格的 规则，叫做约束。
> MySQL数据类型本身，就是一种约束

- 如何选定char和varchar
	- 如果数据长度都一样，就是用定长(char)，比如：身份证，手机号，md5
	- 如果数据长度不一致，就是用变长(varchar)，比如：名字，地址，**但是要保证最长的一个能存进去**
	- 定长的磁盘空间比较浪费，**但是效率高**
	- 变长的磁盘空间比较节约，**但是效率低**
	- 定长的定义是：直接开辟号好对应的空间
	- 变长的定义是：在不超过自定义返回的情况下，动态开辟

- enum和set
	- 如果你限定了enum的范围(**只能多选一，并且插入的字段必须是enum所设置的**)
	- 如果你限定了set的范围(**能多选多，并且插入的字段必须是set所设置的**)
	- 在向enum中插入的时候，可以使用类似数组下标的方式(1, 2, ...)，**enum的访问从1开始计数** 
	- 当我们使用数字的方案，插入set中的元素的时候，不是数组下标，而可以看作比特位，比特位的内容(0 or 1)，代表的是**是/否**。

####  集合查询

- find_in_set函数：

> find_in_set（sub, sr_list)， 如果sub在str_list中，则返回下标。如果不在，返回0,str_list用逗号分割的字符串

```mysql
select find_in_set('a', 'a, b ,c');
1

select find_in_set('d', 'a, b, c');
0
```

### 约束

> 约束：本质上是MySQL通过限制用户操作的方式，来达到维护数据本身的权限，完整性的一套方案
> 为什么要约束：本质上MySQL是一套数据存储解决方案，除了解决基本的数据存储功能之外，还要保证数据尽可能的安全，减少用户的误操作可能性

#### 表的约束

##### 空属性

- 两个值：null(默认的) 和not null(不为空)
- 数据库默认字段基本都是字段为空，但是实际开发时，尽可能保证字段不为空，因为数据为空没办法参与运算

- 案例：

> 创建一个班级表，包含班级名字和班级所在教室
>> 如果班级没有名字，你不知道你所属哪个班
>> 如果教室名字为空，就不知道在哪个教室
>
>所以，我们在设计的时候，就需要进行限制

```mysql
create table myclass(
	class_name varchar(20) not null,
	class_room varchar(20) not null
);
```

> 约束的体现，不仅仅可以体现在数据库层面，在我们进行用户业务逻辑编码的时候，我们其实也可以做到判断(约束)， 约束其实不仅仅只能出现在数据库层面上，编码层面也是可以体现的

##### 默认值

> 默认值：某一种数据会**经常性的出现某个具体的值**，可以在一开始就制定好

```mysql
create table t1(
	name varchar(20) not null,
	age tinyint unsigned default 0,
	sex char(2) default '男'
);
```

- 注意：
	- **not null和default一般不需要同时出现，因为default有默认值，不会为空**

##### 列描述

> comment,没有实际含义，专门用来描述字符，会根据创建语句保存，用来给程序员或者DBA进行了解

```mysql
create table user(
	name varchar(20) comment '姓名'
	age tinyint comment '年龄'
);
```

##### zerofill

```mysql
create table t1(
	id int(10) unsigned default null
);
```

> int(10)代表什么含义呢？
> 如果一个列属性具有了zerofill的约束，**如果宽度小于设定的宽度，自动填充0**
>> **但是注意，这只是显示的结果，在MySQL中实际存储的还是1

##### 主键

> 主键：primary key用来唯一的约束该字段里面的数据，**不能重复，不能为空**，一张表中**最多只有一个主键**

```mysql
create table user(
	id int primary key comment '学号不能为空',
	name varchar(20) not null
);
```

- 注意：
	- 设置主键之后，**默认不能为空**
	- **不要给主键设置默认值**

- 当表创建好后，想要添加主键：

```mysql
alter table table_name add primary key(column)
```

- 删除主键：

```mysql
alter table table_name drop primary key
```

- 复合主键 

> 创建表的时候，在所有字段之后，使用primary key(主键字段列表)来创建主键，如果有多个字段作为主键，可以使用复合主键

```mysql
create table user(
	id int unsigned,
	course char(10) comment '课程代码',
	score tinyint unsigned default 60 comment '成绩',
	primary key(id, course)
);
```

- 注意：
	- **复合主键必须要设置复合主键的列同时严格相同时，才会冲突**

##### 自增长

> auto_increment：当对应的字段，不给值，**会自动的被系统触发，系统会从当前字段中已经有的最大值进行自赠操作，然后得到一个新的不同的值。通常和主键搭配使用，作为逻辑主键**

- 自增长的特点
	- 任何一个字段要做自增长，**前提本身是一个索引(key一栏有值)**
	- 自增长字段**必须是整数**
	- 一张表**最多只能有一个自增长**

```mysql
create table user(
	id int unsigned primary key auto_increment
	name varchar(20)
);
```

- last_insert_id()
	- 获取到最近一次插入的id值

```mysql
select last_insert_id()
```

##### 唯一键

> 一张表中往往有很多字段需要唯一性，**数据不能重复**， 但是**一张表中只能有一个主键**
>>  唯一键就可以**解决表中有多个字段需要唯一性的约束**问题
>
>唯一键的本质：唯一键**允许为空，且可以多个为空，空字段不做唯一性比较**

```mysql
create table user(
	id char(10) unique,
	name varchar(10)
);
```

##### 外键

> 外键用于定义主表和从表之间的关系：外键约束**主要定义在从表上，主表则必须是有主键约束或unique约束**，当定义外键后，要求外键列数据**必须在主表的主键列表存在或者为null**

```mysql
foreign key (字段名) references 主表(列)
```

- 外键存在的意义
	- **建立表和表之间的关系的**
	- 外键和外键约束是不一样的

```mysql
create table if not exists classes(
	id int unsigned primary key comment '班级id的标识信息',
	name varchar(20) not null comment '班级名字'
);

create table if not exists stu(
	stu_id int unsigned primary key,  
	stu_name varchar(20) not null,  
	class_id int unsigned,  
	foreign key (class_id) references classes(id)
);
```

### 基本查询

```mysql
create table students(
	id int unsigned primary key auto_increment,
	sn int not null unique comment '学号',
	name varchar(20) not null,
	qq varchar(20)
);
```

#### 表的数据插入

```mysql
insert [into] table_name [(column [, column] ...)] values (value_list) [, (value_list)]...
```

- 案例

```mysql
# 单行插入
insert into students (sn, name, qq)  
values (123, 'Lily', 2222222);

# 多行插入
insert into students (sn, name, qq) values 
	(123, 'Lily', 2222222),
	(321, 'Ydi', 2144535),
	(4124, 'asjkdhj', 215413515);
```

##### 插入更新

> 由于主键或者唯一键的存在，导致插入失败

```mysql
insert ... on duplicate key update column = value [, column = value] ...
```

- 案例

```mysql
insert into students values (1, 123, 'Lyya', 2154121) on duplicate key update name = 'Lyya', qq = '2154121';
```

##### 插入替换

```mysql
replace into table_name [(column [, column] ...)] values (value_list) [, (value_list)]...
```

- 案例

```mysql
replace into students(sn, name) values (20001, 'Yosy');
```

#### 表的数据查询

```mysql
select 
	[distinct] {* | {column [, column] ...}}
	[from table_name]
	[where ...]
	[order by column [ASC | DESC], ...]
	limit ...
```

##### 全列查询

- 通常情况下，**不建议使用\*进行全列查询**
	- 查询的列越多，意味着需要传输的数据量越大
	- 可能会影响到索引的使用

```mysql
select * from students;
```

##### 指定列查询

```mysql
select column from table_name;
```

##### 为查询结果指定别名

```mysql
select column [as] alias_name from table_name;
```

##### 结果去重

```mysql
select distinct column from table_name;
```

##### where条件

###### 算数运算

| 运算符 | 说明 |
| --- | --- | 
| >, >=, <, <= | 大于，大于等于，小于，小于等于 |
| = | 等于，NULL不安全，例如NULL = NULL的结果是NULL |
| <=> | 等于，NULL安全，例如NULL <=> NULL的结果是TRUE(1) |
| !=, <> | 不等于 |
| between a0 and a1 | 范围匹配，[a0, a1], 如果a0 <= value M= a1，返回TRUE(1) |
| is null | 是NULL |
| is not null | 不是null |
| like | 模糊匹配，%表示任意多个(包括0个)任意字符，\_表示任意一个字符 |

###### 逻辑运算

| 运算符 | 说明 |
| --- | --- |
| and | 多个条件都必须为TRUE(1)，结果才是TRUE(1) | 
| or | 任意一个条件为TRUE(1)，结果为TRUE(1) |
| not | 条件为TRUE(1)，结果为FALSE(0) |

- **别名不能使用在where表达式中**

##### 结果排序

```mysql
# ASC 为升序(从小到大)
# DESC 为降序(从大到小)
# 默认是ASC

select ... from table_name [where ...]
	order by column [ASC | DESC], [...];
```

- 注意：
	- **没有order by子句的查询，返回的顺序是未定义的，永远不要依赖这个顺序**

#### 表的数据更新

```mysql
update table_name set column = expr [, column = expr ...] [where ...] [order by ...] [limit ...]
```

- 注意：
	- **使用update语句必须确保语句正确，否则会发生预料之外的事情**

#### 表的数据删除

```mysql
delete from table_name [where ...] [order by ...] [limit ...]
```

#### 删除表

##### 截断

```mysql
truncate [table] table_name;
```

- 注意：
	- 只能对整表使用，不能像delete一样针对部分数据操作
	- 实际上MySQL不对数据操作，所以比delete更快，但是truncate在删除数据的时候，并不经过真正的事物，**因此无法回滚**
	- **会重置AUTO_INCREMENT**，也就是说，经过delete删除的表，自增长不会被重置，truncate会重置自增长

