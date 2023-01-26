/* Copyright (c) 2010-2019. The SimGrid Team. All rights reserved.          */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

/* ********************************************************************************** */
/* Take this tutorial online: https://simgrid.org/doc/latest/Tutorial_Algorithms.html */
/* ********************************************************************************** */

#include <simgrid/s4u.hpp>
#include<bits/stdc++.h>


XBT_LOG_NEW_DEFAULT_CATEGORY(s4u_app_masterworker, "Messages specific for this example");


//static void my_actor(int temp,int actor_id,std::vector<simgrid::s4u::ActorPtr> actor_list)
//{
 void my_actor(int temp,int i)
{
  //xbt_assert(args.size() == 1, "The worker expects no argument");

 // simgrid::s4u::Host* my_host      = simgrid::s4u::this_actor::get_host();
 //simgrid::s4u::this_actor::get_ppid()
  //std::string worker_rank = ;
  simgrid::s4u::Mailbox* mailbox = simgrid::s4u::Mailbox::by_name(std::to_string(i));

  double compute_cost;
  do {
    double* msg  = mailbox->get<double>();
    compute_cost = *msg;
    delete msg;

    if (compute_cost > 0)
      simgrid::s4u::this_actor::execute(compute_cost);

  } while (compute_cost > 0); 

  XBT_INFO("Exiting now.");
  
}

static void master(std::vector<std::string> args)
{
  //xbt_assert(args.size() > 4, "The master function expects at least 3 arguments");
 
  long duration          = std::stol(args[1]);
  double compute_cost       = std::stod(args[2]);
  double communication_cost = std::stod(args[3]);
  std::vector<simgrid::s4u::Mailbox*> workers;
  simgrid::s4u::Engine* e = e->get_instance();
   
  std::vector<simgrid::s4u::Host*> host_list = e->get_all_hosts();
  XBT_INFO("Length of Hosts_list: %ld ",host_list.size());
     long host_count = e->get_host_count();
    // XBT_INFO("Length of Hosts_list: %ld ",host_list.size());
     XBT_INFO("Number of Hosts: %ld ",host_count);
     std::vector<simgrid::s4u::ActorPtr*> actor_list;
     
     //std::cout<<host_list[0]<<std::endl;
     
     //->get_name()
     for (unsigned int i = 0; i < host_count; i++)
     {
     
     XBT_INFO("host name - %s",host_list[i]->get_cname());
     
     }
     
  for (unsigned int i = 0; i < host_count; i++)
  {
   std::string worker_rank  = std::to_string(i);
   
   std::string mailbox_name = worker_rank;
   int temp=100;
   simgrid::s4u::ActorPtr actor;
   
   //actor_list[i] 
   actor  = simgrid::s4u::Actor::create(worker_rank,host_list[i],&my_actor, temp,i);
   //aid_t actor_id =  actor_list[i].get_pid();
   //XBT_INFO("Actor id:%ld",actor_id);
   workers.push_back(simgrid::s4u::Mailbox::by_name(mailbox_name));
   
  }
  
  
  XBT_INFO("Workers size: %ld ",workers.size());
  
 double start_time= e->get_clock();
 
 for (int i = 0; e->get_clock() - start_time < duration ; i++) 
  { 
    std::string worker_rank          = std::to_string(i % workers.size());
    std::string mailbox_name         = worker_rank;
    simgrid::s4u::Mailbox* mailbox   = simgrid::s4u::Mailbox::by_name(mailbox_name);
    
    XBT_INFO("Sending task %d to mailbox '%s'", i, mailbox->get_cname());
    mailbox->put(new double(compute_cost), communication_cost);
  }

  XBT_INFO("All tasks have been dispatched. Request all workers to stop.");
  for (unsigned int i = 0; i < workers.size(); i++) 
  {
    
    simgrid::s4u::Mailbox* mailbox = workers[i % workers.size()];

    mailbox->put(new double(-1.0), 0);
  }
  
}



int main(int argc, char* argv[])
{
  simgrid::s4u::Engine e(&argc, argv);
  xbt_assert(argc > 2, "Usage: %s platform_file deployment_file\n", argv[0]);
  
  /* Register the functions representing the actors */
  e.register_function("master", &master);
  //e.register_function("worker", &worker);
  

   
  /* Load the platform description and then deploy the application */
  e.load_platform(argv[1]);
  e.load_deployment(argv[2]);

  /* Run the simulation */
  e.run();
//std::vector<simgrid::s4u::Host*> host_list = e.get_all_hosts();
  XBT_INFO("Simulation is over");

  return 0;
}
