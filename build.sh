#!/bin/sh
ndk-build $@
mkdir -p assets/plugins
for i in android_output file flac id3v2 mad tremor curl icymetaint modplug
do
	mv libs/armeabi/lib$i.so assets/plugins/lib$i.so ;
done
