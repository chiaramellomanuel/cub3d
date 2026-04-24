#!/bin/bash

CUB3D_BIN="./cub3d"
TEST_DIR="./tests/cubs"
LOG_DIR="./tests/logs"
EXP_DIR="./tests/expected"
VALGRIND=""

rm -r "$LOG_DIR" 2> /dev/null
mkdir -p "$LOG_DIR"
pass=0
fail=0
val=0

if [ "$1" = "valgrind" ]; then
	VALGRIND="valgrind --leak-check=full --error-exitcode=42 --track-origins=yes --show-leak-kinds=all --suppressions=valgrind.supp -v"
	val=1
fi

run_tests_for() {
	TEST_NAME="$1"
	EXP_STATUS="$2"
	tests=("$TEST_DIR"/$TEST_NAME/*)

	echo
	echo -n "📦 Test: $TEST_NAME:		"
	
	for file in "${tests[@]}"; do
		tmp_err=$(mktemp)
		tmp_vg=$(mktemp)
		vg_status=0
		name=$(basename "$file" .cub)
		final_log="$LOG_DIR/$TEST_NAME/${name}.log"
		expected_log="$EXP_DIR/$TEST_NAME/${name}.log"

		if [ $val -eq 1 ]; then
			{ time $VALGRIND $CUB3D_BIN "$file" --test >/dev/null 2>"$tmp_vg"; } 2>/dev/null
			vg_status=$?
			if [ $vg_status -ne 42 ]; then
				{ time $CUB3D_BIN "$file" --test >/dev/null 2>"$tmp_err"; } 2>/dev/null
				status=$?
			fi
		else
			{ time $CUB3D_BIN "$file" --test >/dev/null 2>"$tmp_err"; } 2>/dev/null
			status=$?
		fi
		
		if [ $vg_status -eq 42 ]; then
				mkdir -p "$LOG_DIR/$TEST_NAME" 2> /dev/null
				cp "$tmp_vg" "$final_log"
				echo -n "❌"
				((fail++))
		elif [ $status -eq $EXP_STATUS ]; then
			if [ ! -f "$expected_log" ]; then
				mkdir -p "$EXP_DIR/$TEST_NAME" 2> /dev/null
				cp "$tmp_err" "$expected_log"
			elif ! cmp -s "$tmp_err" "$expected_log"; then
				mkdir -p "$LOG_DIR/$TEST_NAME" 2> /dev/null
				{
					echo "---expected output---"
					cat "$expected_log"
					echo
					echo "---your output---"
					cat "$tmp_err"
					echo
					echo "---diff---"
					diff -u "$expected_log" "$tmp_err" || true
				} > "$final_log"
				echo -n "❌"
				((fail++))
			else
				echo -n "✅"
				((pass++))
			fi
		else
			mkdir -p "$LOG_DIR/$TEST_NAME" 2> /dev/null
			echo "expected exit status: $EXP_STATUS" > "$final_log"
			echo "your exit status: $status" >> "$final_log"
			echo -n "❌"
			((fail++))
		fi
		rm -f "$tmp_err"
		rm -f "$tmp_vg"
	done
}

run_tests_for file_name 1
run_tests_for texture_path 1
run_tests_for col_gradient 1
run_tests_for map/player 1
run_tests_for map/m_wall 1
run_tests_for /map/inv_char 1
run_tests_for passing_tests 0

echo
echo
echo "––––––––––––––––––––––––"
echo "✅ Passed: $pass"
echo "❌ Failed: $fail"