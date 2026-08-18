# Signals Processing in C

Coursework for an embedded C / digital signal processing course, targeting the
**Analog Devices ADuC841** microcontroller (8051-family, on-chip ADC/DAC).

## Projects

### [`2025test/`](2025test)
UART-based voltmeter: reads channel 0 of the ADC, converts the reading to
millivolts, and transmits the formatted result back over the UART.

### [`MovingAverage/`](MovingAverage)
Moving-average filter lab. Samples channel 0 of the ADC (clocked by Timer 2),
outputs the raw signal on DAC0 and the filtered (smoothed) signal on DAC1,
using an efficient running-sum update (`sum += x_new - x_old`) over a
circular buffer instead of recomputing the full sum every sample.

- `setTimer2.py` — Python script intended to generate `SetTimer2_ADC_DAC.c/.h`
  for a given target ADC sample rate. **Note:** the reload-value formula in
  this script currently has a bug (see the comment inline) — the checked-in
  `SetTimer2_ADC_DAC.c/.h` files were taken from the verified, working Keil
  project instead of being regenerated from the script.

### [`TrafficLightController/`](TrafficLightController)
A separate, unrelated VHDL project (FPGA traffic-light controller) — not part
of the ADuC841/C coursework.

## Toolchain

Code is written for the **Keil µVision** IDE / C51 compiler and targets the
ADuC841. Peripheral access uses `sfr`/`sfr16`/`sbit` declarations and
`interrupt N` ISR syntax specific to the 8051 architecture.
