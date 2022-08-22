# OpenCv    
  
---    

## 模块    
- core模块实现了最核心的数据结构以及基本运算，如绘图函数、数组操作相关函数等  
- highgui模块实现了视频与图像的读取、显示、存储等接口  
- imgproc模块实现了图像处理的基本方法，包括图像滤波、图像的几何变换、平滑、阀值分割等  
  
- features2d模块用于提取图像特征以及特征匹配，nonfree模块实现了一些专利算法，如sift特征  
- objdetect模块实现了一些莫标检测的功能，经典的基于Haar、LBP特征的人脸检测，基于HOG的行人的等  
- stitching模块实现了图像凭借功能  
- FLANN模块包含口语爱苏近似最近邻搜索FLANN和聚类Clustering算法  
- ml模块机器学习模块(SVM,决策树，Boosting等等)  
- photo模块包含图像修复和图像去嘈两部分  
- video模块针对视频处理，如背景分割、前景检测、对象跟踪等  
- calib3d模块即Calibration(校准)3D,这个模块主要是相机校准和三维重建的内容  
- G-API模块包含超高效的图像处理pipeline引擎  


## OpenCV API

### 图像视频的加载

#### 创建窗口和显示窗口

- nameWindow() 
- imshow()显示窗口
- destroyAllwindows()销毁窗口
- resizeWindow()改变窗口大小
- waitKey()

```python
import cv2 as cv 

# cv.namedWindow(window_name, cv.WINDOW_AUTOSIZE)
# WINDOW_NORMAL可以让窗口大小变得可以调节

cv.namedWINDOW('new', cv.WINDOW_NORMAL)

# cv.resizeWindow(window_name, width, height)
cv.resizeWindow('new', 800, 600)

# cv.imshow(window_name, mat)
cv.imshow('new', 0)

# cv.waitKey()
key = cv.waitKey()
if key == 'q': # key & 0xFF == 'q' ASCII是八位的，因此取出后八位来比较
	cv.destroyAllWindows()
# cv.destroyAllWindows()
```

- 注意：
	- **cv.WINDOW_AUTOSIZE不允许使用cv.resizeWindow修改窗口大小**
	- **当窗口退出时，会卡顿，使用cv.waitKey来防止卡顿**
	- cv.waitKey(delay)
		- 设置为0,就是等待键盘按键，设置为其他整数，就是等待时间

#### 加载显示图片

- imread(path, flag)

```python
import cv2 as cv
import matplotlib.pyplot as plt

img = cv.imread('path')
# plt.imshow(img)
cv.imshow('pircture', img)

```

- 注意：
	- **OpenCV读取图片的通道不是RBG,而是BGR通道，因此，如果使用plt.imshow,则颜色与真实的有差异， 因此使用cv.imshow**

#### 保存图片

- imwrite(filename, img)

```python
cv.nameWindow('img', cv.WINDOW_NORMAL)
cv.resizeWindow('img', 320, 240)

img = cv.imread('path')

# 利用while优化退出

while True:
	cv.imshow('img', img)
	key = cv.waitKey(0)
	if key & 0xFF == 'q':
		break
	elif key & 0xFF == 's':
		cv.imwrite('filename', img)
	else :
		print(key)
```

#### 视频采集

> 视频其实也是图片，只不过是一组连续不断的图片快速切换。视频的一帧，就是一幅图片

- VideoCapture
	- 可以捕获图片或者摄像头，用数字来代表不同的设备，比如0,1
	- **如果打开摄像头失败，不会报错**

```python
# 打开视频文件
vc = cv.VideoCapture('path')

# 打开摄像头
vc = cv.VideoCapture(0)
```

- read
	- 获取到对象的每一帧数据
	- **会返回bool以及这一帧的数据,True就是读到了数据，Flase就是没有读到**
	- 此处的True,可以用**isOpened**来代替

```python
while vc.isOpened() # True:
	ret, frame = vc.read()

	# 根据ret做判断
	if not ret:
		break
	# 显示数据
	cv.imshow(window_name, frame)

	key = cv.waitKey(0)
	if key & 0xFF == ord('q'):
		break
cap.release()
cv.destroyAllWindows()
```

- 注意：
	- **当你调用VideoCapture的时候，会占用系统资源，因此，需要在最后使用release释放掉占用的资源**
	- **同理，开启窗口namedWindow也会占用资源，因此也要destroyAllWindows**
	- **此时的waitKey不能设置为0,不然只能获取到第一帧的数据**

#### 视频录制

- VideoWriter
	- 参数一为输出文件，参数二为多媒体文件格式(VideoWriter_fourcc)，参数三为帧率，参数四为分辨率
- wirte
	- 编码并写入缓存
- release
	- 缓存内容写入磁盘，且释放资源

```python
cap = cv2.VideoCapture(0)
fourcc = cv.VideoWriter_fourcc(*'mp4v')
# *'mp4v'解包操作，等同于'm' 'p' '4' 'v'

vm = cv.VideoWriter('output.mp4', fourcc, 20, (640, 480))

while cap.isOpende():
	ret, frame = cap.imread()
	if not ret:
		break
	vm.write(frame)
	cv.imshow('frame', frame)
	if cv.waitKay(1) == ord('q'):
		break;
cap.release()

vm.release()
cv.destroyAllWindows()
```

- 注意：
	- **对于VideoWirter的分辨率，一般就用(640, 480)**
	- write操作实际上**并没有把数据写入硬盘，而是写入缓冲区，release操作才是真正的写入到磁盘上**
	- 视频格式
		- mp4v就是MP4
		- XVID就是AVI

#### 控制鼠标

- setMouseCallBack(winname, callback, userdata)
	- winname就是窗口的名字
	- callback是回调函数
	- userdata是回调函数的参数
- callback(event, x, y, flags, userdata)
	- event是鼠标的事件
	- x,y是鼠标的坐标点
	- flags主要用于组合键
	- userdata就是setMouseCallBack

##### event

| 鼠标事件 | 代码 | 含义 |
| --- | --- | --- | 
| EVENT_MOUSEMOVE | 0 | 鼠标移动 |
| EVENT_LBUTTONDOWN | 1 | 按下鼠标左键 |
| EVENT_RBUTTONDOWN | 2 | 按下鼠标右键 | 
| EVENT_MBUTTONDOWN | 3 | 按下鼠标中键 |
| EVENT_LBUTTONUP | 4 | 左键释放 | 
| EVENT_RBUTTONUP | 5 | 右键释放 | 
| EVENT_MBUTTONUP | 6 | 中键释放 | 
| EVENT_LBUTTONDBLCLK | 7 | 左键双击 | 
| EVENT_RBUTTONDBLCLK | 8 | 右键双击 | 
| EVENT_MBUTTONDBLCLK | 9 | 中键双击 | 
| EVENT_MOUSEWHEEL | 10 | 鼠标滚轮上下滚动 | 
| EVNETN_MOUSEHWHEEL | 11 | 鼠标左右滚动 | 

##### flags

| flags | 代码 | 含义 | 
| --- | --- | --- | 
| EVENT_FLAG_LBUTTON | 1 | 按下左键 | 
| EVENT_FLAG_RBUTTON | 2 | 按下右键 | 
| EVENT_FLAG_MBUTTON | 4 | 按下中键 | 
| EVENT_FLAG_CRTLKEY | 8 | 按下ctrl | 
| EVENT_FLAG_SHIFTKEY | 16 | 按下shift | 
| EVENT_FLAG_ALTKEY | 32 | 按下alt | 

