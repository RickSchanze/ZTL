# 介绍

ZTL是一个小型的标准库，目标是通过造轮子来提高数据结构以及cpp水平。

# 目录结构

```
├─src
│  └─include
├─testztl
└─third_party
    └─googletest-1.13.0
```

`src`用于存放项目的源文件。

`src/include`是项目的包含文件目录。

`testztl`用于存放项目的测试文件

`third_party`用于存放项目所引用的第三方库，目前的第三方库有

| 库名       | 链接                                                         |
| ---------- | ------------------------------------------------------------ |
| googletest | [google/googletest: GoogleTest - Google Testing and Mocking Framework (github.com)](https://github.com/google/googletest) |

# 食用方法

运行环境为windows,g++11.2

首先运行

`git clone https://github.com/RickSchanze/ZTL.git`

在项目文件夹内运行

`cmake -G "Unix Makefiles" -S . -B build`

`cd build`

`make`

`ctest`

即可运行测试
