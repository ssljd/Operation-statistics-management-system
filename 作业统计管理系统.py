import os
import sys
import xlrd
import xlwt
from pyecharts.charts import Pie
from pyecharts import options as opts
from tkinter import *
import time
import threading
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QPushButton

pb_x = 0
pb_y = 0
pb_width = 100
pb_height = 20

pb_bg = "white"
pb_fg = "green"
pb_frame_size = 0
canvas = Canvas

class progress:
    def __init__(self):
        pass

    # 初始化，创建Canvas实例，设定坐标和宽高
    def init(self, master, x=pb_x, y=pb_y,
             width=pb_width, height=pb_height,
             bg=pb_bg, fg=pb_fg,
             frame_size=pb_frame_size):
        global pb_x
        pb_x = x

        global pb_y
        pb_y = y

        global pb_width
        pb_width = width

        global pb_height
        pb_height = height

        global pb_bg
        pb_bg = bg

        global pb_fg
        pb_fg = fg

        global pb_frame_size
        pb_frame_size = frame_size

        global canvas
        canvas = Canvas(master, width=width, height=height, bg=pb_bg)
        canvas.place(x=x, y=y)

    # 运行进度条
    def run(self, master, percentage, text=None):
        global canvas
        fill_line = canvas.create_rectangle(1.5, 1.5, 0, 23, width=0, fill=pb_fg)
        canvas.coords(fill_line, (0, 0, percentage, 60))
        if text:
            label = Label(master, text=text)
            label.place(x=pb_x + pb_width, y=pb_y)
        master.update()

# 主界面
class Mainin(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle('操作界面')
        self.resize(800, 450)
        self.setFixedSize(self.width(), self.height())
        self.setWindowFlags(Qt.WindowCloseButtonHint)
        self.setWindowOpacity(0.9)  # 设置窗口透明度
        self.setWindowFlag(QtCore.Qt.FramelessWindowHint)  # 隐藏边框
        palette = QPalette()
        palette.setBrush(QPalette.Background, QBrush(QPixmap("./1.png")))
        self.setPalette(palette)

        ###### 设置界面控件
        self.verticalLayout = QGridLayout(self)
        self.H = QLabel("")
        self.verticalLayout.addWidget(self.H, 0, 0, 9, 0)

        self.left_close = QtWidgets.QPushButton("")  # 关闭按钮
        self.left_visit = QtWidgets.QPushButton("")  # 空白按钮
        self.left_mini = QtWidgets.QPushButton("")  # 最小化按钮
        self.verticalLayout.addWidget(self.left_mini, 0, 6, 1, 1)
        self.verticalLayout.addWidget(self.left_close, 0, 8, 1, 1)
        self.verticalLayout.addWidget(self.left_visit, 0, 7, 1, 1)
        self.left_close.setFixedSize(15, 15)  # 设置关闭按钮的大小
        self.left_visit.setFixedSize(15, 15)  # 设置最大化按钮大小
        self.left_mini.setFixedSize(15, 15)  # 设置最小化按钮大小
        self.left_close.setStyleSheet(
            '''QPushButton{background:#F76677;border-radius:5px;}QPushButton:hover{background:red;}''')
        self.left_visit.setStyleSheet(
            '''QPushButton{background:#F7D674;border-radius:5px;}QPushButton:hover{background:yellow;}''')
        self.left_mini.setStyleSheet(
            '''QPushButton{background:#6DDF6D;border-radius:5px;}QPushButton:hover{background:green;}''')

        self.pushButton_execute = QPushButton()
        self.pushButton_execute.setText("开始执行")
        self.verticalLayout.addWidget(self.pushButton_execute, 5, 4, 1, 3)
        self.pushButton_execute.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:2px}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")

        self.pushButton_n_execute = QPushButton()
        self.pushButton_n_execute.setText("退出")
        self.verticalLayout.addWidget(self.pushButton_n_execute, 6, 4, 1, 3)
        self.pushButton_n_execute.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:2px}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")

        ###### 绑定按钮事件

        self.pushButton_execute.clicked.connect(self.on_pushButton_execute_clicked)
        self.pushButton_n_execute.clicked.connect(self.n_execute_clicked)

    def on_pushButton_execute_clicked(self):

        print('执行')
        path4 = 'C:/Users/sljd/Desktop/Code_library/python/Leisure code/作业统计管理系统/计科作业/作业三'
        list1 = []
        list2 = []
        listdir(path4, list1, list2, False)

        self.progress_bar()
        all_housework, num = single(list1)
        visualization(num)

    def n_execute_clicked(self):
        main_in.close()

    # 进度条
    def progress_bar(self):
        root = Tk()
        root.title("progressBar")
        root.geometry("300x100")
        progress.init(self=progress, master=root, x=10, y=20)
        for i in range(0, 101):
            progress.run(self=progress, master=root, percentage=i, text="处理进度：" + str(i) + "%")
            time.sleep(0.01)
        root.mainloop()

