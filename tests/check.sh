#!/bin/sh

echo > check.log

tests=0
passed=0
failed=0

for file in $(echo check/*.cu)
do
	testcase=$(echo "$file" | cut -f 1 -d '.')
	expected="$testcase".ok
	args=$(test -e "$testcase".args && cat "$testcase".args)

	echo -n testing "$testcase"...

	cmd="./cu "$args" "$file" -o check/run && ./check/run"

	tests=$((tests + 1))
	if test "$output" = "$expected"
	then
		passed=$((passed + 1))
		echo ok
	else
		failed=$((failed + 1))
		echo fail
	fi;

	if test -n "$VERBOSE"
	then
		echo "$cmd"
	fi
done

echo
echo tests "$tests", passed "$passed", failed "$failed"
