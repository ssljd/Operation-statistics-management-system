import os
import xlrd
import xlwt
import pymysql
import matplotlib.pyplot as plt



# 获取指定文件夹下的文件名，并将文件名储存在list1中，形成一个列表
def listdir(path, list1):
    for p, name, files in os.walk(path, topdown=False):
        # 判断文件名是否为doc或者docx
        for file in os.listdir(p):
            if os.path.splitext(file)[1] == '.doc' or os.path.splitext(file)[1] == '.docx':
                # 特定类型的文件需要用os.path.splitext()函数将路径拆分，拆分为文件名和拓展名，[0]表示文件名，[1]表示拓展名
                list1.append(file)  # 如果是两者中的一种，则将其加在列表中

def single(list1):
    data = xlrd.open_workbook('AI201学生名单.xls')  # 打开当前目录下名为test的文档，即学生信息
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
    b = (25 - a) / 25 * 100
    print('提交人数：', 25 - a)
    print('未提交人数：', a)
    print('提交率为：', b, '%')  # 计算提交率
    print('*' * 40)
    list_all = [len(list1), len(list2)]
    return student, list_all

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

def visualization():
    plt.figure(figsize=(8, 8))


path = 'C:/Users/sljd/Desktop/Code_library/python/Leisure code/作业统计管理系统/作业一'
list = []
listdir(path, list)
print(list)
single(list)
