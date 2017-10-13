#include <stdlib.h>
#include "lem_in.h"

int solve_BFS(t_lem_in *lem_in)
{
    t_room_list     queue;
    t_room          *room;
    t_room_elem     *neighbour;

    room_list_init(&queue);
    room_list_push(&queue, lem_in->start);
    lem_in->start->parent = lem_in->start;
    while (queue.n > 0)
    {
        room = room_list_popfront(&queue);
        neighbour = room->connected.first;
        while (neighbour != NULL)
        {
            if (neighbour->room->parent == NULL)
            {
                room_list_push(&queue, neighbour->room);
                neighbour->room->parent = room;
                if (neighbour->room == lem_in->end)
                    break ;
            }
            neighbour = neighbour->next;
        }
    }
    return (lem_in->end->parent == NULL);
}