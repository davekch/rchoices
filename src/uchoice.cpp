#include "plugin.hpp"
#include "utility.hpp"


struct Uchoice : Module {

	int current = 0;
	Chooser chooser = Chooser();
	dsp::SchmittTrigger newInputTrigger;

	enum ParamIds {
		BUTTON1_PARAM,
		BUTTON2_PARAM,
		BUTTON3_PARAM,
		BUTTON4_PARAM,
		BUTTON5_PARAM,
		BUTTON6_PARAM,
		BUTTON7_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,
		IN4_INPUT,
		IN5_INPUT,
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

	Uchoice() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(BUTTON1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BUTTON2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BUTTON3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BUTTON4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BUTTON5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BUTTON6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BUTTON7_PARAM, 0.f, 1.f, 0.f, "");
	}

	void process(const ProcessArgs& args) override {
		// collect all active inputs (for now, all of them)
		std::vector<int> active;
		for (int i=0; i<7; i++) {
			active.push_back(i);
		}
		// calculate trigger value according to https://vcvrack.com/manual/VoltageStandards#triggers-and-gates
		float trig = rescale(inputs[TRIG_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f);
		if (newInputTrigger.process(trig)) {
			// turn the current light off
			lights[current].setBrightness(0.f);
			// update the selected input source
			current = chooser.random_uniform_choice(&active);
			// turn led for new input on
			lights[current].setBrightness(1.f);
		}
		outputs[OUT_OUTPUT].setVoltage(inputs[current].getVoltage());
	}
};


struct UchoiceWidget : ModuleWidget {
	UchoiceWidget(Uchoice* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/uchoice.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.467, 19.076)), module, Uchoice::BUTTON1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.467, 31.675)), module, Uchoice::BUTTON2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.467, 44.274)), module, Uchoice::BUTTON3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.467, 56.874)), module, Uchoice::BUTTON4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.467, 69.473)), module, Uchoice::BUTTON5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.467, 82.072)), module, Uchoice::BUTTON6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.467, 94.671)), module, Uchoice::BUTTON7_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.691, 19.076)), module, Uchoice::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.691, 31.675)), module, Uchoice::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.691, 44.274)), module, Uchoice::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.691, 56.874)), module, Uchoice::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.691, 69.473)), module, Uchoice::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.691, 82.072)), module, Uchoice::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.691, 94.671)), module, Uchoice::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.691, 109.034)), module, Uchoice::TRIG_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(31.447, 109.235)), module, Uchoice::OUT_OUTPUT));

		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 19.12)), module, Uchoice::LED1_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 31.715)), module, Uchoice::LED2_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 44.31)), module, Uchoice::LED3_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 56.905)), module, Uchoice::LED4_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 69.5)), module, Uchoice::LED5_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 82.095)), module, Uchoice::LED6_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.312, 94.69)), module, Uchoice::LED7_LIGHT));
	}
};


Model* modelUchoice = createModel<Uchoice, UchoiceWidget>("uchoice");
