# use g++ compiler using C++ 17 standard
cc = g++ -std=c++17

# root for include directive and linter
root = ..

# compile with all warnings
flags = -Wall -pedantic
# compile with root on #include root
flags += -I $(root)
# compile with instrumentation for gdb
flags += -g

# compilation to intermediary .o files
compile = $(cc) $(flags) -c -o

# final linked build to binary executable
link = $(cc) -o


# compile YOUR code
# tax
bin/tax.o : src/tax.cc inc/tax.h
	$(compile) $@ $<
# item
bin/item.o : src/item.cc inc/item.h inc/tax.h
	$(compile) $@ $<


# lint code
# tax
tax-style : src/tax.cc inc/tax.h
	cpplint --root=$(root) $^
# item
item-style : src/item.cc inc/item.h
	cpplint --root=$(root) $^

# build and run against tests
#
test-tax : bin/test_tax.o bin/tax.o
	$(link) $@ $^
	./test-tax

# compile your code against MY tests
#
bin/test_tax.o : src/test_tax.cc inc/test_tax.h inc/tax.h
	$(compile) $@ $<

clean:
	rm -f bin/* test-tax
