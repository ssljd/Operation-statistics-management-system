import os
import sys
import numpy
import xlrd
import xlwt
import qtawesome
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
pb_width = 80
pb_height = 20

pb_bg = "white"
pb_fg = "blue"
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
        self.path_floder = ''
        self.path_file = ''
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

        # 获取excel文件按钮
        self.right_folder_button11 = QtWidgets.QPushButton(qtawesome.icon('fa.folder', color='GoldenRod'), "")
        self.verticalLayout.addWidget(self.right_folder_button11, 2, 3, 1, 2)
        self.right_folder_button11.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:none}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")
        self.right_folder_button11.setObjectName('right_search_button')
        self.right_folder_button11.setFont(qtawesome.font('fa', 16))
        self.right_folder_button11.clicked.connect(self.file_button_clicked31)
        self.right_folder_button11.setFixedSize(30, 30)  # 设置按钮大小

        self.right_bar_widget_folder_input8 = QtWidgets.QLineEdit()
        self.right_bar_widget_folder_input8.setPlaceholderText("填入或选择需要上传的excel文件")
        self.right_bar_widget_folder_input8.setObjectName("right_input_item")
        self.verticalLayout.addWidget(self.right_bar_widget_folder_input8, 2, 4, 1, 3)
        self.right_bar_widget_folder_input8.setStyleSheet(
            '''QLineEdit{
                    border:1px solid gray;
                    width:200px;
                    border-radius:10px;
                    padding:2px 4px;
            }''')

        # 获取文件夹按钮
        self.right_folder_button22 = QtWidgets.QPushButton(qtawesome.icon('fa.folder', color='GoldenRod'), "")
        self.verticalLayout.addWidget(self.right_folder_button22, 3, 3, 1, 2)
        self.right_folder_button22.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:none}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")
        self.right_folder_button22.setObjectName('right_search_button')
        self.right_folder_button22.setFont(qtawesome.font('fa', 16))
        self.right_folder_button22.clicked.connect(self.folder_button_clicked31)
        self.right_folder_button22.setFixedSize(30, 30)  # 设置按钮大小

        self.right_bar_widget_folder_input9 = QtWidgets.QLineEdit()
        self.right_bar_widget_folder_input9.setPlaceholderText("填入或选择需要上传的文件夹")
        self.right_bar_widget_folder_input9.setObjectName("right_input_item")
        self.verticalLayout.addWidget(self.right_bar_widget_folder_input9, 3, 4, 1, 3)
        self.right_bar_widget_folder_input9.setStyleSheet(
            '''QLineEdit{
                    border:1px solid gray;
                    width:200px;
                    border-radius:10px;
                    padding:2px 4px;
            }''')

        # 设置开始执行按钮
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

        # 设置退出按钮
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

    # 执行
    def on_pushButton_execute_clicked(self):
        print('执行')
        list1 = []
        list2 = []
        listdir(self.path_folder, list1, list2, True)
        all_homework = mergelist(list1, list2)

        self.progress_bar()
        with open('作业未交信息.txt', 'w') as f:  # 清空作业未交信息.txt之前的信息
            f.write('')
        all_housework = []
        for i in range(len(all_homework)):
            with open('作业未交信息.txt', 'a') as f:
                f.write('{}情况\n'.format(homework_list[i]))
            housework, num = homework_handle(all_homework[i], self.path_file)
            all_housework.append(housework)
        Statistics_excel(all_housework, self.path_file)
        print('完成')

    # 退出
    def n_execute_clicked(self):
        main_in.close()

    # 文件夹的路径选择
    def folder_button_clicked31(self):
        fileName = QtWidgets.QFileDialog.getExistingDirectory(self, "选取文件夹", os.getcwd())
        main_in.right_bar_widget_folder_input9.setText(fileName)
        self.path_folder = fileName

    # excel文件的路径选择
    def file_button_clicked31(self):
        fileName, fileType = QtWidgets.QFileDialog.getOpenFileName(self, "选取文件", os.getcwd(),
                                                                    "All Files(*);;Text Files(*.xls)")
        main_in.right_bar_widget_folder_input8.setText(fileName)
        self.path_file = fileName

    # 进度条
    def progress_bar(self):
        root = Tk()
        root.title("progressBar")
        root.geometry("300x100")
        progress.init(self=progress, master=root, x=10, y=20)
        for i in range(0, 101):
            progress.run(self=progress, master=root, percentage=i, text="处理进度：" + str(i) + "%")
            time.sleep(0.01)
            if i == 100:
                root.destroy()
        root.mainloop()

'''
    @:name: listdir
    @:param1 path: 指定文件夹路径
    @:param2 list1: 储存压缩包文件名
    @:param3 list2: 个人文件夹名
    @:param4 choice: 选择os.walk的执行方式
    @:function : 将总文件夹下的压缩包名储存在list1，将总文件夹下的个人文件夹下的储存在list2
    @:return 无
'''
def listdir(path, list1, list2, choice):
    global homework_list
    for p, names, files in os.walk(path, topdown=choice):
        homework_list = []  # 储存单次作业的文件夹名称
        while (names):
            for file in names:
                homework_list.append(file)
            break
        paths = []
        for i in range(len(homework_list)):
            paths.append(os.path.join(p, homework_list[i]))

        list3 = []  # 新建临时列表
        # 以压缩包作为统计文件，统计交作业的学生个数
        for i in range(len(homework_list)):
            hwork = os.listdir(paths[i])
            for item in hwork:
                if item.split('.')[-1] == 'zip' or item.split('.')[-1] == 'rar':
                    list3.append(item.split('.')[0])
            list1.append(list3)

        # 以文件夹作为统计文件，统计交作业的学生个数
        for i in range(len(homework_list)):
            for pi, name, files_ in os.walk(paths[i], topdown=choice):
                if name:
                    list4 = []  # 新建临时列表
                    for file in name:
                        list4.append(file)
                    list2.append(list4)
                break
        break

