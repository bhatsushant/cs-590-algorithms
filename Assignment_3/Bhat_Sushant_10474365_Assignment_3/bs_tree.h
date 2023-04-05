#ifndef __BS_TREE_H__
#define __BS_TREE_H__

struct bst_node
{
  bst_node *left;
  bst_node *right;
  bst_node *p;
  int key;
};

struct bst_info
{
  int duplicate;

  void reset()
  {
    duplicate = 0;
  }
};

class bs_tree
{
protected:
  bst_node *T_root;
  bst_node *T_nil;

public:
  bs_tree();
  ~bs_tree();

  void insert(int, bst_info &);
  // int convert(int*, int);
  int convert(int *, int);
  void inorder_output(bst_node *T_root, int, int *);
  void remove_all(bst_node *);

protected:
  void insert(bst_node *, bst_info &);
};

#endif
