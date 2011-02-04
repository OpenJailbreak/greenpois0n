#!/bin/bash
export PATH=/usr/bin:/bin:/sbin:/usr/sbin
wuntar "$1" / 2>/tmp/aptoutput
exitcode=$?
echo "wuntar exited with" $exitcode
exit $exitcode