```python
def mouse_callback(event, x, y, flags, userdata):
	print(event, x, y, flags, userdata)

cv.namedWindow('mouse', cv.WINDOW_NORMAL)
cv.resizeWindow('mouse', 640, 360)

# 设置鼠标回调函数
cv.setMouseCallBack('mouse', mouse_callback, '123')

img = np.zeros((360, 640, 3), np.uint8)

while True:
	cv.imshow('mouse', img)
	key = cv.waitKey(1)
	if key & 0xFF == ord('q'):
		break

cv.destroyAllWindow()
```

- 注意：
	- numpy的是行和列，而resizeWindow是宽和高，**是刚好相反的，并且，np还要指出是三维(因为BGR三个通道)**，**并且注意后面的np.uint8**
	- **使用回调函数，可以在内部定义鼠标事件所代表的意义**

#### Trackbar控件

- createTrackbar(trackbarname, winname, value, count, onChange)
	- value为trackbar的默认值
	- count为bar的最大值，最小为0
	- onChange是一个回调函数，**需要自己定义**
- getTrackbarPos(trackbarname, winname)
	- 获取TrackBar当前值

```python
cv.namedWindow('trackbar', cv.WINDOW_NORMAL)
cv.resizeWindow('trackbar', 640, 480)

def callback(value):
	print(value)

cv.createTrackbar('R', 'trackbar', 0, 255, callback)
cv.createTrackbar('G', 'trackbar', 0, 255, callback)
cv.createTrackbar('B', 'trackbar', 0, 255, callback)

img = np.zeros((480, 640, 3), np.uint8)

while True:
	# 获取trackbar的当前值
	r = getTrackbarPos('R', 'trackbar')
	b = getTrackbarPos('B', 'trackbar')
	g = getTrackbarPos('G', 'trackbar')

	# 改变背景图颜色
	img[:] = [b, g, r]
	cv.imshow('trackbar', img)

	key = cv.waitKey(0)
	if key == ord('q'):
		break

cv.destroyAllWindows()
```

- 注意：
	- **当waitKey的参数设置为0的时候，不会显示颜色！！！也就是说，不会跟随trackbar的改变而改变**

--- 

### OpenCV的基础知识和绘制图形

#### 色彩空间

##### RBG和BGR

> 最常见的色彩空间就是RBG,人眼也是基于RBG的色彩空间去区分的

- 但是，**OpenCV默认使用的是BGR, BGR和RBG区别在于图片在色彩通道上的排列顺序不同**

##### HSV

- OpenCV**用的最多的色彩空间是HSV**
	- H：Hue,色相，即色彩。用角度度量，**取值范围为0～360, 从红色开始逆时针计算，红色为0, 绿色为120, 蓝色为240**
	- S：Saturation，饱和度，表示**颜色接近光谱色的程度**。一种颜色也可以看成是光谱色和白色混合的结果。**光谱色的占比越大，颜色就越接近光谱色，饱和度也就越高**。饱和度越高，颜色就深而艳。通常取值0%～100%，值越大，越饱和
	- V：Value,明度。**明度表示颜色明亮的程度**。对于光源色，明度值与发光体的光亮度有关;对于物体色，此值和物体的透射比或反射比有关。**通常取值范围0%(黑)～100%(白)**。

![[Pasted image 20220712175810.png]]

##### HSL

> HSL和HSV相差不多

- H：Hue,色相
- S：Stauration,饱和度
- L：Lightness,亮度

![[Pasted image 20220712180238.png]]

- **HSL在顶部是纯白的，不管是什么颜色**

- HSV和HSL的区别
	- 他们两个在字面以上是都是一样的
	- 但是，在原理和表现上，他们的H(色相)完全一致，S(饱和度)不一样，L和V(B)也不一样
		- HSV(B)中的S**控制纯色中混入白色的量**，值越大，**白色越少**，颜色越纯
		- HSV(B)中的V(B)**控制纯色中混入黑色的量**，值越大，黑色**越少**，亮度越高
		- HSL中的**S和黑白没有关系**，饱和度**不控制颜色中混入黑白的多寡**
		- HSL中的L**控制纯色中混入的黑白两种颜色**

##### YUV

> YUV是一种**颜色编码方法**，常使用在各个视频处理组件上，YUV在对照片或视频编码时，**允许降低色度的带宽**

- Y, 表示**明亮度**(Luminance或者Luma)，**也就是灰度值**
- U和V表示的是色度(Chrominance或者Chroma)，**作用是描述影像色彩及饱和度，用于指定像素的颜色**

> YUV的最大优点在于**只需要占用极少的带宽**

| 比值 | 说明 | 
| --- | --- | 
| 4：4：4 | 完全取样 |
| 4：2：2 | 2：1的水平取样，垂直完全采样 |
| 4：2：0 | 2：1的水平采样，垂直2：1采样 |
| 4：1：1 | 4：1的水平采样，垂直完全采样 |

- 4：2：0的比例是最经常使用的

##### 色彩空间的转换

- cvtColor(img, colorspace)

```python
def callback(value):
	pass

cv.namedWindow('color', cv.WINDOW_NORMAL)
cv.resizeWindow('color', 640, 480)

img = cv.imread('path')

# 常见的色彩空间转换
colorspace = [cv.COLOR_BGR2RGBA, cv.COLOR_BGR2GRAY, cv.COLOR_BGR2HSV, cv.COLOR_BGR2YUV]

cv.createTrackbar('curcolor', 'color', 0, 4, callback)

while True:
	index = cv.getTrackbarPos('curcolor', 'color')

	# 色彩空间转换
	cvt_img = cv.cvtColor(img, colorspace[index])
	cv.imshow('color', cvt_img)
	key = cv.waitKey(10)
	if key == ord('q'):
		break

cv.destroyAllWindows()
```

#### mat

> MAT是OpenCV在C++语言中用来表示图像数据的一种数据结构，在python中转化为numpy中的ndarray

##### mat属性

| 字段 | 说明 | 字段 | 说明 |
| --- | --- | --- | --- | 
| dims | 维度 | channels | 通道数RGB是3 | 
| rows | 行数 | size | 矩阵大小 |
| cols | 列数 | type | dep+dt+chs CV_8UC3 | 
| depth | 像素的深度 | data | 存放数据 |

##### mat的深浅拷贝

- view
	- 浅拷贝
- copy
	- 深拷贝

```python
img = cv.imread('path')

# 浅拷贝
img1 = img.view()

# 深拷贝
img2 = img.copy()
```

#### 通道 的分离和合并

- split(mat)
	- 分割图像的通道
- merge((ch1, ch2, ch3))
	- 融合多个通道

```python
img = np.zeros((480, 640, 3), np.uint8)

# 分割通道
b, g, r = cv.split(img)

# 修改
b[10:100, 10:100] = 255
g[10:100, 10:100] = 255

# 合并通道
img2 = cv.merge((b, g, r))
cv.imshow('img', np.hstack((b, g)))
cv.imshow('img', np.hstack((img, img2)))
```

- 注意：
	- **通道一定是BGR**

#### 绘制图形

- line(img, pt1, pt2, color, thickness, lineType, shift) 画直线
	- img：在哪个图像上画线
	- pt1， pt2：开始点，结束点，指定线的开始与结束位置
	- color：颜色
	- thickness：线宽
	- lineType：线形，线形为-1, 4, 8, 16,**默认为8**，实际上就是锯齿，越高看上去越平滑
	- shift：坐标缩放比例
