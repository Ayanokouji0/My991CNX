# 功能介绍
该项目是参考同学们熟悉的casio991CNX计算器，实现了基本的加、减、乘、除、乘方、对数、绝对值、六种三角函数以及定积分等运算，设计了几个键以便于存储数据，以及history和ans按键用于回溯之前的结算结果。进一步地，我们实现了基本函数的图像绘制功能，这是在casio991CNX基础上做出的拓展。同时，我们对用户使用体验进行了优化，通过键盘上的按键与对应ui界面的链接，让用户尽可能便捷的完成计算，具体的按键对应规则也在introduction界面有详细的解释。
# 模块与类设计细节
整个作业可大体上分为三个模块，分别是实现运算功能、完成绘图功能、设计存储与历史。
## 运算功能

## 绘图功能

## 存储与历史
这个模块主要由history_memory类和save_input类组成，在mainwindow的主界面上表现为A、B、C三个存储变量键，Save键以输入存储变量的值，Ans键以暂存最后一次计算结果的值以及History键以回溯前10次计算结果的值，便于在运算中调用之前计算的结果。
- history_memory类：
主体是一个QVector类的my_vector，以及四个变量memory_a、memory_b、memory_c、memory_ans，同时将该类与exptree类中按下’=’触发slot_eval函数这一事件相关联，在slot_eval函数中调用history_memory类的内置函数将新结果存入my_vector中。
- save_input类：由一个QFormLayout的指针以及三个依次对应A、B、C的QLabel和QLineEdit组成，然后通过设计getStrings函数获得输入的三个字符串。
- ![History界面展示](https://github.com/Flying-dragon-boxing/My991CNX/blob/main/pictures/History%E7%95%8C%E9%9D%A2%E5%B1%95%E7%A4%BA.png)
- 显示History的实现：使用QTextEdit类，从my_vector中由后往前加入计算结果，点击Save按键弹出一个窗口依次显示最近10次计算结果。
- ![Save界面展示](https://github.com/Flying-dragon-boxing/My991CNX/blob/main/pictures/Save界面展示.png)
- 存储与调用A、B、C、Ans四个变量的实现：使用Save键调出save_input类中的QFormLayout，在QLineEdit中对应的存入变量后面输入想要存储的数，遂调用getStrings函数获得输入三个字符串组成的QStringList，再调用history_memory类内置的函数将三个字符串转化为double类型后依次存入对应的memory变量中。Ans变量返回my_vector容器中的最后一个元素。

# 小组分工
- 任泓旭：
- 张立儒：
- 鲁兆昕：设计了数据存储与回溯计算历史功能，完成了键盘上按键与对应ui界面的链接

# 项目总结与反思

