#!/bin/sh
ndk-build $@ APP_ABI=$ABI && mv libs/$ABI/tool-runner libs/$ABI/libtool-runner.so
