#pragma once

#include "../SaddleApi.h"

#include <string>

namespace Saddle {

    class SDL_API CoreGuiItem {
    public:

        CoreGuiItem(const char* name);
        ~CoreGuiItem();


        void text(const char* text);
        void text(const std::string& text);

        bool button(const char* text);
        bool button(const std::string& text);

        void slider(const char* text, float* location, float min, float max);
        void slider(const std::string& text, float* location, float min, float max);
        void slider(const char* text, int* location, int min, int max);
        void slider(const std::string& text, int* location, int min, int max);

        void end();

    private:



    };

}