# 获取指定文件夹下的文件名，并将文件名储存在list中，形成一个列表
# 若choice是true，则将总文件夹下的个人文件夹名储存在list2中
# 若choice是false，则将总文件夹下的个人文件夹下的word文件名储存在list1中
def listdir(path, list1, list2, choice):
    for p, name, files in os.walk(path, topdown=choice):
        if name:
            for file in name:
                list2.append(file)
            break
        # 判断文件名是否为doc或者docx
        for file in os.listdir(p):
            if os.path.splitext(file)[1] == '.doc' or os.path.splitext(file)[1] == '.docx':
                # 特定类型的文件需要用os.path.splitext()函数将路径拆分，拆分为文件名和拓展名，[0]表示文件名，[1]表示拓展名
                list1.append(file)  # 如果是两者中的一种，则将其加在列表中

# 单词作业处理函数
def single(list1):
    # data = xlrd.open_workbook('AI201学生名单.xls')  # 打开当前目录下名为test的文档，即学生信息
    data = xlrd.open_workbook('计科201学生名单.xls')  # 打开当前目录下名为test的文档，即学生信息
    # 获得工作表
    table = data.sheet_by_name('Sheet1')  # 通过名称获取，即读取sheet1表单，
    # 也可以table = data.sheet_by_index(0)通过索引获取，例如打开第一个sheet表格
    # 还可以table = data.sheets()[0]#通过索引顺序获取
    nrows = table.nrows  # 获取该sheet1表格中的有效行数
    student = {}  # 将student{}作为一个字典存取数据
    for i1 in range(1, nrows):  # 从第二行开始有所需要的数据
        xuehao = table.cell_value(i1, 0)  # 获取单元格中的学号
        name = table.cell(i1, 1).value  # 获取单元格中的姓名
        # 获取单元格内容的三种方式：
        # table.cell(i,j).value
        # table.cell_value(i,j)
        # table.row(i)[j].value
        xuehao = int(xuehao)
        # 将浮点数转化为整数
        student[xuehao] = 0  # 默认字典中学号对应0，即未交作业
        for zuoye in list1:  # 遍历每一份作业
            if str(xuehao) in zuoye or name in zuoye:
                # 如果出现学号或者姓名，则认为交了作业
                student[xuehao] = 1  # 记为1，认为交了作业
    print("未交学生的学号:")
    list2 = []  # 新建列表计算未交作业个数
    for key, values in student.items():  # 用items() 函数遍历(键, 值) 元组数组，key表示学号，value表示是否交作业
        if values == 0:
            list2.append(key)
            print(key, end="\n")  # 输出未交学生的学号
    a = len(list2)
    b = (nrows - 1 - a) / (nrows-1) * 100
    print('提交人数：', nrows - 1 - a)
    print('未提交人数：', a)
    print('提交率为：', b, '%')  # 计算提交率
    print('*' * 40)
    list_all = [len(list1), len(list2)]
    return student, list_all