- rectangle(img, pt1, pt2, color, thickness, lineType, shift) 画矩形
- cicle(img, center, radius, color, [, thickness[, lineType[, shift]]])
	- 画圆，括号内表示可选参数
- ellipse(img, 中心点，长宽的一半，角度，从哪个角度开始，从哪个角度结束)
	- 画椭圆

```python
# 创建纯黑的背景
img = np.zeros((480, 640, 3), np.uint8)

cv.line(img, (10, 20), (300, 400), (0, 0, 255), 5, 4)
cv.line(img, (80, 1000), (380, 480), (0, 0, 255), 5, 16)

cv.rectangle(img, (10, 20), (300, 400), (0, 255, 0), 5)

cv.circle(img, (50, 60), 10, (255, 0, 0))

cv.ellipse(img, (320, 240), (100, 50), 0, 0, 360, [0, 0, 255])
```

- 注意：
	- 给定的点，**需要用元组**
	- 给定的颜色，**需要用元组或者列表**
	- lineType越高，看上去的图形就越平滑

#### 绘制多边形

- polylines(img, pts, isClosed, color[, thickness[, lineType[, shift]]])
	- 画多边形
- fillPoly
	- 填充多边形，参数同上，**只少了isClosed,因为一定闭合**

```python
img = np.zeros((480, 640, 3), np.uint8)

pts = np.array([(250, 100), (150, 100), 450, 100], np.int32)

cv.polylines(img, [pts], True, (0, 0, 255), 5)

cv.fillPoly(img, [pts], (0, 0, 255), 5)
```

- 注意：
	- 多边形必须是**np.int32位及以上的**
	- **pts必须是三维**

#### 绘制文本

- putText(img, text, org, fontFace, fontScale, color[, thickness[, lineType[, bottomLeftOrigin]]])
	- 绘制文本
		- text：要绘制的文本
		- org：文本在图片的左下角坐标
		- fontFace：字体
		- fontScale：字体大小

```python
cv.putText(img, "Hello OpenCV", (200, 200), cv.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255))
```

- 注意：
	- **OpenCV没有中文字体，因此写入中文文本会乱码**
	- 但是可以使用Pillow包来解决乱码

```python
from PIL import ImageFont, ImageDraw, Image

img = np.fill((200, 200, 3), fill_value = 255, dtype = np.uint8)

# 导入字体文件
font = ImageFont.truetype('font_path', fontsize)

# 创建pillow图片
img_pil = Iamge.fromarray(img)

draw = ImageDraw.Draw(img_pil)

# 利用draw去绘制中文
draw.text((10, 150), '你好', font = font, fill = (0, 255, 0, 0))

# 重新变回ndarray
img = np.array(img_pil)

cv.imshow('img', img)
```

--- 

### 图像的算术与位运算

#### 图像的算术运算

##### 图像的加法运算

- add
	- opencv使用add来进行执行图像的加法运算
	- **值得注意的是，图片是矩阵，因此两个执行add操作的图片的shape一定要一样，通道数也要相同**
	- add的规则就是两个图的对应位置的元素相加，**如果超过255,那么规定为255**
	- 图片也能和单个数字进行运算，每个数字和100进行加法运算，**超出255的数字，会被截断，相当于%255**

```python
img1 = cv.imread('path1')
img2 = cv.imread('path2')

printf(img1.shape)
printf(img2.shape)

# 如果两张图片shape，不一致，则需要处理，假如img1(640, 480, 3), img2(480, 300, 3)
# 那么使img1变小
new_img1 = img1[0:480, 0:300]

new_img = cv.add(new_img1, img2)
```

##### 图像的减法运算

- substract
	- 同上add一样
	- **但，如果相减位置小于0, 则规定为0**

```python
img1 = cv.imread('path1')
img2 = cv.imread('path2')

printf(img1.shape)
printf(img2.shape)

# 如果两张图片shape，不一致，则需要处理，假如img1(640, 480, 3), img2(480, 300, 3)
# 那么使img1变小
new_img1 = img1[0:480, 0:300]

new_img = cv.substract(new_img1, img2)
```

##### 图像的乘法运算

- multiply
	- 同上add一致

```python
img1 = cv.imread('path1')
img2 = cv.imread('path2')

printf(img1.shape)
printf(img2.shape)

# 如果两张图片shape，不一致，则需要处理，假如img1(640, 480, 3), img2(480, 300, 3)
# 那么使img1变小
new_img1 = img1[0:480, 0:300]

new_img = cv.multiply(new_img1, img2)
```

##### 图像的除法运算

- divide
	- 同上substract一致

```python
img1 = cv.imread('path1')
img2 = cv.imread('path2')

printf(img1.shape)
printf(img2.shape)

# 如果两张图片shape，不一致，则需要处理，假如img1(640, 480, 3), img2(480, 300, 3)
# 那么使img1变小
new_img1 = img1[0:480, 0:300]

new_img = cv.divide(new_img1, img2)
```

#### 图像的融合

> 不是简单的加法，而是相当于对图片做线性运算：new_img = img1 * w1 + img2 * w2 + bias

- addWeighted(src1, alpha, src2, beta, gamma)
	- alpha：是第一个权重参数
	- beta：是第二个权重参数
	- gamma：是偏置
	- **但是，图片的运算始终是要求图片shape和维数一致的**

```python
img1 = cv.imread('path1')
img2 = cv.imread('path2')

printf(img1.shape)
printf(img2.shape)

# 如果两张图片shape，不一致，则需要处理，假如img1(640, 480, 3), img2(480, 300, 3)
# 那么使img1变小
new_img1 = img1[0:480, 0:300]

res = cv.addWeighted(new_img1, 0.4, img2, 0.6, 0)
```

#### 逻辑运算

> 对应位置进行与或非，异或等逻辑运算

- 注意：
	- opencv中的非，**0反过来是255,255反过来是0**
	- bitwise_not
		- 非操作
	- bitwise_and
		- 与操作
	- bitwise_or
		- 或操作
	- bitwise_xor
		- 异或操作

```python
img1 = cv.imread('path1')
img2 = cv.imread('path2')

printf(img1.shape)
printf(img2.shape)

# 如果两张图片shape，不一致，则需要处理，假如img1(640, 480, 3), img2(480, 300, 3)
# 那么使img1变小
new_img1 = img1[0:480, 0:300]

ref1 = cv.bitwise_not(nwe_img1, img2)
ref2 = cv.bitwise_and(nwe_img1, img2)
ref3 = cv.bitwise_ro(nwe_img1, img2)
ref4 = cv.bitwise_xor(nwe_img1, img2)
```

### 图形的基本变换

#### 图像的放大与缩小

- resize(src, dsize[, dst[, fx[, fy[, interpolation]]]])
	- src：需要缩放的图片
	- dsize：缩放之后的图片大小，**元组和列表表示均可**
	- dst：可选参数，缩放之后的输出图片
	- fx, fy：x轴和y轴的缩放比，即宽度与高度的缩放比
	- imterpolation：插值算法：
		- INTER_NEAREST,邻近插值，速度快，效果差
		- INTER_LINEAR.双线性插值，使用原图的4个点进行插值，**默认**
		- INTER_CUBIC,三次插值，原图中的16个点
		- INTER_AREA,区域插值，效果最好，计算时间最长

