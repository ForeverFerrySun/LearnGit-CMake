# 生成库[search]

主要生成自定义生成库，生成动态库和静态库，没有生成对应的*.cmake连接。适用于比较小的项目。

### 注意事项

**window下使用添加如下命令：**

```cmake
#windows系统动态库生成lib文件命令
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
```

在 CMake 中，通过 `add_library()` 命令可以创建静态库、动态库和模块库。这是用于将源文件编译为库，并在项目中进行组织和管理的一种方式。库可以在同一项目内被多个目标使用，也可以为不同的项目提供共享功能。以下是关于如何通过 CMake 创建库以及如何将其连接到可执行文件的优化整理。

### **`add_library()` 创建库文件**

#### `add_library()` 创建库目标：

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

#### [CMake - add_library() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/add_library)

- **`<name>`**: 库目标的逻辑名称，必须在项目中全局唯一。生成的库文件名根据平台约定命名（如 Linux 上的 `lib<name>.a`，Windows 上的 `<name>.lib`）。
- **`STATIC`**: 创建静态库，即编译时将目标文件打包为一个档案，在链接时使用。
- **`SHARED`**: 创建动态库，即运行时加载的共享库（例如 `.so` 或 `.dll` 文件）。
- **`MODULE`**: 创建模块库，不用于链接其他目标，但可以在运行时动态加载（如插件系统）。

如果没有指定库类型，则根据 `BUILD_SHARED_LIBS` 变量的值自动确定。如果 `BUILD_SHARED_LIBS=ON`，则创建动态库，否则创建静态库。

#### 生成静态库/动态库

```cmake
# 设置生成库
add_library(${PROJECT_NAME}
    SHARED
    # STATIC
    BinarySearch.cpp
    InsertionSearch.cpp
    SequentialSearch.cpp
)

# 设定动态链接库的存储路径
set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
    # static静态库
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
    )

# 将头文件粘贴到指定目录
file(GLOB HEARD "*.h")
file(COPY ${HEARD} DESTINATION ${CMAKE_BINARY_DIR}/../include)
```



### `set_target_properties`设置目标的属性

可以配置目标（如可执行文件、库等）的各种属性，例如输出目录、编译选项、链接选项等。

```scss
set_target_properties(target1 target2 ...
                      PROPERTIES prop1 value1
                      prop2 value2 ...)
```

#### [CMake - set_target_properties() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/set_target_properties)

- **`OUTPUT_NAME`**: 设置目标的输出名称。  
- **`ARCHIVE_OUTPUT_DIRECTORY`**: 设置静态库的输出目录。 
- **`LIBRARY_OUTPUT_DIRECTORY`**: 设置共享库的输出目录。  
- **`RUNTIME_OUTPUT_DIRECTORY`**: 设置可执行文件的输出目录。 
- **`COMPILE_FLAGS`**: 设置编译选项。  
- **`LINK_FLAGS`**: 设置链接选项。
- **`POSITION_INDEPENDENT_CODE`**: 设置目标是否生成位置无关代码（PIC）。  

```
# 设定动态链接库的存储路径
set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
    # static静态库
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
    )
```



### **`target_include_directories()`**头文件公开

使用 `target_include_directories()` 命令将库的头文件路径公开给需要使用该库的目标。

将包含目录添加到目标。

```cmake
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

```

#### [CMake - target_include_directories() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/target_include_directories)

指定编译给定目标时要使用的包含目录。

