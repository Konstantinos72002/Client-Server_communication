compile_Server:
	$(MAKE) -C Server -w --no-print-directory

compile_Client:
	$(MAKE) -C Client -w --no-print-directory


compile_all: compile_Server compile_Client