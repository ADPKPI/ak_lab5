KDIR := /lib/modules/$(shell uname -r)/build

# Підключення заголовкового файлу
ccflags-y := -I$(PWD)/inc

# Модулі ядра
obj-m += hello1.o
obj-m += hello2.o

# Шлях до файлів
hello1-objs := src/hello1.o
hello2-objs := src/hello2.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
