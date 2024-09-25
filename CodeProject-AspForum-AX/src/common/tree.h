// ###########################################################################
// #
// # file:
// #	tree.h
// #
// # remarks:
// #	copyright © 2000 zeta software GbR.
// #
// # history:
// #	2000-05-16 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __TREE_H__
#define __TREE_H__


//////////////////////////////////////////////////////////////////////////////
// a generic tree.

class tree {
public:
	tree() { m_root=0; }
	virtual ~tree() { clear(); }
	void clear() { delete m_root; m_root=0; }

public:
	struct node_data {
		node_data() {}
		virtual ~node_data() {}
	};

	struct node {
		node() { owner=0; parent=child=next=prev=0; data=0; }
		virtual ~node() { delete data; delete_childs(); }

		node *goto_prev();			// always the prev, ignoring child and parent-relationships.
		node *goto_next();			// always the next, ignoring child and parent-relationships.

		node *insert_before_first_child();
		node *insert_after_last_child();
		node *insert_sibling_before();
		node *insert_sibling_after();

		long get_child_cnt( const bool deep=true );

		tree		*owner;

		node		*parent;
		node		*child;
		node		*next;
		node		*prev;

		node_data	*data;

	private:
		node *get_last_item();		// gets last item in the branch.
		node *get_root_item();

		void delete_childs();

		// unimplemented copy operations.
		node( const node& src ) {}
		node& operator=( const node& src ) {}
	};

	node *get_root() const { return m_root; }	// returns the root node.
	node *insert_root();

private:
	node	*m_root;

	// unimplemented copy operations.
	tree( const tree& src ) {}
	tree& operator=( const tree& src ) {}

	friend struct node;
};


//////////////////////////////////////////////////////////////////////////////

#endif