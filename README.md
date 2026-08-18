# Signals Processing in C

Coursework for an embedded C / digital signal processing course, targeting the
**Analog Devices ADuC841** microcontroller (8051-family, on-chip ADC/DAC).

## Projects

### [`2025test/`](2025test)
UART-based voltmeter: reads channel 0 of the ADC, converts the reading to
millivolts, and transmits the formatted result back over the UART.

### [`MovingAverage/`](MovingAverage) — [details & block diagram](MovingAverage/README.md)
Moving-average filter lab. Samples channel 0 of the ADC (clocked by Timer 2),
outputs the raw signal on DAC0 and the filtered (smoothed) signal on DAC1,
using an efficient running-sum update (`sum += x_new - x_old`) over a
circular buffer instead of recomputing the full sum every sample.

- `setTimer2.py` — Python script intended to generate `SetTimer2_ADC_DAC.c/.h`
  for a given target ADC sample rate. **Note:** the reload-value formula in
  this script currently has a bug (see the comment inline) — the checked-in
  `SetTimer2_ADC_DAC.c/.h` files were taken from the verified, working Keil
  project instead of being regenerated from the script.

### [`FIR/`](FIR) — [details & block diagram](FIR/README.md)
FIR low-pass filter lab (Chapter 22). Samples channel 0 of the ADC (clocked
by Timer 2), outputs the raw signal on DAC0, and outputs the filtered signal
on DAC1 (clamped to zero if negative). The filter is a windowed-sinc
low-pass design, convolved over a shifting `idata` sample buffer against
`code`-segment, scaled-`char` coefficients.

- `fir_design.py` — designs the filter (given a corner frequency and sample
  rate) and generates `coeffs.h` with the coefficients, tap count, and
  scaling factor. `coeffs.h` currently holds placeholder values
  (f=100Hz, Fs=1kHz) — regenerate it for the lab's actual target parameters.

## Toolchain

Code is written for the **Keil µVision** IDE / C51 compiler and targets the
ADuC841. Peripheral access uses `sfr`/`sfr16`/`sbit` declarations and
`interrupt N` ISR syntax specific to the 8051 architecture.
