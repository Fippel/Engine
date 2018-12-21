#include "menustate.hpp"
#include "textcomponent.hpp"
#include "EntityHandler.hpp"

MenuState::MenuState() {
	this->type = MENU_STATE;
}

MenuState::~MenuState() {
}

void MenuState::initialize() {
	Entity* ent = new Entity("Menu");
	ent->addComponent(new TextComponent());
	EntityHandler::getInstance()->add(ent);
}

void MenuState::update(double dt) {
}

void MenuState::destroy() {
	EntityHandler::getInstance()->clean();
}
