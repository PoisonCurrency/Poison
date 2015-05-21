#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/poison.ico

convert ../../src/qt/res/icons/poison-16.png ../../src/qt/res/icons/poison-32.png ../../src/qt/res/icons/poison-48.png ${ICON_DST}
