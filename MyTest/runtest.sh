#!/bin/bash
cd queue

echo -e "[\033[32m+\033[0m] Making project"
make

echo -e "[\033[32m+\033[0m] Start test"
cnt=1
for dic in `ls ../testcase`;
do
  inputFile="../testcase/$dic/input.txt"
  memoryFile="../testcase/$dic/memory.txt"
  outputFile="../output/${dic}.txt"
  checkOutput="../testcase/$dic/output.txt"

  START=$(date +%s.%N)
  ./VirtualMachine -i ${inputFile} -m ${memoryFile} -o ${outputFile}
  END=$(date +%s.%N)
  DIFF=$(echo "$END - $START" | bc)
  echo -e "Task #${cnt} (${dic}) Used time: ${DIFF} \c"

  DIFF=$(diff ${outputFile} ${checkOutput})
  if [ "$DIFF" != "" ]
  then
    echo -e "\033[31mError\033[0m"
  else
    echo -e "\033[32mSuccess\033[0m"
  fi

  cnt=`expr $cnt + 1`
done
