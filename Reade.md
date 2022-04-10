# hisi35xx 利用tde、ive加速图像处理

先看cmake 确认交叉编译工具链路径正确
- 交叉编译
```
mkdir build
cd build
make -j4
```
- 运行
把本地文件夹环境mount到板子上
[NFS配置]( https://editor.csdn.net/md/?articleId=117387364)
```
mount -t nfs -o nolock 192.168.*.*:/nfs路径(本地路径) /home (盒子路径)
```

