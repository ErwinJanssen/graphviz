#!/bin/sh
cd ${TRAVIS_BUILD_DIR}
if [ ${SONARQUBE} ] ; then
    build-wrapper-linux-x86-64 --out-dir bw-output ./ci/${BUILD_SYSTEM}-build_and_test.sh
    sonar-scanner
elif [ ! ${DOCKER_BUILD} ] ; then
    ./ci/${BUILD_SYSTEM}-build_and_test.sh
elif [ ${DOCKER_BUILD} ] ; then
    docker run --rm -v `pwd`:/graphviz -w /graphviz -i -t centos7-build-env bash "ci/${BUILD_SYSTEM}-build_and_test.sh"
fi
