/*
   ____    _ __           ____               __    ____
  / __/___(_) /  ___ ____/ __ \__ _____ ___ / /_  /  _/__  ____
 _\ \/ __/ / _ \/ -_) __/ /_/ / // / -_|_-</ __/ _/ // _ \/ __/
/___/\__/_/_.__/\__/_/  \___\_\_,_/\__/___/\__/ /___/_//_/\__(_)

Copyright 2008 SciberQuest Inc.
*/
#include "postream.h"

#ifdef WIN32
  #include <Winsock2.h>
#else
  #include <unistd.h>
#endif

#include <mpi.h>

//-----------------------------------------------------------------------------
ostream &pCerr()
{
  int WorldRank;
  MPI_Comm_rank(MPI_COMM_WORLD,&WorldRank);

  char host[256]={'\0'};
  gethostname(host,256);

  cerr << "[" << host << ":" << WorldRank << "] ";

  return cerr;
}

