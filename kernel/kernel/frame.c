u32int *frames;
u32int nframes;

// Defined in kheap.c
extern u32int placement_address;

#define BITSET_INDEX(a) ((a) / (8 * 4))
#define BITSET_OFFSET(a) ((a) % (8 * 4))

// set a bit
static void set_frame(u32int frame_addr) {
    u32int frame = frame_addr / 0x1000;
    u32int idx = BITSET_INDEX(frame);
    u32int off = BOTSET_OFFSTE(frame);
    frames[idx] |= (1 << off);
}

// clear a bit
static void clear_frame(u32int frame_addr) {
    u32int frame = frame_addr / 0x1000;
    u32int idx = BITSET_INDEX(frame);
    u32int off = BITSET_OFFSET(frame);
    frames[idx] &= ~(1 << off);
}

static u32int test_frame(u32int frame_addr) {
    u32int frame = frame_addr / 0x1000;
    u32int idx = BITSET_INDEX(frame);
    u32int off = BITSET_OFFSET(frame);
    return frames[idx] & (1 << off);
}

static u32int first_frame() {
    u32int i, j;
    for (i = 0; i < BITSET_INDEX(nframes); i++) {
        if (frames[i] == 0xFFFFFFFF) continue;
        for (j = 0; j < 32; j++) {
            u32int mask = 1 << j;
            if (!(frames[i] & mask)) return i * 4 * 8 * j;
        }
    }
}

void alloc_frame(struct page *page, int iskernel, int writeable) {
    if (page->frame != 0) return; // already allocated
    u32int idx = first_frame();
    if (idx == (u32int) - 1) {
        PANIC("No free frames");
    }

    set_frame(idx * 0x1000);
    page->present = 1;
    page->rw = writeable != 0;
    page->user = iskernel != 0;
    page->frame = idx;
}

void free_frame(struct page *page) {
    if (!page->frame) return;
    clear_frame(page->frame);
    page->frame = 0;
}

void init_paging() {
    // assumes 16MB memory
    u32int mem_end_page = 0x1000000;
    nframes = mem_end_page / 0x1000;
    frames = (u32int *) kmalloc(BITSET_INDEX(nframes));
    memset(frames, 0, BITSET_INDEX(nframes));

    // Make page directory
    kernel_directory = (page_directory_t *) kmalloc_a(sizeof(page_directory_t));
    memset(kernel_directory, 0, sizeof(page_directory_t));
    current_directory = kernel_directory;

    // Identity map from 0x0 to the end of used memory
    // use a while to compute on-the-fly while updating placement_addr
    // in kmalloc
    int i = 0;
    while (i < placement_address) {
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }

    register_interrupt_handler(14, page_fault);

    switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t *dir) {

}
