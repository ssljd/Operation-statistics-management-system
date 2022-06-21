# 作业管理系统

### 介绍
该系统是我本科阶段大二上学期的课程设计，题目为“作业统计管理系统”。

该系统是使用PYQT5来制作功能界面，tkinter制作欢迎界面，该系统的执行流程如下：</p>
1）选择人员名单excel文件，其人员名单[样例](data/计科201学生名单.xls) </p>
2）选择作业文件夹，其[样例](data/计科作业) </p>
3）开始执行(执行过程会产生进度条)，生成作业统计.xls文件和作业未交信息.txt

### 软件架构
python + pycharm

### 目录结构及主要文件说明
```
├─data  
│   ├─.xls文件                      （人员名单）
│   ├─文件夹                        （储存需要统计的作业）
│
├─result
│   ├─作业未交信息.txt
│   ├─作业统计.txt
│
├─图片界面
│   ├─9.gif                        （欢迎界面图）
│   ├─1.png                        （功能界面图）
│
├─示例
│
├─config.txt                       （配置文件）
│
├─作业统计管理系统                   （自己编写的代码）
```



### 安装教程
[配置文件](config.txt)

### 相关资料
[资料1](https://blog.csdn.net/weixin_51390582/article/details/119269917) </p>  
[资料2](https://blog.csdn.net/m0_46315929/article/details/120177940) </p>  
[示例代码(github)](https://github.com/wuhudasm-lll/-2.0) </p>  
[示例代码(本地)](示例/-2.0-main) </p>  


![系统欢迎界面](图片界面/9.gif)  
<center><p>欢迎界面</center>

![系统功能界面](图片界面/1.png)  
<center><p>功能界面</center>