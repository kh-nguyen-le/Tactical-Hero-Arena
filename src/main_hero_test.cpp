#include <cadmium/core/logger/csv.hpp>  // To import a CSV logger (to store simulation results in CSV file)
#include <cadmium/core/simulation/root_coordinator.hpp>  // To import the root coordinator
#include <limits>
#include "../model/testhero.hpp"

int main() {
  auto model = std::make_shared<TestHero>("hero");
  auto rootCoordinator = cadmium::RootCoordinator(model);

  auto logger = std::make_shared<cadmium::CSVLogger>("log_hero.csv", ";");
  rootCoordinator.setLogger(logger);
  
  // To start the simulation we 1) start, 2) simulate 3) stop.
  rootCoordinator.start();
  // in simulate method, we can select a maximum simulation time (in this case, infinity)
  rootCoordinator.simulate(std::numeric_limits<double>::infinity());
  rootCoordinator.stop();

  return 0;
}