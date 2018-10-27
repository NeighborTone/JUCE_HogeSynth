/*
  ==============================================================================

	Synte.cpp
	Created: 27 Oct 2018 12:08:00am
	Author:  tonari
	Reference source: http://aogiri-m2d.hatenablog.com/entry/2017/06/07/232240

  ==============================================================================
*/

#include "../Source/Synth.h"
namespace synth
{
	void Synth::midiProcessing(MidiMessage& midiMsg, double hostSampleRate)
	{
		//受け取ったMidiがOn信号だった場合
		//midi信号からノート番号を取り出しOscを走らせる
		if (midiMsg.isNoteOn())
		{
			sineOsc.midiOn(midiMsg.getNoteNumber(), hostSampleRate);
		}
		else
		{
			sineOsc.midiOff();
		}
	}

	void Synth::renderWaveData(float* hostAudioBuffer, int bufferSize)
	{
		//bufferSizeサンプル時間分Sine波を生成
		//1サンプル時間レンダリングするたびに、Oscの経過サンプル時間を進める
		for (int n = 0; n < bufferSize; ++n)
		{
			hostAudioBuffer[n] = sineOsc.get();
			sineOsc.phaseIncrement();
		}
	}

	void doProcessing(Synth& sy, AudioSampleBuffer& sampleBuff, MidiBuffer& midiBuff, double hostSampleRate)
	{
		//midiの処理
		MidiBuffer::Iterator it(midiBuff);
		MidiMessage msg(0);	//デフォルトでNoteOff
		int midiPosition;	//この変数の値は実際には使用しない

		//受け取ったmidiBufferを走査し、midi入力が存在するかを探索
		//midi入力あれば、getNextEventの第一引数にmidiデータ、第二引数にmidiデータの位置が書き込まれtrueを返す
		//今回、第二引数は使用しない
		while (it.getNextEvent(msg, midiPosition))
		{
			sy.midiProcessing(msg, hostSampleRate);
		}

		//audioの処理
		float* leftChannelAudio = sampleBuff.getWritePointer(0);
		float* rigthChannelAudio = sampleBuff.getWritePointer(1);
		int buffSize = sampleBuff.getNumSamples();

		//hostAudioBufferにSine波をレンダリング
		sy.renderWaveData(leftChannelAudio, buffSize);

		//モノラル
		for (int n = 0; n < buffSize; ++n)
		{
			rigthChannelAudio[n] = leftChannelAudio[n];
		}

	}

}	//namespace synth