/*
  ==============================================================================

    SineOscillator.h
    Created: 27 Oct 2018 12:09:09am
    Author:  tonari
	Reference source: http://aogiri-m2d.hatenablog.com/entry/2017/06/07/232240

  ==============================================================================
*/

#pragma once
//円周率とかを使うため
#include "JuceHeader.h"

class SineOscillator
{
private:
	bool midiInput_ = false;			//Oscの状態がMidOnかOffかどうか
	double elapsedSamplingTime_ = 0;	//波形生成を開始してからの経過サンプル時間
	double frequency_ = 440;			//周波数(A)
	double samplingPeriod_ = 100;		//周期(サンプル時間)
public:
	//midiOn入力があったときの処理
	void midiOn(int midiNoteNumber, double hostSampleRate);	
	//midiOffがあったときの処理
	void midiOff();			
	//現在のサンプル時間のSine波を取得
	double get();			
	//1サンプル進める
	void phaseIncrement();	
};