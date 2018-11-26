#include "state.hpp"

State::State() {
}

State::~State() {
}

void State::initialize(BatchHandler* bh, EntityHandler* eh) {
	_bh = bh;
	_eh = eh;
}

void State::update(double dt) {

}

void State::destroy() {

}
