// ###########################################################################
// #
// # file:
// #	tree.cpp
// #
// ###########################################################################

#include "stdafx.h"
#pragma warning(disable:4786)
#include "tree.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////////
// a generic tree.

tree::node *tree::node::goto_prev()
{
	node *cur = prev;

	if ( cur==0 )
		cur = parent;
	else
		cur = get_last_item();

	return cur;
}

tree::node *tree::node::goto_next()
{
	node *itm = this;
	node *cur = itm->child;
	
	if ( cur==0 ) {

		while ( (cur=itm->next)==0 ) {
			if ( (itm=itm->parent)==0 )
				return 0;
		}
	}

	return cur;
}

tree::node *tree::node::insert_before_first_child()
{
	// no child yet.
	if ( !child ) {
		child = new node;
		child->owner  = owner;
		child->parent = this;
		child->next   = 0;
		child->prev   = 0;

		return child;

	// has already childs.
	} else {
		child->prev = new node;

		child->prev->owner  = owner;
		child->prev->parent = this;
		child->prev->prev   = 0;
		child->prev->next   = child->prev;

		child = child->prev;
		return child;
	}
}

tree::node *tree::node::insert_after_last_child()
{
	// no child yet.
	if ( !child ) {
		child = new node;
		child->owner  = owner;
		child->parent = this;
		child->next   = 0;
		child->prev   = 0;

		return child;

	// has already childs.
	} else {
		node *cur = child;

		while ( cur->next )
			cur = cur->next;

		cur->next = new node;
		cur->next->owner  = owner;
		cur->next->parent = this;
		cur->next->prev   = cur;
		cur->next->next   = 0;

		return cur->next;
	}
}

tree::node *tree::node::insert_sibling_before()
{
	node *nd = new node;
	nd->owner  = owner;
	nd->parent = parent;
	nd->prev   = prev;
	nd->next   = this;
	nd->child  = 0;

	if ( parent && !prev )
		parent->child = nd;
	if ( prev )
		prev->next = nd;

	if ( owner->m_root==this )
		owner->m_root = nd;

	prev = nd;

	return nd;
}

tree::node *tree::node::insert_sibling_after()
{
	node *nd = new node;
	nd->owner  = owner;
	nd->parent = parent;
	nd->prev   = this;
	nd->next   = next;
	nd->child  = 0;

	if ( next )
		next->prev = nd;

	next = nd;
	return nd;
}

void tree::node::delete_childs()
{
	if ( !child )
		return;

	// to pre-last child.
	node *cur = child;
	while ( cur->next && cur->next->next )
		cur = cur->next;

	// delete those childs.
	while ( cur ) {
		delete cur->next;
		cur->next = 0;

		cur = cur->prev;
	}

	// delete the direct child.
	delete child;
	child = 0;
}

tree::node *tree::node::get_last_item()
{
	// last child of the last child of the last child ...
	node *nxt = 0;
	node *itm = this;
	
	// commented out, since myself can never be 0.
	/*
	if ( itm==0 ) {
		// get the last item at the top level.
		nxt = get_root_item();
		while ( nxt ) {
			itm = nxt;
			nxt = nxt->next;
		}
	}
	*/
	
	while ( itm->child ) {
		nxt = itm->child;

		while ( nxt ){
			itm = nxt;
			nxt = nxt->next;
		}
	}
	
	return itm;
}

tree::node *tree::node::get_root_item()
{
	node *cur = this;

	while ( cur && cur->parent )
		cur = cur->parent;

	return cur;
}

long tree::node::get_child_cnt( const bool deep )
{
	long cnt = 0;
	node *cur = child;

	while ( child ) {
		cnt++;

		if ( deep )
			cnt += child->get_child_cnt();

		child = child->next;
	}

	return cnt;
}

tree::node *tree::insert_root()
{
	delete m_root;
	m_root = new node;

	m_root->owner = this;

	return m_root;
}


//////////////////////////////////////////////////////////////////////////////