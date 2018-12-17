#include "HighsSetup.h"
#include "LoadProblem.h"
#include "HighsTimer.h"

int main(int argc, char **argv) {
  // Initialise timer
  HighsTimer timer;
  int loadClock = timer.clockDef("Load", " Ld");
  int runClock = timer.clockDef("Run", "Run");
  //  timer.reset();

  // Load user options.
  HighsOptions options;
  HighsStatus init_status = loadOptions(argc, argv, options);

  // Use to replace old HighsOptions.
  // HighsStringOptions options_;
  // HighsStatus init_status_ = loadOptions(argc, argv, options_);

  if (init_status != HighsStatus::OK) {
//    printHelp(argv[0]);
    return 0;
  }

  HighsLp lp;
  timer.start(loadClock);
  HighsInputStatus read_status = loadLpFromFile(options, lp);
  timer.stop(loadClock);
  if (read_status != HighsInputStatus::OK) {
    return (int) HighsStatus::LpError;
  }

  Highs highs(options);
  HighsSolution solution;

  timer.start(runClock);
  HighsStatus run_status = highs.run(lp, solution);
  timer.stop(runClock);

  checkStatus(run_status);

  // Report times
  int clockList[] = {loadClock, runClock};
  timer.report(clockList);
  return 0;
}
