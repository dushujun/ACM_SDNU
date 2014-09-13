// Trie树 动态开辟内存实现

#define MAX_NUM 26
enum NODE_TYPE{ //"COMPLETED" means a string is generated so far.
  COMPLETED,
  UNCOMPLETED
};
struct Node {
  enum NODE_TYPE type;
  char ch;
  struct Node* child[MAX_NUM]; //26-tree->a, b ,c, .....z
};
 
struct Node* ROOT; //tree root
 
struct Node* createNewNode(char ch){
  // create a new node
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->ch = ch;
  new_node->type == UNCOMPLETED;
  int i;
  for(i = 0; i < MAX_NUM; i++)
    new_node->child[i] = NULL;
  return new_node;
}
 
void initialization() {
//intiazation: creat an empty tree, with only a ROOT
ROOT = createNewNode(' ');
}
 
int charToindex(char ch) { //a "char" maps to an index<br>
return ch - 'a';
}
 
int find(const char chars[], int len) {
  struct Node* ptr = ROOT;
  int i = 0;
  while(i < len) {
   if(ptr->child[charToindex(chars[i])] == NULL) {
   break;
  }
  ptr = ptr->child[charToindex(chars[i])];
  i++;
  }
  return (i == len) && (ptr->type == COMPLETED);
}
 
void insert(const char chars[], int len) {
  struct Node* ptr = ROOT;
  int i;
  for(i = 0; i < len; i++) {
   if(ptr->child[charToindex(chars[i])] == NULL) {
    ptr->child[charToindex(chars[i])] = createNewNode(chars[i]);
  }
  ptr = ptr->child[charToindex(chars[i])];
}
  ptr->type = COMPLETED;
}
