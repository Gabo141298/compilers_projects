.PHONY: all clean test

all:
	@make -C build

configure:
	./configure

clean:
	@rm -frv build/
	@rm -frv parser

test: all
	@echo foo | ./parser
