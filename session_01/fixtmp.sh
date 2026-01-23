#!/bin/bash

echo "clearing /tmp ..."

/bin/rm -r /tmp/.X11-unix
/bin/rm /tmp/XWin.log

echo "Ok, checking /tmp ..."
ls -alF /tmp
