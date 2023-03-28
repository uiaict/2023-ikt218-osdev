#define GDT_ENTRIES 5


void init_gdt() asm ("init_gdt");

extern "C" {
  extern void gdt_flush(uint32_t);
  static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);
}

// gdt.h
struct gdt_entry {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

void init_gdt();
void gdt_load(struct gdt_ptr *gdt_ptr);
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_check(struct gdt_ptr *gdt_ptr);
void printmyword(char word[50]);

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gdt_ptr;

void init_gdt() {

  // Set the GDT limit
  gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
  gdt_ptr.base = (uint32_t) &gdt;
	
	// num, base, limit, access, granularity 
	gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

  // Load the GDT
  gdt_load(&gdt_ptr);
	
	// Flush GDT pointer
	gdt_flush((uint32_t)&gdt_ptr);

  gdt_check(&gdt_ptr);
}

void gdt_load(struct gdt_ptr *gdt_ptr) {
  asm volatile("lgdt %0" : : "m" (*gdt_ptr));
}

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}

void gdt_check(struct gdt_ptr *gdt_ptr) {
  asm volatile("sgdt (%0)" : : "r"(&gdt_ptr));
  int lim = gdt_ptr->limit;
  int base = gdt_ptr->limit;
  //printf("GDT base: 0x%x, limit: 0x%x\n", gdtr.base, gdtr.limit);
}


void printmyword(char word[50])
{
  uint8_t (*fb)[80][2] = (uint8_t (*)[80][2]) 0xb8000;

  int wordlen = 0;
  while(word[wordlen] != '\0' ){
      wordlen++;
  }

  for(int i = 0; i < wordlen; i++)
  {
    fb[0][i][0]= word[i];   
  }
}