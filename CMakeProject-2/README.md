## CMake生成库文件

### CMake的第三方库使用

主要生成自定义生成库，生成动态库和静态库，没有生成对应的*.cmake连接。





#### 注意事项

**window下使用**

```
#windows系统动态库生成lib文件命令
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
```



### 排序，查找

将排序和查找的功能进行编译，生成库文件，在main.cpp中调用库文件

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

# 设定动态链接库的存储路径
set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
    # static静态库
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
    )

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
