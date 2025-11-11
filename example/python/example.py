#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
简单的 Python 示例，演示如何使用生成的 protobuf 代码
"""

import sys
import os

# 添加父目录到路径，以便导入生成的 protobuf 代码
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../..', 'generated', 'python'))

import uav_service_pb2  # type: ignore


# ============================================================================
# 打印函数 - 将打印逻辑封装到单独的函数中，方便理解和修改
# ============================================================================

def print_upload_status_request(request):
    """
    打印 UploadStatusRequest 消息
    你可以在这个函数中添加自己的逻辑
    """
    print(f"   data: {request.data}")
    print(f"   uav_id: {request.uav_id}")
    print(f"   完整对象: {request}")
    
    # TODO: 在这里添加你自己的逻辑
    # 例如：数据验证、日志记录、业务处理等


def print_upload_status_response(response):
    """
    打印 UploadStatusResponse 消息
    你可以在这个函数中添加自己的逻辑
    """
    print(f"   success: {response.success}")
    print(f"   message: {response.message}")
    print(f"   完整对象: {response}")
    
    # TODO: 在这里添加你自己的逻辑
    # 例如：错误处理、状态检查、回调处理等


def print_set_safety_space_request(request):
    """
    打印 SetSafetySpaceRequest 消息
    你可以在这个函数中添加自己的逻辑
    """
    print(f"   data: {request.data}")
    print(f"   uav_id: {request.uav_id}")
    print(f"   完整对象: {request}")
    
    # TODO: 在这里添加你自己的逻辑
    # 例如：安全空间验证、数据解析、权限检查等


def print_set_safety_space_response(response):
    """
    打印 SetSafetySpaceResponse 消息
    你可以在这个函数中添加自己的逻辑
    """
    print(f"   success: {response.success}")
    print(f"   message: {response.message}")
    print(f"   完整对象: {response}")
    
    # TODO: 在这里添加你自己的逻辑
    # 例如：结果处理、通知更新、状态同步等


# ============================================================================
# 主函数 - 演示如何使用 protobuf 消息
# ============================================================================

def main():
    print("=" * 50)
    print("Python Protobuf 示例")
    print("=" * 50)
    
    # 示例1: 创建 UploadStatusRequest
    print("\n1. 创建 UploadStatusRequest:")
    upload_request = uav_service_pb2.UploadStatusRequest()
    upload_request.data = b"test_data_123"
    upload_request.uav_id = "UAV-001"
    print_upload_status_request(upload_request)
    
    # 示例2: 创建 UploadStatusResponse
    print("\n2. 创建 UploadStatusResponse:")
    upload_response = uav_service_pb2.UploadStatusResponse()
    upload_response.success = True
    upload_response.message = "上传成功"
    print_upload_status_response(upload_response)
    
    # 示例3: 创建 SetSafetySpaceRequest
    print("\n3. 创建 SetSafetySpaceRequest:")
    safety_request = uav_service_pb2.SetSafetySpaceRequest()
    safety_request.data = b"safety_space_data"
    safety_request.uav_id = "UAV-002"
    print_set_safety_space_request(safety_request)
    
    # 示例4: 创建 SetSafetySpaceResponse
    print("\n4. 创建 SetSafetySpaceResponse:")
    safety_response = uav_service_pb2.SetSafetySpaceResponse()
    safety_response.success = True
    safety_response.message = "安全空间设置成功"
    print_set_safety_space_response(safety_response)
    
    print("\n" + "=" * 50)
    print("示例执行完成！")
    print("=" * 50)


if __name__ == "__main__":
    main()

