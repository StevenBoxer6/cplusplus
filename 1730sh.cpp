#include <iostream>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <pwd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <map>

using namespace std;

void close_pipe(int pipefd [2]);
vector<char *> mk_cstrvec(vector<string> & strvec);
void dl_cstrvec(vector<char *> & cstrvec);
void nice_exec(vector<string> args);
int help();
void callKill(vector<string> & strvec);
void shift(char* path,int index);
string getPrompt();
bool run = true;

/**
 This is our main function which loops through
and acts as a working shell until the user
enters exit into the shell.
 */
int main(const int argc, const char * argv [], char * envp[]) {

  int pid;
  pid_t JID = 0;

  string prompt = "cs1730sh:";
  pid_t homePID = getpgrp();
  pid_t status [50];  
  int random = 0;
  pid_t list[50];
  int listIndex = 0;
  int statusIndex = 0;

  string currentJobs [50][30];
  for(int i = 0; i < 50; i++)
    {
      for(int j = 0; j < 30; j++)
	{
	  currentJobs[i][j] = '\0';
	}
      list[i] = '\0';
    }
  int jobIndex = 0;
  
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  // signal(SIGCHLD, SIG_IGN);
  
  while(run)
    {
      int pstatus;
      pid_t wpid;
      bool ampersand = false;
      char pwd[300];
      for(int i =0; i < 300; i++)
        {
          pwd[i] = '\0';
        }

      getcwd(pwd,sizeof(pwd));

      struct passwd *pw = getpwuid(getuid());
      const char * homeDir = pw->pw_dir;
      
      cout << prompt<< "~";
      for(int i = strlen(homeDir); i < 300 ; i++)
	{
	  cout << pwd[i];
	}
      cout << "$ ";
      
      string input =  "";
      getline(cin, input);

      istringstream istring(input);
  
      vector<string> vec;
      string word;
  

      while(getline(istring, word, ' '))
	{
	  bool change = false;
	  string check = "";
	  check.assign(word);
	  bool same = false;
	  // bool more = false;
	  string c = "";
	  string c2 = "";
	  string both = "\\";
	  string q = "\"";

	  //cout << "both " << both << endl;
	  // cout<< word.size() << endl;
	  //cout << check << endl;
	  	   
	      for(uint i = 0; i < check.size(); i++)
		{
		  
		  string c = check.substr(i,1);
		  if((i+1) < check.size())
		    {
		      c2 = check.substr(i+1, 1);
		      // more = true;
		    }

		  // cout << "c: " << c << endl;
		  //cout <<"c2: " << c2 << endl;
		  
		  if((c.compare(both)==0) && c2.compare(q) == 0)
		    {
		      if(same)
			{
			  
			  check.erase(i,1);
			}
		      else
			{
			  check.erase(i,1);
			}
		      
		        
		      // cout << "after both " << check.size()<<endl;
		      change = true;
			
		      same = true;
		    }
		
		  else if(c.compare(q)==0)
		    {
		  if(same)
		    {
		      check.erase(i-1,1);
		    }
		  else
		    {
		      check.erase(i,1);
		    }   
		  
		  // cout << "after qoute " << check.size() << endl;
		    
		  change = true;
		  
		  same = true;
		  
		}
	      else
		{
		  continue;
		}
	      
		}
	
	  if(change)
	    {
	      //cout <<"what would go into the vec " <<  check << endl;
	      vec.push_back(check);
	    }
	   else
	     {
	      vec.push_back(word);
	     }   
	    
	}//filling vector
      
      string arguments[30];
      int aindex = 0;
      int asize = input.size();
      input = input.c_str();
      string werd = "";
      for(int i = 0; i < asize+1; i++)
	{
	  char atemp = input[i];
          if(atemp != ' ')
            {
              werd += atemp;
            }
          else if(atemp == ' ')
            {
              if(input[i+1] == ' ')
                continue;
              arguments[aindex] = werd;
	      currentJobs[jobIndex][aindex] = werd;
              aindex ++;
              werd = "";
            }
        }
      
      if(werd != "")
        {
          arguments[aindex] = werd;
	  if(werd == "&")
	    {
	      ampersand = true;
	    }
	  currentJobs[jobIndex][aindex] = werd;
        }
      
      for(int i = 0; i < aindex; i++)
        {
          if(arguments[i] == ">" || arguments[i] == ">>" || arguments[i] == "e>>" || arguments[i] == "<")
            {
              for(int j = i; j < aindex; j++)
                {
                  arguments[j] = arguments[j+2];
		  currentJobs[jobIndex][j] = arguments[j+2];
                }
              aindex -=2;
              i = 0;
            }
        }

      jobIndex ++;
      
      
      
      string jIn = "STDIN_FILENO";
      string jOut = "STDOUT_FILENO";
      string jErr = "STDERR_FILENO";

      uint pipeCount = 0;
      uint proc = 0;

      string jobIn = "";
      string jobOut = "";
      string jobErr = "";
      
      bool trunc = false;
      bool app = false;
      bool in = false;
      bool out = false;
      bool err = false;
      bool etrunc = false;
      bool eapp = false;

      for(uint i = 0; i < vec.size(); i++)//chekcs STDIN, STDOUT, STDERR and number of pipes and processes                                                                             
	{
	 
	  if(vec[i] == "<")
	    {
	      jobIn =  vec[i+1];
	      in = true;
	    }

	  if(vec[i] == ">")
	    {
	      jobOut = vec[i+1];
	      trunc = true;
	      out  = true;
	    }

	  if(vec[i] == ">>")
	    {
	      jobOut =  vec[i+1];
	      app = true;
	      out = true;
	    }
	  if(vec[i] == "e>")
            {
              jobErr =  vec[i+1];
	      etrunc = true;
              err = true;
            }

	  if(vec[i] == "e>>")
	    {
	      jobErr =  vec[i+1];
	      eapp = true;
	      err = true;
	    }

	  if(vec[i] == "|")
	    {
	      pipeCount++;
	    }
	}
      
    
      proc = pipeCount +1;
      
      //create backups for standard input,output, and error
      int backIn = dup(STDIN_FILENO);
      int backOut = dup(STDOUT_FILENO);
      int backErr = dup(STDERR_FILENO);
      int inFd = 0;
      int outFd = 0;
      int errFd = 0;
      random = errFd;			  
      random ++;
      
      // int qCount = 0;

      uint num = 0;
      uint count = 0;
      vector< vector<string> > commands;
      vector<string> temp;
      
      for(uint j = 0; j < vec.size(); j++)//prints out the processes
	{
	  if(vec[j] == "<" ||vec[j] == ">>" || vec[j] == ">"|| vec[j] == "e>>")
	    {
	      j = vec.size() - 1;
	    }
	  else
	    {
	      if(count < proc)
		{
		  //cout << "\n";
		  //cout << "Process " << count << " argv:" << endl;
		}
	      while(vec[j] != "|" && vec[j] != "<" && vec[j] != ">>" && vec[j] !=">" && vec[j] != "e>>"  && j < vec.size()&& count < proc)
		{
		 
		  if(vec[j] == "" || vec[j] == "&")
		    {
		      if(j == vec.size()-1)
			{
			  break;
			}
		      j++;
		    }/*
		  else if(pos1 !=  std::string::npos)
		    {
		      for(uint i =0; i < 
		      }*/
		  else
		    {
		      temp.push_back(vec[j]);
		      //cout << num << ":  " << vec[j] << endl;
		      
		      num++;
		      
		      if(j ==  vec.size()-1)
			{
			  break;
			}
		      j++;
		    }
		}
	      if(temp.size() > 0)
		{
		  commands.push_back(temp);
		}
	      temp.clear();
	      num = 0;
	      count++;
	      
	      if(j ==  vec.size()-1)                     
		{
		  break;
		}
	    }	 
	}
    
      vec.clear();
      vector<array<int, 2>> pipes;
      
      
      
      for (unsigned int i = 0; i < commands.size(); ++i) {
	

	if(commands[i][0] == "export")
	  {
	    if(commands[i].size() == 1)
	      {
		for(int j = 0; envp[j] != nullptr; j++)
		  {
		    cout <<"declare -x " <<envp[j] << endl;
		  }
	      }
	    else
	      {
		string temp = commands[i][1];
		string name = "";
		string word = "";
		for(uint j = 0; j < temp.size(); j++)
		  {
		    if(temp[j] == '=')
		      {
			name = temp.substr(0,j);
			word = temp.substr(j+1);
		      }
		  }
		if(setenv(name.c_str(), word.c_str(), 1) == -1)
		  {
		    cout << "Error! Type export NAME=WORD" << endl;
		  }
		
	      }
	    continue;
	  }
	
	if(commands[i][0] == "jobs")
	  {
	    if(listIndex != 0)
	      {
		bool statusChange = false;
		cout << "JID    STATUS \t  COMMANDS" <<endl;
		for(int j = 0;j < listIndex; j++)
		  {
		    cout << list[j];
		    int temp = int(list[j]);
		    for(int k = 0; k < statusIndex; k++)
		      {
			if(temp == status[k])
			  statusChange = true;
		      }
		    if(statusChange == true)
		      cout <<"  Stopped    ";
		    else
		      cout <<"  Running    ";
		    int tempsize = sizeof(currentJobs[j])/sizeof(currentJobs[j][0]);
		    for(int k = 0; k < tempsize; k++)
		      {
			cout << currentJobs[j][k] << " ";
		      }
		    cout << '\n';
		  }
	      }
	    continue;
	  }
	if(commands[i][0] == "exit") //EXIT BUILT IN
	  {
	    if(commands.at(i).size() == 1)
	      return EXIT_SUCCESS;
	    else
	      {
		int exitStatus = atoi(commands[i][1].c_str());
		exit(exitStatus);
	      }
	    
	  }

	if(commands[i][0] == "kill") //KILL BUILT IN
	  {
	    callKill(commands[i]);
	    continue;
	  }

	if(commands[i][0] == "cd") //CD BUILT IN
	  {
	    string s = commands[i][1];
	    int x = chdir(s.c_str());


	    if(x ==-1)
	      {
		perror("chdir");
	      }
	    	    
	    continue;
	  }
	
	if(commands[i][0] == "help") //HELP BUILTIN                                             
	  {
	    int temp = help();
	    if (temp == 2)
	      {
		temp++;
	      }
	    continue;
	  }

	if(commands[i][0] == "bg") //BG BUILT IN
	  {
	    tcsetpgrp(STDIN_FILENO, homePID);
	    continue;
	  }

	if(commands[i][0] == "fg") //FG BUILT IN                               
          {
	    int temp = atoi(commands[i][1].c_str());
	    pid_t set = (pid_t)temp;
            tcsetpgrp(STDIN_FILENO, set);
	    continue;
	  }
	
	if(i == 0 && in) //INPUT REDIRECTION
	  {
	    inFd = open(jobIn.c_str(), O_RDONLY);
	    dup2(inFd, STDIN_FILENO);
	  }

	if(i == commands.size() -1) //OUTPUT/ERROR REDIRECTION
	  {
	    if(out)
	      {
		if(trunc)
		  {
		    outFd = open(jobOut.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0777);
		  }		    
		else if(app)
		  {
		    outFd = open(jobOut.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0777);
		  }
		
		dup2(outFd, STDOUT_FILENO);
		
	      }
	    if(err)
              {
                if(etrunc)
                  errFd= open(jobErr.c_str(), O_WRONLY| O_TRUNC);
                else if(eapp)
                  errFd= open(jobErr.c_str(), O_WRONLY| O_APPEND);

                dup2(outFd, STDERR_FILENO);
              }
	  }

	if (i != commands.size() - 1) {
	  int pipefd [2];
	  if (pipe(pipefd) == -1) {
	    perror("pipe");
	    exit(EXIT_FAILURE);
	  } // if
	  pipes.push_back({pipefd[0], pipefd[1]});
	} // if
	
	
	if ((pid = fork()) == -1) {  //FORK
	  perror("fork");
	  exit(EXIT_FAILURE);
	} else if (pid == 0) {
	  
	  signal(SIGINT, SIG_DFL);
	  signal(SIGQUIT, SIG_DFL);
	  signal(SIGTSTP, SIG_DFL);
	  signal(SIGTTIN, SIG_DFL);
	  signal(SIGTTOU, SIG_DFL);
	  
	  if(i == 0){
            JID = getpid();
	  }
	  
	  setpgid(getpid(),JID);
	  
	  if(ampersand == false)
	    tcsetpgrp(STDIN_FILENO, JID);
	  
	  if (i != 0) {
	    	    
	    if (dup2(pipes.at(i-1)[0], STDIN_FILENO) == -1) {
	      perror("dup2");
	      exit(EXIT_FAILURE);
	    }//if
		
	  } // if
	    
	  if (i != commands.size() - 1) {
	    if (dup2(pipes.at(i)[1], STDOUT_FILENO) == -1) {
	      perror("dup2");
	      exit(EXIT_FAILURE);
	    } // if
	  } // if
	  
	    // close all pipes created so far
	  for (unsigned int i = 0; i < pipes.size(); ++i) {
	    close_pipe(pipes.at(i).data());
	  } // for
	  	  
	  	  
	  //else
	  nice_exec(commands.at(i));
	    
	}// if
	else{
	  if(i == 0)
	    JID = pid;
	  setpgid(pid,JID);
	  //list[listIndex] = JID;
          //listIndex ++;
	  
	  if(ampersand == false)
	    tcsetpgrp(STDIN_FILENO, JID);
	}
      } // for
      
      list[listIndex] = JID;
      listIndex ++;

      	// close all pipes
      for (unsigned int i = 0; i < pipes.size(); ++i) {
	close_pipe(pipes.at(i).data());
      } // for
      
      for(uint y = 0; y < commands.size(); y++)
	{
	  uint x = commands.at(y).size();
	  
	  for(uint z = 0; z < x; z++)
	    {
	      commands[y][z].clear();
	    }
	}
      
     
      dup2(backIn, STDIN_FILENO);
      dup2(backOut, STDOUT_FILENO);
      dup2(backErr, STDERR_FILENO);

      
      while ((wpid = waitpid(-1, &pstatus, WNOHANG | WUNTRACED | WCONTINUED)) > 0) 
	{
	  
	  pid_t tempID = getpgid(wpid);
	  //int tempIndex = 0;
	  //int temporary = (int)tempID;
	  /*
	  for(i = 0; i < sizeof(list)/sizeof(list[0]));i++)
	    {
	      
	      if(tempID == list[i])
		{
		  if(temporary == list[i])
		    break;
		}
	      tempIndex ++;
	    }
	  */
	  status[statusIndex] = tempID;
	  /*
	  if (WIFEXITED(pstatus)) 
	    {
	      pid_t tempID = getpgid(wpid);
	      int tempIndex = 0;
	      int temporary= (int)tempID;

	      for(uint i = 0; i < sizeof(list)/sizeof(list[0]);i++)
		{
		  
		  if(tempID == list[i])
		    {
		      if(temporary == list[i])
			break;
		    }  
		  tempIndex ++;
		}
	      int tempsize = sizeof(currentJobs[tempIndex])/sizeof(currentJobs[tempIndex][0]);
	      for(int i = 0; i < tempsize; i++)
		{
		  cout << currentJobs[tempIndex][i] + " ";
		  cout << "was exited normally." << endl;
		}
	    } 
	  else if (WIFSTOPPED(pstatus)) 
	    {
	      pid_t tempID = getpgid(wpid);
              int tempIndex = 0;
              int temporary= (int)tempID;

              for(uint i = 0; i < sizeof(list)/sizeof(list[0]);i++)
                {

                  if(tempID == list[i])
                    {
                      if(temporary == list[i])
                        break;
                    }
                  tempIndex ++;
                }
	      int tempsize = sizeof(currentJobs[tempIndex])/sizeof(currentJobs[tempIndex][0]);
              for(int i = 0; i < tempsize; i++)
		{
                  cout << currentJobs[tempIndex][i] + " ";
                  cout << "was stopped.." << endl;
		}
	      
	      	 
	    } 
	  else if (WIFSIGNALED(pstatus)) 
	    {
	      int sig = WTERMSIG(pstatus);
	      pid_t tempID = getpgid(wpid);
              int tempIndex = 0;
              int temporary= (int)tempID;

              for(uint i = 0; i < sizeof(list)/sizeof(list[0]);i++)
                {

                  if(tempID == list[i])
                    {
                      if(temporary == list[i])
                        break;
                    }
                  tempIndex ++;
                }
	      int tempsize = sizeof(currentJobs[tempIndex])/sizeof(currentJobs[tempIndex][0]);
              for(int i = 0; i < tempsize; i++)
		{
                  cout << currentJobs[tempIndex][i] + " ";
                  cout << "exited abnormally from signal = " << sig << " " << "(" << strsignal(sig) << ")" << endl;
		}
	      
	    }
	  */
	  statusIndex++;
	} 
      
      waitpid(pid,nullptr,0);
     
      if(ampersand == false)
	tcsetpgrp(STDIN_FILENO, homePID);

    }//while

  return EXIT_SUCCESS;
  
} // main
/*
  Closes the pipes.

@param int
@return void
 */