```python
img = cv.imread('path')

new_img = cv.resize(img, (640, 480))
```

- 注意：
	- **opencv的图片大小是先宽后高**

#### 图像的翻转

- flip(src, flipCode[, dst])
	- flipCode：控制反转。**code=0, 表示上下翻转，code>0,表示左右翻转,code<0,表示上下+左右翻转**

```python
cv.flipCode(img, filpCode = 0)
```

#### 图像的旋转

- rotate(img, rotateCode)
	- ROTATE_90_CLOCKWISE 90度顺时针
	- ROTATE_180 180度
	- ROTATE_90_COUNTERCLOCKWISE 90度逆时针

```python
cv.rotate(img, cv.ROTATE_90_CLOCKWISE)
```

#### 仿射变换

> 仿射变换是图像转换，缩放，平移的总称。具体的做法是通过一个矩阵和原图片坐标进行计算，得到新的坐标，完成变换，**所以关键在于矩阵**

##### 图像平移

- warpAffine(src, M, dsize, flags, mode, value)
	- M：变换矩阵
	- dsize：输出图片大小
	- flag：与resize的插值算法一样
	- mode：边界外推法标志
	- value：填充边界值

- 平移矩阵
	- 矩阵中的每个像素由(x, y)组成，(x, y)表示这个像素的坐标。假设沿x轴平移$t_x$，沿y轴平移$t_y$，最后得到的坐标为$(\hat{x}, \hat{y}) = (x + t_x, y + t_y)$,用矩阵表示：

$$
\begin{bmatrix}
\hat x \\\
\hat y \\\
1
\end{bmatrix} = 
\begin{bmatrix}
1 & 0 & t_x \\\
0 & 1 & t_y \\\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x \\\
y \\\
1
\end{bmatrix}
$$

```python
img = cv.imread('path')

M = np.float([[1, 0, 200], [0, 1, 0]])
h, w, ch = img.shape

cv.warpAffine(img, M, dsize=(w, h))
```

- 注意：
	- **M变换矩阵要求最低是float32位的**
	- **M变换矩阵实际上就是二维，\[\[1, 0, tx\], \[0, 1, ty\]\]特定格式**

##### 获取变换矩阵

- getRotationMatrix2D(center, angle, scale)
	- center：中心点，以图片的哪个点作为旋转时的中心点
	- angle：角度，旋转的角度，**按照逆时针旋转**
	- scale：缩放比例，想把图片进行什么样的缩放

```python
img = cv.imread('path')

h, w, ch = img.shape

M = cv.getRotationMatrix2D((w/2, h/2), 15, 1.0)

new_img = warpAffine(img, M, dsize=(w, h))
```

- getAffineTransform(src[], dst[])
	- 通过三点可以确定变换后的位置，相当于解方程。三个点对应三个方程，能解出偏置的参数和旋转的角度
	- src：原目标的三个点
	- dst：变换后的三个点

```python
img = cv.imread('path')

h, w, ch = img.shape

src = np.float32([[200, 100], [300, 100], [200, 300]])
dst = np.float32([[100, 150], [360, 200], [280, 120]])

M = cv.getAffineTransform(src, dst)

new_img = warpAffine(img, M, dsize=(w, h))
```

##### 透视变换

> 透视变换就是将一种坐标系变成另一种坐标系，简单来说就是可以把“斜”变“正”

- warpPerspective(img, M, dsize, ...)
	- **透视变换的变换矩阵一定是3\*3的矩阵**
	- getPerspectiveTransform(src, dst)
		- 需要四个点，**即图片的四个角**

```python
img = cv.imread('path')

src = np.float32([[100, 1100], [2100, 1100], [100, 4000], [2100, 3900]])
dst = np.float32([[0, 0], [2300, 0], [0, 3000], [2300, 3000]])

M = cv.getPerspectiveTraqnsform(src, dst)

cv.warpPerspective(img, M, (2300, 3000))
```

- 注意：
	- 四个角的顺序分别是**上左、上右、下左、下右**

### 滤波器

#### 卷积

##### 什么是图片卷积

> 图片卷积就是**卷积核在图像上按行滑动遍历像素时不断的相乘求和的过程**

![[Pasted image 20220714125732.png]]

- **卷积不一定是2\*2的**
- 滑动的矩形被称为卷积核，得到的最后结果被成为卷积特征

##### 步长

> 步长就是卷积核在图像上移动的步幅。**为了充分扫描图片，一般设置步长为1**

##### padding

> 我们发现，图片经过卷积之后会影响图片的大小，因此我们需要在图片的周围填充0,来保证图片的大小不变。**padding就是填充0的圈数**

- 计算padding：
	- 输入体积大小$H_!*W_!*D_!$
	- 四个超参数
		- Filter(卷积核)数量K
		- Filter大小F
		- 步长S
		- 零填充大小P
	- 输出体积大小$H_2*W_2*D_2$
		- $H_2 = (H_1 - F + 2P)/S + 1$
		- $W_2 = (W_1 - F + 2P)/S + 1$
		- $D_2 = K$

- 如果要保持卷积之后的大小不变，就有：$(N + 2P - F + 1) = N$，从而可以得出$P = \frac{F - 1}{2}$

##### 卷积核的大小

> 在图片卷积中，**卷积核一般都是奇数**

- 根据上面的padding计算，可以发现如果要保持图像大小不变，采用偶数会出现小数的情况
- 奇数维度的过滤器有中心，便于指出过滤器的位置，即OpenCv卷积中的锚点

##### 卷积api

- filter2D(src, ddepth, kernel, dst[, anchor[, delta[, borderType]]])
	- ddepth：卷积之后的图片的位深，**即卷积之后图片的数据类型**， 一般设置为-1,表示和原图类型一样
	- kernel：卷积核大小，用**元组或者ndarray**表示，要求**数据类型必须是float型**
	- anchor：锚点，**即卷积核的中心点**，是可选参数，默认是(-1, 1)
	- delta：可选参数，表示卷积之后额外加的一个值，相当于线性方程中的偏差，默认是0
	- borderType：边界类型，一般不设

```python
img = cv.imread('path')

kernel = np.ones((5, 5), np.float32) / 25

cv.filter2D(img, -1, kernel)
```

#### 方盒滤波和均值滤波

- boxFilter(src, ddepth, ksize[, dst[, anchor[, normalize[, borderType]]]])
	- 方盒滤波

- 方盒滤波的卷积核：

$$ K = a
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 & 1\\\
1 & 1 & 1 & \cdots & 1 & 1\\\
\vdots & \vdots & \vdots & \cdots & \vdots & \vdots \\\
1 & 1 & 1 & \cdots & 1 & 1
\end{bmatrix}
$$
- 参数
	- normalize = True时，$a = 1 / (W * H)$
	- normalize = False时， a = 1
	- 一般情况下我们都使用normalize = True的情况，**此时的方盒滤波等价于均值滤波**

- blur(src, ksize[, dst[, anchor[, borderType]]])
	- 均值滤波
	- **均值滤波没有位深这个参数**

```python
img = imread('path')

new_img = cv.boxFilter(img, -1, (5, 5), normalize = True)

new_img = cv.blur(img, (5, 5))

```

#### 高斯滤波

> 了解高斯滤波之前，先要了解高斯函数，高斯函数符合正太分布(也就是高斯分布)的数据的概率密集函数

![[Pasted image 20220714152044.png]]

- 一维高斯分布：

