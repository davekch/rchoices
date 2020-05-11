#include "plugin.hpp"
#include "utility.hpp"

const int NUM_SOURCES = 7;

struct Gchoice : Module {
	enum ParamIds {
		MEAN_ATT_PARAM,
		MEAN_PARAM,
		SPREAD_PARAM,
		SPREAD_ATT_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		ENUMS(SOURCE_INPUTS, NUM_SOURCES),
		MEAN_CV_INPUT,
		SPREAD_CV_INPUT,
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

	int current = 3;
	Chooser chooser = Chooser();
	dsp::SchmittTrigger newInputTrigger;

	Gchoice() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(MEAN_PARAM, 0.f, 6.f, 3.f, "");
		configParam(MEAN_ATT_PARAM, 0.f, 0.6, 0.f, "");
		configParam(SPREAD_PARAM, 0.5, 3.5, 2.f, "");
		configParam(SPREAD_ATT_PARAM, 0.f, 0.35, 0.f, "");
	}

	void process(const ProcessArgs& args) override {
		// calculate mean and spread from knobs + attenuator * cv
		float mean = params[MEAN_PARAM].getValue() + params[MEAN_ATT_PARAM].getValue() * inputs[MEAN_CV_INPUT].getVoltage();
		float spread = params[SPREAD_PARAM].getValue() + params[SPREAD_ATT_PARAM].getValue() * inputs[SPREAD_CV_INPUT].getVoltage();
		// make sure that mean and spread are not smaller / larger than their min/max values
		mean = std::max(std::min(mean, 6.f), 0.f);
		spread = std::max(std::min(spread, 3.5f), 0.5f);
		for (int i=0; i<NUM_LIGHTS; i++) {
			lights[i].value = gauss(float(i), mean, spread);
		}
		// select a new source on trigger
		float trig = rescale(inputs[TRIG_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f);
		if (newInputTrigger.process(trig)) {
			int choice = chooser.random_gaussian(mean, spread);
			if (!(choice < 0 || choice >= NUM_SOURCES)) {
				current = SOURCE_INPUTS + choice;
			}
		}
		// light up the corresponding LED
		lights[current].value = 1.f;
		// route input to output
		outputs[OUT_OUTPUT].setVoltage(inputs[current].getVoltage());
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
		addParam(createParam<LargeSlider>(mm2px(Vec(26.615, 15.296)), module, Gchoice::MEAN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.03, 58.208)), module, Gchoice::SPREAD_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(43.03, 70.665)), module, Gchoice::SPREAD_ATT_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 19.076)), module, Gchoice::SOURCE_INPUTS + 6));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 31.675)), module, Gchoice::SOURCE_INPUTS + 5));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 44.274)), module, Gchoice::SOURCE_INPUTS + 4));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 56.874)), module, Gchoice::SOURCE_INPUTS + 3));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 69.473)), module, Gchoice::SOURCE_INPUTS + 2));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 82.072)), module, Gchoice::SOURCE_INPUTS + 1));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.749, 94.671)), module, Gchoice::SOURCE_INPUTS + 0));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(43.03, 32.418)), module, Gchoice::MEAN_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(43.03, 80.872)), module, Gchoice::SPREAD_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.76, 109.034)), module, Gchoice::TRIG_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(43.03, 109.034)), module, Gchoice::OUT_OUTPUT));

		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 19.12)), module, Gchoice::LED7_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 31.715)), module, Gchoice::LED6_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 44.31)), module, Gchoice::LED5_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 56.905)), module, Gchoice::LED4_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 69.5)), module, Gchoice::LED3_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 82.095)), module, Gchoice::LED2_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 94.69)), module, Gchoice::LED1_LIGHT));
	}
};


Model* modelGchoice = createModel<Gchoice, GchoiceWidget>("gchoice");
