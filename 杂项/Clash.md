# Linux配置Clash for Linux

---   

> 由于qv2ray工作团队内部矛盾，导致却vray不再更新，虽然还能用，但是致命问题很多  
> 比如，在今天(2022年6月13日)我正常的打开我的linux,却发现我的代理炸了，同时，告诉我丢失了libprotobo.so.31的库
> 我查阅了很多资料发现，没用！
> 因此我打算不做人啦！开始配置当初我嫌麻烦的clash

## 安装Clash
> 废话不多说，直接上网址  

[clash](https://github.com/Dreamacro/clash/releases/tag/v1.10.6)
- 注意，要根据自己电脑的处理器选择对应的版本
	- clash-linux-amd64
- 如果不想这么麻烦，其实还可以
	- wget https://github.com/Dreamacro/clash/releases/tag/v1.10.6/clash-linux-amd64-v1.10.6.gz
	- 但是要保证你的网络能够访问上github

## 开始配置

### 解压
> 安装完毕之后，将压缩包直接移动到桌面

```
mv clash-linux-amd64-v1.10.6.gz ~/
gzip -d clash-linux-amd64-v1.10.6.gz
sudo chmod +x clash-linux-amd64-v1.10.6
```

### 配置文件

> 配置文件对于每一个v*n来说是至关重要的，对应的配置文件需要自行在对应的网站上下载，这里我只说我目前使用的(但是下述方法也能适用于其他)
> 蜂巢上的配置文件不是实际上的链接，而是需要通过base64解码之后才有的，但是我们的clash配置文件不能这样简单的获取
>

1.  需要先在手机上用clash配置好蜂巢
2.  进入clash之后点击配置
3.  看见对应的配置项后选择编辑
4.  点击浏览文件，就会看到一个配置文件.yaml
5.  下载到手机上然后上传到自己的电脑上

> 至此，前提条件就准备好了

### 配置Clash
```
mv clash-linux-amd64-v1.10.6 clash # 为了方便，我们先将clash的包名改成clash
mkdir ~/.config/clash
mv ./clash ~/.config/clash
./clash # 执行clash,第一次执行会在当前路径下生成config.yaml和Conutry.mmdb,但是由于网络原因,Country.mmdb可能会下载失败
axel http://www.ideame.top/mmdb/Country.mmdb
# 如果提示没有axel
# 使用yum install axel或者yay -S axel或者sudo apt-get install axel
# 安装完毕之后，再次键入axel http://www.ideame.top/mmdb/Country.mmdb
# 处理完之后，将从手机上下载的配置文件.yaml放入该目录中，替换掉原本的配置文件
# 假设已经将配置文件.yaml传输到主目录中
mv 配置文件.yaml config.yaml
rm .config/clash/config.yaml
mv config.yaml .config/clash/
./clash # 再次执行clash,此时就能成功运行
```

### 配置自启动和代理
```
mv .config/clash/clash /usr/local/bin/

vim .bashrc
export http_proxy='http://127.0.0.1:7890'
export https_proxy='https://127.0.0.1:7890'
:wq

source .bashrc
```

- 自启动服务
```
sudo vim /etc/systemd/system/clash.service

[Unit]
Description=Clash service
After=network.target

[Service]
Type=simple
User=louis（你的用户名）
ExecStart=/home/louis/Clash/clash（Clash 程序路径）
Restart=on-failure
RestartPreventExitStatus=23

[Install]
WantedBy=multi-user.target
:wq

sudo systemctl enable clash 
```

> 至此，clash在linux上就配置完成了，如果在chrome中能够访问页面，就可以放心使用啦