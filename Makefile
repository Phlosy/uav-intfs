# Makefile for generating Python and C++ code from Protocol Buffers

# 配置变量
PROTO_FILE = uav_service.proto
PROTO_DIR = .
PYTHON_OUT_DIR = generated/python
CPP_OUT_DIR = generated/cpp
PROTOC = protoc

# Python 相关配置
PYTHON_PACKAGE = uav

# C++ 相关配置
CPP_NAMESPACE = uav

# 默认目标：生成所有代码
.PHONY: all
all: clean python cpp
	@echo "所有代码生成完成！"

# 生成 Python 代码（生成前先清理）
.PHONY: python
python: clean-python $(PYTHON_OUT_DIR)
	@echo "正在生成 Python 代码..."
	$(PROTOC) --python_out=$(PYTHON_OUT_DIR) \
	          --proto_path=$(PROTO_DIR) \
	          $(PROTO_FILE)
	@echo "Python 代码生成完成！输出目录: $(PYTHON_OUT_DIR)"

# 生成 C++ 代码（生成前先清理）
.PHONY: cpp
cpp: clean-cpp $(CPP_OUT_DIR)
	@echo "正在生成 C++ 代码..."
	$(PROTOC) --cpp_out=$(CPP_OUT_DIR) \
	          --proto_path=$(PROTO_DIR) \
	          $(PROTO_FILE)
	@echo "C++ 代码生成完成！输出目录: $(CPP_OUT_DIR)"

# 创建输出目录
$(PYTHON_OUT_DIR):
	@mkdir -p $(PYTHON_OUT_DIR)

$(CPP_OUT_DIR):
	@mkdir -p $(CPP_OUT_DIR)

# 清理生成的代码
.PHONY: clean
clean:
	@echo "正在清理生成的代码..."
	@rm -rf $(PYTHON_OUT_DIR)
	@rm -rf $(CPP_OUT_DIR)
	@echo "清理完成！"

# 仅清理 Python 代码
.PHONY: clean-python
clean-python:
	@echo "正在清理 Python 代码..."
	@rm -rf $(PYTHON_OUT_DIR)
	@echo "Python 代码清理完成！"

# 仅清理 C++ 代码
.PHONY: clean-cpp
clean-cpp:
	@echo "正在清理 C++ 代码..."
	@rm -rf $(CPP_OUT_DIR)
	@echo "C++ 代码清理完成！"

# 帮助信息
.PHONY: help
help:
	@echo "可用的 Make 目标："
	@echo "  make all          - 清理并生成所有代码（Python + C++）"
	@echo "  make python       - 清理并生成 Python 代码"
	@echo "  make cpp          - 清理并生成 C++ 代码"
	@echo "  make clean        - 清理所有生成的代码"
	@echo "  make clean-python - 仅清理 Python 代码"
	@echo "  make clean-cpp    - 仅清理 C++ 代码"
	@echo "  make help         - 显示此帮助信息"

