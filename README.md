# LearnGit-CMake

学习使用CMake，这里记录一下

### CMake 基础信息设置

在使用 CMake 构建项目时，初始设置至关重要，它包括项目的最小版本、项目名称、编译选项和可执行文件的生成等。以下是关于 CMake 基础设置的详细说明和优化建议。

#### 1. **CMake 最小版本**

```cmake
cmake_minimum_required(VERSION <min> [<policy_max>] [FATAL_ERROR])
```

此命令指定 CMake 构建系统的最低版本要求。如果运行的 CMake 版本低于 `<min>` 版本，构建将会终止并提示错误。

- **`VERSION <min>`**: 指定所需的最低版本号。
- **`FATAL_ERROR`**: 对 CMake 2.6 及以上版本支持，如果版本不满足要求，则停止并报告错误。

示例：

```cmake
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
```

#### 2. **设置项目名称**

```cmake
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```

- **`PROJECT-NAME`**: 项目名称，设置后可以通过变量 `PROJECT_NAME` 和 `CMAKE_PROJECT_NAME` 访问。
- **`VERSION`**: 设置项目的版本号（可选）。
- **`DESCRIPTION`**: 项目的描述（可选）。
- **`HOMEPAGE_URL`**: 项目主页 URL（可选）。
- **`LANGUAGES`**: 指定要使用的编程语言（如 `C`、`CXX`）。

示例：

```cmake
project(MyProject 
    VERSION 1.0.1 
    DESCRIPTION "My sample project with C++"
    HOMEPAGE_URL "https://github.com/user/myproject"
    LANGUAGES CXX)
```

该项目定义了名称、版本、描述和主页，并使用 C++ 作为编程语言。

#### 3. **C++ 版本Qt内容设置**

在 CMake 中，可以通过以下选项为项目指定特定的 C++ 版本以及编译器选项：

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

- **`CMAKE_CXX_STANDARD`**: 设置 C++ 标准版本（如 17、20 等）。
- **`CMAKE_CXX_STANDARD_REQUIRED`**: 确保所指定的 C++ 标准是强制要求的，如果编译器不支持将会出错。
- **`CMAKE_CXX_EXTENSIONS`**: 禁用编译器特定的语言扩展，确保使用标准 C++ 语法。

此外，对于 Qt 项目，还可以自动处理 Qt 的相关编译器工具：

```cmake
set(CMAKE_AUTOUIC ON)  # 自动处理 .ui 文件
set(CMAKE_AUTOMOC ON)  # 自动处理 MOC
set(CMAKE_AUTORCC ON)  # 自动处理资源文件 (.qrc)
```

#### 4. **编译器设置**

为了避免编译时的编码问题，特别是在 Windows 下使用 MSVC 编译器时，可以通过以下方式设置 UTF-8 编码并解决常见的警告：

```cmake
if(MSVC)
    # 设置UTF-8编码并消除C4819警告
    add_compile_options("/utf-8" "/W3" "/Zc:__cplusplus" "/EHsc")
endif()
```

#### 5. **生成可执行文件**

通过 `add_executable()` 命令生成可执行文件。它的基本格式如下：

```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL] [source1] [source2 ...])
```

- **`name`**: 可执行文件的名称，必须全局唯一。
- **`WIN32`**: 用于 Windows 平台，创建 GUI 应用程序而非控制台应用程序。
- **`MACOSX_BUNDLE`**: 用于 macOS 系统，创建一个 GUI 应用程序的 bundle。
- **`EXCLUDE_FROM_ALL`**: 如果指定，可执行文件不会被默认构建。

示例：

```cmake
add_executable(MyApp main.cpp app.cpp)
```

此外，还可以导入外部可执行文件或者为可执行文件创建别名：

```cmake
add_executable(MyApp IMPORTED)  # 导入外部可执行文件
add_executable(MyAlias ALIAS MyApp)  # 为可执行文件创建别名
```

#### 6. **完整示例**

下面是一个完整的 CMake 项目设置示例，展示了如何定义项目、指定 C++ 标准、处理编码问题以及生成可执行文件：

```cmake
# CMake 最低版本
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# 项目信息
project(MyProject
    VERSION 1.0.0
    DESCRIPTION "An example C++ project using CMake"
    LANGUAGES CXX)

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译器设置：针对 MSVC 处理 UTF-8 编码和警告
if(MSVC)
    add_compile_options("/utf-8" "/W3" "/Zc:__cplusplus" "/EHsc")
endif()

# 生成可执行文件
add_executable(MyApp main.cpp app.cpp)
```





### CMake 创建库

