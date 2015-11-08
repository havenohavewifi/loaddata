
#include"b_plus_tree.h"
#include<stdio.h>


void getRoot(FILE *index, Node &node)
{
	int offset;
	rewind(index);
	if(fread(&offset, 1, sizeof(offset), index) == 0)
	{
		offset = sizeof(offset);
		fwrite(&offset, 1, sizeof(offset), index);
		fflush(index);
	}
	fseek(index, offset, SEEK_SET);
	if(fread(&node, 1, sizeof(node), index) == 0)
	{
		fseek(index, sizeof(node), SEEK_CUR);
		node.count = 0;
		node.parent = 0;
		node.type = LEAF;
	}
}

int search(FILE *index, int key)
{
	Node node;
	int pos;
	getRoot(index, node);
	searchNode(index, node, key);
	pos = searchRecord(node, key);
	if(pos == node.count || node.pair[pos].key != key)
		return -1;
	else
		return node.pair[pos].pos;
}

int searchRecord(Node &node, int key)
{
	int i;
	for(i = 0; i < node.count && key > node.pair[i].key; i ++);
	return i;
}

void searchNode(FILE *index, Node &node, int key)
{
	int pos, offset;
	if(node.type == LEAF)
		return;
	else
	{
		pos = searchRecord(node, key);
		pos = pos == node.count ? pos - 1 : pos;
		offset = node.pair[pos].pos;
		fseek(index, offset, SEEK_SET);
		fread(&node, 1, sizeof(node), index);
		searchNode(index, node, key);
	}
}

int insertRecord(FILE *index, Node &node, Element elem)
{
	int pos, cur;
	pos = searchRecord(node, elem.key);
	if(pos == node.count || node.pair[pos].key != elem.key)
	{
		if(node.count < MAX)
		{
			for(cur = node.count; cur > pos; cur --)
			{
				node.pair[cur] = node.pair[cur - 1];
			}
			node.pair[pos] = elem;
			node.count ++;
			fseek(index, -(int)sizeof(node), SEEK_CUR);
			fwrite(&node, 1, sizeof(node), index);
			fflush(index);
			if(pos == node.count - 1 && node.parent != 0)
			{
				enlargeKey(index, node);
			}
		}
		else
			splitNode(index, node, elem, pos);
		return 0;
	}
	else
		return -1;
}

void splitNode(FILE *index, Node &nodea, Element elem, int pos)
{
	Node nodeb, top;
	Element elema, elemb;
	int cur;
	nodeb.type = nodea.type;
	nodeb.parent = nodea.parent;
	nodeb.count = (MAX + 1) / 2;
	nodea.count = nodea.count - nodeb.count + 1;
	for(cur = MAX; cur > pos && cur >= nodea.count; cur --)
		nodeb.pair[cur - nodea.count] = nodea.pair[cur - 1];
	if(cur < nodea.count)
	{
		for(; cur > pos; cur --)
			nodea.pair[cur] = nodea.pair[cur - 1];
		nodea.pair[pos] = elem;
	}
	else
	{
		nodeb.pair[pos - nodea.count] = elem;
		for(cur --; cur >= nodea.count; cur --)
			nodeb.pair[cur - nodea.count] = nodea.pair[cur];
	}
	fseek(index, -(int)sizeof(nodea), SEEK_CUR);
	elema.key = nodea.pair[nodea.count - 1].key;
	elema.pos = ftell(index);
	fseek(index, 0, SEEK_END);
	elemb.key = nodeb.pair[nodeb.count - 1].key;
	elemb.pos = ftell(index);
	fwrite(&nodeb, 1, sizeof(nodeb), index);
	fflush(index);
	if(nodea.parent == 0)
	{
		top.count = 0;
		top.type = NODE;
		top.parent = 0;
		fseek(index, 0, SEEK_END);
		cur = ftell(index);
		nodea.parent = cur;
		nodeb.parent = cur;
		fseek(index, elema.pos, SEEK_SET);
		fwrite(&nodea, 1, sizeof(nodea), index);
		fflush(index);
		fseek(index, elemb.pos, SEEK_SET);
		fwrite(&nodeb, 1, sizeof(nodeb), index);
		fflush(index);
		fseek(index, sizeof(top), SEEK_CUR);
		insertRecord(index, top, elema);
		insertRecord(index, top, elemb);
		rewind(index);
		fwrite(&cur, 1, sizeof(cur), index);
		fflush(index);
	}
	else
	{
		fseek(index, elema.pos, SEEK_SET);
		fwrite(&nodea, 1, sizeof(nodea), index);
		fflush(index);
		fseek(index, elemb.pos, SEEK_SET);
		fwrite(&nodeb, 1, sizeof(nodeb), index);
		fflush(index);
		fseek(index, nodea.parent, SEEK_SET);
		fread(&top, 1, sizeof(top), index);
		cur = searchRecord(top, elemb.key);
		if(cur == top.count)
			cur --;
		top.pair[cur] = elema;
		insertRecord(index, top, elemb);
	}
	
	if(nodeb.type == NODE)
	{
		Node node;
		for(cur = 0; cur < nodeb.count; cur ++)
			changeParent(index, node, nodeb.pair[cur].pos, elemb.pos);
	}
}