void close_pipe(int pipefd [2]) {
  if (close(pipefd[0]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
  if (close(pipefd[1]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
} // close_pipe

/*
Makes a vector into a c-string
vector.

@param vector<string> &
@return vector<char *>
 */
vector<char *> mk_cstrvec(vector<string> & strvec) {
  vector<char *> cstrvec;
  for (unsigned int i = 0; i < strvec.size(); ++i) {
    cstrvec.push_back(new char [strvec.at(i).size() + 1]);
    strcpy(cstrvec.at(i), strvec.at(i).c_str());
  } // for
  cstrvec.push_back(nullptr);
  return cstrvec;
} // mk_cstrvec
/*
Destroys a c-string vector.

@param vector<char *> &
@return void
 */
void dl_cstrvec(vector<char *> & cstrvec) {
  for (unsigned int i = 0; i < cstrvec.size(); ++i) {
    delete[] cstrvec.at(i);
  } // for
} // dl_cstrvec

/*
Function to call execcvp.

@parm vector<string> stargs
@return void
 */
void nice_exec(vector<string> strargs) {
  vector<char *> cstrargs = mk_cstrvec(strargs);
  execvp(cstrargs.at(0), &cstrargs.at(0));
  perror("execvp");
  dl_cstrvec(cstrargs);
  exit(EXIT_FAILURE);
}
/*
Prints out the message when the 
help command is entered.

@return int
 */
 int help()
 {
   cout << "GNU bash, version 4.1.2(1)-release (x86_64-redhat-linux-gnu)" << endl;
   cout << "These shell commands are defined internally.Type" << "`help'"<< " to see this list. " << endl;
   cout << "Type " << "`help name'" << " to find out more about the function `name'." << endl;
   cout << "Use " << "`info bash'" << " to find out more about the shell in general." << endl;
   cout << "Use "<<"`man -k'" <<" or " <<"`info'"<<" to find out more about commands not in this list." << endl;
   cout << endl;

   cout << "A star (*) next to a name means that the command is disabled." << endl;
   cout << endl;

   cout << "bg [job_spec ...]" << endl;
   cout << "cd [-L|-P] [dir]" << endl;
   cout <<"export [-fn] [name[=value] ...] or export -p" << endl;
   cout << "exit [n]" << endl;
   cout << "fg [job_spec]" << endl;
   cout << "help [-dms] [pattern ...]               { COMMANDS ; }" << endl;
   cout<<"jobs [-lnprs] [jobspec ...] or jobs -x command [args]" << endl;
   cout << "kill [-s sigspec | -n signum | -sigspec] pid | jobspec ... or kill -l [sigspec]" << endl;
   return 1;
}

/*
This function calls kill
for us when the kill command 
is enterd into the shell.

@param vector<string> &
@return void
 */
 void callKill(vector<string> & strvec)
 {
   pid_t pidNumber;
   if(strvec[1] != "-s") //NO -s specfied
     {
       pidNumber = atoi(strvec[1].c_str());
       kill(pidNumber, SIGTERM);
       
     }
   else
     {
       pidNumber = atoi(strvec[3].c_str());
       //string signal = strvec[2];
       const map<string,int>sigmap{
#ifdef SIGHUP
	 {"SIGHUP", SIGHUP},
#endif
#ifdef SIGINT
	   {"SIGINT", SIGINT},
#endif
#ifdef SIGTERM
	     {"SIGTERM", SIGTERM},
#endif
#ifdef SIGKILL
	       {"SIGKILL", SIGKILL},
#endif
#ifdef SIGSTOP
		 {"SIGSTOP", SIGSTOP},
#endif
#ifdef SIGCONT
		   {"SIGCONT", SIGCONT},
#endif
#ifdef SIGQUIT
		     {"SIGQUIT", SIGQUIT},
      #endif
#ifdef SIGALRM
		       {"SIGALRM", SIGALRM},
#endif
#ifdef SIGTSTP
			 {"SIGTSTP", SIGTSTP},
#endif
			   };
       
       int sig = sigmap.at(strvec[2]);
       kill(pidNumber,sig);
          
     }

  
 }


