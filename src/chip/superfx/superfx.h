class SuperFX : public MMIO { public:
  #include "core/core.h"

  void init();
  void enable();
  void power();
  void reset();

  uint8 mmio_read (uint addr);
  void  mmio_write(uint addr, uint8 data);

private:
  #include "regs.h"
  uint8 cache[512]; //cache RAM
};

extern SuperFX superfx;