int insert(FILE *index, Element elem)
{
	Node node;
	getRoot(index, node);
	searchNode(index, node, elem.key);
	return insertRecord(index, node, elem);
}

void enlargeKey(FILE *index, Node &node)
{
	int key;
	key = node.pair[node.count - 1].key;
	fseek(index, node.parent, SEEK_SET);
	fread(&node, 1, sizeof(node), index);
	if(node.pair[node.count - 1].key < key)
	{
		node.pair[node.count - 1].key = key;
		fseek(index, -(int)sizeof(node), SEEK_CUR);
		fwrite(&node, 1, sizeof(node), index);
		fflush(index);
		if(node.parent != 0)
		{
			enlargeKey(index, node);
		}
	}
}

int del(FILE *index, int key)
{
	Node node;
	getRoot(index, node);
	searchNode(index, node, key);
	return delRecord(index, node, key);
}

int delRecord(FILE *index, Node &node, int key)
{
	Node left, right, top;
	Element recol, recor, recot, recon;
	int pos, tpos;
	pos = searchRecord(node, key);
	if(pos == node.count)
		return -1;
	else if(node.parent == 0 || node.count > MIN)
	{
		for(node.count --; pos < node.count; pos ++)
			node.pair[pos] = node.pair[pos + 1];
		if(node.parent == 0 && node.count == 1 && node.type == NODE)
		{
			node.count = 0;
			fseek(index, -(int)sizeof(node), SEEK_CUR);
			fwrite(&node, 1, sizeof(node), index);
			fflush(index);
			rewind(index);
			fwrite(&node.pair[0].pos, 1, sizeof(node.pair[0].pos), index);
			fflush(index);
			changeParent(index, node, node.pair[0].pos, 0);
		}
		else
		{
			fseek(index, -(int)sizeof(node), SEEK_CUR);
			fwrite(&node, 1, sizeof(node), index);
			fflush(index);
			if(node.parent != 0 && pos == node.count)
				ensmallKey(index, node);
		}
		return 0;
	}
	else
	{
		recon.key = node.pair[node.count - 1].key;
		recon.pos = ftell(index) - sizeof(node);
		recot.pos = node.parent;
		fseek(index, recot.pos, SEEK_SET);
		fread(&top, 1, sizeof(top), index);
		recot.key = top.pair[top.count - 1].key;
		tpos = searchRecord(top, key);
		if(tpos == top.count - 1)
		{
			recol = top.pair[tpos - 1];
			fseek(index, recol.pos, SEEK_SET);
			fread(&left, 1, sizeof(left), index);
			if(left.count > MIN)
			{
				transRecord(index, left, node, RIGHT, pos);
				if(node.type == NODE)
					changeParent(index, right, node.pair[0].pos, recon.pos);
				recon.key = node.pair[node.count - 1].key;
				recol.key = left.pair[left.count - 1].key;
				top.pair[tpos - 1] = recol;
				top.pair[tpos] = recon;
				fseek(index, recol.pos, SEEK_SET);
				fwrite(&left, 1, sizeof(left), index);
				fflush(index);
				fseek(index, recon.pos, SEEK_SET);
				fwrite(&node, 1, sizeof(node), index);
				fflush(index);
				fseek(index, recot.pos, SEEK_SET);
				fwrite(&top, 1, sizeof(top), index);
				fflush(index);
			}
			else
			{
				for(node.count --; pos < node.count; pos ++)
					node.pair[pos] = node.pair[pos + 1];
				if(node.type == NODE)
				{
					for(pos = 0; pos < node.count; pos ++)
						changeParent(index, right, node.pair[pos].pos, recol.pos);
				}
				mergeNode(index, left, node);
				fseek(index, recol.pos, SEEK_SET);
				fwrite(&left, 1, sizeof(left), index);
				fflush(index);
				fseek(index, recon.pos, SEEK_SET);
				fwrite(&node, 1, sizeof(node), index);
				fflush(index);
				recon.key = left.pair[left.count - 1].key;
				recon.pos = recol.pos;
				top.pair[tpos] = recon;
				fseek(index, recot.pos, SEEK_SET);
				fwrite(&top, 1, sizeof(top), index);
				fflush(index);
				delRecord(index, top, recol.key);
			}
			if(top.parent != 0 && top.count != 0)
				ensmallKey(index, top);
		}
		else
		{
			recor = top.pair[tpos + 1];
			fseek(index, recor.pos, SEEK_SET);
			fread(&right, 1, sizeof(right), index);
			if(right.count > MIN)
			{
				transRecord(index, node, right, LEFT, pos);
				if(node.type == NODE)
					changeParent(index, left, node.pair[node.count - 1].pos, recon.pos);
				recon.key = node.pair[node.count - 1].key;
				top.pair[tpos] = recon;
				fseek(index, recor.pos, SEEK_SET);
				fwrite(&right, 1, sizeof(right), index);
				fflush(index);
				fseek(index, recon.pos, SEEK_SET);
				fwrite(&node, 1, sizeof(node), index);
				fflush(index);
				fseek(index, recot.pos, SEEK_SET);
				fwrite(&top, 1, sizeof(top), index);
				fflush(index);
			}
			else if(tpos != 0)
			{
				recol = top.pair[tpos - 1];
				fseek(index, recol.pos, SEEK_SET);
				fread(&left, 1, sizeof(left), index);
				if(left.count > MIN)
				{
					transRecord(index, left, node, RIGHT, pos);
					if(node.type == NODE)
						changeParent(index, right, node.pair[0].pos, recon.pos);
					recon.key = node.pair[node.count - 1].key;
					recol.key = left.pair[left.count - 1].key;
					top.pair[tpos - 1] = recol;
					top.pair[tpos] = recon;
					fseek(index, recol.pos, SEEK_SET);
					fwrite(&left, 1, sizeof(left), index);
					fflush(index);
					fseek(index, recon.pos, SEEK_SET);
					fwrite(&node, 1, sizeof(node), index);
					fflush(index);
					fseek(index, recot.pos, SEEK_SET);
					fwrite(&top, 1, sizeof(top), index);
					fflush(index);
				}
				else
				{
					for(node.count --; pos < node.count; pos ++)
						node.pair[pos] = node.pair[pos + 1];
					if(right.type == NODE)
					{
						for(pos = 0; pos < right.count; pos ++)
							changeParent(index, left, right.pair[pos].pos, recon.pos);
					}
					mergeNode(index, node, right);
					fseek(index, recor.pos, SEEK_SET);
					fwrite(&right, 1, sizeof(right), index);
					fflush(index);
					fseek(index, recon.pos, SEEK_SET);
					fwrite(&node, 1, sizeof(node), index);
					fflush(index);
					recor.pos = recon.pos;
					top.pair[tpos + 1] = recor;
					fseek(index, recot.pos, SEEK_SET);
					fwrite(&top, 1, sizeof(top), index);
					fflush(index);
					delRecord(index, top, recon.key);
				}
			}
			else
			{
				for(node.count --; pos < node.count; pos ++)
						node.pair[pos] = node.pair[pos + 1];
					if(right.type == NODE)
					{
						for(pos = 0; pos < right.count; pos ++)
							changeParent(index, left, right.pair[pos].pos, recon.pos);
					}
					mergeNode(index, node, right);
					fseek(index, recor.pos, SEEK_SET);
					fwrite(&right, 1, sizeof(right), index);
					fflush(index);
					fseek(index, recon.pos, SEEK_SET);
					fwrite(&node, 1, sizeof(node), index);
					fflush(index);
					recor.pos = recon.pos;
					top.pair[tpos + 1] = recor;
					fseek(index, recot.pos, SEEK_SET);
					fwrite(&top, 1, sizeof(top), index);
					fflush(index);
					delRecord(index, top, recon.key);
			}
		}
		return 0;
	}
}

