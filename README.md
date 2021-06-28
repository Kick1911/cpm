# C-lang Project Manager

The purpose of this project is to solve some of the biggest problems with C
development:

- Starting a C project (Directory structure)
- Building a project
- Dependency management

CPM creates a directory structure for your project and inserts a scalable
Makefile script for building your project.
Just add `.c` files and code. The Makefile script with recognise them and
compile them.

## Dependencies

Dependencies can be added in the project.mk file. These dependencies will
be downloaded and added to the project.

Requirements for dependencies:

- Must have a release with archive attached named `lib<project-name>.*`(regex)
- The header file must be located in `src/<project-name>.h`

## Create project

```bash
$ cpm init <project-name>
```

## Compile binary project
```bash
$ make
  CC src/cpm.c -> src/cpm.o
  CC src/components/init.c -> src/components/init.o
  CC src/components/update.c -> src/components/update.o
  CC src/utils/render.c -> src/utils/render.o
  CC src/utils/util.c -> src/utils/util.o
  BIN cpm
```

## Compile static project
```bash
$ make static_library
```

## Compile shared project
```bash
$ make shared_library
```

## Run tests
```bash
$ export DEBUG=-g3
$ make clean;cd tests;make
$ make test target=./test_<component>.out # Run one test
$ make test target=`ls ./*.out` # Run all tests
```

