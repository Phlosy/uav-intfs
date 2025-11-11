# UAV 接口服务

基于 Protocol Buffers 的无人机接口服务定义和代码生成项目。

## 项目简介

本项目定义了无人机服务的 Protocol Buffers 接口，支持自动生成 Python 和 C++ 代码，方便在不同语言环境中使用。

### 主要功能

- **上传无人机状态数据**：接收无人机上传的状态信息
- **下发无人机安全空间**：向无人机下发安全空间配置

## 项目结构

```
uav-intfs/
├── uav_service.proto      # Protocol Buffers 服务定义文件
├── Makefile               # 代码生成和构建配置
├── README.md              # 本文件
├── generated/             # 生成的代码目录（自动生成）
│   ├── python/           # Python 生成的代码
│   └── cpp/              # C++ 生成的代码
└── example/               # 示例代码
    ├── python/            # Python 示例
    │   └── example.py
    ├── cpp/               # C++ 示例
    │   ├── example.cpp
    │   └── Makefile
    └── README.md          # 示例代码说明
```

## 依赖要求

### 必需工具

1. **Protocol Buffers 编译器 (protoc)**
   - 版本要求：与生成的代码兼容
   - 安装方法：
     ```bash
     # Ubuntu/Debian
     sudo apt-get install protobuf-compiler
     
     # 或从官网下载安装
     # https://grpc.io/docs/protoc-installation/
     ```

2. **Python 环境**（如使用 Python）
   - Python 3.6+
   - protobuf 库：
     ```bash
     pip install protobuf
     ```

3. **C++ 编译环境**（如使用 C++）
   - g++ 编译器（支持 C++17）
   - Protocol Buffers C++ 库：
     ```bash
     # Ubuntu/Debian
     sudo apt-get install libprotobuf-dev
     ```

## 快速开始

### 1. 生成代码

生成所有语言的代码（Python + C++）：

```bash
make all
```

或分别生成：

```bash
# 生成 Python 代码
make python

# 生成 C++ 代码
make cpp
```

生成的代码将输出到 `generated/` 目录下。

### 2. 运行示例

#### Python 示例

```bash
cd example/python
python3 example.py
```

#### C++ 示例

```bash
cd example/cpp
make        # 编译
make run    # 运行
```

## Makefile 使用说明

项目根目录的 Makefile 提供了以下命令：

| 命令 | 说明 |
|------|------|
| `make all` | 清理并生成所有代码（Python + C++） |
| `make python` | 清理并生成 Python 代码 |
| `make cpp` | 清理并生成 C++ 代码 |
| `make clean` | 清理所有生成的代码 |
| `make clean-python` | 仅清理 Python 代码 |
| `make clean-cpp` | 仅清理 C++ 代码 |
| `make help` | 显示帮助信息 |

**注意**：每次生成代码前，Makefile 会自动清理对应目录中的已有代码，确保生成的是全新代码。

## 服务定义

### 消息类型

#### UploadStatusRequest（上传状态请求）
- `data` (bytes): 字节流数据
- `uav_id` (string): 无人机编号

#### UploadStatusResponse（上传状态响应）
- `success` (bool): 是否成功
- `message` (string): 响应消息

#### SetSafetySpaceRequest（设置安全空间请求）
- `data` (bytes): 字节流数据
- `uav_id` (string): 无人机编号

#### SetSafetySpaceResponse（设置安全空间响应）
- `success` (bool): 是否成功
- `message` (string): 响应消息

### RPC 服务

#### UavService

- **UploadStatus**: 上传无人机状态数据
  - 输入：`UploadStatusRequest`
  - 输出：`UploadStatusResponse`

- **SetSafetySpace**: 下发无人机安全空间
  - 输入：`SetSafetySpaceRequest`
  - 输出：`SetSafetySpaceResponse`

## 使用生成的代码

### Python

```python
import sys
import os
sys.path.insert(0, 'generated/python')
import uav_service_pb2

# 创建请求消息
request = uav_service_pb2.UploadStatusRequest()
request.data = b"your_data"
request.uav_id = "UAV-001"

# 使用消息...
```

### C++

```cpp
#include "generated/cpp/uav_service.pb.h"
using namespace uav;

// 创建请求消息
UploadStatusRequest request;
request.set_data("your_data");
request.set_uav_id("UAV-001");

// 使用消息...
```

## 示例代码

项目提供了完整的示例代码，演示如何使用生成的 protobuf 代码：

- **位置**：`example/` 目录
- **说明**：详见 [example/README.md](example/README.md)

示例代码特点：
- 将打印逻辑封装到单独的函数中，方便理解和修改
- 包含 TODO 注释，提示可以添加自定义逻辑的位置
- 适合初学者学习和后续扩展

## 开发指南

### 修改服务定义

1. 编辑 `uav_service.proto` 文件
2. 运行 `make all` 重新生成代码
3. 更新示例代码（如需要）

### 添加新语言支持

1. 在 Makefile 中添加新的生成目标
2. 使用对应的 protoc 插件（如 `--go_out` 用于 Go）
3. 更新文档

## 常见问题

### Q: 生成的代码在哪里？

A: 生成的代码在 `generated/` 目录下，按语言分类：
- Python: `generated/python/`
- C++: `generated/cpp/`

### Q: 如何清理生成的代码？

A: 使用 `make clean` 清理所有生成的代码，或使用 `make clean-python` / `make clean-cpp` 清理特定语言的代码。

### Q: protoc 版本不兼容怎么办？

A: 确保安装的 protoc 版本与生成代码时使用的版本兼容。建议使用最新版本的 protoc。

### Q: 如何在自己的项目中使用生成的代码？

A: 
1. 将生成的代码复制到你的项目中
2. 确保 protobuf 库已安装
3. 按照示例代码的方式导入和使用

## 许可证

[根据实际情况添加许可证信息]

## 贡献

欢迎提交 Issue 和 Pull Request！

## 联系方式

[根据实际情况添加联系方式]