void transRecord(FILE *index, Node &left, Node &right, int dir, int pos)
{
	if(dir == RIGHT)
	{
		for(left.count --; pos > 0; pos --)
			right.pair[pos] = right.pair[pos - 1];
		right.pair[0] = left.pair[left.count];
	}
	else
	{
		for(; pos < left.count - 1; pos ++)
			left.pair[pos] = left.pair[pos + 1];
		left.pair[pos] = right.pair[0];
		right.count --;
		for(pos = 0; pos < right.count; pos ++)
			right.pair[pos] = right.pair[pos + 1];
	}
}

void mergeNode(FILE *index, Node &left, Node &right)
{
	int pos;
	for(pos = 0; pos < right.count; pos ++)
		left.pair[pos + left.count] = right.pair[pos];
	left.count += right.count;
	right.count = 0;
}

void changeParent(FILE *index, Node &node, int child, int parent)
{
	fseek(index, child, SEEK_SET);
	fread(&node, 1, sizeof(node), index);
	node.parent = parent;
	fseek(index, -(int)sizeof(node), SEEK_CUR);
	fwrite(&node, 1, sizeof(node), index);
	fflush(index);
}

void ensmallKey(FILE *index, Node &node)
{
	int key, pos;
	key = node.pair[node.count - 1].key;
	fseek(index, node.parent, SEEK_SET);
	fread(&node, 1, sizeof(node), index);
	pos = searchRecord(node, key);
	if(node.pair[pos].key != key)
	{
		node.pair[pos].key = key;
		fseek(index, -(int)sizeof(node), SEEK_CUR);
		fwrite(&node, 1, sizeof(node), index);
		fflush(index);
		if(pos == node.count - 1 && node.parent != 0)
			ensmallKey(index, node);
	}
}