在 CMake 中，通过 `add_library()` 命令可以创建静态库、动态库和模块库。这是用于将源文件编译为库，并在项目中进行组织和管理的一种方式。库可以在同一项目内被多个目标使用，也可以为不同的项目提供共享功能。以下是关于如何通过 CMake 创建库以及如何将其连接到可执行文件的优化整理。

#### 1. **`add_library()` 基本语法**

`add_library()` 用于创建库目标：

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

- **`<name>`**: 库目标的逻辑名称，必须在项目中全局唯一。生成的库文件名根据平台约定命名（如 Linux 上的 `lib<name>.a`，Windows 上的 `<name>.lib`）。
- **`STATIC`**: 创建静态库，即编译时将目标文件打包为一个档案，在链接时使用。
- **`SHARED`**: 创建动态库，即运行时加载的共享库（例如 `.so` 或 `.dll` 文件）。
- **`MODULE`**: 创建模块库，不用于链接其他目标，但可以在运行时动态加载（如插件系统）。

如果没有指定库类型，则根据 `BUILD_SHARED_LIBS` 变量的值自动确定。如果 `BUILD_SHARED_LIBS=ON`，则创建动态库，否则创建静态库。

#### 2. **组织项目结构**

为了更好地组织代码和库，我们可以将不同的功能模块放在单独的子目录中，每个子目录包含自己的 `CMakeLists.txt`。通过顶层 `CMakeLists.txt` 使用 `add_subdirectory()` 命令引入这些子目录。

项目目录结构示例：
```
/MyProject
    /src
        /common
            common.cpp
            CMakeLists.txt
        /app
            main.cpp
            CMakeLists.txt
    CMakeLists.txt
```

顶层 `CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.12)
project(MyProject)

# 添加子目录
add_subdirectory(src/common)
add_subdirectory(src/app)
```

`src/common/CMakeLists.txt`（创建库）：

```cmake
# 定义源文件
set(SRC_LIST common.cpp)

# 创建静态库 common
add_library(common STATIC ${SRC_LIST})
```

`src/app/CMakeLists.txt`（创建可执行文件并链接库）：

```cmake
# 定义源文件
set(APP_SRC main.cpp)

# 创建可执行文件
add_executable(MyApp ${APP_SRC})

# 链接 common 库
target_link_libraries(MyApp PRIVATE common)
```

#### 3. **`target_include_directories()`**

使用 `target_include_directories()` 命令将库的头文件路径公开给需要使用该库的目标。

```cmake
# 在 common 库的 CMakeLists.txt 中
target_include_directories(common
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # 将 include 目录公开给依赖者
)
```

`PUBLIC`、`PRIVATE` 和 `INTERFACE` 关键字的含义与 `target_link_libraries()` 类似：
- **`PRIVATE`**: 头文件仅对当前目标可见。
- **`PUBLIC`**: 头文件对当前目标和所有依赖该目标的目标都可见。
- **`INTERFACE`**: 头文件仅对依赖该目标的目标可见。

#### 4. **`target_link_libraries()` 连接库**

通过 `target_link_libraries()` 命令将库与可执行文件或其他库链接。可以使用 `PRIVATE`、`PUBLIC` 或 `INTERFACE` 控制库的可见性。

```cmake
# 在 src/app/CMakeLists.txt 中链接库
target_link_libraries(MyApp PRIVATE common)
```

- **`PRIVATE`**: `common` 库只对 `MyApp` 可见。
- **`PUBLIC`**: `common` 库对 `MyApp` 以及依赖 `MyApp` 的所有目标可见。
- **`INTERFACE`**: `MyApp` 本身不会链接 `common`，但依赖 `MyApp` 的其他目标会链接 `common`。

#### 5. **使用 `target_sources()` 动态添加源文件**

CMake 3.11 之后可以使用 `target_sources()` 动态添加源文件，而不必在 `add_library()` 时指定所有源文件。这有助于更灵活地管理库的源文件。

```cmake
add_library(common STATIC)  # 创建库，不指定源文件
target_sources(common PRIVATE common.cpp)  # 动态添加源文件
```

#### 6. **模块库和插件**

`MODULE` 库用于创建不需要在编译时链接但可以在运行时动态加载的插件库。

```cmake
# 创建模块库
add_library(MyPlugin MODULE plugin.cpp)

# 在可执行文件中使用dlopen或类似函数动态加载插件
```

在跨平台的项目中，特别是在需要插件机制的情况下，`MODULE` 库非常有用。

#### 7. **使用 `BUILD_SHARED_LIBS` 自动化库类型**

