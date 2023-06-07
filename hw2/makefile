cc = g++ -std=c++17  # use g++ compiler with C++ 17 source code

root = ..  # define root of project/system as parent dir

flags = -Wall      # compile with all warnings
flags += -I $(root) # compile with root on include preproc path
flags += -g         # compile with GDB instrumentation

link = $(cc) $(flags) -o  # final linked build to binary executable

compile = $(cc) $(flags) -c -o  # compilation to intermediary .o files


bin/parse_grades.o : src/parse_grades.cc inc/parse_grades.h
	$(compile) $@ $<

parse-grades-style : src/parse_grades.cc inc/parse_grades.h
	cpplint --root=$(root) $^


test-parse-num-stu : bin/test_parse_num_stu.o bin/parse_grades.o
	$(link) $@ $^
bin/test_parse_num_stu.o : src/test_parse_num_stu.cc inc/parse_grades.h
	$(compile) $@ $<


test-parse-num-exam : bin/test_parse_num_exam.o bin/parse_grades.o
	$(link) $@ $^
bin/test_parse_num_exam.o : src/test_parse_num_exam.cc inc/parse_grades.h
	$(compile) $@ $<


test-parse-quiz-values : bin/test_parse_quiz_values.o bin/parse_grades.o
	$(link) $@ $^
bin/test_parse_quiz_values.o : src/test_parse_quiz_values.cc inc/parse_grades.h
	$(compile) $@ $<


test-find-quiz : bin/test_find_quiz.o bin/parse_grades.o
	$(link) $@ $^
bin/test_find_quiz.o : src/test_find_quiz.cc inc/parse_grades.h
	$(compile) $@ $<


clean:
	$(RM) bin/*.o test-*
