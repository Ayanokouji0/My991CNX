# 功能介绍

该项目是参考同学们熟悉的casio991CNX计算器，实现了基本的加、减、乘、除、乘方、对数、绝对值、六种三角函数以及定积分等运算，设计了几个键以便于存储数据，以及history和ans按键用于回溯之前的结算结果。进一步地，我们实现了基本函数的图像绘制功能，这是在casio991CNX基础上做出的拓展。同时，我们对用户使用体验进行了优化，通过键盘上的按键与对应ui界面的链接，让用户尽可能便捷的完成计算，具体的按键对应规则也在introduction界面有详细的解释。

# 模块与类设计细节
整个作业可大体上分为三个模块，分别是界面显示，实现运算功能、完成绘图功能、设计存储与历史。

## 界面显示
- `MJaxAdaptor`和`TexSvg`类：这两个类是用来实现LaTeX公式的渲染的，`MJaxAdaptor`类是对MathJax库的封装，`TexSvg`类是对MathJax的SVG渲染的封装，这两个类的主要作用是把LaTeX公式转换为矢量图，然后在`QLabel`上显示出来。
- `TexSvg`类：处理了主界面发来的渲染信号，并返回SVG矢量图。
- `MJaxAdaptor`类：利用`QWebEngineView`类，接受`TexSvg`发来的信号，然后调用MathJax实现渲染。

## 运算功能
这个模块首先由`exptree`类和`exptree::node`类组成，然后由`mainwindow`类与`exptree`类相关联，实现计算器的基本运算功能。特别地，定积分采用了Romberg积分方法，效率和精度都较高。

- `exptree`类：这是一个表达式树，包含根节点`root`，选中的节点`cur`，有成员函数`eval`可以求值，`to_latex`可以把表达式树转换为公式，`hist_mem`存储历史结果。此外还有槽函数`next`，`prev`，`del`，`all_clear`，`add_oper`，`add_number`用于切换表达式选中的位置，增删表达式树的节点
- `exptree::node`类：是`number`，`oper`，`blank`，`variable`的基类。通过递归调用来实现表达式的求值和转换为LaTeX公式。
- `integral`函数：是Romberg积分函数

## 绘图功能

## 存储与历史
这个模块主要由`history_memory`类和`save_input`类组成，在`mainwindow`的主界面上表现为A、B、C三个存储变量键，Save键以输入存储变量的值，Ans键以暂存最后一次计算结果的值以及History键以回溯前10次计算结果的值，便于在运算中调用之前计算的结果。

- `history_memory`类：
主体是一个`QVector`类的`my_vector`，以及四个变量`memory_a`、`memory_b`、`memory_c`、`memory_ans`，同时将该类与`exptree`类中按下’=’触发`slot_eval`函数这一事件相关联，在`slot_eval`函数中调用`history_memory`类的内置函数将新结果存入my_vector中。
- `save_input`类：由一个`QFormLayout`的指针以及三个依次对应A、B、C的`QLabel`和`QLineEdit`组成，然后通过设计`getStrings`函数获得输入的三个字符串。
- ![History界面展示](https://github.com/Flying-dragon-boxing/My991CNX/blob/main/pictures/History%E7%95%8C%E9%9D%A2%E5%B1%95%E7%A4%BA.png)
- 显示History的实现：使用`QTextEdit`类，从`my_vector`中由后往前加入计算结果，点击Save按键弹出一个窗口依次显示最近10次计算结果。
- ![Save界面展示](https://github.com/Flying-dragon-boxing/My991CNX/blob/main/pictures/Save界面展示.png)
- 存储与调用A、B、C、Ans四个变量的实现：使用Save键调出`save_input`类中的`QFormLayout`，在`QLineEdit`中对应的存入变量后面输入想要存储的数，遂调用`getStrings`函数获得输入三个字符串组成的`QStringList`，再调用`history_memory`类内置的函数将三个字符串转化为`double`类型后依次存入对应的`memory`变量中。Ans变量返回`my_vector`容器中的最后一个元素。

# 小组分工
- 任泓旭：基本的计算功能的实现，绘制了计算器的UI界面背景和各按钮，完成了计算器的整体框架搭建，实现了调用MathJax库将公式渲染为矢量图并显示。
- 张立儒：
- 鲁兆昕：设计了数据存储与回溯计算历史功能，完成了键盘上按键与对应ui界面的链接

# 项目总结与反思
* 本来计划使输入完全和函数计算器的输入方式一致，但是表达式的解析在加入了积分、三角函数等操作之后确实是一个比较难而且需要一定理论基础的工作，所以最后采用了一个变通的方法（某种意义上和逆波兰表达式很像），每个符号都是一个树节点，这样便于求值，也容易转换与LaTeX公式。* 表达式中选中节点的切换个人认为是一个比较难的问题，因为要考虑到各种情况：自己是叶节点的情况（这里面甚至分为是否为母节点的最后一个叶节点），自己有子节点的情况都要分开讨论，设计比较费时，代码量也比较大。
* 渲染公式方面，参考了其他开源项目后，决定使用`QWebEngineView`加调用JavaScript库MathJax的方式，学习对应开源项目时学到了很多。

