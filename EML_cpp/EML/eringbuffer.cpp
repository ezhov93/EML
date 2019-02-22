/*
 * @file   eringbuffer.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Simple circular buffer file.
 */
 
#include "eringbuffer.h"

static inline void rb_init(ring_buffer *rb, uint16 size, uint8 *buf) {
    rb->head = 0;
    rb->tail = 0;
    rb->size = size - 1;
    rb->buf = buf;
}

static inline uint16 rb_full_count(ring_buffer *rb) {
    __IO ring_buffer *arb = rb;
    int32 size = arb->tail - arb->head;
    if (arb->tail < arb->head) {
        size += arb->size + 1;
    }
    return (uint16)size;
}

static inline int rb_is_full(ring_buffer *rb) {
    return (rb->tail + 1 == rb->head) ||
        (rb->tail == rb->size && rb->head == 0);
}

static inline int rb_is_empty(ring_buffer *rb) {
    return rb->head == rb->tail;
}

static inline void rb_insert(ring_buffer *rb, uint8 element) {
    rb->buf[rb->tail] = element;
    rb->tail = (rb->tail == rb->size) ? 0 : rb->tail + 1;
}

static inline uint8 rb_remove(ring_buffer *rb) {
    uint8 ch = rb->buf[rb->head];
    rb->head = (rb->head == rb->size) ? 0 : rb->head + 1;
    return ch;
}

static inline int rb_peek(ring_buffer *rb) 
{  
	if (rb->head == rb->tail)
	{
		return -1;
	}
	else
	{
		return rb->buf[rb->head];
	}
}

static inline int16 rb_safe_remove(ring_buffer *rb) {
    return rb_is_empty(rb) ? -1 : rb_remove(rb);
}

static inline int rb_safe_insert(ring_buffer *rb, uint8 element) {
    if (rb_is_full(rb)) {
        return 0;
    }
    rb_insert(rb, element);
    return 1;
}

static inline int rb_push_insert(ring_buffer *rb, uint8 element) {
    int ret = -1;
    if (rb_is_full(rb)) {
        ret = rb_remove(rb);
    }
    rb_insert(rb, element);
    return ret;
}

/**
 * @brief Discard all items from a ring buffer.
 * @param rb Ring buffer to discard all items from.
 */
static inline void rb_reset(ring_buffer *rb) {
    rb->tail = rb->head;
}



