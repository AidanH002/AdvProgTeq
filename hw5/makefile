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
# median 
bin/median.o: src/median.cc inc/median.h inc/statistic.h
	$(compile) $@ $<


# lint code
# median
median-style : src/median.cc inc/median.h
	cpplint --root=$(root) $^

# test 1
# collect test
test-median-collect: bin/test_median_collect.o bin/median.o
	$(link) $@ $^
# build
bin/test_median_collect.o: src/test_median_collect.cc inc/median.h \
        inc/statistic.h
	$(compile) $@ $<

# test 2
# calculate test
test-median-calculate: bin/test_median_calculate.o bin/median.o
	$(link) $@ $^
# build
bin/test_median_calculate.o: src/test_median_calculate.cc inc/median.h \
        inc/statistic.h
	$(compile) $@ $<

clean:
	$(RM) bin/* test-*
