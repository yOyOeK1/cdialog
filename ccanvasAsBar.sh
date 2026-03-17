#!/bin/sh

echo '{"version": 1}'
echo '['
echo '[]'

exec /home/yoyo/Apps/cdialog/ccanvash.bin -asBar $* | grep -e 'full_text'
