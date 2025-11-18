#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "../../generated/cpp/uav_service.pb.h"
#include "../../generated/cpp/uav_service.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using uav::UavService;
using uav::UploadStatusRequest;
using uav::UploadStatusResponse;
using uav::SetSafetySpaceRequest;
using uav::SetSafetySpaceResponse;

// ============================================================================
// UavService 服务实现
// ============================================================================

class UavServiceImpl final : public UavService::Service {
public:
    /**
     * 处理上传无人机状态数据的请求
     */
    Status UploadStatus(ServerContext* /*context*/,
                       const UploadStatusRequest* request,
                       UploadStatusResponse* response) override {
        std::cout << "[服务端] 收到上传状态请求 - UAV ID: " << request->uav_id()
                  << ", 数据长度: " << request->data().size() << " 字节" << std::endl;
        
        // 数据验证
        if (request->uav_id().empty()) {
            response->set_success(false);
            response->set_message("uav_id 不能为空");
            return Status(grpc::StatusCode::INVALID_ARGUMENT, "uav_id 不能为空");
        }
        
        if (request->data().empty()) {
            response->set_success(false);
            response->set_message("data 不能为空");
            return Status(grpc::StatusCode::INVALID_ARGUMENT, "data 不能为空");
        }
        
        // TODO: 在这里添加你的业务逻辑
        // 例如：
        // - 解析和验证数据
        // - 保存到数据库
        // - 更新无人机状态
        // - 触发其他服务
        
        std::cout << "[服务端] 成功处理 UAV " << request->uav_id() << " 的状态数据" << std::endl;
        
        response->set_success(true);
        response->set_message("成功接收 UAV " + request->uav_id() + 
                             " 的状态数据，数据大小: " + 
                             std::to_string(request->data().size()) + " 字节");
        
        return Status::OK;
    }
    
    /**
     * 处理下发无人机安全空间的请求
     */
    Status SetSafetySpace(ServerContext* /*context*/,
                         const SetSafetySpaceRequest* request,
                         SetSafetySpaceResponse* response) override {
        std::cout << "[服务端] 收到设置安全空间请求 - UAV ID: " << request->uav_id()
                  << ", 数据长度: " << request->data().size() << " 字节" << std::endl;
        
        // 数据验证
        if (request->uav_id().empty()) {
            response->set_success(false);
            response->set_message("uav_id 不能为空");
            return Status(grpc::StatusCode::INVALID_ARGUMENT, "uav_id 不能为空");
        }
        
        if (request->data().empty()) {
            response->set_success(false);
            response->set_message("data 不能为空");
            return Status(grpc::StatusCode::INVALID_ARGUMENT, "data 不能为空");
        }
        
        // TODO: 在这里添加你的业务逻辑
        // 例如：
        // - 解析和验证安全空间数据
        // - 检查权限
        // - 下发到无人机
        // - 更新配置数据库
        // - 通知相关服务
        
        std::cout << "[服务端] 成功为 UAV " << request->uav_id() << " 设置安全空间" << std::endl;
        
        response->set_success(true);
        response->set_message("成功为 UAV " + request->uav_id() + 
                             " 设置安全空间，数据大小: " + 
                             std::to_string(request->data().size()) + " 字节");
        
        return Status::OK;
    }
};

// ============================================================================
// 服务器启动函数
// ============================================================================

void RunServer(int port = 50051) {
    std::string server_address("0.0.0.0:" + std::to_string(port));
    UavServiceImpl service;
    
    ServerBuilder builder;
    
    // 监听指定地址，不使用认证
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    
    // 注册服务
    builder.RegisterService(&service);
    
    // 构建并启动服务器
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "============================================================" << std::endl;
    std::cout << "UAV gRPC 服务端" << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "监听端口: " << port << std::endl;
    std::cout << "服务器地址: " << server_address << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "[服务端] gRPC 服务器已启动，等待客户端连接..." << std::endl;
    
    // 等待服务器关闭
    server->Wait();
}

// ============================================================================
// 主函数
// ============================================================================

int main(int argc, char** argv) {
    int port = 50051;
    
    // 解析命令行参数
    if (argc > 1) {
        if (std::string(argv[1]) == "--port" && argc > 2) {
            port = std::stoi(argv[2]);
        } else if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
            std::cout << "用法: " << argv[0] << " [--port <端口>]" << std::endl;
            std::cout << "默认端口: 50051" << std::endl;
            return 0;
        }
    }
    
    RunServer(port);
    
    return 0;
}

