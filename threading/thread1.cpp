//1. Implement a proper worker pool with appropriate functions. Use your queue class in general-1. Threading can be done with std::thread or pthreads (or even winapi if you hate yourself as much as i do).

// use get_nprocs(3) to get worker count
//pthread_cond_wait keeps threads from gonig ham
#include <stdio.h>
#include <sys/sysinfo.h>


#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <pthread.h>


//http://stackoverflow.com/questions/22284557/thread-pool-implementation-using-pthreads

bool quit = FALSE;
struct singlyLL{
	void *task;
	struct singlyLL *next;
};

struct jobInfo{
	void *task;

};

class mtQueue{
	private:
		singlyLL *front;
		singlyLL *back;
		unsigned int size;
		
	public:
		pthread_cond_t cond;
		pthread_mutex_t lock;
		mtQueue();
		~mtQueue();
		void push(void *task);
		void* pop();
		inline unsigned int getSize();
		inline bool isEmpty();
};


mtQueue::mtQueue(){
	front = NULL;
	back = NULL;
	size = 0;
	pthread_mutex_init(&lock,0);
	pthread_cond_init(&cond,0);;
}

mtQueue::~mtQueue(){
	pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
}
void mtQueue::push(void *task){
	
	
	if (size == 0){
		front->task = task;
		front->next = NULL;
		back = front;
	}
	
	
	else{
		singlyLL *next = new(singlyLL);
		next->task = task;
		next->next = NULL;
		back->next = next;
	}
	
	
	size++;

}

void* mtQueue::pop(){
	if(size == 0){
		printf("Cannot not pop empty queue");
		return NULL;
	}
	
	
	else if (size == 1){
		void* task= front->task;
		front = NULL;
		return task;
		//need to free popped LL that just disappears???
	}
	else{
		void* task = front->task;
		singlyLL *p = front;
		front = front->next;
		free(p);
		return task;
	}
}

inline bool mtQueue::isEmpty(){
	if (size == 0){
		return true;
	}
	else {	
		return false;
	}
}

inline unsigned int mtQueue::getSize(){
	return size;
}

/* notes

*/

void queue_add(mtQueue q, void *task)
{
    pthread_mutex_lock(&q.lock);

    /* Add element normally. */
    q.push(task);

    pthread_mutex_unlock(&q.lock);

    /* Signal waiting threads. */
    pthread_cond_signal(&q.cond);
}


void queue_get(mtQueue q, void **val_r)
{
    pthread_mutex_lock(&q.lock);

    int rc;
    /* Wait for element to become available. */
    while (q.isEmpty()){
        rc = pthread_cond_wait(&q.cond, &q.lock);
        if (rc != 0){
        	//trouble?
        }
    }

    /* We have an element. Pop it normally and return it in val_r. */
    *val_r = q.pop();
    pthread_mutex_unlock(&q.lock);
}



void* getJob(){
	
	void *job;
	while(!quit){
		queue_get(taskQueue,job);

	}
}

void* testTask2(void* b){
	printf("Test2\n");
	int *myint = (int*)b;
	*myint = 1;
	return NULL;
}

int main(void){
	printf("This system has %d processors configured and "
            "%d processors available.\n",
            get_nprocs_conf(), get_nprocs());


	mtQueue taskQueue = new(mtQueue);
	int check;
	pthread_t a,b;
	int data = -1;

	pthread_t workers[get_nprocs()];
	for (int i = 0; i < get_nprocs(); i++){
		check = pthread_create(&workers[i],NULL,getJob,NULL);
		if (check != 0){
			exit("Error creating thread\n");
		}
	}

	pthread_join(a,NULL);
	pthread_join(b,NULL);
	return 1;
}

/*
8:17 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/gameplay.h#L95-L103
8:17 PM - zoi: wrapper function example
8:17 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/gameplay.h#L89-L92
8:17 PM - zoi: struct example
8:17 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/gameplay.h#L177-L179
8:18 PM - zoi: add job to queue example
8:18 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/nx_src/nx_deferred_processing.cpp#L62-L107
8:18 PM - zoi: worker thread example
8:19 PM - zoi: youll notice that the work() function is part of the class that wraps up the queue as well as all workers
8:19 PM - zoi: you can do that with pthreads by wrapping the class and making work a public function
8:20 PM - zoi: https://github.com/dannyluong408/arenagame
*/

