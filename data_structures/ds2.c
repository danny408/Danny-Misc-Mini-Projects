//2. Write a 3D spatially-mapped tree. Write a function that inserts objects into this tree. 
//Write a function which returns all objects within a 3D bounding box inside of this tree.

//objects = triangles
//50000 triangles
//evenly spread about 2 dimensions

//use Quad tree
#include <stdio.h>
#include <stdlib.h>

#define MAX_TRIANGLES 21474836467 // 2^32-1

//Bounding Box
struct bb {
    struct {
        float x,y,z;
    } point[8]; //8 points for a 3d box
};

struct triangleNode{
	float x,y,z;
};

struct quadTree{
	struct triangleNode *trianglePos;
	struct quadTree *NW;
	struct quadTree *NE;
	struct quadTree *SW;
	struct quadTree *SE;
	unsigned int size;
};

void buildQuadTree(struct quadTree *n);

void printQuadTree(struct quadTree *n, int depth);

void deleteQuadTree(struct quadTree *n);

struct quadTree* BuildQTree(struct quadTree *n, struct quadTree  *nParent, int index);


int main(void){
	//struct quadTree* root = malloc(sizeof(struct quadTree));
	//setQuad(root);
	return 1;
}

void setQuad(struct quadTree *qt){
	qt->trianglePos = NULL;
	qt->NW = NULL;
	qt->NE = NULL;
	qt->SW = NULL;
	qt->SE = NULL;
	qt->size = 0;
}

void buildQuadTree(struct quadTree *qt){
	
}

void insert(struct quadTree *qt, float x, float y, float z){
	if (qt->size == 0){
		qt->size++;
		qt->trianglePos = malloc(sizeof(struct triangleNode));
		qt->trianglePos[qt->size-1].x=x;
		qt->trianglePos[qt->size-1].y=y;
		qt->trianglePos[qt->size-1].z=z;
	}
	else if(qt->size<21474836467){
		qt->size++;
		qt->trianglePos = realloc(qt->trianglePos,sizeof(struct triangleNode)*(qt->size));
		qt->trianglePos[qt->size-1].x=x;
		qt->trianglePos[qt->size-1].y=y;
		qt->trianglePos[qt->size-1].z=z;
	}
	else{//need to make new 4 quads under this one
	}
}

