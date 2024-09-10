# 定义编译器
CC=gcc

# 定义编译选项，-g 用于调试，-Wall 显示所有警告
CFLAGS=-g -Wall

# 定义目标文件名
TARGET=myprogram

# 定义源文件
SOURCES=$(TARGET).c

# 定义对象文件
OBJECTS=$(SOURCES:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译源文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -f $(TARGET) $(OBJECTS)

# 伪目标，避免与同名文件冲突
.PHONY: all clean
