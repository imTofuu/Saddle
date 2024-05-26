#pragma once

extern void Saddle::Start();

int main(int argc, char** argv) {
	Saddle::Application app;
	app.Run(Saddle::Start);
}