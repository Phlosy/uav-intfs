#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "../../generated/cpp/uav_service.pb.h"
#include "../../generated/cpp/uav_service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using uav::UavService;
using uav::UploadStatusRequest;
using uav::UploadStatusResponse;
using uav::SetSafetySpaceRequest;
using uav::SetSafetySpaceResponse;

// ============================================================================
// UAV 服务客户端类
// ============================================================================

class UavServiceClient {
public:
    UavServiceClient(std::shared_ptr<Channel> channel)
        : stub_(UavService::NewStub(channel)) {}
    
    /**
     * 上传无人机状态数据
     */
    bool UploadStatus(const std::string& uav_id, const std::string& data) {
        UploadStatusRequest request;
        request.set_uav_id(uav_id);
        request.set_data(data);
        
        UploadStatusResponse response;
        ClientContext context;
        
        std::cout << "[客户端] 发送上传状态请求 - UAV ID: " << uav_id
                  << ", 数据长度: " << data.size() << " 字节" << std::endl;
        
        Status status = stub_->UploadStatus(&context, request, &response);
        
        if (status.ok()) {
            std::cout << "[客户端] 收到响应 - 成功: " << (response.success() ? "true" : "false")
                      << ", 消息: " << response.message() << std::endl;
            return response.success();
        } else {
            std::cout << "[客户端] RPC 调用失败: " << status.error_code() 
                      << " - " << status.error_message() << std::endl;
            return false;
        }
    }
    
    /**
     * 设置无人机安全空间
     */
    bool SetSafetySpace(const std::string& uav_id, const std::string& data) {
        SetSafetySpaceRequest request;
        request.set_uav_id(uav_id);
        request.set_data(data);
        
        SetSafetySpaceResponse response;
        ClientContext context;
        
        std::cout << "[客户端] 发送设置安全空间请求 - UAV ID: " << uav_id
                  << ", 数据长度: " << data.size() << " 字节" << std::endl;
        
        Status status = stub_->SetSafetySpace(&context, request, &response);
        
        if (status.ok()) {
            std::cout << "[客户端] 收到响应 - 成功: " << (response.success() ? "true" : "false")
                      << ", 消息: " << response.message() << std::endl;
            return response.success();
        } else {
            std::cout << "[客户端] RPC 调用失败: " << status.error_code() 
                      << " - " << status.error_message() << std::endl;
            return false;
        }
    }

private:
    std::unique_ptr<UavService::Stub> stub_;
};

// ============================================================================
// 测试函数
// ============================================================================

void RunTests(const std::string& server_address) {
    // 创建客户端通道
    auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    
    // 等待通道就绪
    std::cout << "[客户端] 正在连接到服务器: " << server_address << std::endl;
    auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(5);
    if (!channel->WaitForConnected(deadline)) {
        std::cerr << "[客户端] 错误: 无法连接到服务器 " << server_address << std::endl;
        return;
    }
    std::cout << "[客户端] 连接成功！" << std::endl;
    std::cout << std::endl;
    
    // 创建客户端
    UavServiceClient client(channel);
    
    // 测试 1: 上传状态数据
    std::cout << "[测试 1] 上传无人机状态数据" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    bool success = client.UploadStatus("UAV-001", "status_data_12345");
    if (success) {
        std::cout << "✓ 测试通过" << std::endl;
    } else {
        std::cout << "✗ 测试失败" << std::endl;
    }
    std::cout << std::endl;
    
    // 测试 2: 设置安全空间
    std::cout << "[测试 2] 设置无人机安全空间" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    success = client.SetSafetySpace("UAV-001", "safety_space_config_data");
    if (success) {
        std::cout << "✓ 测试通过" << std::endl;
    } else {
        std::cout << "✗ 测试失败" << std::endl;
    }
    std::cout << std::endl;
    
    // 测试 3: 错误处理 - 空 uav_id
    std::cout << "[测试 3] 测试错误处理 - 空 uav_id" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    success = client.UploadStatus("", "test_data");
    if (!success) {
        std::cout << "✓ 错误处理正常（预期失败）" << std::endl;
    } else {
        std::cout << "✗ 错误处理异常（应该失败但成功了）" << std::endl;
    }
    std::cout << std::endl;
}

// ============================================================================
// 主函数
// ============================================================================

int main(int argc, char** argv) {
    std::string server_address = "localhost:50051";
    
    // 解析命令行参数
    if (argc > 1) {
        if (std::string(argv[1]) == "--server" && argc > 2) {
            server_address = argv[2];
        } else if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
            std::cout << "用法: " << argv[0] << " [--server <地址>]" << std::endl;
            std::cout << "默认服务器地址: localhost:50051" << std::endl;
            std::cout << "示例: " << argv[0] << " --server localhost:50052" << std::endl;
            return 0;
        }
    }
    
    std::cout << "============================================================" << std::endl;
    std::cout << "UAV gRPC 客户端" << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "服务器地址: " << server_address << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    RunTests(server_address);
    
    std::cout << "============================================================" << std::endl;
    std::cout << "测试完成" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    return 0;
}

