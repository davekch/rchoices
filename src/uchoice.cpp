#include "plugin.hpp"


struct Uchoice : Module {

	enum ParamIds {
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
		NUM_LIGHTS
	};

	Uchoice() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
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

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.3, 21.624)), module, Uchoice::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.206, 33.481)), module, Uchoice::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.276, 46.675)), module, Uchoice::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.276, 59.897)), module, Uchoice::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.276, 73.504)), module, Uchoice::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.276, 87.301)), module, Uchoice::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.276, 100.813)), module, Uchoice::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.371, 115.554)), module, Uchoice::TRIG_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.894, 115.516)), module, Uchoice::OUT_OUTPUT));
	}
};


Model* modelUchoice = createModel<Uchoice, UchoiceWidget>("uchoice");
