# 示例代码说明

本目录包含 Python 和 C++ 的示例代码，演示如何使用生成的 protobuf 代码。

## 目录结构

```
example/
├── python/              # Python 示例代码
│   ├── example.py      # 基础 protobuf 使用示例
│   ├── grpc_server.py  # gRPC 服务端示例
│   └── grpc_client.py  # gRPC 客户端示例
├── cpp/                # C++ 示例代码
│   ├── example.cpp
│   └── Makefile
└── README.md           # 本文件
```

## Python 示例

### 基础 Protobuf 示例

#### 运行方法

```bash
# 确保已安装 protobuf Python 包
pip install protobuf

# 运行示例
cd example/python
python3 example.py
```

### gRPC 传输示例

本目录包含完整的 gRPC 服务端和客户端示例，演示如何使用 protobuf + gRPC 进行网络传输。

#### 前置要求

1. **安装依赖**：
```bash
pip install grpcio grpcio-tools protobuf
```

2. **生成 gRPC 代码**：
```bash
# 在项目根目录执行
cd /home/node7/xpk/uav-intfs
make python
```

这将生成 `uav_service_pb2.py` 和 `uav_service_pb2_grpc.py` 文件。

#### 运行 gRPC 服务端

```bash
cd example/python

# 使用默认端口 50051
python3 grpc_server.py

# 或指定自定义端口
python3 grpc_server.py --port 50052
```

服务端将启动并监听指定端口，等待客户端连接。

#### 运行 gRPC 客户端

**测试模式**（自动运行测试用例）：
```bash
cd example/python

# 连接到默认服务器地址 localhost:50051
python3 grpc_client.py --test

# 或指定服务器地址
python3 grpc_client.py --server localhost:50052 --test
```

**交互模式**（手动输入命令）：
```bash
cd example/python
python3 grpc_client.py

# 在交互模式下，可以使用以下命令：
# upload <uav_id> <data>  - 上传状态数据
# safety <uav_id> <data>  - 设置安全空间
# quit                    - 退出
```

#### 完整示例流程

1. **启动服务端**（终端 1）：
```bash
cd example/python
python3 grpc_server.py
```

2. **运行客户端测试**（终端 2）：
```bash
cd example/python
python3 grpc_client.py --test
```

#### gRPC 代码结构

**服务端 (grpc_server.py)**：
- `UavServiceServicer` 类：实现 `UavService` 服务接口
  - `UploadStatus()`: 处理上传状态请求
  - `SetSafetySpace()`: 处理设置安全空间请求
- `serve()`: 启动 gRPC 服务器

**客户端 (grpc_client.py)**：
- `UavServiceClient` 类：封装客户端功能
  - `connect()`: 连接到服务器
  - `upload_status()`: 上传状态数据
  - `set_safety_space()`: 设置安全空间
  - `disconnect()`: 断开连接

### 代码结构

Python 示例代码将打印逻辑封装到单独的函数中，方便初学者理解和后续修改：

- `print_upload_status_request()` - 打印上传状态请求
- `print_upload_status_response()` - 打印上传状态响应
- `print_set_safety_space_request()` - 打印安全空间设置请求
- `print_set_safety_space_response()` - 打印安全空间设置响应

每个打印函数都包含：
1. 打印消息的各个字段
2. 打印完整的消息对象
3. TODO 注释，提示可以在这里添加自己的逻辑

## C++ 示例

### 基础 Protobuf 示例

#### 代码结构说明

C++ 示例代码将打印逻辑封装到单独的函数中，方便初学者理解和后续修改：

- `printUploadStatusRequest()` - 打印上传状态请求
- `printUploadStatusResponse()` - 打印上传状态响应
- `printSetSafetySpaceRequest()` - 打印安全空间设置请求
- `printSetSafetySpaceResponse()` - 打印安全空间设置响应

每个打印函数都包含：
1. 打印消息的各个字段
2. 打印完整的消息对象
3. TODO 注释，提示可以在这里添加自己的逻辑

#### 编译和运行

```bash
# 编译示例
cd example/cpp
make

# 运行示例
make run
# 或直接运行（需要设置 LD_LIBRARY_PATH）
LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH ./example

# 清理生成的文件
make clean
```

### gRPC 传输示例

本目录包含完整的 gRPC 服务端和客户端示例，演示如何使用 protobuf + gRPC 进行网络传输。

#### 前置要求

1. **安装依赖**：
```bash
# 需要安装 protobuf 和 gRPC C++ 库
# 如果使用 conda 环境，通常已经包含
conda install protobuf grpc-cpp
```

