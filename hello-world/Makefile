CONTIKI_PROJECT = hello-world
all: $(CONTIKI_PROJECT)

CONTIKI_WITH_IPV6 = 0
CONTIKI_WITH_RIME = 1

CONTIKI = $(HOME)/contiki-git
include $(CONTIKI)/Makefile.include

erase: 
	/home/csse3010/uniflash_3.4/uniflash.sh -ccxml ~/Downloads/sensortag.ccxml -targetOp reset -operation Erase

prog: 
	/home/csse3010/Downloads/DSLite/DebugServer/bin/DSLite load -c ~/Downloads/DSLite/CC2650F128_TIXDS110_Connection.ccxml -f $(CONTIKI_PROJECT).elf

progu: 
	/home/csse3010/uniflash_3.4/uniflash.sh -ccxml ~/Downloads/sensortag.ccxml -targetOp reset -operation Erase
	/home/csse3010/uniflash_3.4/uniflash.sh -ccxml ~/Downloads/sensortag.ccxml -program $(CONTIKI_PROJECT).hex
