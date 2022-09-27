#!/usr/bin/env bash

main() {
    SELF_DIR="$(dirname $(readlink -f ${BASH_SOURCE[0]}))"
    [ "${#}" -eq 0 ] && usage
    while getopts "mbrdh" opt; do
        case "${opt}" in
            m) container_make "build_container" && container_restart "httpd_container" ;;
            b) container_make "build_container" ;;
            r) container_restart "httpd_container" ;;
            d) container_bootstrap ;;
            h | *) usage ;;
        esac
    done
}

usage () {
    cat << EOF
usage: ${0} [-hmbrd]

Tools to assist with building and testing the module.

optional arguments:
    -h  show this help message and exit
    -m  build the software in a docker container and restart the testing
        environment container
    -b  only build the software
    -r  only restart the testing environment container
    -d  bootstrap the container environments
EOF
}

container_make() {
    echo "Building software..."
    docker run -v "${SELF_DIR}:${SELF_DIR}" -w "${SELF_DIR}" -i -t "${1}" /bin/bash -c "make"
}

container_restart() {
    echo "Restarting testing environment container..."
    docker restart "${1}"
}

container_bootstrap() {
    echo "Preparing build environment container..."
    (
        cd "${SELF_DIR}/../docker/build_container"
        docker build -t build_container .
    )
    echo "Building software for use in testing environment..."
    (
        cd "${SELF_DIR}"
        container_make "build_container"
    )
    echo "Preparing testing environment container..."
    (
        cd "${SELF_DIR}/../docker/httpd_container"
        docker-compose up -d --build
    )
}

main "${@}"
