DOCKER_RUN=docker run -w /files --rm -it  -v `pwd`:/files -a STDOUT -a STDERR nihohit/data-oriented-design-demo:latest
BUILD_DEBUG=${CXX} -std=c++17 -o check *.cpp -O0 -g  -isystem gsl/include
BUILD_RELEASE=${CXX} -std=c++17 -o check *.cpp -O0 -g  -isystem gsl/include
RUN=./check ${MODELS} ${ANIMATIONS} ${REPETITIONS}

clean:
	rm -rf ./check

debug: *.cpp *.hpp
	${BUILD_DEBUG}

check: *.cpp *.hpp
	${BUILD_RELEASE}

docker-build-debug: *.cpp *.hpp
	${DOCKER_RUN} ${BUILD_DEBUG}

docker-build-release: *.cpp *.hpp
	${DOCKER_RUN} ${BUILD_RELEASE}

run-debug: docker-build-debug
	${DOCKER_RUN} ${RUN}

run-check: docker-build-release
	${DOCKER_RUN} ${RUN}
