#!/bin/sh
ndk-build $@ APP_ABI=$ABI
mkdir -p assets/plugins
rm -f assets/plugins/*
for i in android_output file flac id3v2 mad tremor curl icymetaint modplug faad mp4
do
	mv libs/$ABI/lib$i.so assets/plugins/lib$i.so ;
done