$$
	G(x) = \frac{1}{\sqrt{2\pi\sigma}}e^{-\frac{x^2}{2\sigma^2}}
$$

![[Pasted image 20220714154337.png]]

- 二维高斯分布

$$
G(x, y) = \frac{1}{2\pi\sigma^2}e^{-\frac{x^2 + y^2}{2\sigma^2}}
$$

![[Pasted image 20220714154407.png]]

> 高斯滤波是**使用符合高斯分布的卷积核对图片进行卷积操作，所以高斯滤波的重点就是计算符合高斯分布的卷积核，即高斯模板**

![[Pasted image 20220714160057.png]]

- **可以观察到，越靠近中心，数值越大，越边缘的数值越小，符合高斯分布的特点**

- 如何计算：
	- 取定中间点坐标(0, 0)，然后取得最近的八个点坐标，设定$\sigma=1.5$，则模糊半径为1就通过$G(x, y) = \frac{1}{2\pi\sigma^2}e^{-\frac{x^2 + y^2}{2\sigma^2}}$算得
	- 由于算得之后全是小数，因此要进行**归一化**
	- 每一个值都除以最左上角的数值，然后向下取整就得到最后的**高斯模板**

- GaussianBlur(src, ksize, sigmaX[, dst[, sigmaY[, borderType]]])
	- kernel：高斯核的大小
	- sigmaX：X轴的标准差
	- sigmaY：Y轴的标准差，**默认为0,此时sigmaX = sigmaY**
	- **如果没有指定sigma值，会分别从ksize的宽度按和高度中计算sigma**
- 选择不同的sigma值会得到不同的平滑效果，**sigma越大，平滑效果越明显**
- 没有指定sigma的时候，**ksize越大，平滑效果越明显**

```python
img = cv.imread('path')

new_img = cv.GuassianBlur(img, (5, 5), sigmaX = 1)
```

- 一般来说，**高斯滤波常用于去噪**

#### 中值滤波

> 中值滤波，假设有一个数组[1 5 5 6 7 8 9 ]，取其中间值(即中位数)作为卷积之后的结果值即可，**中值滤波对胡椒噪声(椒盐噪声)效果明显**

- medianBlur(img, ksize)
	- **注意，此时的ksize就是一个数字，不要写成元组**

```python
cv.medianBlur(img, 5)
```

![[Pasted image 20220714164243.png]]

#### 双边滤波

> 双边滤波**对于图像的边缘信息能够更好的保存，其原理为一个与空间距离相关的高斯函数与一个灰度距离相关的高斯函数相等

- 空间距离：指的是当前点与中心点的欧式距离。空间域高斯函数数学表达式：

$$
	e^{-\frac{(x_i - x_c)^2 + (y_i - y_c)^2}{2\sigma^2}}
$$
> 其中，$(x_i, y_i)$为当前点位置，$(x_c, y_c)$为中心点位置，sigma为空间域标准差

- 灰度距离：指的是当前点灰度与中心点的差的绝对值，值域高斯函数其数学表达式：

$$
	e^{-\frac{(gray(x_i, y_i) - gray(x_c, y_c))}{2\sigma^2}}
$$

> 其中，$gray(x_i, y_i)$为当前灰度值，$gray(x_c， y_c)$为中心点灰度值，sigma为值域标准差

> 双边滤波本质上就是高斯滤波，但是**双边滤波既利用了位置信息，又利用了像素信息来定义滤波窗口的权重，而高斯滤波只用了位置信息**
> 对于高斯滤波，仅用空间距离的权值系数核与图像卷积后，确定中心点的灰度值。**即认为离中心点越近的点，其权重系数越大**
> 双边滤波中加入对灰度信息的权重，**即在邻域内，灰度值越接近中心点灰度值的点的权重更大，灰度值相差大的点权重越小，此权重越小，则由值域高斯函数确定**
> 二者权重系数相乘，得到追中卷积模板，由于双边滤波需要每个中心点邻域的灰度信息来确定其系数，所以其速度与一般的滤波慢很多，而且计算量增长速度为核大小的平方

$$
	BF[I]_p = \frac{1}{W_p}\sum_{q \in S}G_{\sigma_s}(||p - q||) G_{\sigma_\iota}(|I_p - I_q|)I_q
$$

![[Pasted image 20220714174810.png]]

- bilateralFilter(src. d, sigmaColor, sigmaSpace[, dst[, borderType]])
	- d：相当于就是卷积核的大小(d * d )
	- sigmaColor：计算像素信息使用的sigma
	- sigmaSpace：计算空间信息使用的sigma

```python
cv.bilateralFilter(img, 7, sigmaColor = 20, sigmaSpace = 20)
```

- **双边滤波对椒盐噪声基本没有效果**

### 算子


> 边缘是像素值发生跃迁的位置，是图像的显著特征之一，在图像特征提取，对象检测，模式识别等方面都有重要的作用
  
- 比如有一幅图像，图里面有一条线，左边很亮右边很暗，就很容易识别到这根线，**也就是像素的灰度值快速变化的地方**

#### 索贝尔(sobel)算子

> sobel算子对图像求一阶导数，一阶导数越大，说明像素在该方向的变化越大，边缘信号越强
> 因为图像的灰度值都是离散的数字，因此采用离散差分算子计算图像像素点亮度值的近似梯度
> 图像是二维的，因此沿着宽度和高度两个方向

- 水平方向

$$

G_x = \begin{bmatrix}

-1 & 0 & +1 \\\

-2 & 0 & +2 \\\

-1 & 0 & +1

\end{bmatrix} * I

$$

- 垂直方向

$$

G_y = \begin{bmatrix}

-1 & -2 & -1 \\\

0 & 0 & 0 \\\

+1 & +2 & +1

\end{bmatrix} * I

$$

- 综合考虑两个方向的变化

$$

G = \sqrt{G_x^2 + G_y^2}

$$

- 但有时候为了简化，可以直接用绝对值相加代替

$$

G = |G_X| + | G_Y |

$$

- Sobel(src, ddepth, dx, dy[, dst[, ksize[, scale[, delta[, borderType]]]]])

```python

img = cv.imread('path')

dx = cv.Sobel(img, cv.CV_64F, dx = 1, dy = 0, ksize = 3)

dy = cv.Sobel(img, cv.CV_64F, dx = 0, dy = 1, ksize = 3)

new_img = cv.add(dx, dy)

# new_img = cv.addWeighted(dx, 0.5, dy, 0.5, gamma = 0)

```

- 注意：

	- **ksize在这里也是一个值**
	- Sobel**需要分别求出x轴和y轴的梯度，因此需要自己手动合并**

  

#### 沙尓(Scharr)算子

- Scharr(src, ddepth, dx, dy[, dst[, scale[, delta[, borderType]]]])

	- **当内核大小为3时，Sobel可能产生较大的误差，因此OpenCV提供了Scharr来解决**
	- **但，Scharr仅适用于核大小为3**

$$

G_x = \begin{bmatrix}

-3 & 0 & +3 \\\

-10 & 0 & +10 \\\

-13& 0 & +3

\end{bmatrix}

$$

$$

G_y = \begin{bmatrix}

-3 & -10 & -3 \\\

0 & 0 & 0 \\\

+3 & +10 & +3

\end{bmatrix}

$$