# 获取列表的最大值
def Max(len1, len2):
    if len2 >= len1:
        return len2
    else:
        return len1

# 合并列表list1和list2
def mergelist(list1, list2):
    global all_homework
    all_homework = []

    for i in range(Max(len(list1), len(list2))):
        single_homework = []
        [single_homework.append(item1) for item1 in list1[i]]
        [single_homework.append(item2) for item2 in list2[i]]
        all_homework.append(numpy.unique(single_homework))
    return all_homework

'''
    @:name: homework_handle
    @:param1 list: 储存学生信息列表
    @:param2 file_path: excel表文件路径
    @：function: 获取未交学生学号，并将未交学生学号以及提交人数、为提交人数、提交率打印到文本文件
    @：return: student, list_all
'''
def homework_handle(list, file_path):
    # data = xlrd.open_workbook('AI201学生名单.xls')  # 打开当前目录下名为test的文档，即学生信息
    data = xlrd.open_workbook(file_path)  # 打开当前目录下名为test的文档，即学生信息
    # 获得工作表
    table = data.sheet_by_name('Sheet1')  # 通过名称获取，即读取sheet1表单，
    # 也可以table = data.sheet_by_index(0)通过索引获取，例如打开第一个sheet表格
    # 还可以table = data.sheets()[0]#通过索引顺序获取
    nrows = table.nrows  # 获取该sheet1表格中的有效行数
    student = {}  # 将student{}作为一个字典存取数据
    student_name = {}

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
        # student_name[name] = 0
        for zuoye in list:  # 遍历每一份作业
            if str(xuehao) in zuoye or name in zuoye:
                # 如果出现学号或者姓名，则认为交了作业
                student[xuehao] = 1  # 记为1，认为交了作业
                # student_name = 1
    with open('作业未交信息.txt', 'a') as f:
        f.write('"未交学生的学号:"\n')
    list6 = []  # 新建列表计算未交作业个数
    for key, values in student.items():  # 用items() 函数遍历(键, 值) 元组数组，key表示学号，value表示是否交作业
        if values == 0:
            list6.append(key)
            with open('作业未交信息.txt', 'a') as f:
                f.write('{}\n'.format(key))
    a = len(list6)
    b = (nrows - 1 - a) / (nrows-1) * 100
    with open('作业未交信息.txt', 'a') as f:
        f.write('提交人数：{}\n'.format(nrows - 1 - a))
        f.write('未提交人数：{}\n'.format(a))
        f.write('{}\n'.format('*' * 40))
    list_all = [len(list), len(list6)]
    return student, list_all

'''
    @:name: Statistics_excel
    @:param1 all_homework: 储存学生信息列表
    @:param2 file_path: excel表文件路径
    @：function: 将学生的提交信息导入到XLS文件中
    @：return: 无
'''
def Statistics_excel(all_homework, file_path):
    date = xlrd.open_workbook(file_path)  # 打开当前学生名单
    table = date.sheet_by_name('Sheet1')  # 通过名称获取，即读取sheet1表单s
    # 也可以table = data.sheet_by_index(0)通过索引获取，例如打开第一个sheet表格
    # 还可以table = data.sheets()[0]#通过索引顺序获取
    nrows = table.nrows  # # 获取该sheet1表格中的有效行数
    workbook = xlwt.Workbook(encoding='utf-8')  # 创建一个workbook 设置编码。Workbook（）是构造函数，返回一个工作薄的对象。
    sheet_test = workbook.add_sheet('sheet_test', cell_overwrite_ok=True)  # 用cell_overwrite_ok=True实现对单元格的重复写
    sheet_test.write(0, 0, '学号')  # 将学号写入Excel中
    sheet_test.write(0, 1, '姓名')  # 将姓名写入Excel中
    j = 2   # 从第三列开始写作业名称到第一列
    for i in range(len(homework_list)):
        sheet_test.write(0, j, homework_list[i])
        j += 1
    n = 2  # 从第三列开始储存每次作业的情况
    style = "font:colour_index red;"
    red_style = xlwt.easyxf(style)
    for homework in all_homework:
        for i1 in range(1, nrows):
            xuehao = int(table.cell(i1, 0).value)  # 获取学号单元格的值
            stuname = table.cell(i1, 1).value  # 获取姓名单元格的值
            sheet_test.write(i1, 0, xuehao)
            sheet_test.write(i1, 1, stuname)
            if homework[xuehao] == 1:
                sheet_test.write(i1, n, '已交')  # 将完成与否填入表格中
            elif homework[xuehao] == 0:
                sheet_test.write(i1, n, '未交', red_style)  # 将完成与否填入表格中
        n = n + 1
        workbook.save('作业统计.xls')

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

    path_folder = ''
    path_file = ''

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

