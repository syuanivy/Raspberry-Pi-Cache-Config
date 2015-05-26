#!/usr/bin/python
import os
import platform
import re
from subprocess import * 

env_dict = {}

def def_env():
    global env_dict
    env_dict['PROJECT_ROOT']	= os.path.abspath('.')
    detect_chip()
    env_dict['LIB_DIR']		= '$(PROJECT_ROOT)/lib'
    env_dict['INC_DIR']		= '-I$(PROJECT_ROOT)/include'
    #------------------------------------------------
    # for raspbian
    #------------------------------------------------"""
    env_dict['RASPBIAN_DIR']	= '$(PROJECT_ROOT)/src/raspbian'
    env_dict['CC']		= 'gcc'
    env_dict['FLAGS']		= '-std=c99 -Wall -O0'
    env_dict['SOURCE']		= '$(wildcard $(RASPBIAN_DIR)/*.c)'
    env_dict['OBJECTS']		= '$(patsubst %.c, %.o, $(SOURCE))'
    env_dict['TARGETS']		= '$(patsubst %.c, %, $(SOURCE))'
    #------------------------------------------------
    # for bare-metal
    #------------------------------------------------"""
    env_dict['BM_DIR']		= '$(PROJECT_ROOT)/src/bare-metal'
    env_dict['BM_SOURCE']	= '$(wildcard $(BM_DIR)/*.c)'
    env_dict['BM_OBJECTS']	= '$(patsubst %.c, %.o, $(BM_SOURCE))'
    env_dict['BM_TARGET']	= '$(patsubst %.c, %.img, $(BM_SOURCE))'
    env_dict['BM_FLAGS']	= '-std=c99 -Wall -O0 -nostdlib -nostartfiles -ffreestanding -mcpu=arm1176jzf-s'
    env_dict['ELF']		= '$(patsubst %.c, %.elf, $(BM_SOURCE))'
    env_dict['ENTRANCE']	= '$(BM_DIR)/entrance.o'
    env_dict['MEMMAP']		= '$(BM_DIR)/linker_script.ld'
    return env_dict
    
def detect_chip():
    global env_dict
    system_info = check_output(['uname', '-a']),
    match = re.search('arm', system_info[0]);
    if match == None:
	env_dict['ARMGNU'] = 'arm-none-eabi-'
	env_dict['EXTRA_LIBS'] = '-lgcc -lc -lm -lrdimon'

def main():
    env_dict = def_env()
    f = open('incl.mk', 'w')
    for key in env_dict:
	line = key + '=' + env_dict[key] + '\n'
	f.write(line)

if __name__ == '__main__':
    main()

