Singularity
===========

Compilación
-----------

La primera vez que se vaya a compilar y cada vez que se haga un clean, se debe correr el siguiente comando.

```sh
$ ./configure
```

Una vez que haya ejecutado, se podrá correr el comando:

```sh
$ ./make
```

Ejecución del programa
---

Para usar el programa, se ejecuta el comando:

```sh
$ ./parser <nombre_archivo>
```

Dependencias
------------

* Bison
* Flex
* CMake
* Versión reciente del compilador de C++ (`g++` or `clang++`)
* LLVM, preferiblemente la versión 7.

Reconocimiento
--------------

Tomamos el código del repositorio https://github.com/remusao/Bison-Flex-CPP-template, que nos presenta una plantilla para usar Bison y Flex con C++.