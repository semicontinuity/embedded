#!/bin/bash
# Reads properties from the file $TARGET.conf and outputs them in the format -Dname=value.
# This is useful to pass defines to the C compiler

if [[ $# == 1 ]]; then
  CONF_FILE=$1
else
  CONF_FILE=$TARGET.conf
fi

cat ${CONF_FILE} | while read line; do
  if [ x"$line" != x ]; then
    chr=${line:0:1}
    case $chr in
    "#" )  # Currently we ignore commented lines
        ;;
     *  )
        echo \"-D$line\"
        ;;
    esac
  fi
done