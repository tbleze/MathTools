# 以 CPP 为基础开发的科学计算器

相关信息：     

    姓名：杨向原        
    学校：兰州大学      
    学院：信息科学与工程学院        
    学生卡号：320220942311

    姓名：李宏诚        
    学校：兰州大学      
    学院：信息科学与工程学院        
    学生卡号：320220941681

    姓名：周鸿越       
    学校：兰州大学      
    学院：信息科学与工程学院        
    学生卡号：320220942531


开发平台：Windows11,QTcreator community 15.0,VScode,TensorFlow(或者PyTorch，根据最终决定需要使用的模型进行调整）       

## 具体内容
开发流程    

    1.实现不同数据类型的数据互通√   
    2.完成不同数据类型之间的数据计算√   
    3.生成函数图像√     
    4.矩阵运算√     
    5.函数运算√     
    6.根据一个已经训练好的AI(参数约为1.5B或者更小)进行微调，使其可以辅助使用这个软件√        
    7.封装QT桌面应用

## 实现方法        
### 不同数据类型的数据互通        
通过template和使用<type_traits>库中的common::type<A,B>返回进行运算的两个数据类型中更高阶的数据类型实现        
### 不同数据类型之间的数据计算        
通过定义，目前仅仅定义了+,-,*,/，后续会加入**,&,|,~等计算        
### 生成函数图像        
通过FunctionPlotter.cpp文件和matplotlibcpp.h引入python，再通过python3.8提供的numpy以及matplotlib进行图像绘制        
### AI训练        

    1.采用了colab在服务器上进行训练     
    2.使用unsloth对模型微调进行了优化，原先对Gemma3-4B的模型要求是RTX2060以上，微调一般需要两倍的峰值消耗，而unsloth可以减少60%左右的性能消耗而且可以加速1.5倍左右，使得模型微调成为了可能      
    3.采用的数据集是https://huggingface.co/datasets/ecnu-icalk/cmm-math，这是一个中文的高中左右难度的数学问题综合性数据集，可以很好的满足中文需求       
    4.训练好的模型保存至https://huggingface.co/BigCowHorse/gemma-3-math-solver，以便后续和其他的文件一起封装使用，可以解决数学问题      
    

### QT封装        
最终实现效果描述：        

    1.拥有两级页面，第一级页面是导览图，点击上面的科学计算器、函数图像生成器或者AI使用三选一。        
    2.点击第一级页面后进入第二级页面，分别实现科学计算器、函数图像生成器以及AI语言模型的功能。
    3.还需要实现根据窗口大小对分辨率调整的功能，可以实现对各种窗口大小的适配。
    4.最终能够通过常见问题的测试。
