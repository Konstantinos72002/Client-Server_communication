compile_Server:
	$(MAKE) -C Server

compile_Client:
	$(MAKE) -C Client


compile_all: compile_Server compile_Client

run_2:
	./pollSwayer localhost 5640 input_file &
	./pollSwayer localhost 5640 input_file2 &