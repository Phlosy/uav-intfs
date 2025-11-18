# gRPC 传输示例使用指南

本目录包含完整的 gRPC 服务端和客户端示例，演示如何使用 protobuf + gRPC 进行网络传输。

## 快速开始

### 1. 安装依赖

```bash
pip install grpcio grpcio-tools protobuf
```

### 2. 生成 gRPC 代码

在项目根目录执行：

```bash
cd /home/node7/xpk/uav-intfs
make python
```

这将生成以下文件：
- `generated/python/uav_service_pb2.py` - protobuf 消息定义
- `generated/python/uav_service_pb2_grpc.py` - gRPC 服务定义

### 3. 运行示例

#### 启动服务端

```bash
cd example/python
python3 grpc_server.py
```

服务端默认监听端口 `50051`，你可以使用 `--port` 参数指定其他端口：

```bash
python3 grpc_server.py --port 50052
```

#### 运行客户端

**测试模式**（推荐首次使用）：
```bash
cd example/python
python3 grpc_client.py --test
```

**交互模式**：
```bash
cd example/python
python3 grpc_client.py

# 可用命令：
# upload <uav_id> <data>  - 上传状态数据
# safety <uav_id> <data>  - 设置安全空间
# quit                    - 退出
```

## 文件说明

### grpc_server.py

gRPC 服务端实现，包含：

- **UavServiceServicer 类**：实现 `UavService` 服务接口
  - `UploadStatus(request, context)`: 处理上传无人机状态数据的请求
  - `SetSafetySpace(request, context)`: 处理下发无人机安全空间的请求
- **serve(port)**: 启动 gRPC 服务器

**特性**：
- 数据验证（检查 uav_id 和 data 是否为空）
- 错误处理和日志记录
- 支持自定义端口
- 优雅关闭（Ctrl+C）

### grpc_client.py

gRPC 客户端实现，包含：

- **UavServiceClient 类**：封装客户端功能
  - `connect()`: 连接到服务器
  - `upload_status(uav_id, data)`: 上传状态数据
  - `set_safety_space(uav_id, data)`: 设置安全空间
  - `disconnect()`: 断开连接

**特性**：
- 自动连接测试
- 错误处理和日志记录
- 支持测试模式和交互模式
- 支持自定义服务器地址

## 使用示例

### 完整测试流程

1. **终端 1 - 启动服务端**：
```bash
cd example/python
python3 grpc_server.py
```

输出示例：
```
============================================================
UAV gRPC 服务端
============================================================
监听端口: 50051
============================================================

INFO:__main__:gRPC 服务器已启动，监听端口: 50051
INFO:__main__:服务器地址: [::]:50051
```

2. **终端 2 - 运行客户端测试**：
```bash
cd example/python
python3 grpc_client.py --test
```

输出示例：
```
============================================================
UAV gRPC 客户端
============================================================
服务器地址: localhost:50051
============================================================

INFO:__main__:已连接到服务器: localhost:50051
INFO:__main__:连接测试成功

[测试 1] 上传无人机状态数据
------------------------------------------------------------
INFO:__main__:发送上传状态请求 - UAV ID: UAV-001, 数据长度: 17 字节
INFO:__main__:收到响应 - 成功: True, 消息: 成功接收 UAV UAV-001 的状态数据，数据大小: 17 字节
✓ 成功: 成功接收 UAV UAV-001 的状态数据，数据大小: 17 字节

[测试 2] 设置无人机安全空间
------------------------------------------------------------
INFO:__main__:发送设置安全空间请求 - UAV ID: UAV-001, 数据长度: 24 字节
INFO:__main__:收到响应 - 成功: True, 消息: 成功为 UAV UAV-001 设置安全空间，数据大小: 24 字节
✓ 成功: 成功为 UAV UAV-001 设置安全空间，数据大小: 24 字节
```

### 交互模式示例

```bash
cd example/python
python3 grpc_client.py
```

```
> upload UAV-001 test_status_data
结果: 成功接收 UAV UAV-001 的状态数据，数据大小: 17 字节

> safety UAV-001 safety_config_data
结果: 成功为 UAV UAV-001 设置安全空间，数据大小: 18 字节

> quit
```

## 自定义开发

### 在服务端添加业务逻辑

编辑 `grpc_server.py`，在 `UploadStatus` 和 `SetSafetySpace` 方法中的 `TODO` 注释处添加你的业务逻辑：

```python
def UploadStatus(self, request, context):
    # ... 数据验证 ...
    
    # TODO: 在这里添加你的业务逻辑
    # 例如：
    # - 解析和验证数据
    # - 保存到数据库
    # - 更新无人机状态
    # - 触发其他服务
    
    # 你的代码：
    # process_status_data(request.uav_id, request.data)
    # save_to_database(request)
    
    return uav_service_pb2.UploadStatusResponse(...)
```

### 在客户端添加功能

编辑 `grpc_client.py`，可以添加更多方法或修改现有方法：

```python
def custom_method(self, ...):
    """自定义方法"""
    request = uav_service_pb2.CustomRequest(...)
    response = self.stub.CustomMethod(request, timeout=10)
    return response
```

## 故障排除

### 问题：无法导入 gRPC 代码

**错误信息**：
```
ImportError: cannot import name 'uav_service_pb2_grpc'
```

**解决方法**：
1. 确保已安装 `grpcio-tools`：`pip install grpcio-tools`
2. 运行 `make python` 生成 gRPC 代码
3. 检查 `generated/python/` 目录下是否有 `uav_service_pb2_grpc.py` 文件

### 问题：连接失败

**错误信息**：
```
连接超时: 无法连接到服务器 localhost:50051
```

**解决方法**：
1. 确保服务端正在运行
2. 检查端口是否正确
3. 检查防火墙设置
4. 尝试使用 `--server` 参数指定正确的服务器地址

### 问题：端口被占用

**错误信息**：
```
Address already in use
```

**解决方法**：
使用 `--port` 参数指定其他端口：
```bash
python3 grpc_server.py --port 50052
```

## 更多信息

详细文档请参考：
- [example/README.md](../README.md) - 完整示例说明
- [项目根目录 README.md](../../README.md) - 项目总体说明