通过设置 `BUILD_SHARED_LIBS` 变量，用户可以决定是构建静态库还是动态库，而无需修改 CMakeLists.txt。

顶层 `CMakeLists.txt` 中：

```cmake
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
```

这使用户可以通过配置选项自动选择库类型，而不必手动修改每个库的定义。

#### 8. **条件编译和平台特定库**

通过条件判断指令，可以根据操作系统选择不同的库类型或编译选项。

```cmake
if(WIN32)
    target_link_libraries(MyApp PRIVATE ws2_32)  # Windows下使用
elseif(UNIX)
    target_link_libraries(MyApp PRIVATE pthread)  # Unix平台下使用
endif()
```

#### 9. **CMake示例**

以下是一个完整的项目示例，展示如何使用 `add_library()` 创建库并将其链接到可执行文件：

```
/MyProject
    /src
        /common
            common.cpp
            common.h
            CMakeLists.txt
        /app
            main.cpp
            CMakeLists.txt
    CMakeLists.txt
```

顶层 `CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.12)
project(MyProject)

# 设置库的编译选项
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# 添加子目录
add_subdirectory(src/common)
add_subdirectory(src/app)
```

`src/common/CMakeLists.txt`：

```cmake
# 定义源文件
set(SRC_LIST common.cpp)

# 创建动态库 common
add_library(common SHARED ${SRC_LIST})

# 添加头文件目录
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
```

`src/app/CMakeLists.txt`：

```cmake
# 定义源文件
set(APP_SRC main.cpp)

# 创建可执行文件
add_executable(MyApp ${APP_SRC})

# 链接 common 库
target_link_libraries(MyApp PRIVATE common)
```

#### 10. **总结**

- `add_library()` 用于创建静态库、动态库或模块库，可以从多个源文件生成一个库目标。
- 通过 `add_subdirectory()` 和子目录中的 `CMakeLists.txt` 实现模块化管理。
- 使用 `target_include_directories()` 和 `target_link_libraries()` 将库的头文件路径和依赖关系传播给可执行目标。
- `STATIC` 和 `SHARED` 库分别对应静态库和动态库，`MODULE` 库用于插件机制。
- 使用 `BUILD_SHARED_LIBS` 变量可以灵活选择是构建静态库还是动态库。

### CMake链接库

在CMake中，将外部库或自定义库与项目进行链接是常见的操作。通过使用 `target_link_libraries()` 命令，可以指定要链接的库及其顺序，确保在构建时正确解析依赖关系。以下是如何优化使用 `target_link_libraries()` 的整理。

#### 1. **基本语法**

```cmake
target_link_libraries(<target> [item1 [item2 [...]]]
                      [PRIVATE|PUBLIC|INTERFACE] <lib>)
```

- **`<target>`**：要链接的目标（如可执行文件或库）。
- **`PRIVATE`**：仅对目标的私有部分可见。链接库只在目标内部使用，依赖库不会传播。
- **`PUBLIC`**：对目标和依赖目标都可见。链接库对该目标和所有依赖目标都可见。
- **`INTERFACE`**：仅对依赖目标可见。该目标本身不会链接库，但依赖它的目标会。

#### 2. **链接系统库**

当你需要将系统库链接到目标时，只需将库名称传递给 `target_link_libraries()`，CMake会自动找到它：

```cmake
target_link_libraries(MyApp PUBLIC m pthread)  # 链接数学库和线程库
```

CMake会在标准库路径下寻找这些库。

#### 3. **链接自定义库**

如果你在项目中创建了自己的库，可以通过 `target_link_libraries()` 将它与可执行文件或其他库链接：

```cmake
add_library(MyLib STATIC mylib.cpp)
add_executable(MyApp main.cpp)

# 链接自定义静态库MyLib到可执行文件MyApp
target_link_libraries(MyApp PRIVATE MyLib)
```

- **`PRIVATE`**：MyLib只对MyApp内部可见，依赖MyApp的目标不会继承这个库。

#### 4. **链接第三方库**

如果使用了像 `find_package()` 或 `pkg-config` 来查找第三方库，使用 `target_link_libraries()` 可以将查找到的库链接到目标：

```cmake
find_package(VTK REQUIRED)
target_link_libraries(DealWithMould PRIVATE ${VTK_LIBRARIES})
```

`VTK_LIBRARIES` 是 `find_package(VTK)` 命令导出的库列表，CMake会自动处理链接路径和库依赖。

#### 5. **PUBLIC、PRIVATE、INTERFACE 区别**

