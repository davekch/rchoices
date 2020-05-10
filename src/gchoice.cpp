#include "plugin.hpp"


struct Gchoice : Module {
	enum ParamIds {
		MEAN_ATT_PARAM,
		MEAN_PARAM,
		SPREAD_PARAM,
		SPREAD_ATT_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		IN2_INPUT,
		MEAN_CV_INPUT,
		IN3_INPUT,
		IN4_INPUT,
		IN5_INPUT,
		SPREAD_CV_INPUT,
		IN6_INPUT,
		IN7_INPUT,
		TRIG_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		LED1_LIGHT,
		LED2_LIGHT,
		LED3_LIGHT,
		LED4_LIGHT,
		LED5_LIGHT,
		LED6_LIGHT,
		LED7_LIGHT,
		NUM_LIGHTS
	};

	Gchoice() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(MEAN_ATT_PARAM, 0.f, 1.f, 0.f, "");
		configParam(MEAN_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SPREAD_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SPREAD_ATT_PARAM, 0.f, 1.f, 0.f, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct GchoiceWidget : ModuleWidget {
	GchoiceWidget(Gchoice* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/gchoice.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(43.03, 22.211)), module, Gchoice::MEAN_ATT_PARAM));
		addParam(createParam<RoundBlackKnob>(mm2px(Vec(26.615, 15.296)), module, Gchoice::MEAN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.03, 58.208)), module, Gchoice::SPREAD_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(43.03, 70.665)), module, Gchoice::SPREAD_ATT_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 19.076)), module, Gchoice::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 31.675)), module, Gchoice::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(43.03, 32.418)), module, Gchoice::MEAN_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 44.274)), module, Gchoice::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 56.874)), module, Gchoice::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 69.473)), module, Gchoice::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(43.03, 80.872)), module, Gchoice::SPREAD_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 82.072)), module, Gchoice::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 94.671)), module, Gchoice::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.76, 109.034)), module, Gchoice::TRIG_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(43.03, 109.034)), module, Gchoice::OUT_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.312, 19.12)), module, Gchoice::LED1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.312, 31.715)), module, Gchoice::LED2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.312, 44.31)), module, Gchoice::LED3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.312, 56.905)), module, Gchoice::LED4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.312, 69.5)), module, Gchoice::LED5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.312, 82.095)), module, Gchoice::LED6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.312, 94.69)), module, Gchoice::LED7_LIGHT));
	}
};


Model* modelGchoice = createModel<Gchoice, GchoiceWidget>("gchoice");
