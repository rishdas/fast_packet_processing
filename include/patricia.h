/*
 * patricia.h
 *
 * Patricia trie implementation.
 *
 * Functions for inserting nodes, removing nodes, and searching in
 * a Patricia trie designed for IP addresses and netmasks.  A
 * head node must be created with (key,mask) = (0,0).
 *
 * NOTE: The fact that we keep multiple masks per node makes this
 *       more complicated/computationally expensive then a standard
 *       trie.  This is because we need to do longest prefix matching,
 *       which is useful for computer networks, but not as useful
 *       elsewhere.
 *
 * Matthew Smart <mcsmart@eecs.umich.edu>
 *
 * Copyright (c) 2000
 * The Regents of the University of Michigan
 * All rights reserved
 *
 * $Id$
 */

#ifndef _PATRICIA_H_
#define _PATRICIA_H_


/*
 * Patricia tree mask.
 * Each node in the tree can contain multiple masks, so this
 * structure is where the mask and data are kept.
 */
struct ptree_mask {
	unsigned int pm_mask;
	void *pm_data;
};


/*
 * Patricia tree node.
 */
struct ptree {
	unsigned int p_key;		/* Node key		*/
	struct ptree_mask *p_m;		/* Node masks		*/
	unsigned char p_mlen;		/* Number of masks	*/
	char p_b;			/* Bit to check		*/
	struct ptree *p_left;		/* Left pointer		*/
	struct ptree *p_right;		/* Right pointer	*/
};


extern struct ptree *pat_insert(struct ptree *n, struct ptree *head);
extern int           pat_remove(struct ptree *n, struct ptree *head);
extern struct ptree *pat_search(unsigned int key, struct ptree *head);

#endif /* _PATRICIA_H_ */
