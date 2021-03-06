//PPUcounter emulates the H/V latch counters of the S-PPU2.
//
//real hardware has the S-CPU maintain its own copy of these counters that are
//updated based on the state of the S-PPU Vblank and Hblank pins. emulating this
//would require full lock-step synchronization for every clock tick.
//to bypass this and allow the two to run out-of-order, both the CPU and PPU
//classes inherit PPUcounter and keep their own counters.
//the timers are kept in sync, as the only differences occur on V=240 and V=261,
//based on interlace. thus, we need only synchronize and fetch interlace at any
//point before this in the frame, which is handled internally by this class at
//V=128.

struct PPUcounter {
  auto tick() -> void;
  auto tick(uint clocks) -> void; private:
  auto tickScanline() -> void; public:

  auto interlace() const -> bool;
  auto field() const -> bool;
  auto vcounter() const -> uint;
  auto hcounter() const -> uint;
  auto hdot() const -> uint; private:
  auto vperiod() const -> uint; public:
  auto hperiod() const -> uint;

  auto vcounter(uint offset) const -> uint;
  auto hcounter(uint offset) const -> uint;

  auto reset() -> void;
  auto serialize(serializer&) -> void;

  function<void ()> scanline;

private:
  struct {
    bool interlace = 0;
    bool field = 0;
    uint vperiod = 0;
    uint hperiod = 0;
    uint vcounter = 0;
    uint hcounter = 0;
  } time;

  struct {
    uint vperiod = 0;
    uint hperiod = 0;
  } last;
};
