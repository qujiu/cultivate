#include "UIManager.h"
#include "Form.h"

SINGLETON_DEFINE_INST(UIManager, Ref);

UIManager::UIManager(){
	for (auto & e : m_FormArr)
	{
		e = nullptr;
	}
}

UIManager::~UIManager(){

}

Form* UIManager::createForm(WINDOW_ID id, Form * form){
	if (id == IDC_NULL) return nullptr;

	m_FormArr[id] = form;

	return m_FormArr[id];
}

Form* UIManager::findForm(WINDOW_ID id){
	if (id == IDC_NULL) return nullptr;

	return m_FormArr[id];
}

void UIManager::releaseForm(WINDOW_ID id){
	if (id == IDC_NULL) return;

	m_FormArr[id] = nullptr;
}