/*
8:35 PM - gamer26: to 2^32 -1
8:37 PM - @nevinyrral #dreams: can i not read
8:37 PM - gamer26: so you think
8:38 PM - gamer26: you skip to literally 4 * sizeof(triangle) gigabytes
8:38 PM - gamer26: of memory
8:38 PM - @nevinyrral #dreams: no
8:38 PM - @nevinyrral #dreams: this implementation here is fine where u just check the size
8:38 PM - @nevinyrral #dreams: and increase up to 232-1
8:38 PM - @nevinyrral #dreams: and then u break it into 4
8:38 PM - @nevinyrral #dreams: if it hits that
8:38 PM - @nevinyrral #dreams: so idk what ur trying to say
8:38 PM - gamer26: max is 4
8:38 PM - gamer26: until you cant split into quadrants
8:38 PM - gamer26: anymore
8:38 PM - gamer26: surely your tree has to have limits right?
8:39 PM - @nevinyrral #dreams: u mean in depth/
8:39 PM - gamer26: what is your tree representing
8:39 PM - @nevinyrral #dreams: objects
8:39 PM - @nevinyrral #dreams: in a 3d plane
8:39 PM - @nevinyrral #dreams: children are within their parents bounds
8:39 PM - gamer26: hmm
8:39 PM - gamer26: 3d plane
8:39 PM - gamer26: planes are 2d
8:39 PM - gamer26: are you sure youre representing a plane?
8:40 PM - gamer26: no i dont
8:40 PM - gamer26: obviously you dont either
8:40 PM - gamer26: otherwise youd say it
8:40 PM - gamer26: 3d space
8:40 PM - @nevinyrral #dreams: A QUAD TREE REPRESENTS ITS OBJECTS
8:40 PM - @nevinyrral #dreams: IN 3D SPACE
8:40 PM - gamer26: so you're representing 3d space
8:40 PM - @nevinyrral #dreams: AND ITS CHILDREN
8:40 PM - gamer26: hmm
8:40 PM - @nevinyrral #dreams: ARE WITHIN THEIR PARENTS
8:40 PM - @nevinyrral #dreams: 3D SPACE
8:40 PM - gamer26: so can you represent infinite space
8:40 PM - @nevinyrral #dreams: BOUND WISE
8:40 PM - gamer26: within your program
8:40 PM - @nevinyrral #dreams: NO
8:40 PM - @nevinyrral #dreams: UR ROOT NODE
8:40 PM - @nevinyrral #dreams: DETERMINES
8:40 PM - @nevinyrral #dreams: UR BOUNDING BOX
8:40 PM - gamer26: so the structure must have limits
8:40 PM - @nevinyrral #dreams: yes sir
8:40 PM - @nevinyrral #dreams: UNLESS WE GO INTO
8:40 PM - gamer26: when you reach the limits, what do you do?
8:40 PM - @nevinyrral #dreams: CS THEORY
8:40 PM - @nevinyrral #dreams: you have to scale
8:40 PM - @nevinyrral #dreams: thats modern society
8:40 PM - gamer26: sure lets go into cs theory
8:41 PM - @nevinyrral #dreams: scalability
8:41 PM - gamer26: yeah
8:41 PM - gamer26: youre banned from buzzwords
8:41 PM - @nevinyrral #dreams: LOL
8:41 PM - gamer26: dont ever fucking type "scalability" or "cs theory" to me
8:41 PM - @nevinyrral #dreams: okay obviously theres an upper limit
8:41 PM - gamer26: there's a very reachable limit
8:41 PM - gamer26: because you can't accurately represent space with reasonable precision using a float
8:41 PM - gamer26: so you use integers
8:41 PM - gamer26: large integers
8:42 PM - gamer26: and you get nice 1 cycle division
8:42 PM - gamer26: because all your splits are division by 2
8:42 PM - gamer26: aka a bit shift
8:42 PM - gamer26: so whats your limit when you divide by 2
8:42 PM - gamer26: on a uint32_t
8:42 PM - @nevinyrral #dreams: do u want me to calcualte that
8:42 PM - @nevinyrral #dreams: or just tell u its half of that
8:42 PM - gamer26: hmm?
8:42 PM - gamer26: tell me your limits
8:42 PM - gamer26: of the struct
8:43 PM - gamer26: lets use
8:43 PM - gamer26: int32_t
8:43 PM - gamer26: instead of uint32_t
8:43 PM - @nevinyrral #dreams: 2^32 / 2 is 2^31
8:43 PM - @nevinyrral #dreams: i believe
8:43 PM - gamer26: because we want to represent negatives right?
8:43 PM - gamer26: ah yes
8:43 PM - gamer26: but uint32_t isn't 2^32
8:43 PM - gamer26: it's 2^32 -1
8:43 PM - gamer26: keep that in mind for your int32_t answer
8:44 PM - @nevinyrral #dreams: why is it -1
8:44 PM - @nevinyrral #dreams: its just 111111111111111111111111111111111
8:44 PM - gamer26: because 0 exists
8:44 PM - @nevinyrral #dreams: cause u can use the highest bit now
8:44 PM - @nevinyrral #dreams: since its not signed
8:44 PM - @nevinyrral #dreams: isnt 0 just 0000000000000000
8:44 PM - gamer26: do you think 0xFF is 256
8:44 PM - @nevinyrral #dreams: no
8:44 PM - @nevinyrral #dreams: its 255
8:44 PM - @nevinyrral #dreams: DUH
8:45 PM - gamer26: then why do you thinjk 0xFFFFFFFF is 2^32
8:45 PM - @nevinyrral #dreams: okay so its 2^31-1
8:45 PM - gamer26: neat
8:45 PM - gamer26: lets make our root node represent -2^30 to +2^30
8:45 PM - gamer26: sound good?
8:45 PM - @nevinyrral #dreams: why are we bringing negatives
8:46 PM - gamer26: do you not want negative space
8:46 PM - gamer26: or do you want to run all of your coordinates and all of your triangles through nice translations
8:46 PM - gamer26: every time you want to use them
8:46 PM - @nevinyrral #dreams: yea
8:46 PM - @nevinyrral #dreams: dont u just
8:46 PM - @nevinyrral #dreams: transformation matrix
8:46 PM - @nevinyrral #dreams: to make them all positive
8:46 PM - @nevinyrral #dreams: when u need to
8:46 PM - gamer26: you need to study your math
8:46 PM - gamer26: youre doing one transform
8:46 PM - gamer26: why do you have a whole matrix
8:47 PM - gamer26: translating coordinates requires one addition operation per dimension
8:47 PM - gamer26: all you need is the position and the offset
8:47 PM - gamer26: so wheres the matrix come into play
8:48 PM - gamer26: nowhere?
8:48 PM - gamer26: all right
8:48 PM - gamer26: let's skip that then
8:48 PM - gamer26: do you want them to be all positive?
8:48 PM - gamer26: even if they are all positive, what do you gain?
8:49 PM - gamer26: ill answer that question because ur brain seems to be afk
8:49 PM - gamer26: you dont really gain anything
8:49 PM - gamer26: your triangles map perfectly to it
8:49 PM - gamer26: assuming theyre within the bounds of the area you're trying to represent
8:49 PM - gamer26: if they aren't, you can still store them in the root node
8:49 PM - gamer26: works fine right?
8:50 PM - gamer26: right.
8:50 PM - gamer26: since you only check nodes you enter and you always enter the root node
8:50 PM - gamer26: good answer nevin
8:50 PM - @nevinyrral #dreams: i dont wanna get
8:50 PM - @nevinyrral #dreams: yleled at
8:50 PM - @nevinyrral #dreams: for saying something
8:50 PM - gamer26: you didnt get yelled at
8:50 PM - @nevinyrral #dreams: thx
8:50 PM - gamer26: i told you that either
8:50 PM - gamer26: your math education is horribly insufficient
8:51 PM - gamer26: or youre not putting an ounce of thought into this project
8:51 PM - @nevinyrral #dreams: i told u
8:51 PM - gamer26: you can fix both of those
8:51 PM - @nevinyrral #dreams: linear eq + diff eq
8:51 PM - @nevinyrral #dreams: was like
8:51 PM - @nevinyrral #dreams: a hybrid course
8:51 PM - @nevinyrral #dreams: one semester
8:51 PM - gamer26: so your math education is horribly insufficient?
8:51 PM - gamer26: which way am i right here
8:51 PM - gamer26: because i know im right one way
8:51 PM - gamer26: maybe both
8:51 PM - gamer26: why dont we carry on
8:51 PM - gamer26: excuses are even more annoying than silly thoughts
8:52 PM - gamer26: so you have your area you're trying to represent
8:52 PM - gamer26: -2^30 to +2^30
8:52 PM - gamer26: is this right
8:52 PM - gamer26: or did we do something wrong
8:52 PM - gamer26: i think youll find your average map isn't spread out enough to use outer nodes
8:53 PM - @nevinyrral #dreams: yea
8:53 PM - @nevinyrral #dreams: sure
8:53 PM - @nevinyrral #dreams: thats our
8:53 PM - gamer26: so maybe we can get away with 2^14
8:53 PM - @nevinyrral #dreams: theoreticaly max bound
8:53 PM - @nevinyrral #dreams: with ints
8:53 PM - gamer26: not necessarily
8:53 PM - gamer26: remember what i said
8:53 PM - gamer26: triangles outside of those bounds can still be used
8:53 PM - gamer26: they go on the root node
8:53 PM - gamer26: why si that?
8:53 PM - @nevinyrral #dreams: they share a side?
8:53 PM - gamer26: the root node is always accessed
8:53 PM - gamer26: no matter what
8:54 PM - gamer26: you determine relevancy by quadrant
8:54 PM - @nevinyrral #dreams: yea so
8:54 PM - @nevinyrral #dreams: if u have it in th e root
8:54 PM - @nevinyrral #dreams: u dont know where its at
8:54 PM - gamer26: if your target doesn't intersect or surround a quadrant, that quadrant is irrelevant
8:54 PM - gamer26: you don't even enter it
8:54 PM - gamer26: that's what makes this design efficient
8:55 PM - gamer26: you reduce your traversal to logn by skipping data by quadrant
8:55 PM - gamer26: objects that cant fit within a child node must be stored on the current node
8:55 PM - gamer26: that's always a rule when inserting
8:56 PM - gamer26: if you insert into the root node and there's no sufficient child for it, it goes on the root node
8:56 PM - gamer26: anyway thats all
8:56 PM - gamer26: go forth and bring me code
*/


