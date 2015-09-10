set -e

echo "Running unit tests:"

for i in tests/*_tests
do
	if test -f $i
	then
		if $VALGRIND ./$i build/libex29.so uppercase "hello world" 2>> tests/tests.log
		then
			echo $i PASS
		else
			echo "ERROR in test $i: here's tests/tests.log"
			echo "_____"
			tail tests/tests.log
			exit 1
		fi
	fi
done

echo ""