# 多次作业处理函数
def multiple(all_homework):
    date = xlrd.open_workbook('test.xlsx')  # 打开当前学生名单
    table = date.sheet_by_name('Sheet1')  # 通过名称获取，即读取sheet1表单s
    # 也可以table = data.sheet_by_index(0)通过索引获取，例如打开第一个sheet表格
    # 还可以table = data.sheets()[0]#通过索引顺序获取
    nrows = table.nrows  # # 获取该sheet1表格中的有效行数
    workbook = xlwt.Workbook(encoding='utf-8')  # 创建一个workbook 设置编码。Workbook（）是构造函数，返回一个工作薄的对象。
    sheet_test = workbook.add_sheet('sheet_test', cell_overwrite_ok=True)  # 用cell_overwrite_ok=True实现对单元格的重复写
    sheet_test.write(0, 0, '学号')  # 将学号写入Excel中
    sheet_test.write(0, 1, '姓名')  # 将姓名写入Excel中
    n = 2  # 从第三列开始储存每次作业的情况
    for homework in all_homework:
        for i in homework:  # 遍历每次作业
            sheet_test.write(0, n, i)
            student = all_homework[i]
            for i1 in range(1, nrows):
                xuehao = table.cell(i1, 0).value  # 获取学号单元格的值
                stuname = table.cell(i1, 1).value  # 获取姓名单元格的值
                sheet_test.write(i1, 0, xuehao)
                sheet_test.write(i1, 1, stuname)
                sheet_test.write(i1, n, student[xuehao])  # 将完成与否填入表格中
            n = n + 1
            workbook.save('C:/Users/sljd/Desktop/Code_library/python/Leisure code/作业统计管理系统/作业统计.xlsx')

def visualization(num):
    situation = ['已提交', '未提交']
    pie = Pie()
    pie.add("", [list(z) for z in zip(situation, num)])
    pie.set_colors(["#38E737", "#FF3366"])
    pie.set_global_opts(title_opts=opts.TitleOpts(title="Pie-设置颜色"))
    pie.render("pie.html")

#欢迎界面
def showWelcome():
    sw = root1.winfo_screenwidth()  # 获取屏幕宽度
    sh = root1.winfo_screenheight()  # 获取屏幕高度r
    root1.overrideredirect(True)  # 去除窗口边框
    root1.attributes("-alpha", 1)  # 窗口透明度（1为不透明，0为全透明）
    x = (sw - 800) / 2
    y = (sh - 450) / 2
    root1.geometry("800x450+%d+%d" % (x, y))  # 将窗口置于屏幕中央
    if os.path.exists(r'./9.gif'):  # 搜索图片文件（只能是gif格式）
        bm = PhotoImage(file=r'./9.gif')
        lb_welcomelogo = Label(root1, image=bm)  # 将图片放置于窗口
        lb_welcomelogo.bm = bm
        lb_welcomelogo.place(x=-2, y=-2, )  # 设置图片位置

def closeWelcome():
    for i in range(2):
        time.sleep(1)  # 屏幕停留时间
    root1.destroy()


if __name__ == '__main__':
    root1 = Tk()
    tMain = threading.Thread(target=showWelcome)  # 开始展示
    tMain.start()
    t1 = threading.Thread(target=closeWelcome)  # 结束展示
    t1.start()
    root1.mainloop()
    app = QtWidgets.QApplication(sys.argv)

    main_in = Mainin()
    main_in.show()

    sys.exit(app.exec_())

    # path1 = 'C:/Users/sljd/Desktop/Code_library/python/Leisure code/作业统计管理系统/作业一'
    # path2 = 'C:/Users/sljd/Desktop/Code_library/python/Leisure code/作业统计管理系统/作业二'
    # path3 = 'C:/Users/sljd/Desktop/Code_library/python/Leisure code/作业统计管理系统/作业三'
    # path4 = 'C:/Users/sljd/Desktop/Code_library/python/Leisure code/作业统计管理系统/作业四'
    # list1 = []
    # list2 = []
    # listdir(path1, list1, list2, False)
    # all_housework, num = single(list1)
    # visualization(num)
