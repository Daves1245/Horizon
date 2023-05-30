#include <stdio.h>
#include <algorithms/sorting.h>

#include <kernel/tty.h>
#include <kernel/descriptor_tables.h>

void print(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void kernel_main(void) {
    // IRS and segmentation (we implement paging later)
    init_descriptor_tables();
	terminal_initialize();

    int n = 10;
    int arr[n];
    for (int i = 0; i < 10; i++) {
        arr[i] = 10 - i;
    }
    printf("Unsorted array: ");
    print(arr, n);
    quick_sort(arr, n);
    printf("Sorted array: ");
    print(arr, n);

    asm volatile("int $0x3"); 
    asm volatile("int $0x4"); 

    return;
}
