cmake_minimum_required(VERSION 3.15)
project(Shaft C)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(modulo_f)
include_directories(modulo_t)
include_directories(modulo_c)
include_directories(modulo_d)


add_executable(Shaft
        modulo_c/estruturas.c
        modulo_c/estruturas.h
        modulo_c/interpreta_codificacao.c
        modulo_c/interpreta_codificacao.h
        modulo_c/modulo_c.c
        modulo_c/modulo_c.h
        modulo_c/terminal.c
        modulo_c/terminal.h
        modulo_t/algoritmo_shanon_fanon.c
        modulo_t/algoritmo_shanon_fanon.h
        modulo_t/t_estruturas.c
        modulo_t/t_estruturas.h
        modulo_t/modulo_t.c
        modulo_t/modulo_t.h
        modulo_t/tratamento_file_cod.c
        modulo_t/tratamento_file_cod.h
        modulo_t/tratamento_file_freq.c
        modulo_t/tratamento_file_freq.h
        modulo_d/modulo_d.c
        modulo_d/modulo_d.h
        modulo_f/modulo_f.c
        modulo_f/modulo_f.h
        modulo_f/functions.c
        modulo_f/functions.h
        modulo_f/functions_freq.c
        modulo_f/functions_freq.h
        modulo_f/functions_rle.c
        modulo_f/functions_rle.h
        comum.c
        comum.h
        interface.c
        interface.h
        shafa.c)

target_link_libraries(Shaft m)