- **PRIVATE**：链接的库只对当前目标可见，依赖目标不会继承。
- **PUBLIC**：链接的库对当前目标和依赖目标都可见。
- **INTERFACE**：链接的库仅对依赖目标可见，当前目标不会实际链接该库。

```cmake
target_link_libraries(MyApp PRIVATE MyLib)  # MyLib仅对MyApp可见
target_link_libraries(MyApp PUBLIC MyLib)   # MyLib对MyApp和依赖MyApp的目标可见
target_link_libraries(MyLib INTERFACE MyOtherLib)  # MyLib依赖MyOtherLib，但MyLib本身不链接MyOtherLib
```

#### 6. **传递库的依赖**

当一个库依赖其他库时，使用 `PUBLIC` 或 `INTERFACE` 能传递依赖，避免手动链接所有依赖库。

```cmake
add_library(HelloLib hello.cpp)
target_link_libraries(HelloLib PUBLIC UtilsLib)  # HelloLib依赖UtilsLib

add_executable(MyApp main.cpp)
target_link_libraries(MyApp HelloLib)  # MyApp自动链接HelloLib及其依赖的UtilsLib
```

#### 7. **链接顺序**

CMake在构建时按照传递顺序链接库，因此顺序很重要。如果一个库依赖于另一个库，依赖库必须在先：

```cmake
target_link_libraries(MyApp LibB LibA)  # LibA必须先于LibB被链接
```

#### 8. **条件链接**

可以使用 `if` 语句来根据不同的平台或条件链接不同的库：

```cmake
if(WIN32)
    target_link_libraries(MyApp ws2_32)  # Windows下链接Winsock库
elseif(UNIX)
    target_link_libraries(MyApp pthread)  # Linux下链接pthread库
endif()
```

#### 9. **使用 `find_package()` 结合**

`find_package()` 能查找系统中的库，并自动设置库路径和依赖变量，然后通过 `target_link_libraries()` 进行链接：

```cmake
find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(MyApp PRIVATE Boost::filesystem)
```

#### 10. **示例**

完整的使用 `target_link_libraries()` 的项目配置示例如下：

```cmake
cmake_minimum_required(VERSION 3.12)
project(MyProject VERSION 1.0 LANGUAGES CXX)

# 添加源文件
add_executable(MyApp main.cpp)

# 查找并链接第三方库（例如Boost）
find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(MyApp PRIVATE Boost::filesystem)

# 创建自定义库并链接
add_library(MyLib STATIC mylib.cpp)
target_link_libraries(MyApp PRIVATE MyLib)

# 链接系统库
target_link_libraries(MyApp PRIVATE pthread)
```

#### 总结
- `target_link_libraries()` 用于将外部或自定义库链接到目标（如可执行文件或库）。
- **PRIVATE**、**PUBLIC** 和 **INTERFACE** 关键字控制库的可见性和依赖传播。
- 系统库、第三方库和自定义库均可使用该命令进行链接。
- 使用 `find_package()` 结合 `target_link_libraries()` 是处理第三方库的常见模式。





### CMake 输出路径配置及安装设置

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

#### 3. **设置动态库输出路径**
为动态库目标设置输出路径，使用 `SET_TARGET_PROPERTIES` 来对指定目标动态库单独设置：
```cmake
set_target_properties(dllname PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
```

#### 4. **设置不同版本库文件的后缀名**
设置 Debug 和 Release 版本下生成的库文件后缀名：
```cmake
set(CMAKE_DEBUG_POSTFIX "_d")    # Debug 库文件后缀
set(CMAKE_RELEASE_POSTFIX "_r")  # Release 库文件后缀
```

#### 5. **设置不同版本可执行文件的后缀名**
为特定目标的可执行文件在不同版本下设置后缀名：
```cmake
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")
```

#### 6. **设置安装目录 `CMAKE_INSTALL_PREFIX`**
配置项目的安装路径，指定不同类型的文件（如动态库、静态库、可执行文件、头文件等）的安装目录：
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

#### 7. **默认安装路径说明**
`CMAKE_INSTALL_PREFIX` 的默认值如下：
- **Unix**: `/usr/local`
- **Windows**: `C:/Program Files/${PROJECT_NAME}`

#### 8. **可选的安装路径配置**
如果不使用默认路径，`DESTINATION` 后的路径可以根据需要自行制定。可以用 `set()` 方法提前设置自定义安装路径：

```cmake
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)  # 自定义安装路径
```

