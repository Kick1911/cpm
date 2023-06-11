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
```

## Gitlab CI
```yaml
variables:
  PROJECT_NAME: <project name>
  PACKAGE_REGISTRY_BASE_URL: "$CI_API_V4_URL/projects/$CI_PROJECT_ID/packages/generic"
  ARCHIVE_URL: '$PACKAGE_REGISTRY_BASE_URL/dist/$CI_COMMIT_TAG/dist.tar.gz'

stages:
  - test
  - upload
  - release

test_and_build:
  stage: test
  image: gcc
  before_script:
    - apt update && apt -y install make valgrind
  script:
    - make test
    - make clean
    - make package
  artifacts:
    paths:
      - './$PROJECT_NAME-*.tar.gz'

upload:
  stage: upload
  image: curlimages/curl:latest
  rules:
    - if: $CI_COMMIT_TAG
  script:
    - |
      curl --header "JOB-TOKEN: $CI_JOB_TOKEN" --upload-file $PROJECT_NAME-*.tar.gz $ARCHIVE_URL

release:
  stage: release
  image: registry.gitlab.com/gitlab-org/release-cli:latest
  rules:
    - if: $CI_COMMIT_TAG
  script:
    - echo "Releasing $CI_COMMIT_TAG"
  release:
    name: 'Release $CI_COMMIT_TAG'
    tag_name: '$CI_COMMIT_TAG'
    ref: '$CI_COMMIT_SHA'
    description: '64bit release $CI_COMMIT_TAG'
    assets:
      links:
        - name: dist.tar.gz
          url: '$ARCHIVE_URL'
```
