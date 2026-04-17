#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "spinlock.h"
#include "sleeplock.h" // Added: Defines the lock used by buf.h
#include "fs.h"        // Added: Defines BSIZE (usually 512)
#include "buf.h"

// Reserve a massive chunk of raw disk blocks specifically for swapping memory
#define SWAP_BLOCK_START 2000 
#define BLOCKS_PER_PAGE (PGSIZE / BSIZE) // 4096 bytes / 512 bytes = 8 disk blocks

struct spinlock swaplock;

// Setup the lock when the OS boots
void swapinit(void) {
  initlock(&swaplock, "swap");
}

// Kick a RAM page out to the hard drive
uint swapWrite(char *physical_page) {
  static uint next_free_block = SWAP_BLOCK_START;
  uint target_block;

  // Lock the system so two programs don't overwrite each other's swap
  acquire(&swaplock);
  target_block = next_free_block;
  next_free_block += BLOCKS_PER_PAGE; 
  release(&swaplock);

  // Chop the 4096-byte page into 8 blocks and write them to the hard drive
  for(int i = 0; i < BLOCKS_PER_PAGE; i++){
    struct buf *b = bread(1, target_block + i); // Read the raw disk block
    memmove(b->data, physical_page + (i * BSIZE), BSIZE); // Copy 512 bytes of RAM into it
    bwrite(b); // Save it permanently to the disk
    brelse(b); // Release the block
  }
  
  // Return the disk address so the OS knows where it hid the memory!
  return target_block; 
}





// Bring a RAM page back from the hard drive
void swapRead(char *physical_page, uint target_block) {
  for(int i = 0; i < BLOCKS_PER_PAGE; i++){
    struct buf *b = bread(1, target_block + i); // Read the raw disk block
    memmove(physical_page + (i * BSIZE), b->data, BSIZE); // Copy it into RAM
    brelse(b); // Release the block
  }
}