1:00 PM - @nevinyrral #dreams: yes sir..
1:06 PM - @nevinyrral #dreams: how can i fix my issue
1:06 PM - @nevinyrral #dreams: with these trees and graphs
1:06 PM - zoi: what issue
1:06 PM - zoi: also what graph
1:06 PM - @nevinyrral #dreams: idk
1:07 PM - @nevinyrral #dreams: justi n general
1:07 PM - @nevinyrral #dreams: im still having trouble wraapping my head around the quad tree one
1:07 PM - @nevinyrral #dreams: so basically like u said
1:07 PM - @nevinyrral #dreams: we want 4 children per node
1:07 PM - @nevinyrral #dreams: until we reach a max
1:07 PM - @nevinyrral #dreams: as per a normal quad tree
1:07 PM - zoi: max depth
1:07 PM - @nevinyrral #dreams: each node has 4 triangles each?
1:07 PM - @nevinyrral #dreams: until theres no more space?
1:07 PM - zoi: variable triangles
1:07 PM - @nevinyrral #dreams: then each node has uint32max/2?
1:07 PM - zoi: yeah
1:07 PM - zoi: we'll go with that
1:08 PM - zoi: dont expand your triangle bucket
1:08 PM - zoi: unless
1:08 PM - zoi: its the final node
1:08 PM - zoi: or you have more than 4 triangles which wont fit in subchildren
1:08 PM - @nevinyrral #dreams: ?
1:08 PM - @nevinyrral #dreams: we need to use the same terms here
1:08 PM - @nevinyrral #dreams: what is my triangle bucket
1:08 PM - @nevinyrral #dreams: just my variable arrray
1:08 PM - @nevinyrral #dreams: of triangles
1:08 PM - @nevinyrral #dreams: per node?
1:08 PM - @nevinyrral #dreams: which is set to 4
1:08 PM - zoi: yes
1:08 PM - zoi: max 4 by default
1:08 PM - @nevinyrral #dreams: until i run out of space for 4 * max depth
1:08 PM - @nevinyrral #dreams: or whatever
1:09 PM - @nevinyrral #dreams: so within that specific quadrant if theres more than 4 triangles that fit under that
1:09 PM - @nevinyrral #dreams: i just need to break it into 4 more quads
1:09 PM - @nevinyrral #dreams: then when i cant break it anymore aka max depth
1:09 PM - @nevinyrral #dreams: then i increase the limit on every single previous node
1:09 PM - @nevinyrral #dreams: and just insert from there?
1:09 PM - @nevinyrral #dreams: if i increase the max from 4 -> max
1:09 PM - @nevinyrral #dreams: i would have to rebalance each quad?
1:10 PM - @nevinyrral #dreams: cause then for more accuracy id have them all at the deepest level of the tree
1:10 PM - @nevinyrral #dreams: since its the most accurate
1:10 PM - zoi: but you dont want to have to enter those children
1:10 PM - zoi: if you dont need to make new children
1:10 PM - zoi: you dont
1:10 PM - @nevinyrral #dreams: say we have depth of like 5
1:10 PM - @nevinyrral #dreams: every single node has 4 triangles
1:10 PM - @nevinyrral #dreams: when u insert one
1:11 PM - @nevinyrral #dreams: now u have to rebalance every node to have "max" triangles
1:11 PM - zoi: why
1:11 PM - @nevinyrral #dreams: thats our "design"?
1:11 PM - @nevinyrral #dreams: or do u just insert the 5th new one
1:11 PM - @nevinyrral #dreams: at the bottom
1:11 PM - zoi: it goes as deep as possible
1:11 PM - zoi: if "as deep as possible" node is full, you swap it
1:12 PM - @nevinyrral #dreams: why are we swapping
1:12 PM - @nevinyrral #dreams: we shudnt ever be full
1:12 PM - @nevinyrral #dreams: after increasing the triangle cap per node
1:12 PM - @nevinyrral #dreams: from 4
1:13 PM - zoi: 14:07 - zoi: dont expand your triangle bucket
14:08 - zoi: unless
14:08 - zoi: its the final node
14:08 - zoi: or you have more than 4 triangles which wont fit in subchildren
1:13 PM - zoi: stop messaging me and go read up on it
1:13 PM - zoi: you should be able to do this with what ive given you
1:13 PM - zoi: but youre not reading
1:13 PM - @nevinyrral #dreams: i dont know what to read
1:13 PM - @nevinyrral #dreams: quadtrees just works with like
1:13 PM - @nevinyrral #dreams: pixels
1:13 PM - zoi: start with reading my instructions
1:13 PM - zoi: next read my steam messages
1:13 PM - zoi: and no
1:13 PM - @nevinyrral #dreams: i dont know whats "FINAL NODE"
1:13 PM - zoi: thats not true
1:14 PM - zoi: final node is max depth
1:14 PM - zoi: ie your limits
1:14 PM - @nevinyrral #dreams: max depth has like 4^depth nodes in that row isnt it
1:14 PM - @nevinyrral #dreams: which ones actually the final
1:14 PM - zoi: we learned that if you use int32_t to designate your bounds, your limits with divisible by two numbers is 30
1:14 PM - zoi: you can identify when youre in a final node
1:14 PM - zoi: max depth
1:15 PM - zoi: when the bounds are 1x1
1:15 PM - @nevinyrral #dreams: okay
1:15 PM - @nevinyrral #dreams: lets say we do hit this final node
1:15 PM - @nevinyrral #dreams: i "expand" my bucket now
1:15 PM - @nevinyrral #dreams: so every single node in my tree i resize triangle array to MAX?
1:15 PM - zoi: what the fuck makes you think this
1:15 PM - zoi: 14:07 - zoi: dont expand your triangle bucket
14:08 - zoi: unless
14:08 - zoi: its the final node
14:08 - zoi: or you have more than 4 triangles which wont fit in subchildren
1:15 PM - zoi: god dammit nevin
1:15 PM - zoi: youre still not reading the things im typing
1:15 PM - @nevinyrral #dreams: i need some fucking visual aid
1:16 PM - @nevinyrral #dreams: i dont understand what ur typing
1:16 PM - zoi: you need to fucking read my messages
1:16 PM - @nevinyrral #dreams: u said expand teh triangle bucket
1:16 PM - @nevinyrral #dreams: unless its final node
1:16 PM - @nevinyrral #dreams: and then i said
1:16 PM - zoi: 14:07 - zoi: dont expand your triangle bucket
14:08 - zoi: unless
14:08 - zoi: its the final node
14:08 - zoi: or you have more than 4 triangles which wont fit in subchildren
1:16 PM - @nevinyrral #dreams: okay were at final node
1:16 PM - zoi: final node = 1x1
1:16 PM - zoi: thats the bounds of your final node
1:16 PM - zoi: its a 1x1 node
1:16 PM - zoi: because we cant have a 2d space with less than 1 space
1:16 PM - zoi: that would be 0
1:16 PM - zoi: 14:07 - zoi: dont expand your triangle bucket
14:08 - zoi: unless
14:08 - zoi: its the final node
14:08 - zoi: or you have more than 4 triangles which wont fit in subchildren
1:16 PM - zoi: other condition: you have 4 triangles already which you cant fit into children
1:17 PM - zoi: ie theyre too big or span across edges of the children
1:17 PM - zoi: http://imgur.com/hWZR93p
1:17 PM - zoi: triangle thats too big to fit in a child
1:18 PM - zoi: so it goes in the root node
1:18 PM - zoi: because the whole triangle cant fit in a child
1:18 PM - @nevinyrral #dreams: a child is either the 1x1
1:18 PM - @nevinyrral #dreams: or the biggest quadrant u ahve right
1:18 PM - @nevinyrral #dreams: aka the first depth
1:18 PM - @nevinyrral #dreams: would be ur biggest quadrant
1:18 PM - @nevinyrral #dreams: so it cant fit into that
1:18 PM - @nevinyrral #dreams: it wont be able to fit into anything else
1:18 PM - zoi: look
1:18 PM - @nevinyrral #dreams: further down
1:18 PM - zoi: this is the roto node only
1:18 PM - zoi: you see
1:18 PM - zoi: theres 1 triangle in here
1:18 PM - zoi: root node
1:18 PM - zoi: 4 possible children
1:18 PM - @nevinyrral #dreams: yea
1:18 PM - zoi: cant fit into any children
1:18 PM - zoi: so it goes in root node
1:18 PM - @nevinyrral #dreams: 4 possible children
1:19 PM - zoi: you have 5 of those triangles that wont fit
1:19 PM - zoi: so you have no choice but to expand
1:19 PM - zoi: or break into multiple triangles
1:19 PM - zoi: we arent going to break our triangle
1:19 PM - @nevinyrral #dreams: then what do u do
1:19 PM - @nevinyrral #dreams: if u have 5
1:19 PM - @nevinyrral #dreams: in the root node
1:19 PM - @nevinyrral #dreams: since they dont fit anywhere
1:19 PM - zoi: nothing
1:19 PM - zoi: they all go in the root node
1:19 PM - zoi: thats literally what i typed
1:19 PM - zoi: you expand your bucket of triangles
1:19 PM - zoi: if you have to
1:20 PM - zoi: theres two conditions when you have to
1:20 PM - zoi: too many that cant go deeper
1:20 PM - zoi: or too many that cant go deeper because you cant get deeper
1:20 PM - @nevinyrral #dreams: and what does expand my bucket mean
1:20 PM - @nevinyrral #dreams: since u cant go deeper than 1x1
1:20 PM - zoi: n_triangles++
1:20 PM - zoi: triangles = realloc(triangles, n)
1:20 PM - @nevinyrral #dreams: for the array per node?
1:21 PM - @nevinyrral #dreams: instead of 4 per node its 5?
1:21 PM - zoi: what does per node mean
1:21 PM - @nevinyrral #dreams: what is triangles
1:21 PM - @nevinyrral #dreams: its the array
1:21 PM - zoi: of triangles
1:21 PM - @nevinyrral #dreams: struct
1:21 PM - zoi: inside of your child
1:21 PM - @nevinyrral #dreams: yea
1:21 PM - zoi: yes
1:21 PM - @nevinyrral #dreams: and how many
1:21 PM - @nevinyrral #dreams: does this array start with
1:21 PM - @nevinyrral #dreams: 4 ?
1:21 PM - @nevinyrral #dreams: each of the 4 possible children
1:21 PM - @nevinyrral #dreams: start with 4 triangles max inside each
1:21 PM - zoi: no
1:21 PM - zoi: it starts with whatever you want
1:21 PM - zoi: the bucket size is max 4, unless otherwise
1:22 PM - zoi: it would start with 0
1:22 PM - @nevinyrral #dreams: when u refer to bucket
1:22 PM - zoi: because you dont have anything inserted
1:22 PM - @nevinyrral #dreams: is that the triangle array
1:22 PM - zoi: yes
1:22 PM - @nevinyrral #dreams: okay
1:22 PM - @nevinyrral #dreams: so from the root
1:22 PM - @nevinyrral #dreams: we have 4 possible children each
1:22 PM - @nevinyrral #dreams: and each children
1:22 PM - @nevinyrral #dreams: has a triangle bucket
1:22 PM - @nevinyrral #dreams: thats var length
1:22 PM - @nevinyrral #dreams: starting with 0
1:22 PM - @nevinyrral #dreams: until we add stuff
1:23 PM - zoi: ur doing good so far
1:23 PM - @nevinyrral #dreams: whats my condition
1:23 PM - @nevinyrral #dreams: to go from 4 children
1:23 PM - @nevinyrral #dreams: to 16
1:23 PM - zoi: you dont think of it in
1:23 PM - zoi: n children
1:23 PM - zoi: its
1:23 PM - zoi: each child can have 4 children max
1:23 PM - @nevinyrral #dreams: yea
1:23 PM - zoi: children are only allocated when theyre needed
1:23 PM - @nevinyrral #dreams: the deeper u go
1:23 PM - @nevinyrral #dreams: the more precise
1:23 PM - zoi: ie when your bucket fills
1:23 PM - zoi: it spills to children
1:23 PM - @nevinyrral #dreams: ur location of that triangle is
1:24 PM - zoi: the fuck does that even mean
1:24 PM - @nevinyrral #dreams: OKAY
1:24 PM - zoi: the precision doesnt change
1:24 PM - @nevinyrral #dreams: SO
1:24 PM - @nevinyrral #dreams: WHEN BUCKET > 4
1:24 PM - @nevinyrral #dreams: U CREATE
1:24 PM - @nevinyrral #dreams: A NEW ROW
1:24 PM - @nevinyrral #dreams: depth
1:24 PM - zoi: a new child
1:24 PM - zoi: spill triangles from your bucket
1:24 PM - zoi: ie it overfills
1:24 PM - zoi: so you spill
1:24 PM - zoi: if you can
1:24 PM - zoi: to children
1:24 PM - zoi: into their buckets
1:24 PM - @nevinyrral #dreams: okay
1:24 PM - @nevinyrral #dreams: lets say
1:24 PM - @nevinyrral #dreams: u have
1:24 PM - @nevinyrral #dreams: 4 in child node
1:24 PM - @nevinyrral #dreams: and u want a 5th
1:24 PM - @nevinyrral #dreams: so u create  4 more child nodes
1:24 PM - @nevinyrral #dreams: do u realloc the 5 triangles
1:24 PM - @nevinyrral #dreams: into the 4 children
1:25 PM - zoi: nigger go fuckign kill yourself
1:25 PM - @nevinyrral #dreams: ?
1:25 PM - zoi: im not dealing with your shit
1:25 PM - zoi: 14:23 - zoi: children are only allocated when theyre needed
1:25 PM - zoi: 14:24 - zoi: a new child
14:24 - zoi: spill triangles from your bucket
14:24 - zoi: ie it overfills
14:24 - zoi: so you spill
14:24 - zoi: if you can
14:24 - zoi: to children
14:24 - zoi: into their buckets
1:26 PM - zoi: you can dump all your triangles into children if you want to
1:26 PM - zoi: thats your fucking perogative
1:26 PM - zoi: i didnt specify it
1:26 PM - zoi: so do whatever the fuck hyou want
1:26 PM - zoi: just read my messages
2:41 PM - @nevinyrral #dreams: ty
2:42 PM - @nevinyrral #dreams has changed their name to broken english = feeding.
3:58 PM - zoi is now Online.
4:43 PM - broken english = feeding has changed their name to @nevinyrral #dreams.
6:45 PM - @nevinyrral #dreams has changed their name to team = broken english gg.
6:48 PM - team = broken english gg has changed their name to @nevinyrral #dreams.
10:43 PM - zoi is now Online.
10:56 PM - zoi: trees figured out?
