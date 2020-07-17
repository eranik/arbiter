#!/bin/bash

# zip file contianing submission zip files
BASE_ZIP="$1"
# Defines the entry point for the console application.
APP_ENTRY_FILE="./cmpt225a1statistics.cpp"
# Seconds
EXECUTION_TIMEOUT=20

BASE_EXTRACTED="$BASE_ZIP""_extracted"
COMPILED_PATH="$BASE_EXTRACTED""/COMPILED"
NOT_COMPILED_PATH="$BASE_EXTRACTED""/NOT_COMPILED"
TIMED_OUT_PATH="$COMPILED_PATH""/TIMED_OUT"
SEG_FAULTED_PATH="$COMPILED_PATH""/SEG_FAULT"
NOT_SEG_FAULTED_PATH="$COMPILED_PATH""/OK"
mkdir -p "$BASE_EXTRACTED" "$COMPILED_PATH" "$NOT_COMPILED_PATH" "$SEG_FAULTED_PATH" "$NOT_SEG_FAULTED_PATH" "$TIMED_OUT_PATH"

COMPILE_COMMAND="g++ -w $APP_ENTRY_FILE ./Sequence.cpp &>./compile.log"
RUN_COMMAND="./a.out &> ./run.log"        # for dev-testing current script for seg-fault use: "kill -11 $$"

unzip "$BASE_ZIP" -d "$BASE_EXTRACTED"
pushd "$BASE_EXTRACTED"
    mkdir -p ./ZIP_FILES
    find . -iname "*.zip" -exec unzip "{}" -d "{}_extracted" \;
    find . -maxdepth 1 -iname "*.zip" -exec mv "{}" "./ZIP_FILES/" \;
popd

for i in "$BASE_EXTRACTED/"*_extracted
do
    cp "$APP_ENTRY_FILE" "$i"
    pushd "$i"
        bash -c "${COMPILE_COMMAND}"
        compile_result=$?
    popd
    if [ "$compile_result" == 0 ]
    then
        seg_faulted=false
        trap "seg_faulted=true" SIGSEGV

        pushd "$i"
            start_time=$(date +%s%3N)
                timeout $EXECUTION_TIMEOUT bash -c "${RUN_COMMAND}"
                runner_sub_bash_return=$?
            end_time=$(date +%s%3N)
            run_duration=$(bc -l <<< "scale=3; ($end_time-$start_time)/1000.0")
            echo "Run duration: $run_duration (s)" >> ./time.log
            if [ "$runner_sub_bash_return" == 124 ] # timeout
            then
                echo "Exceeded time-out limit of $EXECUTION_TIMEOUT (s)" >> ./time.log
            elif [ "$runner_sub_bash_return" != 0 ] # segfault
            then
                seg_faulted=true
            fi
        popd

        if [ "$runner_sub_bash_return" == 124 ]
        then
            mv "$i" "$TIMED_OUT_PATH"
        elif [ "$seg_faulted" = true ]
        then
            mv "$i" "$SEG_FAULTED_PATH"
        else
            mv "$i" "$NOT_SEG_FAULTED_PATH"
        fi
    else
        mv "$i" "$NOT_COMPILED_PATH"
    fi
done
