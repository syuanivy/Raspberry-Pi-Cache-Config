include ../../incl.mk

LIBS			= $(LIB_DIR)/timer.o

#------------------------------------------------
# by default we will build the RP local version
#------------------------------------------------
all: rp

#------------------------------------------------
# this target is for running on raspberry pi
#------------------------------------------------
rp: raspberry-pi
raspberry-pi: $(LIBS) $(TARGETS)

$(TARGETS): % : %.o
	@echo
	@echo "====== Linking $@ ======"
	$(ARMGNU)$(CC) -o $@ $^ -lm $(LIBS) $(EXTRA_LIBS)
		
$(LIBS): %.o : %.c
	@echo
	@echo "====== Compiling $@ ======"
	$(ARMGNU)$(CC) $(FLAGS) $(INC_DIR) -c -o $@ $^

%.o : %.c
	@echo
	@echo "====== Compiling $@ ======"
	$(ARMGNU)$(CC) $(FLAGS) $(INC_DIR) -c -o $@ $^


#------------------------------------------------
# housekeeping targets
#------------------------------------------------
clean:
	@echo "Cleaning raspbian folder..."
	-@rm $(LIBS) $(OBJECTS) $(TARGETS) 2>/dev/null || true

