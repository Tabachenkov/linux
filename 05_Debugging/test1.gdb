set pagination off

b range_get if r->i % 5 == 0
commands
	silent
	printf "@@@ start=%d stop=%d step=%d i=%d\n", r->start, r->stop, r->step, r->i
	continue
end

run 1 12 > /dev/null
quit
