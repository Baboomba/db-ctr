# 컴파일러
CC = gcc

# 컴파일 옵션
CFLAGS = -I/usr/include/python3.11 \
         -I/home/ansungeun/Documents/programming/.venv/base/lib/python3.11/site-packages/numpy/core/include \
		 -I/usr/include \
		 -I/usr/include/freetds \
		 -I/usr/lib

# 링크 옵션
LDFLAGS = -lpython3.11 \
		  -lmysqlclient \
		  -lodbc \
		  -L/usr/lib/x86_64-linux-gnu -lct

# 대상 파일 이름
TARGET = main

# 소스 파일 목록
SRCS = main.c src/ctr_mysql.c src/ctr_mssql.c

# 기본 빌드 규칙
all: $(TARGET)

# 실행 파일을 생성하기 위한 규칙
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

# 클린 규칙
clean:
	rm -f $(TARGET)

# 폴더 내의 모든 객체 파일 및 실행 파일을 삭제하는 규칙
.PHONY: all clean



# # 컴파일러
# CC = gcc

# # 컴파일 옵션
# CFLAGS = -I/usr/include/python3.11 \
#          -I/home/ansungeun/Documents/programming/.venv/base/lib/python3.11/site-packages/numpy/core/include

# # 링크 옵션
# LDFLAGS = -lpython3.11 -lmysqlclient

# # 대상 파일 이름
# TARGET = main

# # 소스 파일 목록
# SRCS = main.c src/ctr_mysql.c

# # 객체 파일 목록
# OBJS = $(SRCS:.c=.o)

# # 기본 빌드 규칙
# all: $(TARGET)

# # 실행 파일을 생성하기 위한 규칙
# $(TARGET): $(OBJS)
# 	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# # 개별 소스 파일을 객체 파일로 컴파일하기 위한 규칙
# %.o: %.c
# 	$(CC) -c $< -o $@ $(CFLAGS)

# # 클린 규칙
# clean:
# 	rm -f $(OBJS) $(TARGET)

# # 폴더 내의 모든 객체 파일 및 실행 파일을 삭제하는 규칙
# .PHONY: all clean
