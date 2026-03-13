#!/bin/sh

exec alacritty \
	-o "window.dimensions.lines=20" \
	-o "window.dimensions.columns=60" \
	--title "cdialoger" \
	-e build2Res.bin1