2. **生成 gRPC 代码**：
```bash
# 在项目根目录执行
cd /home/node7/xpk/uav-intfs
make cpp
```

这将生成 `uav_service.pb.h`、`uav_service.pb.cc`、`uav_service.grpc.pb.h` 和 `uav_service.grpc.pb.cc` 文件。

#### 编译 gRPC 示例

```bash
cd example/cpp

# 编译所有示例（包括 gRPC）
make all

# 或单独编译
make grpc_server  # 编译服务端
make grpc_client  # 编译客户端
```

#### 运行 gRPC 服务端

```bash
cd example/cpp

# 使用默认端口 50051
make run-server

# 或直接运行（需要设置 LD_LIBRARY_PATH）
LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH ./grpc_server

# 指定自定义端口
LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH ./grpc_server --port 50052
```

服务端将启动并监听指定端口，等待客户端连接。

#### 运行 gRPC 客户端

```bash
cd example/cpp

# 连接到默认服务器地址 localhost:50051
make run-client

# 或直接运行
LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH ./grpc_client

# 指定服务器地址
LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH ./grpc_client --server localhost:50052
```

#### 完整示例流程

1. **启动服务端**（终端 1）：
```bash
cd example/cpp
make run-server
```

2. **运行客户端**（终端 2）：
```bash
cd example/cpp
make run-client
```

#### gRPC 代码结构

**服务端 (grpc_server.cpp)**：
- `UavServiceImpl` 类：实现 `UavService::Service` 接口
  - `UploadStatus()`: 处理上传状态请求
  - `SetSafetySpace()`: 处理设置安全空间请求
- `RunServer()`: 启动 gRPC 服务器

**客户端 (grpc_client.cpp)**：
- `UavServiceClient` 类：封装客户端功能
  - `UploadStatus()`: 上传状态数据
  - `SetSafetySpace()`: 设置安全空间
- `RunTests()`: 运行测试用例

### 如何添加自己的逻辑

在每个打印函数中，都有 `// TODO:` 注释标记的位置，你可以：

1. **数据验证**：在打印前验证数据是否有效
2. **业务处理**：添加你的业务逻辑
3. **日志记录**：记录到日志文件或数据库
4. **错误处理**：处理异常情况
5. **回调处理**：调用其他函数或服务

#### Python 示例

```python
def print_upload_status_request(request):
    # 数据验证
    if not request.uav_id:
        print("错误: uav_id 不能为空")
        return
    
    # 打印信息
    print(f"   data: {request.data}")
    print(f"   uav_id: {request.uav_id}")
    
    # 你的业务逻辑
    # 例如：保存到数据库、发送到服务器等
    # save_to_database(request)
    # send_to_server(request)
```

#### C++ 示例

```cpp
void printUploadStatusRequest(const UploadStatusRequest& request) {
    // 数据验证
    if (request.uav_id().empty()) {
        cerr << "错误: uav_id 不能为空" << endl;
        return;
    }
    
    // 打印信息
    cout << "  data: " << request.data() << endl;
    cout << "  uav_id: " << request.uav_id() << endl;
    
    // 你的业务逻辑
    // 例如：保存到数据库、发送到服务器等
    // saveToDatabase(request);
    // sendToServer(request);
}
```

## 注意事项

1. **protobuf 版本**：确保系统安装的 protobuf 库版本与生成代码时使用的 protoc 版本兼容
2. **编译依赖**：
   - C++ 基础示例需要链接 protobuf 库
   - C++ gRPC 示例需要链接 protobuf 和 gRPC 库
3. **路径问题**：确保从正确的目录运行代码，以便找到生成的 protobuf 文件
4. **gRPC 代码生成**：
   - Python: 使用 gRPC 示例前，需要先运行 `make python` 生成 gRPC 代码
   - C++: 使用 gRPC 示例前，需要先运行 `make cpp` 生成 gRPC 代码
5. **gRPC 工具**：
   - Python: 确保已安装 `grpcio-tools`，否则无法生成 gRPC 代码
     ```bash
     pip install grpcio-tools
     ```
   - C++: 确保已安装 `grpc_cpp_plugin`，否则无法生成 gRPC 代码
6. **端口占用**：如果默认端口 50051 被占用，可以使用 `--port` 参数指定其他端口
7. **运行时库路径**（C++）：
   - 如果使用 conda 环境，Makefile 会自动设置 `LD_LIBRARY_PATH`
   - 手动运行可执行文件时，需要设置：
     ```bash
     export LD_LIBRARY_PATH=$CONDA_PREFIX/lib:$LD_LIBRARY_PATH
     ```
