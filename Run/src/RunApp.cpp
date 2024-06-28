#include <Saddle.h>

#include <Saddle/Logging/Logger.h>

#include <Saddle/Layers/CoreGuiItem.h>
#include <Saddle/Layers/LayerManager.h>

#include "EditorLayer.h"

void Saddle::Start() {

	LayerManager::addLayer<EditorLayer>(0, 0);
	
}

void Saddle::Update() {

}