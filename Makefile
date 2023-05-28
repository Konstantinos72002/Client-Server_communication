compile_Server:
	$(MAKE) -C Server

compile_Client:
	$(MAKE) -C Client


compile_all: compile_Server compile_Client