/*
7:17 PM - zoi: its so good
7:17 PM - @nevinyrral #dreams: with hentai clips
7:17 PM - @nevinyrral #dreams: in it
7:17 PM - zoi: https://www.youtube.com/watch?v=UWDRPVDTeuc
7:35 PM - @nevinyrral #dreams: thank god its only 2min long
7:35 PM - zoi: put it on repeat
7:35 PM - @nevinyrral #dreams: u know
7:35 PM - @nevinyrral #dreams: id actually do it
7:35 PM - @nevinyrral #dreams: if it made me a better programmer
7:35 PM - @nevinyrral #dreams: i doubt u have this on repeat
7:35 PM - @nevinyrral #dreams: while coding
7:35 PM - zoi: i doubt that
7:35 PM - @nevinyrral #dreams: or maybe thats why u never finished ur game
7:35 PM - @nevinyrral #dreams: cause u listen to this shit
7:35 PM - zoi: im listening to like
7:35 PM - zoi: 2005 emo music
7:35 PM - zoi: right now
7:36 PM - @nevinyrral #dreams: i liek white noise music
7:36 PM - zoi: christ
7:36 PM - zoi: it probably reminds you of your thoughts
7:36 PM - @nevinyrral #dreams: ?
7:36 PM - @nevinyrral #dreams: are u gonna support me
7:36 PM - @nevinyrral #dreams: or fucking just shittalk me
7:36 PM - zoi: im implying that the thoughts that go through your head are essentialyl white noise
7:36 PM - zoi: in case you missed that
7:36 PM - @nevinyrral #dreams: im trying to develop some worker pool thread queue
7:36 PM - zoi: u got the queue
7:36 PM - zoi: need the workers.
7:36 PM - @nevinyrral #dreams: yea
7:36 PM - @nevinyrral #dreams: im doing the wait loop
7:37 PM - @nevinyrral #dreams: how do u determine
7:37 PM - @nevinyrral #dreams: how many workers u have
7:37 PM - zoi: store it
7:37 PM - @nevinyrral #dreams: by ur system?
7:37 PM - zoi: dont spam get_nprocs
7:37 PM - zoi: bad perf
7:37 PM - @nevinyrral #dreams: i mean like
7:37 PM - @nevinyrral #dreams: how many workers
7:37 PM - @nevinyrral #dreams: do u want
7:37 PM - @nevinyrral #dreams: just a static amount?
7:37 PM - @nevinyrral #dreams: or load balance
7:37 PM - @nevinyrral #dreams: depending on jobs
7:37 PM - zoi: n_workers = get_nprocs +1
7:37 PM - zoi: in general
7:37 PM - @nevinyrral #dreams: whats the signifcance of that
7:37 PM - zoi: depends on work
7:37 PM - @nevinyrral #dreams: get nprocs + 1
7:37 PM - zoi: lets assume youre doing flops
7:37 PM - zoi: amd = get_nprocs/2
7:37 PM - @nevinyrral #dreams: flops? like flip flops?
7:37 PM - @nevinyrral #dreams: what the fuck is flops
7:38 PM - zoi: floating point operations
7:38 PM - zoi: per second
7:38 PM - zoi: if youre doing a bunch of fp math
7:38 PM - zoi: amds arch isnt fp friendly
7:38 PM - zoi: 2 cores share 1 fpu
7:39 PM - zoi: so naturally its not get_nprocs
7:39 PM - @nevinyrral #dreams: is that like an ALU
7:39 PM - @nevinyrral #dreams: but for fp
7:39 PM - zoi: yes
7:39 PM - @nevinyrral #dreams: on ARM/Intel each core gets its own?
7:39 PM - zoi: no
7:39 PM - zoi: not necessarily
7:39 PM - zoi: ht i7s would be /2
7:40 PM - zoi: so heres the deal
7:40 PM - zoi: you just do get_nprocs+1
7:40 PM - zoi: why +1?
7:40 PM - zoi: thats just what i do for generic jobs
7:40 PM - zoi: you can fine tune it depending on workload
7:40 PM - @nevinyrral #dreams: so theres no particular reason
7:40 PM - @nevinyrral #dreams: why u +1'd it
7:40 PM - @nevinyrral #dreams: u just do it that way
7:40 PM - zoi: when i start my game, most of my workers are essentially idle waiting on disk i/o
7:41 PM - zoi: i do +1 because most of my jobs are i/o releated
7:41 PM - zoi: related
7:41 PM - zoi: if they were all collision
7:41 PM - zoi: 24/7
7:41 PM - zoi: id do get_nprocs
7:41 PM - zoi: and thats it
7:41 PM - zoi: but theres other shit floating around in there
7:41 PM - @nevinyrral #dreams: so in theory
7:41 PM - @nevinyrral #dreams: u cant have more threads than nprocs
7:41 PM - zoi: yes
7:41 PM - zoi: no
7:41 PM - @nevinyrral #dreams: cause they all use the "bus" (im applying my comp archtecture class)
7:41 PM - @nevinyrral #dreams: but io operations
7:41 PM - @nevinyrral #dreams: dont nee dto access ram
7:42 PM - @nevinyrral #dreams: or whatever
7:42 PM - @nevinyrral #dreams: necessary
7:42 PM - @nevinyrral #dreams: or take control of the bus
7:42 PM - zoi: if you're doing slow non-cache access
7:42 PM - zoi: you will gain perf from +1
7:42 PM - zoi: or +n
7:42 PM - zoi: depending on the application
7:42 PM - zoi: if you spin up so many threads that you're forcing your cache to thrash
7:42 PM - zoi: you lose perf
7:43 PM - zoi: cache or disk
7:43 PM - zoi: well disk cache
7:43 PM - zoi: anyway
7:43 PM - zoi: dota 2
7:43 PM - zoi: test your application
7:43 PM - zoi: if youre writing high perf code, you always benchmark
7:43 PM - zoi: ie ffmpeg
7:43 PM - zoi: well
7:43 PM - zoi: x264
7:43 PM - zoi: x)
7:44 PM - zoi: x264 is the encoder that 99% of the world uses right now
7:44 PM - zoi: for streamed video
7:44 PM - zoi: so naturally they have thousands of people who go over every detail
7:44 PM - @nevinyrral #dreams: what is the x264 from
7:44 PM - @nevinyrral #dreams: is that a hardware
7:44 PM - zoi: its a program
7:44 PM - zoi: software
7:44 PM - @nevinyrral #dreams: oh
7:44 PM - @nevinyrral #dreams: thats in like OBS
7:44 PM - zoi: https://github.com/mirror/x264
7:44 PM - @nevinyrral #dreams: doesnt nvidia have their own
7:44 PM - @nevinyrral #dreams: for their cards
7:45 PM - zoi: they do but its shit
7:45 PM - zoi: so is quicksync tbh
7:45 PM - zoi: x264 is the highest quality encoder
7:46 PM - @nevinyrral #dreams: what do u mean
7:46 PM - @nevinyrral #dreams: spin up so many threads
7:46 PM - @nevinyrral #dreams: its a static amount on compile time
7:46 PM - zoi: get_nprocs isnt
7:51 PM - @nevinyrral #dreams: what was
7:51 PM - @nevinyrral #dreams: job my_job;
7:52 PM - @nevinyrral #dreams: in that pastebin
7:52 PM - @nevinyrral #dreams: is that just a void pointer
7:52 PM - @nevinyrral #dreams: to grab a function
7:52 PM - @nevinyrral #dreams: from the queue
7:52 PM - @nevinyrral #dreams: job is the struct that contains a void pointer right
7:54 PM - zoi: its whatever ur job struct is
7:54 PM - zoi: you copy to it
7:54 PM - zoi: and store it locally
7:54 PM - @nevinyrral #dreams: i dont have a job struct
7:54 PM - zoi: while you work on it
7:54 PM - @nevinyrral #dreams: why do i need one
7:55 PM - zoi: to store
7:55 PM - @nevinyrral #dreams: the queue has "functions " to do
7:55 PM - zoi: void pointer
7:55 PM - @nevinyrral #dreams: and then u jsut grab
7:55 PM - @nevinyrral #dreams: the function
7:55 PM - zoi: and void input
7:55 PM - @nevinyrral #dreams: like
7:55 PM - @nevinyrral #dreams: when u call
7:55 PM - @nevinyrral #dreams: getQueue
7:55 PM - @nevinyrral #dreams: it pops a function
7:55 PM - @nevinyrral #dreams: cant u just like
7:55 PM - @nevinyrral #dreams: void *getjob = poppedjob
7:55 PM - @nevinyrral #dreams: so that getjob poitner
7:55 PM - @nevinyrral #dreams: points to the function u wanna run
7:55 PM - @nevinyrral #dreams: then u run it
7:55 PM - @nevinyrral #dreams: or is it another cant type void* issue
7:55 PM - zoi: need function input
7:55 PM - zoi: as well
7:56 PM - zoi: function(input)
7:56 PM - zoi: is basically what ur doing
7:57 PM - @nevinyrral #dreams: alright im lost here
7:57 PM - @nevinyrral #dreams: say the queue has a job
7:57 PM - @nevinyrral #dreams: int getSum(int a, int b);
7:57 PM - @nevinyrral #dreams: when u run queuegetjob
7:57 PM - zoi: nope
7:57 PM - zoi: that isnt a job
7:57 PM - @nevinyrral #dreams: u get a pointer getSum
7:58 PM - zoi: your function must be
7:58 PM - zoi: a specific type
7:58 PM - @nevinyrral #dreams: ?
7:58 PM - @nevinyrral #dreams: so it cant just be any function?
7:58 PM - zoi: it has to be the type youre storing
7:58 PM - @nevinyrral #dreams: a "job" has to all be the same return typoe + param type + # of params?
7:58 PM - zoi: yep
7:58 PM - zoi: you can use stdarg if you want to vary it
7:58 PM - @nevinyrral #dreams: so the queue only handles one type of job
7:58 PM - zoi: but thats outside the scope of ur shit
7:58 PM - zoi: and no you match your jobs to your queue
7:59 PM - @nevinyrral #dreams: ?
7:59 PM - @nevinyrral #dreams: what do u mean match jobs
7:59 PM - @nevinyrral #dreams: all the workers are generic
8:00 PM - @nevinyrral #dreams: so ur saying u have specialized workers
8:00 PM - @nevinyrral #dreams: worker a can handle void blah ( void)
8:00 PM - zoi: you have a function
8:00 PM - @nevinyrral #dreams: worker b can handle int blah( int a)
8:00 PM - zoi: do_thing(struct input my_input)
8:00 PM - @nevinyrral #dreams: work c can handle double blah( int a , int b)
8:00 PM - zoi: yeah stop typing
8:00 PM - zoi: im typing right now
8:00 PM - zoi: 21:00 - zoi: do_thing(struct input my_input)
8:00 PM - zoi: you need to wrap this
8:00 PM - zoi: void do_thing_wrapper(void *input)
8:00 PM - zoi: and your job becomes
8:01 PM - zoi: malloc your input, set the input variables
8:01 PM - zoi: my_input.x = x
8:01 PM - zoi: my_Input.y = y
8:01 PM - zoi: add_job(do_thing_wrapper, (void*)my_input)
8:02 PM - zoi: do_thing_wrapper re-casts the void* input to "struct input"
8:02 PM - zoi: and then runs do_thing
8:02 PM - zoi: the code for it would be
8:02 PM - zoi: do_thing((struct input*)input)
8:03 PM - @nevinyrral #dreams: ? so the struct has a variable amount of input params?
8:03 PM - @nevinyrral #dreams: so i can have jobs with 2 input params
8:03 PM - @nevinyrral #dreams: 3 input params
8:03 PM - zoi: no
8:03 PM - @nevinyrral #dreams: it has to be the same?
8:03 PM - zoi: you pack your whole input into a struct
8:03 PM - zoi: think this shit out before you ask please
8:03 PM - zoi: how would you have varying arguments in your struct
8:03 PM - zoi: it has to be a static size at compile time
8:03 PM - zoi: we learned this before
8:04 PM - @nevinyrral #dreams: i mean like
8:04 PM - zoi: if you want to do
8:04 PM - @nevinyrral #dreams: u have in the struct
8:04 PM - @nevinyrral #dreams: arg1
8:04 PM - @nevinyrral #dreams: arg2
8:04 PM - @nevinyrral #dreams: arg3
8:04 PM - @nevinyrral #dreams: then when u unpack it
8:04 PM - zoi: func(int x, int y)
8:04 PM - @nevinyrral #dreams: check if null
8:04 PM - zoi: sure
8:04 PM - zoi: you could make a vector
8:04 PM - zoi: but your function has to read that
8:04 PM - zoi: so that becomes up to your implementation
8:04 PM - zoi: youre still inputting 1 arg
8:05 PM - zoi: to the wrapper
8:05 PM - zoi: your functions must always match the function prototype
8:05 PM - zoi: ie void (void*)
8:05 PM - @nevinyrral #dreams: so the way u get around that is
8:05 PM - @nevinyrral #dreams: u pass structs
8:05 PM - @nevinyrral #dreams: so its always 1 paramter
8:05 PM - zoi: yeah
8:05 PM - zoi: 1 struct with all relevant data
8:05 PM - @nevinyrral #dreams: and the struct can have a varying amount of data in it
8:05 PM - @nevinyrral #dreams: depending on ur function
8:05 PM - zoi: no
8:06 PM - zoi: struct cannot have
8:06 PM - zoi: varying amount of data
8:06 PM - @nevinyrral #dreams: like
8:06 PM - zoi: its a varying struct
8:06 PM - @nevinyrral #dreams: u have a struct for 2 input functions
8:06 PM - @nevinyrral #dreams: a struct for 1 input functions
8:06 PM - zoi: no
8:06 PM - @nevinyrral #dreams: then u pass the appropriate one
8:06 PM - @nevinyrral #dreams: depending on the job
8:06 PM - zoi: you write a struct for your function
8:06 PM - @nevinyrral #dreams: my while loop function?
8:06 PM - @nevinyrral #dreams: or the generic job
8:06 PM - zoi: the job
8:06 PM - @nevinyrral #dreams: the main thing u store is
8:06 PM - @nevinyrral #dreams: function pointer
8:06 PM - @nevinyrral #dreams: and params?
8:06 PM - @nevinyrral #dreams: so u essentially just need two things
8:06 PM - zoi: 1 param
8:06 PM - zoi: void (void*)
8:06 PM - @nevinyrral #dreams: void *pointer
8:06 PM - @nevinyrral #dreams: void *param?
8:07 PM - zoi: void *function, void *input
8:07 PM - zoi: then you do
8:07 PM - zoi: function(input)
8:07 PM - zoi: job.function(job.input)
8:07 PM - zoi: if you have them both on struct job
8:13 PM - @nevinyrral #dreams: man
8:13 PM - @nevinyrral #dreams: give me a doc t o read on this shit
8:13 PM - @nevinyrral #dreams: this shits all fragmeneted
8:13 PM - @nevinyrral #dreams: knowledge gap + ur brain genius methods of implementation
8:14 PM - @nevinyrral #dreams: i need sum resources
8:15 PM - zoi is now Online.
8:15 PM - zoi: what
8:15 PM - @nevinyrral #dreams: idk like  i need a man page
8:15 PM - @nevinyrral #dreams: for worker + thread pool
8:15 PM - @nevinyrral #dreams: thats all connected
8:16 PM - @nevinyrral #dreams: comprehesnsive :^] but basic for now
8:16 PM - zoi: :^]
8:16 PM - @nevinyrral #dreams: ?
8:16 PM - @nevinyrral #dreams: im srs
8:16 PM - zoi: :^]
8:16 PM - @nevinyrral #dreams: ...
8:16 PM - @nevinyrral #dreams: can u not troll m,e
8:16 PM - zoi: im not
8:16 PM - @nevinyrral #dreams: when we discuss this stuff
8:16 PM - zoi: its a fun smiley xD
8:16 PM - @nevinyrral #dreams: can u provide me with this info or what
8:16 PM - zoi: for what
8:16 PM - @nevinyrral #dreams: i still dont get this whole
8:16 PM - zoi: you didnt type shit
8:16 PM - @nevinyrral #dreams: struct function shit
8:17 PM - zoi: you didnt ask a question
8:17 PM - @nevinyrral #dreams: i need like a detailed man page kinda thing on this type of shit
8:17 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/gameplay.h#L95-L103
8:17 PM - zoi: wrapper function example
8:17 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/gameplay.h#L89-L92
8:17 PM - zoi: struct example
8:17 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/gameplay.h#L177-L179
8:18 PM - zoi: add job to queue example
8:18 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/nx_src/nx_deferred_processing.cpp#L62-L107
8:18 PM - zoi: worker thread example
8:19 PM - zoi: youll notice that the work() function is part of the class that wraps up the queue as well as all workers
8:19 PM - zoi: you can do that with pthreads by wrapping the class and making work a public function
8:20 PM - zoi: https://github.com/dannyluong408/arenagame/blob/master/client/nx_src/nx_deferred_processing.cpp#L3-L7
8:21 PM - zoi: and finally
8:21 PM - zoi: https://www.youtube.com/watch?v=UWDRPVDTeuc
8:21 PM - zoi: music to program to
8:21 PM - @nevinyrral #dreams: how do u just link me
8:21 PM - @nevinyrral #dreams: the exact same song
8:21 PM - @nevinyrral #dreams: 3 times
8:22 PM - zoi: good question
8:22 PM - @nevinyrral #dreams: alrigght
8:22 PM - @nevinyrral #dreams: im gonna put this on repeat out of respect for you
8:22 PM - @nevinyrral #dreams: if i shoot myself in an hour
8:22 PM - @nevinyrral #dreams: its on u
8:22 PM - zoi: how are u gonna do that without a gun
8:22 PM - @nevinyrral #dreams: should i put it on 2x speed
8:22 PM - zoi: u little bitch
8:22 PM - zoi: nice threats
8:22 PM - @nevinyrral #dreams: i live in the ghetto
8:22 PM - @nevinyrral #dreams: i can walk up to any mexican
8:22 PM - @nevinyrral #dreams: and ask them to shoot me
8:22 PM - zoi: no you fucking dont
8:22 PM - @nevinyrral #dreams: have u tried this song on 2x speed
8:23 PM - zoi: no
8:23 PM - @nevinyrral #dreams: its alot better
8:23 PM - zoi: its perfecton 1x
8:23 PM - @nevinyrral #dreams: the funny thing is i think its alrdy sped up
8:25 PM - @nevinyrral #dreams: dear lord
8:26 PM - @nevinyrral #dreams: its even worse when uwatch the vid
8:26 PM - @nevinyrral #dreams: while ur listening
8:26 PM - @nevinyrral #dreams: is this from a hentai
8:26 PM - @nevinyrral #dreams: dear lord
8:26 PM - zoi: did you just realize what that moaning was
8:26 PM - @nevinyrral #dreams: is it high speed moaning?
8:26 PM - @nevinyrral #dreams: LMAO
8:26 PM - @nevinyrral #dreams: alright i cant watch this loop anymore
8:39 PM - @nevinyrral #dreams: // what a goddamn emss
void update_player_wrapper(void *input) {
8:39 PM - @nevinyrral #dreams: what a goddamn mess
8:39 PM - zoi: agreed
8:40 PM - zoi: theres a $10 per month gym near me
8:40 PM - zoi: with really shit reviews
8:40 PM - zoi: i bet i get in on that
8:40 PM - zoi: 24/7
8:40 PM - zoi: just go there at like 2 am
8:40 PM - @nevinyrral #dreams: as long as it has dumbells, a power rack , thats all u need
8:41 PM - zoi: their other location looks nuts
8:41 PM - zoi: people are writing about how they dont cancel memberships
8:41 PM - zoi: theyve got fucking tanning machines if you pay $20 per month
8:41 PM - zoi: wtf
8:44 PM - zoi: do u ohp in the squat rack or something
8:44 PM - @nevinyrral #dreams: yea
8:44 PM - @nevinyrral #dreams: then do dunmbell shoulder presses
8:44 PM - @nevinyrral #dreams: on the dumbell seats
8:45 PM - zoi: theyve got 1 squat rack in the whole place
8:45 PM - @nevinyrral #dreams: with the  seat at like 90 degrees
8:45 PM - @nevinyrral #dreams: nice
8:45 PM - @nevinyrral #dreams: thats what 10$ gets u
8:45 PM - @nevinyrral #dreams: sounds about right
8:45 PM - zoi: but they have
8:45 PM - @nevinyrral #dreams: samet hing here at the 10$ gym here
8:45 PM - zoi: 900000000000 treadmills
8:45 PM - @nevinyrral #dreams: yup
8:45 PM - @nevinyrral #dreams: google fitness 19
8:45 PM - @nevinyrral #dreams: same shit
8:45 PM - zoi: theyve got a few benches
8:45 PM - zoi: like a lot actually
8:45 PM - @nevinyrral #dreams: ya
8:46 PM - zoi: do normal people not squat
8:46 PM - @nevinyrral #dreams: most people who go to the gym
8:46 PM - @nevinyrral #dreams: are all upper body
8:46 PM - zoi: thats me dude
8:46 PM - @nevinyrral #dreams: cause fuckboys etc
8:46 PM - zoi: but i dont have any way to do legs
8:46 PM - @nevinyrral #dreams: thats the dont skip leg day meme
8:46 PM - zoi: at my current
8:46 PM - @nevinyrral #dreams: everyone just does like
8:46 PM - zoi: 2 machine gym
8:46 PM - @nevinyrral #dreams: bicep curls
8:46 PM - @nevinyrral #dreams: and bench press
8:46 PM - @nevinyrral #dreams: prolly
8:46 PM - @nevinyrral #dreams: just gotta do squats
8:47 PM - @nevinyrral #dreams: im sure they have
8:47 PM - @nevinyrral #dreams: dumbells at the gym
8:47 PM - zoi: they do
8:47 PM - zoi: a lot
8:47 PM - @nevinyrral #dreams: do goblet squats
8:47 PM - @nevinyrral #dreams: lunges with dumbells
8:47 PM - @nevinyrral #dreams: etc
8:47 PM - @nevinyrral #dreams: better than nothing
8:47 PM - @nevinyrral #dreams: u can hold a heavy ass dumbell with both hands
8:47 PM - @nevinyrral #dreams: and just do a goblet squat
8:47 PM - @nevinyrral #dreams: its kinda like a front squat
8:47 PM - @nevinyrral #dreams: do lunges
8:47 PM - @nevinyrral #dreams: calf raises
8:47 PM - @nevinyrral #dreams: all dumbell-able
8:48 PM - zoi: ill just squat over the bench
8:48 PM - zoi: thats what not manlets do
8:48 PM - Your state is set to Offline.
8:48 PM - zoi is now Offline.
8:48 PM - Online now and rejoined chat.
8:48 PM - zoi is now Online.
8:48 PM - @nevinyrral #dreams: lol
8:51 PM - @nevinyrral #dreams: anyways
8:51 PM - @nevinyrral #dreams: so the wrapper functions the one that can have multiple ones
8:51 PM - @nevinyrral #dreams: the struct is const
8:53 PM - zoi is now Away.

*/