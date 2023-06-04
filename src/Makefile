USER=$(shell whoami)
COMMIT=Dev
FLAGS=-Wall -Werror -Wextra
CC=gcc
GFLAGS=-fprofile-arcs -ftest-coverage
LFLAGS=-lm -lcheck
CLEAN_FILES=a.out test.out s21_decimal.a *.info *.gcno *.gcda unit_test

all: clean s21_decimal.a gcov_report

s21_decimal.a: clean
	$(CC) $(FLAGS) -c s21_decimal.c
	ar -crs s21_decimal.a s21_decimal.o
	ranlib s21_decimal.a
	rm -rf *.o

test: s21_decimal.a
	$(CC) $(FLAGS) test.c s21_decimal.c -o test.out $(LFLAGS) s21_decimal.a
	./test.out

gcov_report: clean test
	$(CC) $(FLAGS) $(GFLAGS) test.c s21_decimal.c -o unit_test $(LFLAGS)
	./unit_test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

clean:
	rm -rf $(CLEAN_FILES)
	rm -rf report

git: git_add git_commit git_push

git_add:
	git add .

git_commit:
	git commit -m "$(COMMIT)"

git_push:
	git push origin $(USER)

style_check:
	clang-format -style=Google -n *.c *.h

style_correct:
	clang-format -style=Google -i *c *.h