# 示例代码说明

本目录包含 Python 和 C++ 的示例代码，演示如何使用生成的 protobuf 代码。

## 目录结构

```
example/
├── python/          # Python 示例代码
│   └── example.py
├── cpp/             # C++ 示例代码
│   ├── example.cpp
│   └── Makefile
└── README.md        # 本文件
```

## Python 示例

### 运行方法

```bash
# 确保已安装 protobuf Python 包
pip install protobuf

# 运行示例
cd example/python
python3 example.py
```

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

### 代码结构说明

C++ 示例代码将打印逻辑封装到单独的函数中，方便初学者理解和后续修改：

- `printUploadStatusRequest()` - 打印上传状态请求
- `printUploadStatusResponse()` - 打印上传状态响应
- `printSetSafetySpaceRequest()` - 打印安全空间设置请求
- `printSetSafetySpaceResponse()` - 打印安全空间设置响应

每个打印函数都包含：
1. 打印消息的各个字段
2. 打印完整的消息对象
3. TODO 注释，提示可以在这里添加自己的逻辑

### 编译和运行

```bash
# 编译示例
cd example/cpp
make

# 运行示例
make run
# 或直接运行
./example

# 清理生成的文件
make clean
```

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
2. **编译依赖**：C++ 示例需要链接 protobuf 库（`-lprotobuf`）
3. **路径问题**：确保从正确的目录运行代码，以便找到生成的 protobuf 文件
