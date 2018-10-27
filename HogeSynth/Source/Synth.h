/*
  ==============================================================================

    Synth.h
    Created: 27 Oct 2018 12:07:40am
    Author:  tonari
	Reference source: http://aogiri-m2d.hatenablog.com/entry/2017/06/07/232240

  ==============================================================================
*/

#pragma once
#include "SineOscillator.h"
namespace synth
{
	class Synth
	{
	public:
		//midi入力をOscに伝える
		void midiProcessing(MidiMessage& midiMsg,double hostSampleRate);
		//Oscから波形データをhostのAudioBufferに書き下す
		void renderWaveData(float* hostAudioBuffer, int bufferSize);
	private:
		SineOscillator sineOsc;
	};

	//一連のmidi処理、audio処理を行う
	//ProcessBlockで呼び出す
	void doProcessing(Synth& synth, AudioSampleBuffer& sampleBuff, MidiBuffer& midiBuff, double hostSampleRate);

}	//namespace synth