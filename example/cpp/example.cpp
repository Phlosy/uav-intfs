#include <iostream>
#include <string>
#include "../../generated/cpp/uav_service.pb.h"

using namespace std;
using namespace uav;

// ============================================================================
// 打印函数 - 将打印逻辑封装到单独的函数中，方便理解和修改
// ============================================================================

/**
 * 打印 UploadStatusRequest 消息
 * 你可以在这个函数中添加自己的逻辑
 */
void printUploadStatusRequest(const UploadStatusRequest& request) {
    cout << "  data: " << request.data() << endl;
    cout << "  uav_id: " << request.uav_id() << endl;
    cout << "  完整对象: " << request.ShortDebugString() << endl;
    
    // TODO: 在这里添加你自己的逻辑
    // 例如：数据验证、日志记录、业务处理等
}

/**
 * 打印 UploadStatusResponse 消息
 * 你可以在这个函数中添加自己的逻辑
 */
void printUploadStatusResponse(const UploadStatusResponse& response) {
    cout << "  success: " << (response.success() ? "true" : "false") << endl;
    cout << "  message: " << response.message() << endl;
    cout << "  完整对象: " << response.ShortDebugString() << endl;
    
    // TODO: 在这里添加你自己的逻辑
    // 例如：错误处理、状态检查、回调处理等
}

/**
 * 打印 SetSafetySpaceRequest 消息
 * 你可以在这个函数中添加自己的逻辑
 */
void printSetSafetySpaceRequest(const SetSafetySpaceRequest& request) {
    cout << "  data: " << request.data() << endl;
    cout << "  uav_id: " << request.uav_id() << endl;
    cout << "  完整对象: " << request.ShortDebugString() << endl;
    
    // TODO: 在这里添加你自己的逻辑
    // 例如：安全空间验证、数据解析、权限检查等
}

/**
 * 打印 SetSafetySpaceResponse 消息
 * 你可以在这个函数中添加自己的逻辑
 */
void printSetSafetySpaceResponse(const SetSafetySpaceResponse& response) {
    cout << "  success: " << (response.success() ? "true" : "false") << endl;
    cout << "  message: " << response.message() << endl;
    cout << "  完整对象: " << response.ShortDebugString() << endl;
    
    // TODO: 在这里添加你自己的逻辑
    // 例如：结果处理、通知更新、状态同步等
}

// ============================================================================
// 主函数 - 演示如何使用 protobuf 消息
// ============================================================================

int main() {
    cout << string(50, '=') << endl;
    cout << "C++ Protobuf 示例" << endl;
    cout << string(50, '=') << endl;
    
    // 示例1: 创建 UploadStatusRequest
    cout << "\n1. 创建 UploadStatusRequest:" << endl;
    UploadStatusRequest upload_request;
    upload_request.set_data("test_data_123");
    upload_request.set_uav_id("UAV-001");
    printUploadStatusRequest(upload_request);
    
    // 示例2: 创建 UploadStatusResponse
    cout << "\n2. 创建 UploadStatusResponse:" << endl;
    UploadStatusResponse upload_response;
    upload_response.set_success(true);
    upload_response.set_message("上传成功");
    printUploadStatusResponse(upload_response);
    
    // 示例3: 创建 SetSafetySpaceRequest
    cout << "\n3. 创建 SetSafetySpaceRequest:" << endl;
    SetSafetySpaceRequest safety_request;
    safety_request.set_data("safety_space_data");
    safety_request.set_uav_id("UAV-002");
    printSetSafetySpaceRequest(safety_request);
    
    // 示例4: 创建 SetSafetySpaceResponse
    cout << "\n4. 创建 SetSafetySpaceResponse:" << endl;
    SetSafetySpaceResponse safety_response;
    safety_response.set_success(true);
    safety_response.set_message("安全空间设置成功");
    printSetSafetySpaceResponse(safety_response);
    
    cout << "\n" << string(50, '=') << endl;
    cout << "示例执行完成！" << endl;
    cout << string(50, '=') << endl;
    
    return 0;
}

