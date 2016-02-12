#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pigpio.h>

// Generates a square wave for duration (microseconds) at frequency (Hz)
// on GPIO pin outPin. dutyCycle is a value between 0 and 1.
static int carrierFrequency(unsigned int outPin, double frequency, double dutyCycle, double duration)
{
	double oneCycleTime = 1000000 / frequency; // 1000000 microseconds in a second
	int onDuration = (int)round(oneCycleTime * dutyCycle);
	int offDuration = (int)round(oneCycleTime * (1.0 - dutyCycle));

	printf("on duration is %i\n", onDuration);
	printf("off duration is %i\n", offDuration);

	int totalCycles = (int)round(duration / oneCycleTime);
	int totalPulses = totalCycles * 2;

	// Allocate twice the number of cycles, as we have two pulses for each cycle,
	// a high pulse and low pulse
	gpioPulse_t* wave = (gpioPulse_t*)malloc(sizeof(gpioPulse_t) * totalPulses);

	int i;
	for (i = 0; i < totalPulses; i++)
	{
		if (i % 2 == 0)
		{
			// High pulse
			wave[i].gpioOn = 1 << outPin;
			wave[i].gpioOff = 0;
			wave[i].usDelay = onDuration;
		}
		else
		{
			// Low pulse
			wave[i].gpioOn = 0;
			wave[i].gpioOff = 1 << outPin;
			wave[i].usDelay = offDuration;
		}
	}

	gpioWaveAddGeneric(totalPulses, wave);
	int waveID = gpioWaveCreate();

	free(wave);

	return waveID;
}

// Generates a low signal gap for duration, in microseconds, on GPIO pin outPin
static int gap(unsigned int outPin, double duration)
{
	gpioPulse_t offPulse = {
		.gpioOn = 0,
		.gpioOff = 0,
		.usDelay = duration
	};

	gpioPulse_t wave[1] = {offPulse};

	gpioWaveAddGeneric(1, wave);
	int waveID = gpioWaveCreate();

	return waveID;
}

int main(int argc, char *argv[])
{
	unsigned int outPin = 23;
	if (gpioInitialise() < 0)
	{
		// Initialization failed
		printf("Initialization failed");
		exit(-1);
	}

	gpioSetMode(outPin, PI_OUTPUT);

	// gpioWrite(outPin, 1);
	// sleep(1);
	// gpioWrite(outPin, 0);
	// sleep(1);

	// gpioPulse_t onPulse = {
	// 	.gpioOn = 1<<outPin,
	// 	.gpioOff = 0,
	// 	.usDelay = 100000
	// };

	// gpioPulse_t offPulse = {
	// 	.gpioOn = 0,
	// 	.gpioOff = 1<<outPin,
	// 	.usDelay = 100000
	// };

	// gpioPulse_t pulses[2] = {onPulse, offPulse};

	gpioWaveClear();
	// gpioWaveAddGeneric(2, pulses);

	// int wave1 = carrierFrequency(outPin, 38000, 0.5, 9000);
	// int wave2 = gap(outPin, 500000);
	// int wave3 = carrierFrequency(outPin, 38000, 0.5, 9000);

	// int waveID = gpioWaveCreate();

	// int waves[3] = {wave1, wave2, wave3};

	gpioWaveChain((char[]) {
		carrierFrequency(outPin, 38000, 0.5, 9000),
		gap(outPin, 4500),

		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),

		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),

		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),

		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),

		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),

		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),

		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),

		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 562),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),
		carrierFrequency(outPin, 38000, 0.5, 562),
		gap(outPin, 1688),

		carrierFrequency(outPin, 38000, 0.5, 562)

	}, 67);

	// if (waveID >= 0)
	// {
	// 	int result = gpioWaveTxSend(waveID, PI_WAVE_MODE_ONE_SHOT);

	// 	printf("Result: %i\n", result);
	// }
	// else
	// {
	// 	printf("Wave failure!\n %i", waveID);
	// }

	while (gpioWaveTxBusy())
	{
		time_sleep(0.1);
	}

	// int i;
	// for (i = 0; i < 3; i++)
	// {
	// 	gpioWaveDelete(waves[i]);
	// }

	gpioTerminate();
}