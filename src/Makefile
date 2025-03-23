# Makefile

# 编译器
CC = gcc.exe
CPPC = g++.exe
WINDRES = windres.exe
MAKE = make.exe

# 目录设置
SRC_DIR = src/
INC_DIR = src/includes/
BUILD_DIR = build/build/
DEST_DIR = build/dest/

# 编译选项
CFLAGS = -fdiagnostics-color=always -I"./${SRC_DIR}" -I"./${INC_DIR}"

# 源文件和目标文件
SRC = $(SRC_DIR)main.cpp
OBJ = \
$(BUILD_DIR)main.o\
$(BUILD_DIR)version.o\
$(BUILD_DIR)program_info.o

# 按需启用图标
# OBJ += $(BUILD_DIR)resource.res

# 目标可执行文件
TARGET = $(DEST_DIR)Example.exe

# 目标规则
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJ)
	@ echo Compiling $@
	$(CPPC) -fdiagnostics-color=always $(OBJ) -o $(TARGET)

# 编译源文件生成目标文件
# build/%.o: src/%.c
# 	$(CPPC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)program_info.o: $(SRC_DIR)program_info.cpp $(SRC_DIR)version.rc flag_every_time
	@ echo Compiling $@
	$(CPPC) $(CFLAGS) -c $< -o $@
	
$(BUILD_DIR)version.o: $(SRC_DIR)version.rc
	@ echo Compiling $@
	$(WINDRES) $< -o $@

$(BUILD_DIR)resource.res: $(SRC_DIR)resource.rc $(INC_DIR)resource.hpp
	@ echo Compiling $@
	$(WINDRES) -I"./${SRC_DIR}" -I"./${INC_DIR}" -i $< -O coff -o $@

$(BUILD_DIR)main.o: $(SRC_DIR)main.cpp \
	$(INC_DIR)program_info.hpp $(SRC_DIR)version.rc $(INC_DIR)resource.hpp
	@ echo Compiling $@
	$(CPPC) $(CFLAGS) -c $< -o $@


define clean_file
	del /Q /F "$(subst /,\\,$(1))"
endef

# 清理生成的文件
clean:
	$(foreach obj_i, $(OBJ), $(call clean_file,$(obj_i)))


define mkdir_withcheck
	@ echo "Checking directory $(subst /,\\,$(strip $1))"
	@ if not exist "$(subst /,\\,$(strip $1))" mkdir "$(subst /,\\,$(strip $1))" && echo "Directory $(subst /,\\,$(strip $1)) created"
endef

prepare_dir:
	$(call mkdir_withcheck,"$(BUILD_DIR)")
	$(call mkdir_withcheck,"$(DEST_DIR)")

flag_every_time:
	@ REM "flag_every_time" # @ echo "flag_every_time"	# This will be executed every time
	

.PHONY: all clean prepare_dir flag_every_time
