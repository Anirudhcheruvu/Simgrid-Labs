/* Copyright (c) 2010-2019. The SimGrid Team. All rights reserved.          */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

/* ********************************************************************************** */
/* Take this tutorial online: https://simgrid.org/doc/latest/Tutorial_Algorithms.html */
/* ********************************************************************************** */

#include <simgrid/s4u.hpp>

XBT_LOG_NEW_DEFAULT_CATEGORY(s4u_app_masterworker, "Messages specific for this example");

static void master(std::vector<std::string> args)
{
  xbt_assert(args.size() > 4, "The master function expects at least 3 arguments");
  long number_workers= std::stol(args[1]);
  long tasks_count          = std::stol(args[2]);
  double compute_cost       = std::stod(args[3]);
  double communication_cost = std::stod(args[4]);
  std::vector<simgrid::s4u::Mailbox*> workers;
  for (unsigned int i = 0; i < number_workers; i++)
  {
   std::string worker_rank          = std::to_string(i);
   std::string mailbox_name         = std::string("worker-") + worker_rank;
  
   workers.push_back(simgrid::s4u::Mailbox::by_name(mailbox_name));
   
   
  }
  XBT_INFO("Workers size: %ld ",workers.size());


  for (int i = 0; i < tasks_count; i++) 
  { /* For each task to be executed: */
   std::string worker_rank          = std::to_string(i % workers.size());
   std::string mailbox_name         = std::string("worker-") + worker_rank;
   simgrid::s4u::Mailbox* mailbox   = simgrid::s4u::Mailbox::by_name(mailbox_name);

    /* - Send the computation cost to that worker */
    XBT_INFO("Sending task %d of %ld to mailbox '%s'", i, tasks_count, mailbox->get_cname());
    mailbox->put(new double(compute_cost), communication_cost);
  }

  XBT_INFO("All tasks have been dispatched. Request all workers to stop.");
  for (unsigned int i = 0; i < workers.size(); i++) {
    /* The workers stop when receiving a negative compute_cost */
    
    simgrid::s4u::Mailbox* mailbox = workers[i % workers.size()];

    mailbox->put(new double(-1.0), 0);
  }
}

static void worker(std::vector<std::string> args)
{
  //xbt_assert(args.size() == 1, "The worker expects no argument");

 // simgrid::s4u::Host* my_host      = simgrid::s4u::this_actor::get_host();
  std::string worker_rank = args[1];
  simgrid::s4u::Mailbox* mailbox = simgrid::s4u::Mailbox::by_name("worker-"+args[1]);

  double compute_cost;
  do {
    double* msg  = mailbox->get<double>();
    compute_cost = *msg;
    delete msg;

    if (compute_cost > 0) /* If compute_cost is valid, execute a computation of that cost */
      simgrid::s4u::this_actor::execute(compute_cost);

  } while (compute_cost > 0); /* Stop when receiving an invalid compute_cost */

  XBT_INFO("Exiting now.");
}

int main(int argc, char* argv[])
{
  simgrid::s4u::Engine e(&argc, argv);
  xbt_assert(argc > 2, "Usage: %s platform_file deployment_file\n", argv[0]);

  /* Register the functions representing the actors */
  e.register_function("master", &master);
  e.register_function("worker", &worker);

  /* Load the platform description and then deploy the application */
  e.load_platform(argv[1]);
  e.load_deployment(argv[2]);

  /* Run the simulation */
  e.run();

  XBT_INFO("Simulation is over");

  return 0;
}
