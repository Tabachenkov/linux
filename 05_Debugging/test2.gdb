set pagination off
set $count = 0

b range_get
commands
    silent
	set $count = $count + 1
	if $count >= 28 && $count <= 35
        	printf "@@@ start=%d stop=%d step=%d i=%d\n", r->start, r->stop, r->step, r->i
    end
	continue
end

run -100 100 3 > /dev/null
quit
