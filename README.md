# LearnGit-CMake

学习使用Git和CMake
cmake 输出路径通常需要设置一下，这里记录一下：

1.设置可执行文件的输出路径：

```
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
```

2.静态库 lib 输出路径：

```
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
```

3.动态库输出路径（注意这个放在最后）：

```
SET_TARGET_PROPERTIES(dllname PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)
```

4.上面两条语句分别设置了Debug版本和Release版本下库文件的后缀名

```
set(CMAKE_DEBUG_POSTFIX "_d")    set(CMAKE_RELEASE_POSTFIX "_r")
```

5.设置了Debug版本和Release版本下可执行文件的后缀名

```
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")
```

6.设置项目名称：

PROJECT( name )

7.设置链接库名称：

target_link_libraries

例：

```
target_link_libraries(DealWithMould ${VTK_LIBRARIES}
)
target_link_libraries（myProject hello）
```

8.可执行文件名，通过指定的源文件列表构建出可执行目标文件：

```
ADD_EXECUTABLE
ADD_EXECUTABLE(main main.cpp context.cpp patten.cpp patten.hpp )
```

9.为生成的target配置安装目录 CMAKE_INSTALL_PREFIX

```
SET(CMAKE_INSTALL_PREFIX <你要安装的路径>)
install(TARGETS MyLib
EXPORT MyLibTargets
LIBRARY DESTINATION lib  # 动态库安装路径
ARCHIVE DESTINATION lib  # 静态库安装路径
RUNTIME DESTINATION bin  # 可执行文件安装路径
PUBLIC_HEADER DESTINATION include  # 头文件安装路径
)
```

LIBRARY, ARCHIVE, RUNTIME, PUBLIC_HEADER是可选的，可以根据需要进行选择。 DESTINATION后面的路径可以自行制定，根目录默认为CMAKE_INSTALL_PREFIX,可以试用set方法进行指定，如果使用默认值的话，Unix系统的默认值为 /usr/local, Windows的默认值为 c:/Program Files/${PROJECT_NAME}。比如字linux系统下若LIBRARY的安装路径指定为lib,即为/usr/local/lib。所以要安装mymath mymathapp我们可以这样写

10.`CMAKE\_RUNTIME\_OUTPUT\_DIRECTORY`和`EXECUTABLE\_OUTPUT\_PATH`都是CMake中用于指定可执行文件输出路径的变量，但它们在用法和作用上有一些区别。

1. \``CMAKE\_RUNTIME\_OUTPUT\_DIRECTORY`\`是一个全局变量，用于指定所有可执行文件（包括主程序和测试程序）的输出路径。通过设置\``CMAKE\_RUNTIME\_OUTPUT\_DIRECTORY`\`，可以将所有生成的可执行文件放置在指定的目录中。
2. \``EXECUTABLE\_OUTPUT\_PATH`\`是一个目标特定的属性，用于指定特定目标的输出路径。通过设置\``EXECUTABLE\_OUTPUT\_PATH`\`，可以将特定目标生成的可执行文件放置在指定的目录中。

区别：

* - \``CMAKE\_RUNTIME\_OUTPUT\_DIRECTORY`\`是全局变量，适用于整个项目中的所有可执行文件，而\``EXECUTABLE\_OUTPUT\_PATH`\`是目标特定的属性，适用于特定的目标。

- \``CMAKE\_RUNTIME\_OUTPUT\_DIRECTORY`\`设置的路径会影响所有的可执行文件，而\`EXECUTABLE\_OUTPUT\_PATH\`只会影响特定目标生成的可执行文件。
- 如果同时设置了\``CMAKE\_RUNTIME\_OUTPUT\_DIRECTORY`\`和\``EXECUTABLE\_OUTPUT\_PATH`\`，\``EXECUTABLE\_OUTPUT\_PATH`\`的优先级更高，会覆盖\``CMAKE\_RUNTIME\_OUTPUT\_DIRECTORY`\`的设置。  在使用时，可以根据具体需求选择使用\``CMAKE\_RUNTIME\_OUTPUT\_DIRECTORY`\`或\``EXECUTABLE\_OUTPUT\_PATH`\`来指定可执行文件的输出路径。
