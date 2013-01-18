#!/bin/sh

echo '{"version": 1, "click_events":true }'
echo '['
echo '[]'

exec $HOME/Apps/cdialog/ccanvash.bin -asBar $* | grep -e 'full_text'
