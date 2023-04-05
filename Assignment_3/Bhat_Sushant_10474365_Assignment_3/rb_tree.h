#ifndef __RB_TREE_H__
#define __RB_TREE_H__

enum rb_tree_color
{
  RB_RED,
  RB_BLACK
};

struct rbt_node
{
  rbt_node *left;
  rbt_node *right;
  rbt_node *p;
  int key;
  int color;
};

struct rbt_info
{
  int left_rotate;
  int right_rotate;
  int duplicate;
  int case_1;
  int case_2;
  int case_3;

  void reset()
  {
    case_1 = case_2 = case_3 = duplicate =
        left_rotate = right_rotate = 0;
  }
};

class rb_tree
{
protected:
  rbt_node *T_nil;
  rbt_node *T_root;

public:
  rb_tree();
  ~rb_tree();

  void insert(int, rbt_info &);
  int convert(int *, int);
  int check_black_height()
  {
    return check_black_height(T_root);
  }

  // void inorder_output()
  //   { inorder_output(T_root, 1, new int[], 0); }
  void output()
  {
    output(T_root, 1);
  }

protected:
  void insert(rbt_node *, rbt_info &);
  void insert_fixup(rbt_node *&, rbt_info &);

  int check_black_height(rbt_node *);
  int rightCount(rbt_node *);
  int leftCount(rbt_node *);

  void remove_all(rbt_node *);

  void left_rotate(rbt_node *);
  void right_rotate(rbt_node *);

  void inorder_output(rbt_node *, int, int *);
  void output(rbt_node *, int);
};

#endif