- **`EXECUTABLE_OUTPUT_PATH`** 和 **`CMAKE_RUNTIME_OUTPUT_DIRECTORY`** 可以二选一，但通常推荐使用 **`CMAKE_RUNTIME_OUTPUT_DIRECTORY`** 来统一管理所有可执行文件的输出路径。
- **`POSTFIX`** 后缀设置可帮助区分 Debug 和 Release 版本文件，便于开发者管理不同版本的文件。
- **`install()`** 指令允许为目标设置特定的安装路径，使项目构建后可以方便地将生成的文件部署到合适的目录。

优化后的设置使项目生成、版本区分、以及安装路径都更灵活统一。

9. CMAKE_RUNTIME_OUTPUT_DIRECTORY 和 EXECUTABLE_OUTPUT_PATH区别

**相同点**：

- 两者都用于指定生成的可执行文件的输出路径。

**不同点**：

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

### `FILE(GLOB ...)` 

`FILE(GLOB ...)` 是 CMake 中的一个命令，用于匹配特定路径中的文件模式并生成相应的文件列表。它可以通过指定通配符（如 `*.cpp`, `*.h` 等）来捕获一组文件，并将它们存储在一个变量中。主要用法如下：

#### 1. 查找文件并存储到变量中

最常见的用法是通过 `FILE(GLOB ...)` 来查找某个路径下所有符合特定模式的文件，并将它们存储在变量中：

```cmake
file(GLOB SOURCES "./src/*.cpp")
file(GLOB HEADERS "./include/*.h")
```

这段代码会查找 `./src` 目录下的所有 `.cpp` 文件和 `./include` 目录下的所有 `.h` 文件，并将它们分别存储到 `SOURCES` 和 `HEADERS` 变量中。

#### 2. 简化源文件管理

通过 `FILE(GLOB ...)`，可以自动将整个目录下的文件添加到编译系统中，而不需要手动列出每个文件。这对于有大量源文件的项目尤为有用：

```cmake
file(GLOB SOURCES "./src/*.cpp" "./include/*.h")
add_executable(MyApp ${SOURCES})
```

这种方式可以简化 CMakeLists.txt 的管理，特别是在源文件频繁变动时，可以避免手动维护文件列表。

#### 3. 多个文件类型匹配

`GLOB` 支持匹配多个文件类型的通配符：

```cmake
file(GLOB ALL_FILES "./src/*.cpp" "./src/*.h")
```

这会将 `./src` 目录下所有 `.cpp` 和 `.h` 文件捕获到 `ALL_FILES` 变量中。

#### 4. 递归查找文件

可以使用 `GLOB_RECURSE` 来递归查找指定目录下所有子目录中的匹配文件：

```cmake
file(GLOB_RECURSE SOURCES "./src/*.cpp")
```

这会查找 `./src` 及其所有子目录中的 `.cpp` 文件。

#### 5. 在其他命令中使用

你可以将 `GLOB` 查找到的文件变量用于其他 CMake 命令中，比如 `add_library`, `target_sources` 等：

```cmake
file(GLOB SOURCES "./src/*.cpp")
add_library(MyLib ${SOURCES})
```

#### 6. 生成文件列表

`FILE(GLOB ...)` 也可以用于生成文件列表，便于其他操作，比如文件拷贝或打包：

```cmake
file(GLOB CONFIG_FILES "./config/*.conf")
install(FILES ${CONFIG_FILES} DESTINATION "/etc/myapp/")
```

这个例子中，`GLOB` 会匹配所有配置文件，并将它们安装到 `/etc/myapp/` 目录下。

#### 7. 用于构建自动化

如果你的项目结构经常变化（比如增加或删除文件），使用 `GLOB` 可以让 CMakeLists.txt 自动跟踪文件变化，无需手动更新文件列表。例如在多人协作或频繁开发迭代的项目中，它有助于保持文件列表的自动化。

#### 8. 使用 `FILE(GLOB ...)` 的注意事项

1. **不建议动态查找源文件**：
   尽管 `FILE(GLOB ...)` 看起来可以自动管理源文件，但它在实际项目中可能不是最佳实践。因为 CMake 是在配置阶段执行的，而 `GLOB` 查找文件后不会自动跟踪文件变动（例如添加或删除文件后，可能需要重新生成构建系统）。因此，如果源文件经常变化，最好手动列出文件，或者确保在文件变化时重新运行 CMake 进行更新。

2. **性能问题**：
   如果使用 `GLOB_RECURSE` 来递归查找文件，可能会导致性能问题，特别是在大型项目中，因为它会递归遍历目录树。





### CMake子目录项目管理

如果项目使用多个子目录来组织代码，可以使用 `add_subdirectory()` 命令将子目录添加到构建中：

```
add_subdirectory(src)
add_subdirectory(lib)
```





