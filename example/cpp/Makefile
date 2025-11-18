# Makefile for compiling C++ example

# 编译器配置
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

# 使用 pkg-config 获取 protobuf 和 grpc 的编译选项
# 优先使用 conda 环境中的库（与 protoc 版本匹配）
CONDA_PREFIX ?= $(shell echo $$CONDA_PREFIX)
ifneq ($(CONDA_PREFIX),)
    PKG_CONFIG_PATH := $(CONDA_PREFIX)/lib/pkgconfig:$(PKG_CONFIG_PATH)
endif
PKG_CONFIG = PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config

PROTOBUF_CFLAGS = $(shell $(PKG_CONFIG) --cflags protobuf 2>/dev/null || echo "-I/usr/local/include")
PROTOBUF_LIBS = $(shell $(PKG_CONFIG) --libs protobuf 2>/dev/null || echo "-lprotobuf")
GRPC_CFLAGS = $(shell $(PKG_CONFIG) --cflags grpc++ 2>/dev/null || echo "")
GRPC_LIBS = $(shell $(PKG_CONFIG) --libs grpc++ 2>/dev/null || echo "-lgrpc++ -lgrpc")

INCLUDES = -I../../generated/cpp $(PROTOBUF_CFLAGS) $(GRPC_CFLAGS)
LIBS = $(PROTOBUF_LIBS) $(GRPC_LIBS)

# 基础示例源文件和目标文件
EXAMPLE_SRC = example.cpp
PROTO_SRC = ../../generated/cpp/uav_service.pb.cc
PROTO_GRPC_SRC = ../../generated/cpp/uav_service.grpc.pb.cc
EXAMPLE_TARGET = example
PROTO_OBJ = uav_service.pb.o
PROTO_GRPC_OBJ = uav_service.grpc.pb.o

# gRPC 服务端和客户端
GRPC_SERVER_SRC = grpc_server.cpp
GRPC_CLIENT_SRC = grpc_client.cpp
GRPC_SERVER_TARGET = grpc_server
GRPC_CLIENT_TARGET = grpc_client

# 默认目标：编译所有示例
.PHONY: all
all: $(EXAMPLE_TARGET) $(GRPC_SERVER_TARGET) $(GRPC_CLIENT_TARGET)
	@echo "所有示例编译完成！"
	@echo "  基础示例: ./$(EXAMPLE_TARGET)"
	@echo "  gRPC 服务端: ./$(GRPC_SERVER_TARGET)"
	@echo "  gRPC 客户端: ./$(GRPC_CLIENT_TARGET)"

# 编译基础示例程序
$(EXAMPLE_TARGET): $(EXAMPLE_SRC) $(PROTO_OBJ)
	@echo "正在编译 C++ 基础示例..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXAMPLE_TARGET) $(EXAMPLE_SRC) $(PROTO_OBJ) $(LIBS)
	@echo "基础示例编译成功！"

# 编译 gRPC 服务端
$(GRPC_SERVER_TARGET): $(GRPC_SERVER_SRC) $(PROTO_OBJ) $(PROTO_GRPC_OBJ)
	@echo "正在编译 gRPC 服务端..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(GRPC_SERVER_TARGET) $(GRPC_SERVER_SRC) $(PROTO_OBJ) $(PROTO_GRPC_OBJ) $(LIBS)
	@echo "gRPC 服务端编译成功！"

# 编译 gRPC 客户端
$(GRPC_CLIENT_TARGET): $(GRPC_CLIENT_SRC) $(PROTO_OBJ) $(PROTO_GRPC_OBJ)
	@echo "正在编译 gRPC 客户端..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(GRPC_CLIENT_TARGET) $(GRPC_CLIENT_SRC) $(PROTO_OBJ) $(PROTO_GRPC_OBJ) $(LIBS)
	@echo "gRPC 客户端编译成功！"

# 编译 protobuf 生成的代码
$(PROTO_OBJ): $(PROTO_SRC)
	@echo "正在编译 protobuf 代码..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(PROTO_SRC) -o $(PROTO_OBJ)

# 编译 gRPC 生成的代码
$(PROTO_GRPC_OBJ): $(PROTO_GRPC_SRC)
	@echo "正在编译 gRPC 代码..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(PROTO_GRPC_SRC) -o $(PROTO_GRPC_OBJ)

# 清理生成的文件
.PHONY: clean
clean:
	@echo "正在清理..."
	@rm -f $(EXAMPLE_TARGET) $(GRPC_SERVER_TARGET) $(GRPC_CLIENT_TARGET)
	@rm -f $(PROTO_OBJ) $(PROTO_GRPC_OBJ)
	@echo "清理完成！"

# 获取 conda 库路径
CONDA_PREFIX ?= $(shell echo $$CONDA_PREFIX)
ifneq ($(CONDA_PREFIX),)
    LD_LIBRARY_PATH := $(CONDA_PREFIX)/lib:$(LD_LIBRARY_PATH)
endif

# 运行基础示例
.PHONY: run
run: $(EXAMPLE_TARGET)
	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./$(EXAMPLE_TARGET)

# 运行 gRPC 服务端
.PHONY: run-server
run-server: $(GRPC_SERVER_TARGET)
	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./$(GRPC_SERVER_TARGET)

# 运行 gRPC 客户端
.PHONY: run-client
run-client: $(GRPC_CLIENT_TARGET)
	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./$(GRPC_CLIENT_TARGET)

# 帮助信息
.PHONY: help
help:
	@echo "可用的 Make 目标："
	@echo "  make all         - 编译所有示例（基础 + gRPC）"
	@echo "  make             - 同 make all"
	@echo "  make run         - 编译并运行基础示例"
	@echo "  make run-server  - 编译并运行 gRPC 服务端"
	@echo "  make run-client  - 编译并运行 gRPC 客户端"
	@echo "  make clean       - 清理生成的文件"
	@echo "  make help        - 显示此帮助信息"