```python

img = cv.imread('path')

dx = cv.ScharrS(img, cv.CV_64F, dx = 1, dy = 0)

dy = cv.ScharrS(img, cv.CV_64F, dx = 0, dy = 1)

new_img = cv.add(dx, dy)

# new_img = cv.addWeighted(dx, 0.5, dy, 0.5, gamma = 0)

```

- 注意：

	- **Scharr依旧需要分别求dx,dy**
	- **Sobel的ksize设置为-1的时候，就相当于Scharr**

#### 拉普拉斯算子

> 边缘处的导数是零，利用这个特性也可以求的图像的边缘。**但是，二阶求导为0的位置也有可能是毫无意义的位置**

- 拉普拉斯推导
	- x方向
		- 一阶差分：$f'(x) = f(x) - f(x - 1)$
		- 二阶差分：$f''(x) = f'(x + 1) - f'(x) = (f(x + 1) - f(x)) - (f(x) - f(x - 1))$
		- 化简：$f''(x) = f(x - 1) - 2f(x) + f(x + 1)$
		- 同理得到：$f''(y) = f(y - 1) - 2f(y) + f(y + 1)$
	- 叠加x,y
		- $f''(x, y) = f'_x(x, y) + f'_y(x, y)$
		- $f''(x, y) = f(x - 1, y) + f(x + 1, y) + f(x, y - 1) + f(x, y + 1) - 4f(x, y)$

$$

f''(x, y) =

\begin{bmatrix}

0 & 1 & 0 \\\

1 & -4 & 1 \\\

0 & 1 & 0

\end{bmatrix} \odot

\begin{bmatrix}

f(x - 1, y - 1) & f(x, y -1) & f(x + 1, y - 1)\\\

f(x - 1, y) & f(x, y) & f(x + 1, y) \\\

f(x - 1, y + 1) & f(x, y + 1) & f(x + 1, y + 1)

\end{bmatrix}

$$

- Laplacian(src, ddepth, dst[, ksize[, delta[, borderType]]])
	- **拉普拉斯算子可以同时求两个方向边缘**
	- **对噪声敏感，一般需要先去噪再调用拉普拉斯**

```python

img = cv.imread('path')

new_img = cv.Laplacian(img, -1, ksize = 3)

```

#### 边缘检测Canny

> 边缘检测Canny是一个多级边缘检测算法，也是被人认为的**最优算法**
>> 低错误率：标示出尽可能多的实际边缘，同时尽可能的减少噪声产生的误报
>> 高定位性：标示出的边缘要与图像中的实际边缘尽可能接近
>> 最小相应：图像中的边缘检测只能标识一次 

- 边缘检测

	- 去噪，**边缘检测容易受到噪声影响，在进行检测之前，一般使用高斯滤波去噪**
	- 计算梯度：对平滑后的图像采用sobel算子计算梯度和方向
	- $G = \sqrt{G_x^2 + G_y^2}$
	- $\theta = arctan{\frac{G_y}{G_x}}$
	- 梯度方向归为四类：垂直、水平和两个对角线
	- ![[Pasted image 20220715135706.png]]

- 非极大值抑制
	- 获取梯度和方向后，遍历图像，**去除所有不是边界的点**
	- 实现方法：逐个遍历，判断当前像素点是否是周围像素点中**具有同方向梯度的最大值**
	- 如果是局部最大值，则保留。如果不是，则抑制(归零)
	- ![[Pasted image 20220715140258.png]]
- 边界阀值
	- ![[Pasted image 20220715141556.png]]

- Canny(img, minVal, maxVal, ...)

```python

img = cv.imread('path')

lena1 = cv.Canny(img, 100, 200)

lena2 = cv.Canny(img, 64, 128)

```

- 注意：
	- 阀值给的越小，图像越细节

### 形态学

#### 概述

- 什么是形态学
	- 指**一系列处理图像的形状特征的图像处理技术**
	- 形态学的基本思想是**利用一种特殊的结构元(本质上是卷积核)来测量或提取输入图像中相应的形状或特征，以便进一步图像分析和目标识别**
	- 处理方法基本上都是对二进制图像进行处理，即黑白图像
	- 卷积核决定着图像处理后的效果
	- 形态学常用的基本操作：
		- 膨胀和腐蚀
		- 开运算
		- 闭运算
		- 顶帽
		- 黑帽

#### 图像全局二值化

> 二值化：将图像的每个像素变成两种值，比如0,255

- threshold(src, thresh, maxval[, type[, dst]])
	- src：**最好是灰度图**
	- thresh：阀值
	- maxval：最大值，最大值不一定是255
	- type：操作类型

- 常见操作类型

