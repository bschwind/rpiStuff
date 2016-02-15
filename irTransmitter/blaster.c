#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pigpio.h>

#define MAX_PULSES 12000;

// This holds the entire IR signal waveform
gpioPulse_t* irSignal[MAX_PULSES] = (gpioPulse_t*)malloc(sizeof(gpioPulse_t) * MAX_PULSES);
int pulseCount = 0;

void addPulse(uint32_t onPins, uint32_t offPins, uint32_t duration)
{
	irSignal[i].gpioOn = 1 << onPins;
	irSignal[i].gpioOff = offPins;
	irSignal[i].usDelay = duration;

	pulseCount++;
}

// Generates a square wave for duration (microseconds) at frequency (Hz)
// on GPIO pin outPin. dutyCycle is a value between 0 and 1.
void carrierFrequency(unsigned int outPin, double frequency, double dutyCycle, double duration)
{
	double oneCycleTime = 1000000.0 / frequency; // 1000000 microseconds in a second
	int onDuration = (int)round(oneCycleTime * dutyCycle);
	int offDuration = (int)round(oneCycleTime * (1.0 - dutyCycle));

	int totalCycles = (int)round(duration / oneCycleTime);
	int totalPulses = totalCycles * 2;

	int i;
	for (i = 0; i < totalPulses; i++)
	{
		if (i % 2 == 0)
		{
			// High pulse
			addPulse(1 << outPin, 0, onDuration);
		}
		else
		{
			// Low pulse
			addPulse(0, 1 << outPin, offDuration);
		}
	}
}

// Generates a low signal gap for duration, in microseconds, on GPIO pin outPin
void gap(unsigned int outPin, double duration)
{
	addPulse(0, 0, duration);
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

	// Setup the GPIO pin as an output pin
	gpioSetMode(outPin, PI_OUTPUT);

	// Start a new wave
	gpioWaveClear();

	// Begin ceiling light IR code
	carrierFrequency(outPin, 38000, 0.5, 9000);
	gap(outPin, 4500);

	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);

	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);

	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);

	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);

	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);

	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);

	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);

	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 562);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);
	carrierFrequency(outPin, 38000, 0.5, 562);
	gap(outPin, 1688);

	carrierFrequency(outPin, 38000, 0.5, 562);
	// End ceiling light IR code

	gpioWaveAddGeneric(pulseCount, irSignal);
	int waveID = gpioWaveCreate();

	if (waveID >= 0)
	{
		int result = gpioWaveTxSend(waveID, PI_WAVE_MODE_ONE_SHOT);

		printf("Result: %i\n", result);
	}
	else
	{
		printf("Wave failure!\n %i", waveID);
	}

	// Wait for the wave to finish transmitting
	while (gpioWaveTxBusy())
	{
		time_sleep(0.1);
	}

	// Delete the wave if it exists
	if (waveID >= 0)
	{
		gpioWaveDelete(waveID);
	}

	// Cleanup
	gpioTerminate();
}