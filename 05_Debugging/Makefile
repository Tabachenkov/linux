.RECIPEPREFIX=:

NUMBERS = 1 2

all: range

range: range.c
:cc -O0 -g range.c -o range

clean:
:rm -f range *.log res*.txt

test: range
:for num in $(NUMBERS); do \
	gdb --batch --quiet -x test$${num}.gdb ./range > test$${num}.log 2>&1; \
	grep '^@@@' test$${num}.log > res$${num}.txt; \
	cmp test$${num}.txt res$${num}.txt || exit 1; \
	echo "Test $${num} is passed"; \
done
