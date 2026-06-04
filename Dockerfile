FROM ubuntu

# Install packages needed
RUN apt-get update && apt-get -y --no-install-recommends install \
        cmake \ 
        build-essential

COPY . ./WebServer

# Build the cmake project
RUN cd WebServer && cmake -S . -B build && cmake --build build
CMD ["WebServer/build/WebServer"]