| 操作类型 | 解释 | 
| --- | --- |
| THRESH_BINARY | $dst(x, y) = \left\{\begin{array}{rcl}maxval&{if src(x, y)>thresh}\\0 & {otherwise} \end{array}\right.$ |
| THRESH_BINARY_INV | $dst(x, y) = \left\{\begin{array}{rcl}0 & {if src(x, y)>thresh}\\maxval & {otherwise} \end{array}\right.$ |
| THRESH_TRUNC | $dst(x, y) = \left\{\begin{array}{rcl}threshold & {if src(x, y)>thresh}\\src(x, y) & {otherwise} \end{array}\right.$ |
| THRESH_TOZERO | $dst(x, y) = \left\{\begin{array}{rcl}src(x, y) & {if src(x, y)>thresh}\\0 & {otherwise} \end{array}\right.$ |
| THRESH_TOZERO_INV | $dst(x, y) = \left\{\begin{array}{rcl}0 & {if src(x, y)>thresh}\\src(x, y) & {otherwise} \end{array}\right.$ |

```python
img = cv.imread('path')

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

thresh, new_img = cv.threshold(hray, 127, 255, cv.THRESH_BINARY)
```

- 注意：
	- **threshold会返回两个值，第一个值是阈值，第二个值是处理后的图片**

#### 自适应阈值二值化

> 当同一幅图像上的不同部分具有不同亮度的时候，我们需要采取自适应阈值。**此时的阈值是根据图像上的每一个小区域计算与其对于那个的阈值**

- adaptiveThreshold(src, maxValue, adaptiveMethod, thresholdType, blockSize, C, dst=None)
	- **该函数的返回值只有一个**
	- Adaptive Method：指定计算阀值的方法
		- ADAPTIVE_THRESH_MEAN_C：阀值取自相邻区域的平均值
		- ADAPTIVE_THRESH_GAUSSIAN_C：阀值取自相邻区域的加权值，权重为一个高斯窗口
	- Block Size：领域大小(用来计算阈值的区域大小)
	- C：这就是一个常数，阈值就等于平均值或者加权平均值减去这个常数

```python
img = cv.imread('path')

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

new_img = cv.adaptiveThreshold(img, 255, cv.ADPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 3, 0)
```

- 注意：
	- 自适应阀值也是最好使用灰度图
	- blockSize的参数是一个值

#### 腐蚀

> 腐蚀操作也是用卷积核扫描图像，只不过**腐蚀操作的卷积核一般都是1**，如果卷积核所有的像素点都是白色，那么锚点也是白色

- erode(src, kernel, dst[, anchor[, iterations[, borderType[, borderValue]]]])
	- iteration：腐蚀操作的迭代次数，次数越多，腐蚀操作执行的次数越多，效果越明显

```python
img = imread('path')

kernel = np.ones((3, 3), np.uint8)

cv.erode(img, kernel, iteration = 1)
```

#### 获取形态学卷积核

- getStructElement(shape, ksize[, anchor])
	- shape：卷积核的形状，**注意不适长宽，而是指卷积核中1形成的形状
		- MORPH_RECT：卷积核中的1是矩形，常用
		- MORPH_ELLIPSE：椭圆
		- MORPH_CROSS：十字

```python
img = cv.imread('path')

kernel = getStructElement(cv.MORPH_RECT, (9, 9))

cv.erode(img, kernel, iterations = 1)
```

#### 膨胀操作

> 膨胀是腐蚀的反操作，**基本原理是只要保存卷积核的锚点是非零值，周边无论是0还是非零，都会变成非零**

- dilate(img, kernel, iteration = 1)
	- kernel也可以用getsStructElement

```
img = cv.imread('path')

kernel = getStructElement(cv.MORPH_RECT, (9, 9))

cv.dilate(img, kernel, iterations = 1)
```

#### 开运算

> 开运算和闭运算都是腐蚀和膨胀的基本应用
> **开运算 = 腐蚀 + 膨胀**

- morphologyEx(img, MORPH_OPEN, kernel)
	- MORPH_OPEN表示形态学的开运算
	- **kernel如果噪点比较多，那么建议选择大一点的kernel,反之，则选择较小的**

```python
img = cv.imread('path')

kernel = getStructElement(cv.MORPH_RECT, (9, 9))

cv.morphologyEx(img, cv.MOPRH_OPEN, kernel)
```

#### 闭运算

> **闭运算= 膨胀 + 腐蚀**

```python
img = cv.imread('path')

kernel = getStructElement(cv.MORPH_RECT, (9, 9))

cv.morphologyEx(img, cv.MORPH_CLOSE, kernel)
```

#### 形态学梯度

- **梯度 = 原图 - 腐蚀**
- 腐蚀之后原图边缘变小了，原图- 腐蚀可以得到被腐蚀的部分，即边缘

```python
img = cv.imread('path')

kernel = getStructElement(cv.MORPH_RECT, (9, 9))

cv.morphologyEx(img, cv.MORPH_GRADIENT, kernel)
```

#### 顶帽操作

- **顶帽 = 原图 - 开运算**
- **开运算的效果是去除掉图像外的噪点，原图 - 开运算就得到了去除之后的噪点**

```python
img = cv.imread('path')

kernel = getStructElement(cv.MORPH_RECT, (9, 9))

cv.morphologyEx(img, cv.MORPH_TOPHAT, kernel)
```

#### 黑帽操作

- 黑帽 = 原图 - 闭运算
- **闭运算的效果是去除掉图像内的噪点，原图 - 闭运算就得到了去除之后的噪点**

```python
img = cv.imread('path')

kernel = getStructElement(cv.MORPH_RECT, (9, 9))

cv.morphologyEx(img, cv.MORPH_BLACKHAT, kernel)
```

### 图像轮廓

#### 什么是图像轮廓

> 图像轮廓就是**具有相同的颜色或灰度的连续点的曲线**，轮廓在形状分析的时候非常有用
>> 用于图形分析
>> 物体识别的分析

- 注意：
	- **为了检测轮廓的准确性，首先要对图像进行二值化或者Canny操作**
	- 画轮廓的时候会修改输入的图像，如果之后向继续使用原始图像，首先要对原始图像进行保存

#### 查找轮廓

- findContours(image, mode, method[, contours[, hierachy[, offset]]])
	- mode：查找轮廓的样式
		- RETR_EXTERNAL = 0 只检查外围轮廓
		- RETR_LIST = 1 检测的轮廓不建立等级关系，即检测所有轮廓，比较常用
		- RETR_CCOMP = 2 每层最多两级，从里到外
		- RETR_TREE = 3 按照树形存储轮廓，从大到小，从右到左，最常用
	- method：
		- CHAIN_APPROX_NONE 保存轮廓上的所有点
		- CHAIN_APPROX_SIMPLE 只保存角点，比如四边形，只保留四边形的四个点，存储信息少，比较常用
	- hierachy和contours
		- 返回轮廓的层级和轮廓
		- contours是一个列表

```python
img = cv.imread('path')

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

thresh, binary_img = cv.threshold(gray, 150, 255, cb.THRESH_BINARY)

contours, hierachy = cv.findContours(img, cv.RETER_TREE, cv.CHAIN_APPROX_SIMPLE)
```

#### 绘制轮廓

- drawContours(image, contours, contouridx, color[, thickness[, lineType[, hierarchy[, maxLevel]]]])
	- contours：轮廓点
	- contouridx：要绘制轮廓的编号，**-1表示所有轮廓**
	- color：轮廓的颜色。
	- thickness：线宽，**-1表示全部填充**

```
img_copy = img
cv.draw(img_copy, contours, -1, (0, 0, 255), 2)
```

#### 轮廓的面积和周长

> 轮廓面积是指每个轮廓中的像素点围成区域的面积，单位为像素
> > 轮廓面积是轮廓的重要统计信息之一，通过轮廓面积的大小可以进一步的分析每个轮廓隐含的信息

- contourArea(contours)
- arcLength(curve, closed)
	- curve：轮廓
	- closed：是否是闭合的轮廓

```python
area = cv.contourArea(contours[1])
length = cv.arcLength(contours[1], closed = True)
```

#### 多边形逼近

> **findContours后的轮廓信息contours可能过于复杂不平滑，可用approxPolyDP函数对该多边形曲线做适当近似**，这就是多边形逼近

- DP算法**核心就是不断找多边形最远点加入形成新的多边形，知道最短距离小于指定的精度**

- approxPolyDP(curve, epsilion, closed, approxCurve)
	- curve：要近似逼近的轮廓
	- epsilion：即DP算法使用的阈值
	- closed：轮廓是否闭合

```
approx = cv.approxPolyDP(contours[0], 20, True)
cv.drawContours(img_copy, [approx], -1, (0, 255, 0), 2)
```

- 注意：
	- 逼近的返回值是一个矩阵，因此画图时需要进行处理

#### 多边形凸包

> 多边形逼近只是轮廓的高度近似。**凸包跟逼近很像，但是凸包是物体最外层的凸多边形。凸包指的是完全包含原有轮廓，并且仅由轮廓上的点所构成的多边形。凸包的每一处都是凸的，即在凸包内连接任意亮点的直线都在凸包的内部。在凸包内，任意连续的三个点的内角和小于180**

- convexHull(points[, hull[, clockwise[, returnPoints]]])
	- points：轮廓
	- clockwise：顺时针绘制

```python
hull = cv.convexHull(contours[0])
cv.drawContours(img_copy, [hull], -1, (0, 255, 0), 2)
```

- 注意
	-  凸包的返回值是一个矩阵，因此画图时需要进行处理

#### 最小外接矩形

- minAreaRet(points)
	- 注意：
		- 返回值是一个元组，内容是一个旋转矩形(RotatedRect)的参数，矩形的起始坐标x,y.矩形的宽度和高度，矩形的旋转角度

```python
ret = cv.minAreaRet(contours[0])
```

- **可以使用boxPoint来自动计算返回值**
	- 但是注意，**最后使用drawContours的时候，坐标必须是整数，因此，需要取整**

```python
box = cv.boxPoint(ret)
box = np.rount(box).astype('int64')
```

#### 最大外接矩形

- boundingRet(points)
	- 返回值直接是x,y和w,h

```python
x, y, w, h = cv.boundingRet(sontours[0])
cv.rectangle(img, (x, y), (x + w, y + h), 2)
```

### 图像金字塔

#### 图像金字塔介绍

> **图像金字塔是图像中多尺度的一种表达，最主要用于图像的分割，是一种以多分辨率来解释图像的有效但概念简单的结构**。
>> 简单来说，图像金字塔是同一图像不同分辨率子图的集合
>
>图像金字塔最初用于机器视觉和图像压缩，一幅图像的金字塔是一系列以金字塔形状排列的**分辨率逐步降低**且来源于**同一原始图像**的集合

- 金字塔的底部是待处理图像的高分辨率表示，而顶部是低分辨率的近似。**层级越高，图像越小，分辨率越低**

![[Pasted image 20220719134952.png]]

- 常见的两类图像金字塔
	- 高斯金字塔
	- > 用来向下/降(分辨率减少)采样，主要的图像金字塔
	- 拉普拉斯金字塔
	- > 用来从金字塔底层图像重建上层未采样图像，在数字图像处理中也即是预测残差，可以对图像进行最大程度的还原，配合高斯金字塔一起使用

#### 高斯金字塔

> 高斯金字塔是通过高斯平滑和亚采样获得一系列下采样图像

- 将$G_i$和高斯内核卷积
- 将所有的偶数行和列去除
- 每次处理后，图像是原来的1/4

![[Pasted image 20220719135902.png]]

- 注意：
	- 向下采样会丢失图像信息

- pyrDown(src)
	- 下采样，分辨率减小的操作

```python
cv.pyrDown(img)
```

- 向上采样
	- 将图像在每个方向扩大为原来的两倍，新增的行和列以0填充
	- 使用先前同样的内核(乘以4)与放大后的图像卷积，获得近似值

- pyrUp(src)

```python
cv.pyrUp(img)
```

- 注意：
	- 高斯金字塔采样**过程不可逆**

#### 拉普拉斯金字塔

$$
	L_i = G_i - PyrUp(PyrDown(G_i))
$$

- G是原始图像
- L是拉普拉斯金字塔图像

- 拉普拉斯金字塔就是通过原图像减去先缩小后放大的图像的一系列图像构成的，保留的是残差
- **拉普拉斯金字塔图像只像图像边缘，用于图像压缩**

![[Pasted image 20220719141440.png]]

```python
img = cv.imread('path')

lap = img - cv.pyrUp(cv.pyrDown(img))
```

### 图像直方图

#### 图像直方图的基本概念

> 在统计学中，直方图是一种对数据分布情况的图形表示，是一种二维的统计图表
> 图像直方图是表示数字图像中亮度分布的直方图，标绘了图像中每个亮度值的像素数。**这种直方图中，横坐标的左侧为纯黑、较暗的区域，而右侧为较亮、纯白的区域**。因此，一张较暗图片的图像直方图中数据多集中于左侧和中间部分，而整体明亮、只有少量阴影的图像则相反

- 横坐标：图像中各个像素点的灰度级
- 纵坐标：具有该灰度级的像素个数

![[Pasted image 20220719142539.png]]

#### 绘制直方图API

- calcHist(images, channels, mask, histSize, ranges[, hist[, accumulate]])
	- images：原始图像
		- **需要中括号括起来**
	- channels：指定通道
		- **需要用中括号括起来，**
		- 灰度图是[0]
		- 彩色的BGR分别是[0], [1], [2]
	- mask：掩码图像
		- 统计整幅图像的直方图，设为None
		- 统计图像的某一部分直方图时，需要掩码图像
	- histSize：bins的数量，也就是X轴的数量
		- **需要用中括号括起来，例如[250]**
	- ranges：像素值的范围，例如[0, 255]
	- accumulate：累积标识
		- 默认值为False
		- 如果被设置为True,则直方图在开始分配时不会清零
		- **该参数允许从多个对象中计算单个直方图，或者用于实时更新直方图**
		- 多个直方图的累积结果，用于对一组图像计算直方图

```python
cv.imread('path')

cv.calcHist([img], [0], None, [256], [0, 255])
```

#### 绘制直方图

- 使用matplotlib

```python
img = cv.imread('path')

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

# plt.hist(gray)
plt.hist(gray,ravel(), bins = 256, ranges = [0, 255])
```

- 使用opencv

```python
img = cv.imread('path')

histb = cv.calcHist([img], [0], None, [256], [0, 255])
histg = cv.calcHist([img], [1], None, [256], [0, 255])
histr = cv.calcHist([img], [2], None, [256], [0, 255])

plt.plot(histb, color = 'b', label='bule')
plt.plot(histg, color = 'g', label='green')
plt.plot(histr, color = 'r', label='red')
plt.legend()
plt.show()
```

#### 使用掩膜的直方图

- 如何生成掩膜
	- 先生成一个全黑的和原始图片大小一样大的图片， **mask = np.zeros(img.shape, np.uint8)**
	- 将想要得到的区域通过索引方式设置为255没**mask[100:200, 200:300] = 255**

```python
img = cv.imread('path')

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

mask = np.zeros(gray.shape, np.uint8)

mask[200:400, 200:400] = 255

# mask_gray = cv.bitwise_and(gray, gray, mask = mask)

hist_mask = cv.calcHist([img], [0], mask, [256], [0, 255])


plt.plot(hist_mask, label='mask')
```

#### 直方图均衡化原理

> 直方图均衡化是通过拉伸像素强度的分布范围，使得在0～255灰阶上的分布更加均匀，提高了图像的对比度，到达改善图像主观视觉的效果。**对比较低的图像适合用均衡化**

- 原理：
	- 先得到归一化直方图
	- 再计算累积直方图
	- 将累积直方图进行区间转化
	- 在累积直方图中，概率相近的原始值会被处理成相同的值

- equalizeHist(src[, dst])
	- src：原始图像
	- dst：目标图像，即处理结果

```python
img = cv.imread('path')
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

gray_dark = gray - 40
gray_bright = gray + 40

hist_gray = cv.calcHist([gray], [0], None, [256], [0, 255])
hist_dark = cv.calcHist([gray_dark], [0], None, [256], [0, 255])
hist_bright = cv.calcHist([gray_bright], [0], None, [256], [0, 255])

plt.plot(hist_gray)
plt.plot(hist_dark)
plt.plot(hist_bright)

dark_equ = cv.equalizeHist(gray_dark)
bright_equ = cv.equalizeHist(gray_bright)

cv.imshow('gray_dark', np.hstack((gray_dark, dark_equ)))
cv.imshow('gray_bright', np.hstack((gray_bright, bright_equ)))
```

### 汽车项目知识补充

#### 背景减除

- BackgroundSubtractorMOG()
	- 这是一个**以高斯模型为基础的前景/背景分割算法**
	- 使用K = 3或5个高斯分布混合对背景进行建模。
	- **在使用之前，需要先使用bgsegm.createBackgroundSubtractorMOG创建一个背景对象，然后使用backgroundsubtractor.apply（）就可以得到前景的掩膜**
	- **移动的物体会被标记为白色，背景会被标记为黑色**

```python
cap = cv.VideoCapture(0)

mog = cv.bgsegm.createBackgroundSubstractorMOG()

while True:
	ret, frame = cap.read()
	if ret = True:
		fgmask = mog.apply(frame)
		cv.imshow('video', fgmask)
```

- 注意：
	- **新版本直接createBackgroundSubtractorMOG2，不需要在加入bgsemg**

