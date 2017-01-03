#include <stdio.h>
#include <string.h>
#include <sqlite3.h> 



void processGet(int sockfd, char* fileName, char* protocol, char* hostname);
void handleGet(int sockfd, char* buffer);
void insertFile(char* fileName,char* contents, size_t fileSize);

class Session{
private:
   int sockfd;
   uint32_t user_id;
   
public:
   Session(const int newsock_fd);
   
   inline uint32_t get_user_id();
   inline int get_sockfd();
};


struct socketInfo{
 	struct sockaddr_in6 serv_addr;//, cli_addr; //struct for server and client addr
    struct hostent *server;
	int sockfd;
	int portno; //inits

	server = ip; //add from db
	portno = portnum;//add from db
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family = AF_INET; //ipv4
	serv_addr.sin_port = htons(portno); //saves port in network byte order
};

int main(int argc, char *argv[]) //format is ./server port
{
   /*
   Creating Server to listen to connections
   */
   int sockfd, portno; // These two variables store the values returned by the socket system call and the accept system call.
   //socklen_t clilen; // stores size of client address
   struct sockaddr_in serv_addr;// ,cli_addr; // server addr and client addr

   //Sig Handler Error Check 
   if (signal(SIGINT, sig_handler) == SIG_ERR){
    printf("Can't catch SIGINT\n"); 
   }

   if (argc < 2) {// standard error check
      fprintf(stderr,"ERROR, no port provided\n");
      exit(1);
   }
   //Valid Ports are 1025 to 65535.
   if (atoi(argv[1]) < 1025 || atoi(argv[1]) > 65535){
      printf("Invalid Port. Use 1025-65535\n");
      exit(1);
   }

   /// you want to set your socket as nonblocking here
   sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0); //establishes new socket
   if (sockfd < 0){
      error("ERROR opening socket");
   }

   bzero((char *) &serv_addr, sizeof(serv_addr)); //clears serv_addr buffer to 0
   portno = atoi(argv[1]); 
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno); //host byte order to network byte orderQ

   if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
      error("ERROR on binding");
   }

   listen(sockfd,10); //process to listen for socket for cons, 5 pending max in queue
   
   /*
   This section establishes the DB Connection
    */
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open("dannyServer.db", &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /*
   This section connects to all available file servers to be used for later
   IN CONSTRUCTION
   */
   	struct sockaddr_in6 serv_addr;//, cli_addr; //struct for server and client addr
    struct hostent *server;
	int sockfd, portno; //inits

	server = ip; 
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
	portno = atoi(portNo); //
	if (portNo < 1025 || portNo > 65535){
        fprintf(stderr,"ERROR, not a valid port numbert\n");
        exit(0);
	}
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd < 0){ 
		error("Error");
    }

	serv_addr.sin_family = AF_INET; //ipv4
	serv_addr.sin_port = htons(portno); //saves port in network byte order





   /*
   While loop that accepts connections and checks sockets for something to be read
    */

   int numConnections = 0, connectionFD = -1;
   
   Session **session;

    while(1){//main accept loop
    	///FIX THIS PART DO NOT BLOCK
      connectionFD = accept(sockfd, (struct sockaddr*) NULL, NULL);//blocks until a client connects
      if (connectionFD >= 0){ // No error codes{
         Session **ptr = (Session**)malloc(sizeof(Session*)*(numConnections+1));
         Session *newSession = new Session(connectionFD);
         if (!ptr || !newSession){
            puts("Can't accept new session");
            free(ptr);
            free(newSession);
            close(connectionFD);
         }
         else{
            memcpy(ptr, session, sizeof(Session*)*numConnections);
            if (session != NULL){
               free(session);
            }
            session = ptr;
            session[numConnections] = newSession;
            numConnections++;
            printf("Accepted new connection #%i\n",numConnections);
            printf("%i Clients Currently Connected\n",numConnections);
         }
      }
      else { //Read messages from clients
         char buffer[10000];
         for (int x = 0; x < numConnections; ++x) {
            const int len = recv(session[x]->get_sockfd(), (void*)buffer, sizeof(buffer), MSG_DONTWAIT);
            if (len > 0) {
               handleGet(session[x]->get_sockfd(),buffer);
            } 
            else if (len == 0) {
               // socket disconnected properly  
               delete session[x];
               numConnections--;
               session[x] = session[numConnections]; // last connection replaces deleted connection
               printf("Connection #%i disconnected\n",x+1);
               printf("%i Clients Currently Connected\n",numConnections);
            }
         }
      }
      printf("Waiting\n");
      sleep(1);
      sched_yield();
    }

    close(sockfd);
    return 0;
}



