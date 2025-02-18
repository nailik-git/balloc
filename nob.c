#define NOB_IMPLEMENTATION
#include "nob.h"

#include <stdio.h>

#define BUILD "build/"
#define SRC "src/"
#define NUM_TESTS 3

int build_tests(Nob_Cmd cmd) {
  char input[64];
  char output[64];
  for(int i = 1; i <= NUM_TESTS; i++) {
    sprintf(input, SRC"test%d.c", i);
    sprintf(output, BUILD"test%d", i);

    if(nob_needs_rebuild(output, (const char*[]){input, SRC"balloc.h", BUILD"balloc.o"}, 3)) {
      nob_cmd_append(&cmd, "clang", "-g", "-O3", "-Wall", "-Wextra");
      nob_cmd_append(&cmd, input, BUILD"balloc.o", "-o", output);

      if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;
    }
    else nob_log(NOB_INFO, "'%s' up to date", output);
  }
  return 0;
}

int run_tests(Nob_Cmd cmd) {
  char path[64];
  for(int i = 1; i <= NUM_TESTS; i++) {
    sprintf(path, BUILD"test%d", i);

    nob_cmd_append(&cmd, path);

    if(nob_cmd_run_sync_and_reset(&cmd)) printf("success\n");
    else return 1;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  nob_mkdir_if_not_exists("build");

  Nob_Cmd cmd = {0};

  if(nob_needs_rebuild(BUILD"balloc.o", (const char*[]){SRC"balloc.c", SRC"balloc.h"}, 2)) {
    nob_cmd_append(&cmd, "clang", "-c", "-g", "-O3", "-Wall", "-Wextra");
    nob_cmd_append(&cmd, SRC"balloc.c", "-o", BUILD"balloc.o");
    if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;
  } else {
    nob_log(NOB_INFO, "'balloc.o' up to date");
  }

  if(build_tests(cmd)) return 1;

  if(argc > 1 && strncmp(argv[1], "test", 4) == 0) {
    if(run_tests(cmd)) return 1;
  }

  return 0;
}
