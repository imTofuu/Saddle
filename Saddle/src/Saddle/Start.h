#pragma once

extern void Saddle::Start();
extern void Saddle::Update();

int main(int argc, char** argv) {
	Saddle::Application app;
	app.Run(Saddle::Start);
}