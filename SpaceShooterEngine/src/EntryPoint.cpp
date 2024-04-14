#include "EntryPoint.h"
#include "framework/Application.h"

int main() {
	ss::Application* app = GetApplication();
	app->Run();
	delete app;
}