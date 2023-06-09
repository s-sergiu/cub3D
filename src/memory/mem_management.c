#include "cub3D.h"

void	add_memory_block(t_memory **head, void *ptr, size_t size)
{
	t_memory *block;

	printf("address: %p\n", ptr);
	block = (t_memory *) malloc(sizeof(t_memory));
	block->address = ptr;
	block->size = size;
	block->next = *head;
	*head = block;
}

void	remove_memory_block(t_memory **head, void *ptr)
{
	t_memory *block;
	t_memory *prev;

	block = *head;
	prev = NULL;
	while (block != NULL)
	{
		if (block->address == ptr)
		{
			if (prev == NULL)
				*head = block->next;
			else
				prev->next = block->next;
			free(block);
			break;
		}
		prev = block;
		block = block->next;
	}
}

void	*malloc_to_block(t_memory **head, size_t size)
{
	void	*address;

	address = malloc(size);
	add_memory_block(head, address, size);
	return (address);
}

void	free_from_block(t_memory **head, void *address)
{
	remove_memory_block(head, address);
	free(address);
}

void	free_all_memory_blocks(t_memory **head)
{
	t_memory	*node;
	t_memory	*next;

	if (head == NULL)
		return ;
	next = NULL;
	node = *head;
	while (node != NULL)
	{
		next = node->next;
		free(node->address);
		free(node);
		node = next;
	}
	*head = NULL;
}
