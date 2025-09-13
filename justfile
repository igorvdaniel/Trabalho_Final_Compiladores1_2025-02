src_path := "interpretador"
build_path := "interpretador/build"

build:
    cmake -G Ninja -S {{ src_path }} -B {{ build_path }}
    ninja -C {{ build_path }}

clean:
    rm -rf {{ build_path }}

run:
    ./{{ build_path }}/interpretador
