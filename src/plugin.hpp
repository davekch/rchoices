#pragma once
#include <rack.hpp>


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelUchoice;
extern Model* modelGchoice;

struct LargeSlider : SvgSlider {
	LargeSlider() {
		maxHandlePos = app::mm2px(Vec(-2.457, 0.738));
		minHandlePos = app::mm2px(Vec(-2.457, 79.40));
		this->setBackgroundSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sliderbackground.svg")));
        this->setHandleSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sliderhandle.svg")));
	}
};
