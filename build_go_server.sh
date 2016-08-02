#!/bin/bash

version=`git describe --tags --abbrev=4`
echo "Github version: $version"
if [[ -n "$1" ]]
then
    version=$1
    echo "Forced version: $version"
fi

echo "Start build"
export GOPATH=`pwd`/gopath
cd $GOPATH/src/griefly-server
go build -ldflags "-X main.clientVersionBuild=$version"
cd -
echo "End build"
