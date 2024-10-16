## CMake编译生成应用程序

### CMake的项目流程

- 设置项目的最小版本
- 设置项目信息
- 设置编译信息
- 设置源文件/头文件
- 生成可执行文件

### 1. 设置项目的最小版本

#### `cmake_minimum_required()`设置项目版本命令（[详细情况](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html)）

```
cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])
```

#### [cmake_minimum_required() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/cmake_minimum_required)

此命令指定 CMake 构建系统的最低版本要求。如果运行的 CMake 版本低于 `<min>` 版本，构建将会终止并提示错误。

- **`VERSION <min>`**: 指定所需的最低版本号。
- **`FATAL_ERROR`**: 对 CMake 2.6 及以上版本支持，如果版本不满足要求，则停止并报告错误。

#### 设置项目最小版本为3.20

```
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
```



### 2. 设置项目信息

#### `project()`设置项目信息（[详细情况](https://cmake.org/cmake/help/latest/command/project.html#)）

设置项目的名称，并将其存储在变量[`PROJECT_NAME`]中。当从顶层调用`CMakeLists.txt`时，还将项目名称存储在变量`CMAKE_PROJECT_NAME`中。

```
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])

```

#### [project() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/project)

- **`PROJECT-NAME`**: 项目名称，设置后可以通过变量 `PROJECT_NAME` 和 `CMAKE_PROJECT_NAME` 访问。
- **`VERSION`**: 设置项目的版本号（可选）。
- **`DESCRIPTION`**: 项目的描述（可选）。
- **`HOMEPAGE_URL`**: 项目主页 URL（可选）。
- **`LANGUAGES`**: 指定要使用的编程语言（如 `C`、`CXX`）。

#### 设置项目为CMakeProject,版本为1.0.0

```
project(CMakeProject
	VERSION 1.0.0
	DESCRIPTION "An example C++ project using CMake"
	LANGUAGES CXX)
```



### 3. 设置编译信息

#### `set()`设置信息变量（[详细情况](https://cmake.org/cmake/help/latest/command/set.html)）

```
# 设置正常变量
set(<variable> <value>... [PARENT_SCOPE])
# 设置缓存条目
set(<variable> <value>... CACHE <type> <docstring> [FORCE])
# 设置环境变量
set(ENV{<variable>} [<value>])
```

#### [set() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/set)

- 在当前函数或目录范围内设置给定的 `<variable>` 。
- 设置给定的缓存 `<variable>` （缓存条目）。由于缓存条目旨在提供用户可设置的值，因此默认情况下不会覆盖现有的缓存条目。使用 `FORCE` 选项覆盖现有条目。
- 将 [`Environment Variable`] 设置为给定值。 `$ENV{<variable>}` 的后续调用将返回这个新值。

#### 设置 C++17 标准

- **`set(CMAKE_CXX_STANDARD 17) `** 将C++标准设置为C++17。项目将使用C++17标准进行编译。
- **`set(CMAKE_CXX_STANDARD_REQUIRED ON) `**确保编译器必须支持C++17标准。如果编译器不支持C++17，构建过程将会失败。
- **`set(CMAKE_CXX_EXTENSIONS OFF) `**禁用了编译器的特定扩展。

这意味着编译器将不会使用任何特定于供应商的C++扩展，而是严格遵循C++17标准。

```
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

#### 警告设置

为了避免编译时的编码问题，特别是在 Windows 下使用 MSVC 编译器时，可以通过以下方式设置 UTF-8 编码并解决常见的警告：

```
if(MSVC)
    # 设置UTF-8编码并消除C4819警告
    add_compile_options("/utf-8" "/W3" "/Zc:__cplusplus" "/EHsc")
endif()


```



### 4. 设置源文件/头文件

#### 源文件/头文件

指定源文件/头文件路径，可以使用`set`/`file`或者直接在`add_executable`添加文件

#### 设置源文件和头文件

```
set(include
    include/8queenF.h
)
set(src
    main.cpp
    src/8queenF.cpp
)
```



### 5. 生成可执行文件

#### `add_executable()`生成可执行文件（[详细情况](https://cmake.org/cmake/help/latest/command/add_executable.html)）

```
# 普通可执行文件
add_executable(<name> <options>... <sources>...)
# 导入的可执行文件
add_executable(<name> IMPORTED [GLOBAL])
# 别名可执行文件
add_executable(<name> ALIAS <target>)
```

#### [add_executable() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/add_executable)

- **`name`**: 可执行文件的名称，必须全局唯一。
- **`WIN32`**: 用于 Windows 平台，创建 GUI 应用程序而非控制台应用程序。
- **`MACOSX_BUNDLE`**: 用于 macOS 系统，创建一个 GUI 应用程序的 bundle。
- **`EXCLUDE_FROM_ALL`**: 如果指定，可执行文件不会被默认构建。

#### 连接源文件和头文件，生成运行程序

```
add_executable(${PROJECT_NAME} ${include} ${src})
```





# 生成可执行文件

add_executable(${PROJECT_NAME} ${include} ${src})

## 项目1

### 八皇后问题描述

在一个8×8的棋盘上放置8个皇后，使得每个皇后都不在同一行、同一列和同一对角线上。

### 解决方案

八皇后问题通常使用回溯算法来解决。回溯算法是一种通过尝试所有可能的配置来找到解决方案的方法。如果当前配置不满足条件，算法会回溯到上一步，尝试另一种配置。

### 回溯算法的基本步骤

1. **初始化**：从第一行开始，尝试在每一列放置一个皇后。
2. **检查冲突**：在放置皇后之前，检查当前位置是否与已经放置的皇后冲突（即在同一行、同一列或同一对角线上）。
3. **放置皇后**：如果没有冲突，放置皇后，并继续到下一行。
4. **回溯**：如果当前行无法放置皇后（即所有列都冲突），则回溯到上一行，尝试在上一行的下一列放置皇后。
5. **完成**：如果成功放置了8个皇后，则找到一个解决方案。

