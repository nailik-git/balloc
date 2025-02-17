#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char* argv[]) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  nob_mkdir_if_not_exists("build");

  Nob_Cmd cmd = {0};

  if(nob_needs_rebuild("balloc.o", (const char*[]){"balloc.c", "balloc.h"}, 2)) {
    nob_cmd_append(&cmd, "clang", "-c", "-g", "-O3", "-Wall", "-Wextra");
    nob_cmd_append(&cmd, "balloc.c");
    if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;
  } else {
    nob_log(NOB_INFO, "'balloc.o' up to date");
  }

  if(nob_needs_rebuild("build/test", (const char*[]){"test.c", "balloc.o", "balloc.h"}, 3)) {
    nob_cmd_append(&cmd, "clang", "-g", "-O3", "-Wall", "-Wextra");
    nob_cmd_append(&cmd, "-o", "build/test", "balloc.o", "test.c");
    if(!nob_cmd_run_sync(cmd)) return 1;
  } else {
    nob_log(NOB_INFO, "'test' up to date");
  }

  return 0;
}
