#pragma once

#include "../SaddleApi.h"
#include "../Windows/Window.h"

namespace Saddle {

    class Window;
    class SDL_API Time {
    public:

        double delta, avg_delta;
        int fls, fps;

    private:

        Time() = default;

        friend class Window;

    };

}