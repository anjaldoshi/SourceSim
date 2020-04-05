#include "SourceSim.h"

SourceSim::SourceSim(String name, int channels, float sampleRate) : Thread(name)
{
	risingEdgeProcessed = false;
	fallingEdgeProcessed = false;

	this->name = name;
	numChannels = channels;
	packetSize = 10;
	this->sampleRate = sampleRate;

	clkEnabled = false;
	clk_period = 1; //s
	clk_tol = 0.001; //sc
	
}

SourceSim::~SourceSim()
{
}

void SourceSim::timerCallback()
{
	if (clkEnabled)
	{
		eventCode = (!(bool)eventCode);
		if (eventCode)
		{
			risingEdgeReceived = true;
			risingEdgeProcessed = false;
		}
		else
		{
			fallingEdgeReceived = true;
			fallingEdgeProcessed = false;
		}
	}

}

void SourceSim::updateClk(bool enable)
{
	clkEnabled = enable;
}

void SourceSim::updateClkFreq(int freq, float tol)
{
	stopTimer();

	clk_period = 1 / (float)freq;

	startTimer(1000 * clk_period / 2);

}

void SourceSim::run()
{

	numSamples = 0;

	startTimer(1000 * clk_period  / 2);

	t1 = high_resolution_clock::now();

	while (!threadShouldExit())
	{
		t2 = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

		if (time_span.count() > 1 / (sampleRate / packetSize))
		{

			if (risingEdgeReceived)
			{
				lastRisingEdgeSampleNum = numSamples;
				risingEdgeReceived = false;
			}
			else if (fallingEdgeReceived)
			{
				lastFallingEdgeSampleNum = numSamples;
				fallingEdgeReceived = false;
			}

			generateDataPacket();

			t1 = high_resolution_clock::now();
		}

	}

	stopTimer();
}