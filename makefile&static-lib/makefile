#main:main.c
#	gcc main.c -o main -I ./include/ -L ./include/ -ltest 

#get all .c files
SrcFiles = $(wildcard *.c)

#get all .o from .c files
ObjectFiles = $(patsubst %.c, %.o, $(SrcFiles))  #main.o

#目标文件用法
app:$(ObjectFiles)
	gcc $(ObjectFiles) -o main -I ./include -L ./include -ltest
	#gcc main.o -o main -I ./include/ -L ./include/ -ltest

#模式匹配规则
%.o:%.c
	gcc -o $@ -c $< -I ./include -L ./include -ltest

#main.o:main.c
#	gcc -c main.c -I ./include/ -L ./include/ -ltest

#防止歧义
.PHONY:clean

#@在规则前不输出命令
#-表示规则失败继续执行
test:
	@echo $(SrcFiles)
	@echo $(ObjectFiles)
clean:
	@rm -f *.o
	@rm -f main
