/*
  ==============================================================================

    SineOscillator.cpp
    Created: 27 Oct 2018 12:09:20am
    Author:  tonari
	Reference source: http://aogiri-m2d.hatenablog.com/entry/2017/06/07/232240

  ==============================================================================
*/

#include "../Source/SineOscillator.h"

void SineOscillator::midiOn(int midiNoteNumber, double hostSampleRate)
{
	//各種パラメータを計算・設定
	midiInput_ = true;
	elapsedSamplingTime_ = 0;
	frequency_ = MidiMessage::getMidiNoteInHertz(midiNoteNumber);	//midiNote番号はただの整数値なので周波数Hzに変換
	samplingPeriod_ = hostSampleRate / frequency_;
}

void SineOscillator::midiOff()
{
	//midiがoffになったら波形生成をやめるので、Sine波の計算に必要な他パラメータは計算・設定する必要無し
	midiInput_ = false;

}

double SineOscillator::get()
{
	if (!midiInput_) { return 0.0; }
	return sin(2.0 * double_Pi * elapsedSamplingTime_ / samplingPeriod_);
}

void SineOscillator::phaseIncrement()
{
	//1サンプル進めて必要に応じて周期化
	if (++elapsedSamplingTime_ >= samplingPeriod_)
	{
		elapsedSamplingTime_ = 
		elapsedSamplingTime_ - static_cast<int>(elapsedSamplingTime_ / samplingPeriod_) * samplingPeriod_;
	}
}