void handleGet(int sockfd, char* buffer){ // shouldnt have error messages cause assume the protocol is always correct???
	char* token = strok(buffer);

	if (strncmp(token,"GET",3) == 0){ // GET Request
		token = strok(buffer," ");
		if (token != NULL){
			char *fileName = (char*) malloc(sizeof(token));
			memcpy(fileName,token,sizeof(token)); // Stores File Name
		}
		else{
			printf("Invalid Request\n");
			close(sockfd);
		}

		token = strok(buffer," ");
		if (token != NULL){
			char *protocol = (char*) malloc(sizeof(token));
			memcpy(protocol,token,sizeof(token));
		}
		else{
			printf("Invalid Request\n");
			close(sockfd);
		}

		token = strok(buffer,"\n");
		if (token != NULL){
			char *hostname = (char*) malloc(sizeof(token));
			memcpy(protocol,token,sizeof(token));
		}
		else{
			printf("Invalid Request\n");
			close(sockfd);
		}

		processGet(sockfd, fileName, protocol, hostname);
		free(token);
		free(fileName);
		free(protocol);
		free(hostname);
	}

	else{
		printf("Invalid Request\n");
		close(sockfd);
	}

}

void processGet(int sockfd,char* fileName, char* protocol, char* hostname){
	bool found = FALSE;
	char* response = (char*)malloc(9);
	unsigned int index = 0;
	unsigned int len;
	//look up db for that hostname if exists, if not return error?
	//get info for that server and connect to it/retrieve the file?
	//send Response block?
	if(found){
		char* protocol = "HTTP/1.1 "; //We'd get it somehow here with a function that returns a char* ideally;
		len = strnlen(protocol,9);
		memcpy(response,protocol,len);
		index += len;
		free(protocol);

		char* statusCode = "200 "; // We'd get it somehow here with a function that returns a char* ideally;
		len = strnlen(statusCode,4);
		realloc(response,index+len);
		memcpy(response+index,statusCode,len);
		free(statusCode);

		char* statusCodeDesc = "OK\n";
		len = strnlen(statusCodeDesc,50);
		realloc(response,index+len);
		memcpy(response+index,statusCodeDesc,len);
		free(statusCodeDesc);

		//repeat for all other info in the response header
		
		char format[5] = "\r\n\r\n";
		format[4] = '\0';
		realloc(response,index+5);
		memcpy(response+index,format,5);
		
		if(!write(sockfd,response,index+1)){
			error("Error Sending Response Header\n");
		}

		//do response body here now?
		
	}
	else{
	/
		//write file not found
		//404 error?
		
	}
	close(sockfd);
}

void insertFile(char* fileName,char* contents, size_t fileSize){
	//pass filename and contents and size
	//open up DB To find best avail server(naive way to sort by most space remaining and pick that one)
	//connect to that server by obtaining info in DB
	//upload file to that server
	//add that info to DB about where file is located
	//close connection

	/*
	Do Lookup here for biggest capacirty avail server info
	 */
	
	char *ip; //add from db
	char *portNum; //add from db
	//sqlite3
	//https://www.sqlite.org/cintro.html

}