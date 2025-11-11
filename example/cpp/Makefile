# Makefile for compiling C++ example

# 编译器配置
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -I../../generated/cpp -I/usr/local/include
LIBS = -lprotobuf

# 源文件和目标文件
EXAMPLE_SRC = example.cpp
PROTO_SRC = ../../generated/cpp/uav_service.pb.cc
EXAMPLE_TARGET = example
PROTO_OBJ = uav_service.pb.o

# 默认目标
.PHONY: all
all: $(EXAMPLE_TARGET)
	@echo "编译完成！运行 ./$(EXAMPLE_TARGET) 来执行示例"

# 编译示例程序
$(EXAMPLE_TARGET): $(EXAMPLE_SRC) $(PROTO_OBJ)
	@echo "正在编译 C++ 示例..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXAMPLE_TARGET) $(EXAMPLE_SRC) $(PROTO_OBJ) $(LIBS)
	@echo "编译成功！"

# 编译 protobuf 生成的代码
$(PROTO_OBJ): $(PROTO_SRC)
	@echo "正在编译 protobuf 代码..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(PROTO_SRC) -o $(PROTO_OBJ)

# 清理生成的文件
.PHONY: clean
clean:
	@echo "正在清理..."
	@rm -f $(EXAMPLE_TARGET) $(PROTO_OBJ)
	@echo "清理完成！"

# 运行示例
.PHONY: run
run: $(EXAMPLE_TARGET)
	@./$(EXAMPLE_TARGET)

# 帮助信息
.PHONY: help
help:
	@echo "可用的 Make 目标："
	@echo "  make        - 编译 C++ 示例"
	@echo "  make run    - 编译并运行示例"
	@echo "  make clean  - 清理生成的文件"
	@echo "  make help   - 显示此帮助信息"

