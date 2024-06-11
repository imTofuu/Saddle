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

        void end();

    private:



    };

}