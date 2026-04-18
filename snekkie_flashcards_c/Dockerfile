FROM debian:sid
RUN apt-get update && apt-get install -y make build-essential valgrind
WORKDIR /src
RUN mkdir /data
RUN mkdir /data/dummy-safe
RUN mkdir /data/readonly
RUN chmod -R a-w /data/readonly
COPY . .
RUN make build
RUN make build_tests
RUN chmod +x /src/compiled/snekkie-flashcards.bin
RUN chmod +x /src/tests-compiled/*
ENV PATH="/src/compiled/:/src/tests-compiled:${PATH}"
ENTRYPOINT ["/src/compiled/snekkie-flashcards.bin"]
