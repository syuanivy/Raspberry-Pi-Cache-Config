include ../../incl.mk

BM_LIBS			= $(LIB_DIR)/bm_timer.o\
				  $(LIB_DIR)/bm_io.o	

all: $(BM_LIBS) $(ENTRANCE) $(BM_TARGET)

$(BM_TARGET) : %.img : %.elf
	@echo
	@echo "====== Linking $^ ======"
	$(ARMGNU)objcopy $^ -O binary $@

$(ELF) : %.elf : %.o
	@echo 
	@echo "====== Linking $@ ======"
	$(ARMGNU)ld $(ENTRANCE) $^ $(BM_LIBS) -T $(MEMMAP) -o $@
#	$(ARMGNU)objdump -D $@ > objdump

$(ENTRANCE) : %.o : %.s
	@echo
	@echo "====== Assembling $@ ======"
	$(ARMGNU)as $^ -o $@
		
$(BM_LIBS): %.o : %.c
	@echo
	@echo "====== Compiling LIBS $@ ======"
	$(ARMGNU)$(CC) $(BM_FLAGS) $(INC_DIR) -c -o $@ $^

$(BM_OBJECTS) : %.o : %.c
	@echo
	@echo "====== Compiling $@ ======"
	$(ARMGNU)$(CC) $(BM_FLAGS) $(INC_DIR) -c -o $@ $^

rebuild: 
	clean all
r:
	rebuild

clean :
	@echo "Cleaning bare-metal folder..."
	-@rm -f *.o 2>/dev/null || true
	-@rm -f $(BM_LIBS) $(BM_TARGET) $(BM_OBJECTS) $(ELF) 2>/dev/null || true
#	rm -f *.bin
#	rm -f *.hex
#	rm -f *.elf
#	rm -f *.list
#	rm -f *.img
#	rm -f *.bc
#	rm -f *.clang.opt.s
