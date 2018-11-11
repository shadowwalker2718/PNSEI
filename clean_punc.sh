#!/bin/bash

if [ "$1" == "" ]; then
  RMDFILE=`find . -name "*.h"`
  CFILE=`find . -name "*.cpp"`
else
  RMDFILE=$1
fi

for i in $RMDFILE; do
echo $i
sed -i -e 's/。/./g' -e 's/，/,/g' -e 's/！/!/g' -e 's/：/:/g' -e 's/）/)/g' \
 -e 's/？/?/g' -e 's/”/"/g' -e 's/…/.../g' -e "s/’/'/g" -e "s/‘/'/g" -e "s/≥/>=/g" \
 -e "s/－/-/g" -e "s/［/[/g" -e "s/］/]/g" -e 's/“/"/g' -e 's/【/[/g' -e 's/】/]/g' \
 -e 's/『//g' -e 's/』//g' -e 's/；/;/g' $i;

done


for i in $CFILE; do
echo $i
sed -i -e 's/。/./g' -e 's/，/,/g' -e 's/！/!/g' -e 's/：/:/g' -e 's/）/)/g' \
 -e 's/？/?/g' -e 's/”/"/g' -e 's/…/.../g' -e "s/’/'/g" -e "s/‘/'/g" -e "s/≥/>=/g" \
 -e "s/－/-/g" -e "s/［/[/g" -e "s/］/]/g" -e 's/“/"/g' -e 's/【/[/g' -e 's/】/]/g' \
 -e 's/『//g' -e 's/』//g' -e 's/；/;/g' $i;

done