- **`target`**: 必须是由 [`add_executable()`] 或 [`add_library()`]等命令创建的，并且不能是 [ALIAS target](https://runebook.dev/zh/docs/cmake/manual/cmake-buildsystem.7#alias-targets) 。

- **`PRIVATE`**: 头文件仅对当前目标可见。
- **`PUBLIC`**: 头文件对当前目标和所有依赖该目标的目标都可见。
- **`INTERFACE`**: 头文件仅对依赖该目标的目标可见。

#### 将头文件进行共享

```cmake
# 在 common 库的 CMakeLists.txt 中
target_include_directories(common
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # 将 include 目录公开给依赖者
)
```



### `set()`设置文件输出路径

#### 1. **设置可执行文件输出路径**

用于设置所有可执行文件的输出路径：

```cmake
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
```

#### 2. **设置静态库输出路径**

用于设置静态库的输出路径：

```cmake
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
```

### `set()`设置文件后缀名

#### 1. **设置不同版本库文件的后缀名**

设置 Debug 和 Release 版本下生成的库文件后缀名：

```cmake
set(CMAKE_DEBUG_POSTFIX "_d")    # Debug 库文件后缀
set(CMAKE_RELEASE_POSTFIX "_r")  # Release 库文件后缀
```

#### 2. **设置不同版本可执行文件的后缀名**

为特定目标的可执行文件在不同版本下设置后缀名：

```cmake
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")
```

#### 3. **设置安装目录 `CMAKE_INSTALL_PREFIX`**

配置项目的安装路径，指定不同类型的文件（如动态库、静态库、可执行文件、头文件等）的安装目录（详细见sort）：

```cmake
set(CMAKE_INSTALL_PREFIX <你要安装的路径>)  # 安装根路径

install(TARGETS MyLib
    EXPORT MyLibTargets
    LIBRARY DESTINATION lib      # 动态库安装路径
    ARCHIVE DESTINATION lib      # 静态库安装路径
    RUNTIME DESTINATION bin      # 可执行文件安装路径
    PUBLIC_HEADER DESTINATION include  # 头文件安装路径
)
```

- **`LIBRARY`**：动态库的安装路径。
- **`ARCHIVE`**：静态库的安装路径。
- **`RUNTIME`**：可执行文件的安装路径。
- **`PUBLIC_HEADER`**：头文件的安装路径。

### `set()`设置安装路径

#### 1. **默认安装路径说明**

`CMAKE_INSTALL_PREFIX` 的默认值如下：

- **Unix**: `/usr/local`
- **Windows**: `C:/Program Files/${PROJECT_NAME}`

#### 2. **可选的安装路径配置**

如果不使用默认路径，`DESTINATION` 后的路径可以根据需要自行制定。可以用 `set()` 方法提前设置自定义安装路径：

```cmake
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)  # 自定义安装路径
```

- **`EXECUTABLE_OUTPUT_PATH`** 和 **`CMAKE_RUNTIME_OUTPUT_DIRECTORY`** 可以二选一，但通常推荐使用 **`CMAKE_RUNTIME_OUTPUT_DIRECTORY`** 来统一管理所有可执行文件的输出路径。
- **`POSTFIX`** 后缀设置可帮助区分 Debug 和 Release 版本文件，便于开发者管理不同版本的文件。
- **`install()`** 指令允许为目标设置特定的安装路径，使项目构建后可以方便地将生成的文件部署到合适的目录。

优化后的设置使项目生成、版本区分、以及安装路径都更灵活统一。



### `CMAKE_RUNTIME_OUTPUT_DIRECTORY` 和 `EXECUTABLE_OUTPUT_PATH`区别

#### **相同点**：

- 两者都用于指定生成的可执行文件的输出路径。

#### **不同点**：

1. **全局性 vs. 目标特定**：

   - **`CMAKE_RUNTIME_OUTPUT_DIRECTORY`** 是一个**全局变量**，适用于整个项目的所有可执行文件（包括主程序、测试程序等）。它为项目中所有可执行文件设置统一的输出目录。
   - **`EXECUTABLE_OUTPUT_PATH`** 是**目标特定的属性**，仅用于指定某个具体目标（可执行文件）的输出路径。

2. **优先级**：

   - **`EXECUTABLE_OUTPUT_PATH`** 的优先级更高。如果同时设置了 `CMAKE_RUNTIME_OUTPUT_DIRECTORY` 和 `EXECUTABLE_OUTPUT_PATH`，则某个特定目标的输出会以 `EXECUTABLE_OUTPUT_PATH` 为准。

3. **使用方式**：

   - **`CMAKE_RUNTIME_OUTPUT_DIRECTORY`**：常用于项目中有多个可执行文件，想统一指定所有可执行文件的输出路径时使用。

     ```cmake
     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
     ```

   - **`EXECUTABLE_OUTPUT_PATH`**：常用于针对单个可执行文件的输出路径需求时使用。

     ```cmake
     set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/custom_output")
     ```

- **`CMAKE_RUNTIME_OUTPUT_DIRECTORY`** 影响全局的可执行文件输出路径。
- **`EXECUTABLE_OUTPUT_PATH`** 影响特定目标的可执行文件输出路径，优先级更高。



# 链接库[search]

### `target_link_libraries`链接库

​	在CMake中，将外部库或自定义库与项目进行链接是常见的操作。通过使用 `target_link_libraries()` 命令，可以指定要链接的库及其顺序，确保在构建时正确解析依赖关系。以下是如何优化使用 `target_link_libraries()` 的整理。

```cmake
target_link_libraries(<target> [item1 [item2 [...]]]
                      [PRIVATE|PUBLIC|INTERFACE] <lib>)
```

#### [target_link_libraries() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/target_link_libraries)

- **`<target>`**：要链接的目标（如可执行文件或库）。
- **`PRIVATE`**：仅对目标的私有部分可见。链接库只在目标内部使用，依赖库不会传播。
- **`PUBLIC`**：对目标和依赖目标都可见。链接库对该目标和所有依赖目标都可见。
- **`INTERFACE`**：仅对依赖目标可见。该目标本身不会链接库，但依赖它的目标会。

```cmake
target_link_libraries(MyApp PRIVATE MyLib)  # MyLib仅对MyApp可见
target_link_libraries(MyApp PUBLIC MyLib)   # MyLib对MyApp和依赖MyApp的目标可见
target_link_libraries(MyLib INTERFACE MyOtherLib)  # MyLib依赖MyOtherLib，但MyLib本身不链接MyOtherLib
```

CMake会在标准库路径下寻找这些库。

如果你在项目中创建了自己的库，可以通过 `target_link_libraries()` 将它与可执行文件或其他库链接：

```cmake
add_library(MyLib STATIC mylib.cpp)
add_executable(MyApp main.cpp)

# 链接自定义静态库MyLib到可执行文件MyApp
target_link_libraries(MyApp PRIVATE MyLib)
```

- **`PRIVATE`**：MyLib只对MyApp内部可见，依赖MyApp的目标不会继承这个库。

#### 1. **传递库的依赖**

当一个库依赖其他库时，使用 `PUBLIC` 或 `INTERFACE` 能传递依赖，避免手动链接所有依赖库。

```cmake
add_library(HelloLib hello.cpp)
target_link_libraries(HelloLib PUBLIC UtilsLib)  # HelloLib依赖UtilsLib

add_executable(MyApp main.cpp)
target_link_libraries(MyApp HelloLib)  # MyApp自动链接HelloLib及其依赖的UtilsLib
```

#### 2. **链接顺序**

CMake在构建时按照传递顺序链接库，因此顺序很重要。如果一个库依赖于另一个库，依赖库必须在先：

```cmake
target_link_libraries(MyApp LibB LibA)  # LibA必须先于LibB被链接
```

#### 3. **条件链接**

可以使用 `if` 语句来根据不同的平台或条件链接不同的库：

```cmake
if(WIN32)
    target_link_libraries(MyApp ws2_32)  # Windows下链接Winsock库
elseif(UNIX)
    target_link_libraries(MyApp pthread)  # Linux下链接pthread库
endif()
```

#### 4. **使用 `find_package()` 结合**

**(详细信息见sort中内容)**

`find_package()` 能查找系统中的库，并自动设置库路径和依赖变量，然后通过 `target_link_libraries()` 进行链接：

```cmake
find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(MyApp PRIVATE Boost::filesystem)
```



### `include_directories`包含头文件路径

将包含目录添加到构建中。`include_directories` 是 CMake 中的一个命令，用于向编译器添加包含目录（include directories）。这些目录会被添加到编译器的搜索路径中，以便在编译源文件时能够找到头文件。

```css
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
```

#### [nclude_directories() [zh\] (runebook.dev)](https://runebook.dev/zh/docs/cmake/command/include_directories)

- **`AFTER` 或 `BEFORE`**: 指定添加包含目录的位置。默认情况下，目录会被添加到现有的包含目录列表的末尾（即 `AFTER`）。如果使用 `BEFORE`，则目录会被添加到列表的开头。
- **`SYSTEM`**: 如果指定 `SYSTEM`，CMake 会告诉编译器这些目录是系统包含目录，这可能会影响编译器的警告行为。
- **`dir1 dir2 ...`**: 要添加的包含目录列表。

#### 设置包含头文件路径

```cmake
include_directories(${PROJECT_SOURCE_DIR}/src/include)
```



### `link_directories`包含库的路径

添加链接器将在其中查找库的目录。

```css
link_directories([AFTER|BEFORE] directory1 [directory2 ...])
```

添加链接器应在其中搜索库的路径。给定此命令的相对路径被解释为相对于当前源目录 。该命令仅适用于调用后创建的目标。

- `directory1 directory2 ...`：库文件的搜索路径，可以是绝对路径，也可以是相对路径。

```cmake
# 包含动态库路径
link_directories(${PROJECT_SOURCE_DIR}/src/lib/Debug)
```



### `link_libraries` 链接到后来添加的所有目标。

将 libraries 链接到后来添加的所有目标。

```css
link_libraries([item1 [item2 [...]]]
               [[debug|optimized|general] <item>] ...)
```

- `[item1 [item1 [...]]]`：需要链接的库名列表，可以是库的路径、库的名称、或者是由 `find_package()` 导出的库变量名。

```cmake
# 链接静态库
link_libraries(search)
```



# 项目1（search)

## 运行步骤：

1. 运行编译src中的CMakeLists可以生成对应的静态库或动态库
2. 检查当前CMakeLists链接库是否正确，在当前文件夹下编译运行。

**注意：使用动态库时，确保 `.dll` 文件在可执行文件可访问的路径上，如放在同一目录或通过 `PATH` 环境变量指定的目录中。**
