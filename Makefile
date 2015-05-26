include incl.mk

CURRIDR = $(PROJECT_ROOT)

DIRS = $(RASPBIAN_DIR) $(BM_DIR)

all:
	@for dir in $(DIRS); do make -C $$dir; echo; done
rp:
	@cd $(RASPBIAN_DIR); make; cd $(CURRIDR);
bm:
	@cd $(BM_DIR); make; cd $(CURRIDR);
clean:
	@for dir in $(DIRS); do make -C $$dir clean; echo; done
#	rm -fv */*.txt */*.out */*.err */*~ */*.o */.*.d */*.log
#install:
#	@for dir in $(DIRS); do make -C $$dir install; echo; done
